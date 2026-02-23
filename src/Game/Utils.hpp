#pragma once

#include<glm/glm.hpp>

inline glm::vec3 RandomOrbit(const glm::vec3& center,float inner_circle_r,float outer_circle_r){
    auto x=((static_cast<float>(rand()%1000)/1000.0f)*outer_circle_r);
    auto clamped_x=inner_circle_r+x;
    auto y=((static_cast<float>(rand()%1000)/1000.0f)*outer_circle_r);
    auto clamped_y=inner_circle_r+y;
    auto z=((static_cast<float>(rand()%1000)/1000.0f)*outer_circle_r);
    auto clamped_z=inner_circle_r+z;
    return glm::vec3(clamped_x,clamped_y,clamped_z);
}
