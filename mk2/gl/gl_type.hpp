//
// Created by Himatya on 2018/02/07.
//

#ifndef LIBMK2_GL_GL_TYPE_HPP
#define LIBMK2_GL_GL_TYPE_HPP

#include <cstddef>

#include <mk2/gl/gl_include.hpp>
#include <mk2/gl/config.hpp>

namespace mk2{
namespace gl{
    
#if defined(MK2_GL_ENABLE)
    template<int TYPE>
    struct gl_type{
        typedef GLvoid type;
        //static_assert((TYPE == 0 || TYPE != 0), "this type is not gl type");
    };
    
    template<>
    struct gl_type<GL_BOOL>{
        typedef GLboolean type;
    };
    
    template<>
    struct gl_type<GL_BYTE>{
        typedef GLbyte type;
    };
    
    template<>
    struct gl_type<GL_SHORT>{
        typedef GLshort type;
    };
    
    template<>
    struct gl_type<GL_INT>{
        typedef GLint type;
    };
    
    template<>
    struct gl_type<GL_UNSIGNED_BYTE>{
        typedef GLubyte type;
    };
    
    template<>
    struct gl_type<GL_UNSIGNED_SHORT>{
        typedef GLushort type;
    };
    
    template<>
    struct gl_type<GL_UNSIGNED_INT>{
        typedef GLuint type;
    };
    
    template<>
    struct gl_type<GL_FLOAT>{
        typedef GLfloat type;
    };
    
    constexpr const std::size_t get_type_size(const GLenum type){
        switch(type){
            case GL_BOOL:           return sizeof(GLboolean);break;
            case GL_BYTE:           return sizeof(GLbyte);break;
            case GL_SHORT:          return sizeof(GLshort);break;
            case GL_INT:            return sizeof(GLint);break;
            case GL_UNSIGNED_BYTE:  return sizeof(GLubyte);break;
            case GL_UNSIGNED_SHORT: return sizeof(GLushort);break;
            case GL_UNSIGNED_INT:   return sizeof(GLuint);break;
            case GL_FLOAT:          return sizeof(GLfloat);break;
        }
        return 0;
    }
#endif
    
}
}

#endif
