//
// Created by Himatya on 2018/02/07.
//

#ifndef LIBMK2_GL_SHADER_PROGRAM_HPP
#define LIBMK2_GL_SHADER_PROGRAM_HPP

#include <cstdlib>
#include <string>
#include <array>
#include <type_traits>

#include <mk2/gl/gl_include.hpp>
#include <mk2/gl/config.hpp>
#include <mk2/debug/debug_log.hpp>

namespace mk2{
namespace gl{
    
#if defined(MK2_GL_ENABLE)
    enum class DefaultUniformEnum{
        kSize,
    };
    
    template<
        typename UniformEnum = DefaultUniformEnum,
        typename = typename std::enable_if<std::is_enum<UniformEnum>::value>::type
    >
    class shader_program{
    public:
        shader_program(GLenum shader_type) :
        shader_type_(shader_type),
        is_available_(false),
        program_(0),
        uniform_keys_(){
        }
        
        bool create_shader_program(const std::array<std::string, static_cast<std::size_t>(UniformEnum::kSize)> &uniform_key_strings, const GLchar *source){
            const GLuint shader = glCreateShader(shader_type_);
            
            if(shader){
                glShaderSource(shader, 1, &source, NULL);
                glCompileShader(shader);
#if defined(MK2_DEBUG)
                GLint logLength;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
                if (logLength > 0) {
                    GLchar *log = (GLchar *)malloc(logLength);
                    glGetShaderInfoLog(shader, logLength, &logLength, log);
                    MK2_DEBUG_STDOUT(log);
                    free(log);
                }
#endif
                //const GLuint program = glCreateProgram();
                program_ = glCreateProgram();
                if(program_){
                    GLint compiled = GL_FALSE;
                    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
                    glProgramParameteri(program_, GL_PROGRAM_SEPARABLE, GL_TRUE);
                    if (compiled) {
                        glAttachShader(program_, shader);
                        glLinkProgram(program_);
                        glDetachShader(program_, shader);
#if defined(MK2_DEBUG)
                        GLint logLength;
                        glGetProgramiv(program_, GL_INFO_LOG_LENGTH, &logLength);
                        if (logLength > 0) {
                            GLchar *log = (GLchar *)malloc(logLength);
                            glGetProgramInfoLog(program_, logLength, &logLength, log);
                            MK2_DEBUG_STDOUT(log);
                            free(log);
                        }
#endif
                        GLint linked = GL_FALSE;
                        glGetProgramiv(program_, GL_LINK_STATUS, &linked);
                        if(linked){
                            uniform_keys_ = std::move(set_uniform(uniform_key_strings));
                            is_available_ = true;
                            return true;
                        }
                        else{
                            glDeleteProgram(program_);
                        }
                    }
                }
                glDeleteShader(shader);
            }
            else{
                glDeleteShader(shader);
            }
            return false;
        }
        
        virtual ~shader_program(){
            glDeleteProgram(program_);
        }
        
        const bool is_available() const {return is_available_;}
        const GLenum get_shader_type() const {return shader_type_;}
        const GLuint get_program() const {return program_;}
        const GLint get_uniform(UniformEnum key) const{
            return uniform_keys_[static_cast<std::size_t>(key)];
        }
        
        template<class T, bool = std::is_same<T, UniformEnum>::value>
        struct is_uniform_enum{};
        
        template<class T>
        struct is_uniform_enum<T, true> : public std::true_type{};
        
        template<class T>
        struct is_uniform_enum<T, false> : public std::false_type{};

        #define UNIFORM_TEMPLATE template<class T, typename = typename std::enable_if<is_uniform_enum<T>::value>::type>
        
        #ifdef GL_VERSION_4_0
                
