#pragma once

#include<iostream>
#include<fstream>
#include"glad.h"


#include<stb/stb_image.h>

class Texture{
        unsigned int texture;


    public:
        Texture(){}
        Texture(const std::string& file){
            Load(file);
        }
        void Load(const std::string& file){
            glGenTextures(1,&texture);
            glBindTexture(GL_TEXTURE_2D,texture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            int width,height,channels;
            unsigned char* data=stbi_load(file.c_str(),&width,&height,&channels,4);

            if(data){
                GLenum format = GL_RGB;
                if (channels == 1) format = GL_RED;
                else if (channels == 3) format = GL_RGB;
                else if (channels == 4) format = GL_RGBA;
                glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
                glGenerateMipmap(GL_TEXTURE_2D);
                stbi_image_free(data);
                glBindTexture(GL_TEXTURE_2D,0);

            }else{
                throw std::runtime_error("Cannot read texture data!");
            }

        }

        void Bind(){
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D,texture);
        }

        ~Texture(){
            glDeleteTextures(1,&texture);
        }

};