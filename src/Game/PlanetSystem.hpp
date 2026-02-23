#pragma once
#include"../base/Game/GameObject.hpp"
#include"Moon.hpp"
#include"MoonInstanced.hpp"
#include"Planet.hpp"
#include"Utils.hpp"


class PlanetSystem:public GameObject{


    private:
        
    public:
        std::vector<std::unique_ptr<GameObject>> objects;
        std::vector<glm::vec3> positions;
        unsigned int count=10000;
        PlanetSystem():GameObject::GameObject(nullptr,nullptr,nullptr){}
        virtual void Start() override{
            GameObject::Start();
            
            srand(time(0));
            auto planet = std::make_unique<Planet>(ResourceManager::GetInstance()->GetTexture("jupyter_tex"),glm::vec3(0.0f),glm::vec3(0.0f),glm::vec3(15.0f));
            planet->tag="Planet";
            planet->speed=-1.0f+((static_cast<float>(rand() % 1000)/1000.0f)*2.0f);
            objects.push_back(std::move(planet));
            

            positions.resize(count);
            for(size_t i=0;i<count;i++){
                auto moon1=std::make_unique<MoonInstanced>(dynamic_cast<Planet*>(objects.at(0).get()));
                moon1->Scale()=glm::vec3((static_cast<float>(rand() % 1000)/1000.0f)+0.01f);
                moon1->tag="Moon";
                moon1->speed=-1.0f+((static_cast<float>(rand() % 1000)/1000.0f)*2.0f);
                moon1->orbitspeed=((static_cast<float>(rand() % 1000)/1000.0f)*45.0f+0.01f);
                auto orbit=RandomOrbit(objects.at(0)->Position(),10.0f,100.0f);
                moon1->Position()=glm::vec3(orbit.x,0.0f,orbit.z);
                objects.push_back(std::move(moon1));
            }

        }
        virtual void Update(Camera& cam,float delta) override{    
            auto rm=ResourceManager::GetInstance();
            for(size_t i =0;i<count;i++){
                if(objects.at(i)->tag=="Moon"){
                    positions.at(i)=objects.at(i)->Position();
                    objects.at(i)->Update(cam,delta);
                }
                if(objects.at(i)->tag=="Planet"){

                    objects.at(i)->Update(cam,delta);
                }
            }
            rm->GetShader("instanced_default").Bind();
            rm->GetShader("instanced_default").UniformSet("VP",cam.CalculateVP());
            rm->GetTexture("asteroid_tex").Bind();
            rm->GetMesh("sphere1instanced").LateLoad(positions);
            rm->GetMesh("sphere1instanced").Draw(count);


            
        }



};