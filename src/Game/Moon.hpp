#pragma once

#include"../base/Game/GameObject.hpp"
#include"../base/Game/ResourceManager.hpp"
#include"Planet.hpp"
#include<cstdlib>

class Moon:public GameObject{

    private:


    public:
        glm::vec3 direction={1.0f,0.0f,1.0f};
        float speed=4.0f;

        float orbitspeed=15.0f;
        Planet* s;
        Moon(Planet* s,const glm::vec3& pos={0.0f,0.0f,0.0f},const glm::vec3& rot={0.0f,0.0f,0.0f},const glm::vec3& scale={1.0f,1.0f,1.0f}):
        GameObject::GameObject(&ResourceManager::GetInstance()->GetMesh("sphere1"),&ResourceManager::GetInstance()->GetShader("default"),&ResourceManager::GetInstance()->GetTexture("asteroid_tex"),pos,rot,scale),s(s){}

        virtual void Start() override{
            GameObject::Start();
        }
        virtual void Update(Camera& cam,float delta) override{
            GameObject::Update(cam , delta);
            
            auto rot_vector=glm::normalize(glm::cross(glm::normalize(glm::vec3(0.0f,1.0f,0.0f)),glm::normalize(Position()-s->Position())));

            Position() += rot_vector * orbitspeed * delta;
            Rotation() += speed * delta * direction;
        }


};


