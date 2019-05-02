//
// Created by Himatya on 2018/02/07.
//

#ifndef LIBMK2_GL_PIPELINE_HPP
#define LIBMK2_GL_PIPELINE_HPP

#include <vector>

#include <mk2/gl/gl_include.hpp>
#include <mk2/gl/config.hpp>
#include <mk2/gl/shader_program.hpp>
#include <mk2/debug/debug_log.hpp>

namespace mk2{
namespace gl{
    
#if defined(MK2_GL_ENABLE)
    
    class pipeline{
    public:
        pipeline() : pipeline_(0){}
        
        ~pipeline(){
            glDeleteProgramPipelines(1, &pipeline_);
        }
        
        void create(){
            create_pipeline();
        }
        
        template<class Program>
        const bool attach_shader(const Program &program){
            const GLbitfield shader_type = shadertype_to_bit(program.get_shader_type());
            if(shader_type != GL_INVALID_VALUE){
                programs_.emplace_back(shader_type, program.get_program());
            }
            return true;
        }
        
        void use_programs(){
            for(auto it = programs_.cbegin(); it != programs_.cend(); ){
                glUseProgramStages(pipeline_, (*it).first, (*it).second);
                ++it;
            }
        }
        
        void bind(){
            glBindProgramPipeline(pipeline_);
        }
        
    private:
        GLuint  pipeline_;
        std::vector<std::pair<GLbitfield, GLuint>> programs_;
        
        const void create_pipeline(){
            glGenProgramPipelines(1, &pipeline_);
            glBindProgramPipeline(pipeline_);
            
#ifdef MK2_DEBUG
            GLint logLength;
            glGetProgramPipelineiv(pipeline_, GL_INFO_LOG_LENGTH, &logLength);
            if (logLength > 0) {
                GLchar *log = (GLchar *)malloc(logLength);
                glGetProgramPipelineInfoLog(pipeline_, logLength, &logLength, log);
                MK2_DEBUG_STDOUT(log);
                free(log);
            }
#endif
            return;
        }
        
        const GLbitfield shadertype_to_bit(const GLenum shader_type){
            switch(shader_type){
                case GL_VERTEX_SHADER:          return GL_VERTEX_SHADER_BIT;
                case GL_TESS_CONTROL_SHADER:    return GL_TESS_CONTROL_SHADER_BIT;
                case GL_TESS_EVALUATION_SHADER: return GL_TESS_EVALUATION_SHADER_BIT;
                case GL_GEOMETRY_SHADER:        return GL_GEOMETRY_SHADER_BIT;
                case GL_FRAGMENT_SHADER:        return GL_FRAGMENT_SHADER_BIT;
#ifdef GL_VERSION_4_3
                case GL_COMPUTE_SHADER:         return GL_COMPUTE_SHADER_BIT;
#endif
            }
            return GL_INVALID_VALUE;
        }
    };
 
#endif
}
}

#endif /* pipeline_h */
