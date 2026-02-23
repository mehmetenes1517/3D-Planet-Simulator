#pragma once

#include<iostream>
#include<fstream>
#include<vector>
#include"VAO.hpp"
#include"glad.h"
#include<glm/glm.hpp>


class InstancedVAO:public VAO{

    protected: 
        unsigned int vao,vbo,instance_bo,ibo,indices_size;

    public:

        InstancedVAO(){}
        InstancedVAO(const std::vector<Vertex>& vertices,std::vector<unsigned int> indices){Load(vertices,indices);}

        virtual void Load(const std::vector<Vertex>& vertices,std::vector<unsigned int> indices) override{
            indices_size=indices.size();

            glGenVertexArrays(1,&vao);
            glGenBuffers(1,&vbo);
            glGenBuffers(1,&ibo);

            glBindVertexArray(vao);
            
            glBindBuffer(GL_ARRAY_BUFFER,vbo);
            glBufferData(GL_ARRAY_BUFFER,sizeof(Vertex)* vertices.size(),vertices.data(),GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)0);

            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)(sizeof(float)*3));

            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)(sizeof(float)*6));

            glGenBuffers(1,&instance_bo);
            glBindBuffer(GL_ARRAY_BUFFER,instance_bo);
            glBufferData(GL_ARRAY_BUFFER,2000*sizeof(glm::mat4),nullptr,GL_DYNAMIC_DRAW);

            glEnableVertexAttribArray(3);
            glVertexAttribPointer(3,3,GL_FLOAT,GL_FALSE,sizeof(glm::vec3),(void*)(0));
            glVertexAttribDivisor(3,1);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*indices.size(),indices.data(),GL_STATIC_DRAW);
            
            
            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER,vbo);
            glBindBuffer(GL_ARRAY_BUFFER,instance_bo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo);
        }
        virtual void LateLoad(const std::vector<glm::vec3>& models) override{
            glBindBuffer(GL_ARRAY_BUFFER,instance_bo);
            glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(glm::vec3)*models.size(),models.data());
            glBindBuffer(GL_ARRAY_BUFFER,0);
        }
        virtual void Draw(unsigned int count) override{
            glBindVertexArray(vao);
            glDrawElementsInstanced(GL_TRIANGLES,indices_size,GL_UNSIGNED_INT,0,count);
            glBindVertexArray(0);

        }
    
     
};

