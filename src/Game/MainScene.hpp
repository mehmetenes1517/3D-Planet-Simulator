#pragma once

#include "../base/Game/Scene.hpp"
#include"Planet.hpp"
#include"PlanetSystem.hpp"
class MainScene:public Scene{
    PlanetSystem system;
    
    public:
        virtual void Start()override{
            auto resourcemanager=ResourceManager::GetInstance();
            resourcemanager->LoadMesh("sphere1","./Resources/sphere.model");
            resourcemanager->LoadMeshInstanced("sphere1instanced","./Resources/sphere.model");
            resourcemanager->LoadShader("default","./Resources/Shaders/default.vert","./Resources/Shaders/default.frag");
            resourcemanager->LoadShader("instanced_default","./Resources/Shaders/instanced_default.vert","./Resources/Shaders/instanced_default.frag");
            resourcemanager->LoadTexture("jupyter_tex","./Resources/Textures/jp.jpg");
            resourcemanager->LoadTexture("asteroid_tex","./Resources/Textures/ast.jpg");
            
            Scene::Start();
            system.Start();

        }
        virtual void Update(Camera& cam,float delta) override{
            Scene::Update(cam,delta);
            system.Update(cam,delta);





        }


};
