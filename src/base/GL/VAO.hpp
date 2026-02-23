#pragma once

#include<iostream>
#include<fstream>
#include<vector>
#include"glad.h"


struct Vertex{
    float x,y,z;
    float r,g,b;
    float u,v;
};

class VAO{

    protected: 
        unsigned int vao,vbo,ibo,indices_size;

    public:

        VAO(){}
        VAO(const std::vector<Vertex>& vertices,std::vector<unsigned int> indices){Load(vertices,indices);}

        virtual void Load(const std::vector<Vertex>& vertices,std::vector<unsigned int> indices){
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

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*indices.size(),indices.data(),GL_STATIC_DRAW);
            
            
            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER,vbo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo);
        }
        virtual void LateLoad(const std::vector<glm::vec3>& models){
            throw std::logic_error("\nLate load dont exist in Regular VAO class");
        }
        //@brief if youre not using instanced rendering , just give count 0
        virtual void Draw(unsigned int count) {
            glBindVertexArray(vao);
            glDrawElements(GL_TRIANGLES,indices_size,GL_UNSIGNED_INT,0);
            glBindVertexArray(0);

        }
    
     
};

