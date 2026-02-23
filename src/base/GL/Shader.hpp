#pragma once

#include<iostream>
#include<map>
#include<fstream>
#include<sstream>
#include<array>
#include"glad.h"
#include<glm/glm.hpp>

inline std::string LoadStringFromFile(const std::string& file){

    std::string content;

    {
        std::stringstream stream;
        std::ifstream f(file);
        if(!f.is_open())
            throw std::runtime_error("Cant find "+file);
        stream<<f.rdbuf();
        content=stream.str();
    }
    return content;
}
class Shader{
    private:
        unsigned int program;
        std::map<std::string,unsigned int> uniform_vars;
    public:
        Shader(){}
        Shader(const std::string& vshader,const std::string& fshader){
            Load(vshader,fshader);
        }
        void Load(const std::string& vs,const std::string& fs){

            std::string v_shader=LoadStringFromFile(vs);
            std::string f_shader=LoadStringFromFile(fs);

            unsigned int vshader,fshader;

            program=glCreateProgram();

            const char* vs_source=v_shader.c_str();
            vshader=glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vshader,1,&vs_source,0);
            glCompileShader(vshader);

            int status;
            glGetShaderiv(vshader,GL_COMPILE_STATUS,&status);
            if(!status){
                std::array<char,4096> err;
                glGetShaderInfoLog(vshader,err.size(),0,err.data());
                std::cout<<"Vertex Shader Error : "<<err.data();
            }

            const char* fs_source=f_shader.c_str();
            fshader=glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fshader,1,&fs_source,0);
            glCompileShader(fshader);

            int status1;
            glGetShaderiv(fshader,GL_COMPILE_STATUS,&status1);
            if(!status1){
                std::array<char,4096> err;
                glGetShaderInfoLog(fshader,err.size(),0,err.data());
                std::cout<<"Fragment Shader Error : "<<err.data();
            }

            glAttachShader(program,vshader);
            glAttachShader(program,fshader);
            glLinkProgram(program);
            
            glDeleteShader(vshader);
            glDeleteShader(fshader);
        }

        void Bind(){
            glUseProgram(program);
        }
        void UniformSet(const std::string& name,const glm::mat4& mvp){
            if(uniform_vars.find(name.c_str())==uniform_vars.end()){
                uniform_vars[name.c_str()]=glGetUniformLocation(program,name.c_str());
            }
            glUniformMatrix4fv(uniform_vars[name.c_str()],1,GL_FALSE,(const float*)&mvp);
        }
        void UniformSet(const std::string& name,float var){
            if(uniform_vars.find(name.c_str())==uniform_vars.end()){
                uniform_vars[name.c_str()]=glGetUniformLocation(program,name.c_str());
            }
            glUniform1f(uniform_vars[name.c_str()],var);
        }
        void UniformSet(const std::string& name, int value) {
            if(uniform_vars.find(name) == uniform_vars.end()){
                uniform_vars[name] = glGetUniformLocation(program, name.c_str());
            }
            glUniform1i(uniform_vars[name], value);
        }

};