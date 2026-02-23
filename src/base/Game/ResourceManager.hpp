#pragma once
#include<iostream>
#include<map>
#include<fstream>
#include<string>
#include<memory>
#include<sstream>
#include"../GL/Shader.hpp"
#include"../GL/Texture.hpp"
#include"../GL/VAO.hpp"
#include"../GL/InstancedVAO.hpp"

inline std::pair<std::vector<Vertex>,std::vector<unsigned int>> ReadMeshFromFile(const std::string& file){
    std::string file_content;
    {
        std::ifstream model_file(file);
        std::stringstream model_stream;
        model_stream<<model_file.rdbuf();
        file_content=model_stream.str();
    }
    uint32_t iter_half=file_content.find("endofvertices");
    if(iter_half==UINT32_MAX){
        throw std::runtime_error("cannot found model separator 'endofvertices' ");
    }
    size_t i=0;
    std::vector<float> vertex_attributes;
    while (i<iter_half)
    {
        if(std::isdigit(file_content.at(i)) || file_content.at(i)=='-'){
            
            std::string number;
            number.push_back(file_content.at(i));
            i++;
            while (i<iter_half)
            {
                if(std::isdigit(file_content.at(i)) || file_content.at(i)=='-' || file_content.at(i)=='.'){
                    number.push_back(file_content.at(i));
                    i++;
                }
                else if(','==(file_content.at(i)) or '\n'==(file_content.at(i))){
                    i++;
                    break;
                }else{
                    i++;
                }
            }
            vertex_attributes.push_back(std::stod(number));
        }else{
            i++;
        }
    }

    std::vector<Vertex> vertices;
    for (size_t i=0;i<vertex_attributes.size();i+=8){
        vertices.push_back((Vertex){vertex_attributes.at(i),vertex_attributes.at(i+1),vertex_attributes.at(i+2),vertex_attributes.at(i+3),vertex_attributes.at(i+4),vertex_attributes.at(i+5),vertex_attributes.at(i+6),vertex_attributes.at(i+7)});
    }
    std::vector<unsigned int> indices;
    i=iter_half;
    while (i<file_content.size())
    {
        if(std::isdigit(file_content.at(i))){
            std::string number;
            while (i<file_content.size())
            {
                if(std::isdigit(file_content.at(i))){
                    number.push_back(file_content.at(i));
                    i++;
                }
                else if(','==(file_content.at(i)) or '\n'==(file_content.at(i))){
                    break;
                }else{
                    i++;
                }
            }
            indices.push_back(std::stoi(number));
        }else{
            i++;
        }
    }

    return std::make_pair(vertices,indices);
}


class ResourceManager{

    private:
        std::map<std::string,std::unique_ptr<Texture>> textures;
        std::map<std::string,std::unique_ptr<Shader>> shaders;
        std::map<std::string,std::unique_ptr<VAO>> meshes;
    public:
        static ResourceManager* instance;
        
        ResourceManager(){}

        void LoadTexture(const std::string& tag,const std::string& filename){
            textures[tag]=std::move(std::make_unique<Texture>(filename));
        }
        void LoadShader(const std::string& tag,const std::string& vertexshader_file,const std::string& fragmentshader_file){
            shaders[tag]=std::move(std::make_unique<Shader>(vertexshader_file,fragmentshader_file));
        }
        void LoadMesh(const std::string& tag,const std::string& filename){
            auto [vertices,indices]=ReadMeshFromFile(filename);
            meshes[tag]=std::move(std::make_unique<VAO>(vertices,indices));
        }
        void LoadMeshInstanced(const std::string& tag,const std::string& filename){
            auto [vertices,indices]=ReadMeshFromFile(filename);
            meshes[tag]=std::move(std::make_unique<InstancedVAO>(vertices,indices));
        }
        VAO& GetMesh(const std::string& tag){
            if(meshes.find(tag)!=meshes.end()){
                return *meshes[tag];
            }else{
                throw std::runtime_error("Cant find "+tag);
            }
        }
        Texture& GetTexture(const std::string& tag){
            if(textures.find(tag)!=textures.end()){
                return *textures[tag];
            }else{
                throw std::runtime_error("Cant find "+tag);
            }
        }
        Shader& GetShader(const std::string& tag){
            if(shaders.find(tag)!=shaders.end()){
                return *shaders[tag];
            }else{
                throw std::runtime_error("Cant Find "+tag);
            }

        }

        static void Init(){
            if(instance==nullptr){
                instance=new ResourceManager;
            }else{
                throw std::runtime_error("Multiple Initializing of resource manager!");
            }
        }
        static ResourceManager* GetInstance(){
            if(instance==nullptr){
                throw std::runtime_error("Instance is null!");
            }else{
                return instance;
            }
        }


};
ResourceManager* ResourceManager::instance=nullptr;