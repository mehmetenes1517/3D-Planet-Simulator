#pragma once
#include<glm/gtc/matrix_transform.hpp>
#include"Window.hpp"
#include"InputManager.hpp"
struct Camera{

    glm::vec3 position={0.0f,0.0f,5.0f};
    glm::vec3 forward={0.0f,0.0f,-1.0f};
    glm::vec3 right={1.0f,0.0f,.0f};
    glm::vec3 up={0.0f,1.0f,0.0f};
    float pov=45.0f;
    float near=0.1f;
    float far=1000.0f;
    


    glm::mat4 CalculateVP(){
        auto View=glm::lookAt(position,position+forward,up);
        
        auto width=Window::GetInstance()->GetWidth();
        auto height=Window::GetInstance()->GetHeight();
        auto Projection=glm::perspective(pov,((float)width/(float)height),near,far);
        
        return Projection*View;
    }
    /*@brief first one is forward vector(looking point) second one is up vector */
    std::pair<glm::vec3,glm::vec3> CalculateOrientation(float yaw,float pitch){

        //*forward vector calculation */

        forward.x=glm::cos(glm::radians(pitch))*glm::cos(glm::radians(yaw));
        forward.y=glm::sin(glm::radians(pitch));
        forward.z=glm::cos(glm::radians(pitch))*glm::sin(glm::radians(yaw));


        forward=glm::normalize(forward);
        right=glm::normalize(glm::cross(forward,glm::vec3(0.0f,1.0f,0.0f)));
        up=glm::normalize(glm::cross(right,forward));
        right=glm::normalize(glm::cross(forward,up));
        return std::make_pair(forward,up);
    }

    /*@brief Camera FPS movement funtion : No need for Deltatime!*/
    void FPSMovement(float speed,uint32_t forw_,uint32_t back_,uint32_t right_,uint32_t left_){
        if(InputManager::GetInstance()->GetKey(forw_))
            position+=speed*Window::GetInstance()->GetDelta()*forward;
        if(InputManager::GetInstance()->GetKey(back_))
            position-=speed*Window::GetInstance()->GetDelta()*forward;
        if(InputManager::GetInstance()->GetKey(right_))
            position+=speed*Window::GetInstance()->GetDelta()*right;
        if(InputManager::GetInstance()->GetKey(left_))
            position-=speed*Window::GetInstance()->GetDelta()*right;
    }    
};