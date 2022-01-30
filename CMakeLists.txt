cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(SuportLibraryProject VERSION 1.0)


# CMake instructions to make the static lib

ADD_LIBRARY(SuportLibrary STATIC
             src/fileSuport.cpp)

#CMake making dynamic lib test...
# ADD_LIBRARY(SuportLibraryDll SHARED src/fileSuport.cpp)


# CMake instructions to test using the static lib

SET(APP_EXE StaticTest)
ADD_EXECUTABLE(${APP_EXE} src/main.cpp)
TARGET_LINK_LIBRARIES( ${APP_EXE} SuportLibrary )


target_include_directories(SuportLibrary PUBLIC include)

