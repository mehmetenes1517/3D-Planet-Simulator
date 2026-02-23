#pragma once

#include<iostream>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include"Camera.hpp"
#include"../GL/Shader.hpp"
#include"../GL/Texture.hpp"
#include"../GL/VAO.hpp"

class GameObject{

    public:
    
    VAO* mesh;
    Shader* shader;
    Texture* tex;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    
    public:
        glm::mat4 CalculateModel(){
            auto translate=glm::translate(glm::mat4(1),position);
            auto z=glm::rotate(glm::mat4(1),rotation.z,glm::vec3(0.0f,0.0f,1.0f));
            auto y=glm::rotate(glm::mat4(1),rotation.y,glm::vec3(0.0f,1.0f,0.0f));
            auto x=glm::rotate(glm::mat4(1),rotation.x,glm::vec3(1.0f,0.0f,0.0f));
            auto scale_=glm::scale(glm::mat4(1),scale);
            auto Model=translate*x*y*z*scale_;
            return Model;
        }
        std::string tag="default";
    
    void Position(const glm::vec3& pos){position=pos;}
    glm::vec3 Position() const{return position;}
    glm::vec3& Position() {return position;}

    void Scale(const glm::vec3& scl){scale=scl;}
    glm::vec3 Scale() const{return scale;}
    glm::vec3& Scale() {return scale;}

    void Rotation(const glm::vec3& rot){rotation=rot;}
    glm::vec3 Rotation() const{return rotation;}
    glm::vec3& Rotation() {return rotation;}


    GameObject(VAO* mesh,Shader* shader,Texture* tex,const glm::vec3& pos={0.0f,0.0f,0.0f},const glm::vec3& rot={0.0f,0.0f,0.0f},const glm::vec3& scale={1.0f,1.0f,1.0f})
    : position(pos),rotation(rot),scale(scale),mesh(mesh),shader(shader),tex(tex){
    }
    virtual void Start(){
    }
    virtual void Update(Camera& cam,float delta){
        shader->Bind();
        tex->Bind();
        shader->UniformSet("VP",cam.CalculateVP());
        shader->UniformSet("Model",CalculateModel());
        mesh->Draw(0);   
    }

};