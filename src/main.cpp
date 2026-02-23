#define STB_IMAGE_IMPLEMENTATION
#include<iostream>
#include<memory>
#include<iomanip>
#include"base/Game/Window.hpp"
#include"base/Game/GameObject.hpp"
#include"base/Game/InputManager.hpp"
#include"base/Game/ResourceManager.hpp"
#include"Game/Planet.hpp"
#include"Game/MainScene.hpp"


int main(){

    try
    {
        Window::Init(1366,768,"Galaxy Simulator");
        auto win=Window::GetInstance();
        InputManager::Init(win);
        ResourceManager::Init();
        auto inputmanager=InputManager::GetInstance();
        auto resourcemanager=ResourceManager::GetInstance();
        inputmanager->CursorDisabled(true);
        
        Camera cam;
    
        MainScene scene;
        scene.Start();
        while (!win->ShouldClose())
        {
            if(inputmanager->GetKey(GLFW_KEY_ESCAPE)){break;}
            win->Clear();
            
            cam.CalculateOrientation(inputmanager->yaw,inputmanager->pitch);
            cam.FPSMovement(20.0f,GLFW_KEY_W,GLFW_KEY_S,GLFW_KEY_D,GLFW_KEY_A);
            scene.Update(cam,win->GetDelta());


            std::cout<<"\n FPS : "<<1/win->GetDelta();
            win->NextFrame();
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    


    return 0;
}