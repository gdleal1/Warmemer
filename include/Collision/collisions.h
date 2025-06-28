#pragma once
#include "Warhammer/Miniatures.hpp"
#include "Warhammer/Armies.hpp"
#include "GastalUtils/SceneObject.h" 
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "GastalUtils/matricies.h"


extern std::map<std::string, SceneObject> g_VirtualScene;

bool MiniaturesAreColliding(const Miniature& a, const Miniature& b);


                      
                     

