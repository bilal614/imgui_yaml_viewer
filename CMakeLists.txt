# CMake entry point
cmake_minimum_required (VERSION 3.11)
project (SimpleImageViewer)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(glfw3 3.3 REQUIRED)

pkg_check_modules(GLFW3 REQUIRED glfw3)

add_subdirectory(${PROJECT_SOURCE_DIR}/yaml-cpp)

get_property(propVal TARGET yaml-cpp PROPERTY INCLUDE_DIRECTORIES)

if (propVal)
    message("${target}-INCLUDE_DIRECTORIES:   ${propVal}")
endif()

if(OPENGL_FOUND AND PKG_CONFIG_FOUND AND GLFW3_FOUND)
    
    include_directories(
        ${OPENGL_INCLUDE_DIRS}
        ${GLFW3_INCLUDE_DIRS}
    )

    add_library(imgui_glfw_opengl SHARED
        ${PROJECT_SOURCE_DIR}/imgui/imgui.cpp
        ${PROJECT_SOURCE_DIR}/imgui/imgui_demo.cpp
        ${PROJECT_SOURCE_DIR}/imgui/imgui_draw.cpp
        ${PROJECT_SOURCE_DIR}/imgui/imgui_tables.cpp
        ${PROJECT_SOURCE_DIR}/imgui/imgui_widgets.cpp
        ${PROJECT_SOURCE_DIR}/imgui/backends/imgui_impl_glfw.cpp
        ${PROJECT_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp
        ${PROJECT_SOURCE_DIR}/imgui/misc/cpp/imgui_stdlib.cpp
    )

    target_include_directories(imgui_glfw_opengl PRIVATE 
        ${PROJECT_SOURCE_DIR}/imgui
    )
    
    add_executable(test_app 
        ${PROJECT_SOURCE_DIR}/imgui/examples/example_glfw_opengl3/main.cpp
    )

    target_include_directories(test_app PUBLIC 
        ${PROJECT_SOURCE_DIR}/imgui
        ${PROJECT_SOURCE_DIR}/imgui/backends
    )

    target_link_libraries(test_app
        imgui_glfw_opengl
        ${OPENGL_LIBRARIES}
        ${GLFW3_LIBRARIES}
        ${CMAKE_DL_LIBS} #link to dl lib for dynamic loading
        -lX11 #In some cases need to explicitly link to x11 lib, needed by glfw3
        -pthread 
    )

    add_executable(yaml_validation_tool
        ${PROJECT_SOURCE_DIR}/src/ErrorView.cpp
        ${PROJECT_SOURCE_DIR}/src/GlfwBackendBinding.cpp
        ${PROJECT_SOURCE_DIR}/src/YamlEditView.cpp
        ${PROJECT_SOURCE_DIR}/src/YamlValidationModel.cpp
        ${PROJECT_SOURCE_DIR}/src/YamlViewModel.cpp
        ${PROJECT_SOURCE_DIR}/src/main.cpp
    )

    target_include_directories(yaml_validation_tool PUBLIC
        ${PROJECT_SOURCE_DIR}/include 
        ${PROJECT_SOURCE_DIR}/imgui
        ${PROJECT_SOURCE_DIR}/imgui/backends
        $<TARGET_PROPERTY:yaml-cpp,INCLUDE_DIRECTORIES>
    )

    target_link_libraries(yaml_validation_tool
        imgui_glfw_opengl
        ${OPENGL_LIBRARIES}
        ${GLFW3_LIBRARIES}
        ${CMAKE_DL_LIBS} #link to dl lib for dynamic loading
        -lX11 #In some cases need to explicitly link to x11 lib, needed by glfw3
        -pthread
        yaml-cpp
    )

endif()
