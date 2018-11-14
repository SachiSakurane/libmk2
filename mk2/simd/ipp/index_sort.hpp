//
// Created by Himatya on 2018/09/11.
//

#pragma once

#include <memory>

#include <mk2/container/fixed_array.hpp>
#include <mk2/simd/ipp/function/arithmetic.hpp>
#include <mk2/simd/ipp/function/conversion.hpp>
#include <mk2/simd/ipp/function/fixed_accuracy_arithmetic.hpp>

namespace mk2 { namespace simd { namespace ipp {

    enum class interpolation_algorithm
    {
        kOff,
        kRound,
        kLinear,
    };

    namespace detail
    {
        // 0 <= src2[n] < (float)n
        // src1[src2[i]]  i: 0 <= i < len
        template<class FloatType>
        class interpolation
        {
        public:
            interpolation() = default;
            virtual ~interpolation() = default;

            virtual void process(const FloatType *src1, const FloatType *src2, FloatType *dst, int len) = 0;

            virtual void resize(size_t size) = 0;
            virtual size_t size() const = 0;
            virtual interpolation_algorithm algorithm() const = 0;
        };

        template<class FloatType>
        class interpolation_off : public interpolation<FloatType>
        {
        public:
            interpolation_off(size_t size) : size_(size) {}

            void process(const FloatType *src1, const FloatType *src2, FloatType *dst, int len) override {}

            void resize(size_t size) override
            {
                size_ = size;
            }

            size_t size() const override { return size_; }

            interpolation_algorithm algorithm() const override { return interpolation_algorithm::kOff; }

        private:
            size_t size_;
        };

        template<class FloatType>
        class interpolation_round : public interpolation<FloatType>
        {
        public:
            interpolation_round(size_t size) :
                size_(size),
                isize_((int)size),
                indexes_(size_)
            {}

            virtual ~interpolation_round() = default;

            void process(const FloatType *src1, const FloatType *src2, FloatType *dst, int len) override
            {
                namespace ipp = mk2::simd::ipp;
                for (int processed = 0; processed < len; processed += size_)
                {
                    auto src_ptr = src2 + processed;
                    auto dst_ptr = dst + processed;
                    auto process_size = len < isize_ ? len : isize_;

                    ipp::function::convert_f2i(src_ptr, indexes_.data(), process_size, ippRndNear);

                    for (int index = 0; index < process_size; ++index)
                    {
                        *(dst_ptr + index) = src1[indexes_[index]];
                    }
                }
            }

            void resize(size_t size) override
            {
                size_ = size;
                isize_ = (int)size;
                indexes_ = mk2::container::fixed_array<Ipp32s>(size_);
            }

            size_t size() const override { return size_; }

            interpolation_algorithm algorithm() const override { return interpolation_algorithm::kRound; }

        private:
            size_t size_;
            int isize_;
            mk2::container::fixed_array<Ipp32s> indexes_;
        };

        template<class FloatType>
        class interpolation_linear : public interpolation<FloatType>
        {
        public:
            interpolation_linear(size_t size) :
                size_(size),
                isize_((int)size),
                buffer_(size_),
                indexes1_(size_),
                indexes2_(size_),
                sample1_(size_),
                sample2_(size_)
            {}

            virtual ~interpolation_linear() = default;

            void process(const FloatType *src1, const FloatType *src2, FloatType *dst, int len) override
            {
                namespace ipp = mk2::simd::ipp;

                auto max = len - 1;

                for (int processed = 0; processed < len; processed += size_)
                {
                    auto src_ptr = src2 + processed;
                    auto dst_ptr = dst + processed;
                    auto process_size = len < isize_ ? len : isize_;

                    ipp::function::convert_f2i(src_ptr, indexes1_.data(), process_size, ippRndNear);
                    ipp::function::addc_sfs(indexes1_.data(), 1, indexes2_.data(), process_size);
                    ipp::function::threshold_gt_inplace(indexes2_.data(), process_size, max);
                    ipp::function::frac(src_ptr, buffer_.data(), process_size);

                    for (int index = 0; index < process_size; ++index)
                    {
                        sample1_[index] = src1[indexes1_[index]];
                        sample2_[index] = src1[indexes2_[index]];
                    }

                    ipp::function::mul(buffer_.data(), sample2_.data(), dst_ptr, process_size);
                    ipp::function::subc_rev_inplace(static_cast<FloatType>(1), buffer_.data(), process_size);
                    ipp::function::addprod(buffer_.data(), sample1_.data(), dst_ptr, process_size);
                }
            }

            void resize(size_t size) override
            {
                size_ = size;
                isize_ = (int)size;
                buffer_ = sample1_ = sample2_ = mk2::container::fixed_array<FloatType>(size_);
                indexes1_ = indexes2_ = mk2::container::fixed_array<Ipp32s>(size_);
            }

            size_t size() const override { return size_; }

            interpolation_algorithm algorithm() const override { return interpolation_algorithm::kLinear; }

        private:
            size_t size_;
            int isize_;
            mk2::container::fixed_array<FloatType> buffer_;
            mk2::container::fixed_array<Ipp32s> indexes1_;
            mk2::container::fixed_array<Ipp32s> indexes2_;
            mk2::container::fixed_array<FloatType> sample1_;
            mk2::container::fixed_array<FloatType> sample2_;
        };

        template<class FloatType>
        std::unique_ptr<interpolation<FloatType>> create_interpolation(
            size_t size, interpolation_algorithm type)
        {
            switch(type)
            {
                case interpolation_algorithm::kOff:
                    return std::make_unique<interpolation_off<FloatType>>(size);

                case interpolation_algorithm::kRound:
                    return std::make_unique<interpolation_round<FloatType>>(size);

                case interpolation_algorithm::kLinear:
                    return std::make_unique<interpolation_linear<FloatType>>(size);
            }
            assert(false);
        }
    }

    template <class FloatType>
    class index_sort
    {
    public:
        index_sort(size_t size, interpolation_algorithm type = interpolation_algorithm::kRound) :
            interpolation_(detail::create_interpolation<FloatType>(size, type))
        {}

        ~index_sort() {}

        void operator()(const FloatType *src, const FloatType *indexes, FloatType *dst, int len)
        {
            interpolation_->process(src, indexes, dst, len);
        }
        
        void inplace(const FloatType *indexes, FloatType *srcdst, int len)
        {
            interpolation_->process(srcdst, indexes, srcdst, len);
        }

        void resize(size_t size) { interpolation_->resize(size); }

        size_t size() const { return interpolation_->size(); }

        interpolation_algorithm algorithm() const { return interpolation_->algorithm(); }

        void change_algorithm(interpolation_algorithm type)
        {
            if (type != algorithm())
            {
                interpolation_ = detail::create_interpolation(interpolation_->size(), type);
            }
        }

    private:
        std::unique_ptr<detail::interpolation<FloatType>> interpolation_;
    };
}}}