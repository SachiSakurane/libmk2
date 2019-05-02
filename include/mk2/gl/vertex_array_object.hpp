//
// Created by Himatya on 2018/02/07.
//

#ifndef LIBMK2_GL_VERTEX_ARRAY_OBJECT_HPP
#define LIBMK2_GL_VERTEX_ARRAY_OBJECT_HPP

#include <vector>

#include <mk2/gl/gl_include.hpp>
#include <mk2/gl/config.hpp>
#include <mk2/gl/gl_type.hpp>
#include <mk2/debug/debug_log.hpp>

namespace mk2{
namespace gl{
    
#if defined(MK2_GL_ENABLE)
    struct attrib_status{
        attrib_status(GLuint index, GLuint size, GLenum type, GLboolean normalized) : index_(index), type_(type), size_(size), normalized_(normalized){}
        const GLuint index_;
        const GLenum type_;
        const GLuint size_;
        const GLboolean normalized_;
    };
    
    class vertex_array_object{
    public:
        vertex_array_object() : vao_(0), vbo_(0), vertex_num_(0){
        }
        
        ~vertex_array_object(){
            glDeleteVertexArrays(1, &vao_);
            glDeleteBuffers(1, &vbo_);
        }
        
        void bind_attrib(const std::vector<attrib_status> &pointer, GLsizeiptr bufsize, const GLvoid *data){
            GLsizei stride = 0;
            for(auto it : pointer)stride += it.size_ * get_type_size(it.type_);
            
            if(!stride){
                MK2_DEBUG_STDERR("stride is zero");
                return;
            }
            
            glGenVertexArrays(1, &vao_);
            glBindVertexArray(vao_);
            
            glGenBuffers(1, &vbo_);
            glBindBuffer(GL_ARRAY_BUFFER, vbo_);
            glBufferData(GL_ARRAY_BUFFER, bufsize, data, GL_STATIC_DRAW);
            
            GLsizei size = 0;
            for(auto it : pointer){
                glEnableVertexAttribArray(it.index_);
                glVertexAttribPointer(it.index_, it.size_, it.type_, it.normalized_, stride, (char*)NULL + (size));
                
                size += it.size_ * get_type_size(it.type_);
            }
            
            glBindVertexArray(0);
            
            vertex_num_ = static_cast<GLsizei>(bufsize) / stride;
        }
        
        void bind(){
            glBindVertexArray(vao_);
        }
        
        void draw(GLenum drawmode){
            glDrawArrays(drawmode, 0, vertex_num_);
        }
        
    private:
        GLuint vao_;
        GLuint vbo_;
        
        GLsizei vertex_num_;
        
        vertex_array_object(const vertex_array_object &)            = delete;
        vertex_array_object &operator=(const vertex_array_object &) = delete;
        vertex_array_object(vertex_array_object &&)                 = delete;
        vertex_array_object &operator=(vertex_array_object &&)      = delete;
    };
    
#endif
}
}

#endif /* vertex_array_object_h */
