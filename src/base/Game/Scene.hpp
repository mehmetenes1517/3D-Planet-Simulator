#pragma once
#include<iostream>
#include<vector>
#include<memory>
#include"GameObject.hpp"
#include"Camera.hpp"
class Scene{
    protected:

        std::vector<std::unique_ptr<GameObject>> gameobjects;

    public:

        virtual void Start(){   
            for(auto& a:gameobjects){
                a->Start();
            }
        }
        virtual void Update(Camera& cam,float delta){
            for(auto& a:gameobjects){
                a->Update(cam,delta);
            }
        }



};