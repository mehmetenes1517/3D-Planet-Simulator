#pragma once
#include<GLFW/glfw3.h>
#include"Window.hpp"
class InputManager{

    Window& win;
    
    public:

        static bool _firsttime_;
        static float Oldmousex,Oldmousey;
        

        
        static float sensivity,deltaX,deltaY,yaw,pitch;


        static InputManager* instance;

        static void Init(Window* win){
            if(instance==nullptr){
                instance=new InputManager(*win);
                glfwSetCursorPosCallback(win->Get(),MouseCursor);
            }
            else{
                throw std::runtime_error("Initializing Input manager multiple times!");
            }
        }

        static InputManager* GetInstance(){
            if(instance!=nullptr){
                return instance;
            }else{
                throw std::runtime_error("Input Manager instance is null!");
            }
        }
                
        static void MouseCursor(GLFWwindow* w,double x,double y){
            float LatestMouseX=static_cast<float>(x);
            float LatestMouseY=static_cast<float>(y);

            if(_firsttime_){
                Oldmousex=LatestMouseX;
                Oldmousey=LatestMouseY;
                _firsttime_=false;
            }
            deltaX=Oldmousex-LatestMouseX;
            deltaY=LatestMouseY-Oldmousey;
            
            deltaX*=sensivity;
            deltaY*=sensivity;
            
            //Do whatever you want here;

                yaw-=Window::GetInstance()->GetDelta()*deltaX;
                pitch-=Window::GetInstance()->GetDelta()*deltaY;

                if(pitch>90){pitch=90.0f;}
                if(pitch<-90){pitch=-90.0f;}


            Oldmousex=LatestMouseX;
            Oldmousey=LatestMouseY;
            deltaX=0.0f;
            deltaY=0.0f;
        }
        InputManager(Window& win):win(win){}

        InputManager(const InputManager& win)=delete;
        InputManager& operator=(const InputManager& inp)=delete;
        void SetCursorPosCallback(GLFWcursorposfun CALLBACK){
            glfwSetCursorPosCallback(win.Get(),CALLBACK);;
        }
        void CursorDisabled(bool mode){
            glfwSetInputMode(win.Get(),GLFW_CURSOR,mode ? GLFW_CURSOR_DISABLED:GLFW_CURSOR_NORMAL);
        }
        bool GetKey(uint32_t key){
            return glfwGetKey(win.Get(),key);
        }
};
/*@brief These are used for mouse controls*/
float InputManager::deltaX=0.0f,InputManager::deltaY=0.0f,InputManager::yaw=270.0f,InputManager::pitch=0.0f,InputManager::sensivity=50.0f;
/*@brief 
* don't touch these Oldmousex Oldmousey
*/
float InputManager::Oldmousex=0.0f,InputManager::Oldmousey=0.0f;
/*@brief
please dont touch the first time variable*/
bool InputManager::_firsttime_=true;

InputManager* InputManager::instance=nullptr;