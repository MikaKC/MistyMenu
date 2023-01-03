cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(MistyMenu)

add_library(MistyMenu SHARED src/main.cpp)

include(cmake/CPM.cmake)

CPMAddPackage("gh:matcool/mat-dash#cdc9f70")
CPMAddPackage("gh:MikaKC/gd.h#main")
CPMAddPackage("gh:TsudaKageyu/minhook#4a45552")

target_compile_definitions(MistyMenu PRIVATE CC_DLL=)

target_include_directories(MistyMenu PRIVATE
	libraries/imgui-hook
	libraries/imgui-hook/imgui
    	${gd.h_SOURCE_DIR}/include ${gd.h_SOURCE_DIR}
    	${minhook_SOURCE_DIR}/include
)

add_subdirectory(libraries/cocos-headers)
add_subdirectory(libraries/imgui-hook)
target_link_libraries(MistyMenu mat-dash cocos2d minhook imgui-hook)
