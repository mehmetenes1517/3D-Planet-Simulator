#pragma once

#include"../base/Game/GameObject.hpp"
#include"../base/Game/ResourceManager.hpp"
#include<cstdlib>

class Planet:public GameObject{

    private:


    public:

        glm::vec3 direction={0.0f,1.0f,0.0f};
        float speed=4.0f;


        Planet(Texture& tex, const glm::vec3& pos={0.0f,0.0f,0.0f},const glm::vec3& rot={0.0f,0.0f,0.0f},const glm::vec3& scale={1.0f,1.0f,1.0f}):
        GameObject::GameObject(&ResourceManager::GetInstance()->GetMesh("sphere1"),&ResourceManager::GetInstance()->GetShader("default"),&ResourceManager::GetInstance()->GetTexture("jupyter_tex"),pos,rot,scale){}

        virtual void Start() override{
            GameObject::Start();
        }
        virtual void Update(Camera& cam,float delta) override{
            GameObject::Update(cam,delta);


            Rotation() += speed*delta*direction;

        }


};


