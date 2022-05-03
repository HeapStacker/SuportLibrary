cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(SuportLibraryProject VERSION 1.0.0)
set(CMAKE_VERBOSE_MAKEFILE ON)


#add_subdirectory(glad)
#add_subdirectory(glfw)
add_subdirectory(src)
ADD_EXECUTABLE(${PROJECT_NAME} main.cpp)


#target_include_directories(${PROJECT_NAME} PUBLIC build/extLibs/glad/include)
#target_include_directories(${PROJECT_NAME} PUBLIC extLibs/glfw/include)

#ASIO
target_include_directories(${PROJECT_NAME} PUBLIC include/asio)

#target_link_libraries(${PROJECT_NAME} suportLibrary glad glfw)
target_link_libraries(${PROJECT_NAME} suportLibrary)