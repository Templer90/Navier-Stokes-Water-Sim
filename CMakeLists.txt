cmake_minimum_required(VERSION 3.23)
project(Water)

set(CMAKE_CXX_STANDARD 20)

set(OpenGlLinkers -lglut -lGLU -lGL) # setting all the Glut libraries as one variable.

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

add_executable(Water main.cpp Tile.cpp Tile.h Color.cpp Color.h helper/TileAction.h helper/ButtonKeys.h Scene/Scene.h Scene/SimpleCell/SimpleCell.cpp Scene/SimpleCell/SimpleCell.h Scene/Full/Full.cpp Scene/Full/Full.h Scene/SceneList.cpp Scene/SceneList.h Scene/Start/Intro.cpp Scene/Start/Intro.h helper/PrintString.h Scene/Full/PhysicsSolver/Container.cpp Scene/Full/PhysicsSolver/Container.h Scene/Full/PhysicsSolver/Physics.cpp Scene/Full/PhysicsSolver/Physics.h Scene/Full/IX.cpp Scene/Full/IX.h Scene/Full/PhysicsSolver/LookUP.cpp Scene/Full/PhysicsSolver/LookUP.h)

target_link_libraries(Water ${OpenGlLinkers}) # linking opengl libraries to the project