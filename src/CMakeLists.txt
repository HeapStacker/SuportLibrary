file(GLOB_RECURSE SRC_FILES *.cpp)

add_library(suportLibrary STATIC ${SRC_FILES})
target_include_directories(suportLibrary PUBLIC ../include)