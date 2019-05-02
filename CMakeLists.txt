cmake_minimum_required(VERSION 3.9)
project(libmk2)

set(CMAKE_CXX_STANDARD 20)
set(LIBMK2_LIB_PATH include)

add_executable(test test/main.cpp)
add_executable(make_include utility/make_include.cpp)

target_include_directories(
        test PRIVATE
        /opt/intel/ipp/include
        /usr/local/opt/boost/include
        ${LIBMK2_LIB_PATH})

target_link_libraries(
        test PRIVATE
        /opt/intel/ipp/lib/libipp_iw.a
        /opt/intel/ipp/lib/libipps.a
        /opt/intel/ipp/lib/libippcore.a
        /opt/intel/ipp/lib/libippvm.a
        /usr/local/opt/boost/lib/libboost_program_options.a
        /usr/local/opt/boost/lib/libboost_filesystem.a
        /usr/local/opt/boost/lib/libboost_system.a)

target_link_libraries(
        make_include PRIVATE
        /usr/local/opt/llvm/lib/libc++fs.a)
