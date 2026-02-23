#pragma once
#include<iostream>
#include<memory>
#include<functional>
#include"../GL/glad.h"
#include<GLFW/glfw3.h>
#include<cstdint>
class Window{
    
    private:
        float delta=0.0f;
        float time=glfwGetTime();
        uint32_t width,height;
        std::string title;

        std::unique_ptr<GLFWwindow,std::function<void(GLFWwindow*)>> window;

    public:
        static Window* instance;

        static void Init(uint32_t w,uint32_t h,const std::string& title){
            if(instance!=nullptr){
                throw std::runtime_error("Multiple init of window!");
            }else{
                instance=new Window(w,h,title);
            }
        }
        static Window* GetInstance(){
            if(instance!=nullptr){
                return instance;
            }else{
                throw std::runtime_error("window instance is null!");
            }
        }

        Window(uint32_t w,uint32_t h,const std::string& title):
                                        width(w),
                                        height(h),
                                        title(title)
                                        {
            if(!glfwInit()){
                throw std::runtime_error("Cannot initialize glfw context");
            }    
            glfwWindowHint(GLFW_RESIZABLE,GLFW_FALSE);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            std::unique_ptr<GLFWwindow,std::function<void(GLFWwindow*)>> win(glfwCreateWindow(width,height,title.c_str(),nullptr,nullptr),[](GLFWwindow* w){glfwDestroyWindow(w);});                     
            this->window=std::move(win);
            if(window.get()==nullptr){
                throw std::runtime_error("Cannot create window");
            }
            glfwMakeContextCurrent(window.get());
            gladLoadGL();
            glEnable(GL_DEPTH_TEST);
        }
        GLFWwindow* Get() const{
            return window.get();
        }
        bool ShouldClose(){
            return glfwWindowShouldClose(window.get());
        }
        void Clear(){
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            delta=glfwGetTime()-time;
            time=glfwGetTime();
        }
        void NextFrame(){
            glfwSwapBuffers(window.get());
            glfwPollEvents();
        }
        float GetTime() const{
            return glfwGetTime();
        }
        float GetDelta() const{
            return delta;
        }
        uint32_t GetWidth() const{
            return width;
        }
        uint32_t GetHeight() const{
            return height;
        }
        std::string GetTitle() const{
            return title;
        }
        ~Window(){
            glfwTerminate();
        }
};
Window* Window::instance=nullptr;
