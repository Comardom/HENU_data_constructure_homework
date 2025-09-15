cmake_minimum_required(VERSION 3.31)
project(ex1)

set(CMAKE_CXX_STANDARD 11)

add_executable(ex1 main.cpp
        cFixedArray.cpp
        cSafeInput.h
        constData.h
        cDynamicArray.cpp
        prototypes.h
        cDyLinkedList.cpp
        cppSet.cpp
        #        .trashbin/cppFixedArray.cpp
)