            #define UNIFORM(prefix, type)                                                                                                                                       \
            UNIFORM_TEMPLATE void uniform1##prefix(T key, type v0){                                     glUniform1##prefix(get_uniform(key), v0);}                              \
            UNIFORM_TEMPLATE void uniform2##prefix(T key, type v0, type v1){                            glUniform2##prefix(get_uniform(key), v0, v1);}                          \
            UNIFORM_TEMPLATE void uniform3##prefix(T key, type v0, type v1, type v2){                   glUniform3##prefix(get_uniform(key), v0, v1, v2);}                      \
            UNIFORM_TEMPLATE void uniform4##prefix(T key, type v0, type v1, type v2, type v3){          glUniform4##prefix(get_uniform(key), v0, v1, v2, v3);}                  \
            UNIFORM_TEMPLATE void uniform1##prefix##v(T key, GLsizei count, const type *value){         glUniform1##prefix##v(get_uniform(key), count, value);}                 \
            UNIFORM_TEMPLATE void uniform2##prefix##v(T key, GLsizei count, const type *value){         glUniform2##prefix##v(get_uniform(key), count, value);}                 \
            UNIFORM_TEMPLATE void uniform3##prefix##v(T key, GLsizei count, const type *value){         glUniform3##prefix##v(get_uniform(key), count, value);}                 \
            UNIFORM_TEMPLATE void uniform4##prefix##v(T key, GLsizei count, const type *value){         glUniform4##prefix##v(get_uniform(key), count, value);}                 \
            UNIFORM_TEMPLATE void program_uniform1##prefix(T key, type v0){                             glProgramUniform1##prefix(program_, get_uniform(key), v0);}             \
            UNIFORM_TEMPLATE void program_uniform2##prefix(T key, type v0, type v1){                    glProgramUniform2##prefix(program_, get_uniform(key), v0, v1);}         \
            UNIFORM_TEMPLATE void program_uniform3##prefix(T key, type v0, type v1, type v2){           glProgramUniform3##prefix(program_, get_uniform(key), v0, v1, v2);}     \
            UNIFORM_TEMPLATE void program_uniform4##prefix(T key, type v0, type v1, type v2, type v3){  glProgramUniform4##prefix(program_, get_uniform(key), v0, v1, v2, v3);} \
            UNIFORM_TEMPLATE void program_uniform1##prefix##v(T key, GLsizei count, const type *value){ glProgramUniform1##prefix##v(program_, get_uniform(key), count, value);}\
            UNIFORM_TEMPLATE void program_uniform2##prefix##v(T key, GLsizei count, const type *value){ glProgramUniform2##prefix##v(program_, get_uniform(key), count, value);}\
            UNIFORM_TEMPLATE void program_uniform3##prefix##v(T key, GLsizei count, const type *value){ glProgramUniform3##prefix##v(program_, get_uniform(key), count, value);}\
            UNIFORM_TEMPLATE void program_uniform4##prefix##v(T key, GLsizei count, const type *value){ glProgramUniform4##prefix##v(program_, get_uniform(key), count, value);}\

            #define UNIFORM_MATRIX(prefix)                                                                                                                                                                                  \
            UNIFORM_TEMPLATE void matrix##prefix##fv(T key, GLsizei count, GLboolean transpose, const GLfloat *value){          glUniformMatrix##prefix##fv(get_uniform(key), count, transpose, value);};                   \
            UNIFORM_TEMPLATE void matrix##prefix##dv(T key, GLsizei count, GLboolean transpose, const GLdouble *value){         glUniformMatrix##prefix##dv(get_uniform(key), count, transpose, value);};                   \
            UNIFORM_TEMPLATE void program_matrix##prefix##fv(T key, GLsizei count, GLboolean transpose, const GLfloat *value){  glProgramUniformMatrix##prefix##fv(program_, get_uniform(key), count, transpose, value);};  \
            UNIFORM_TEMPLATE void program_matrix##prefix##dv(T key, GLsizei count, GLboolean transpose, const GLdouble *value){ glProgramUniformMatrix##prefix##dv(program_, get_uniform(key), count, transpose, value);};  \
        
        #endif
        
        UNIFORM(i, GLint)
        UNIFORM(f, GLfloat)
        UNIFORM(d, GLdouble)
        UNIFORM(ui, GLuint)
        
        UNIFORM_MATRIX(2)
        UNIFORM_MATRIX(3)
        UNIFORM_MATRIX(4)
        UNIFORM_MATRIX(2x3)
        UNIFORM_MATRIX(2x4)
        UNIFORM_MATRIX(3x2)
        UNIFORM_MATRIX(3x4)
        UNIFORM_MATRIX(4x3)
        
        #undef UNIFORM
        #undef UNIFORM_MATRIX
        #undef UNIFORM_TEMPLATE
        
        typedef UniformEnum uniform_type;
        
    private:
        const GLenum    shader_type_;
        bool            is_available_;
        GLuint          program_;
        std::array<GLuint, static_cast<std::size_t>(UniformEnum::kSize)> uniform_keys_;
        
        std::array<GLuint, static_cast<std::size_t>(UniformEnum::kSize)> &&set_uniform(const std::array<std::string, static_cast<std::size_t>(UniformEnum::kSize)> &strings){
            std::array<GLuint, static_cast<std::size_t>(UniformEnum::kSize)> keys;
            for(auto it = strings.begin(); it != strings.end(); ++it){
                keys[std::distance(strings.begin(), it)] = glGetUniformLocation(program_, (*it).c_str());
            }
            return std::move(keys);
        }
        
        shader_program(const shader_program &)              = delete;
        shader_program &operator=(const shader_program &)   = delete;
        shader_program(shader_program &&)                   = delete;
        shader_program &operator=(shader_program &&)        = delete;
    };
    
    //vertexのin(旧attribute)は、location確認すればできるでは
    template<
        typename UniformEnum = DefaultUniformEnum,
        typename = typename std::enable_if<std::is_enum<UniformEnum>::value>::type
    >
    class vertex_shader_program : public shader_program<UniformEnum>{
    public:
        vertex_shader_program() : shader_program<UniformEnum>(GL_VERTEX_SHADER){}
    };
    
    template<
        typename UniformEnum = DefaultUniformEnum,
        typename = typename std::enable_if<std::is_enum<UniformEnum>::value>::type
    >
    class fragment_shader_program : public shader_program<UniformEnum>{
    public:
        fragment_shader_program() : shader_program<UniformEnum>(GL_FRAGMENT_SHADER){}
    };
    
#endif
}
}

#endif /* shader_program_hpp */
