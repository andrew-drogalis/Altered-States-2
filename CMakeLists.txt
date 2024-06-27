cmake_minimum_required(VERSION 3.20)
project(Altered-States-2)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(GNUInstallDirs)

add_executable(${PROJECT_NAME} altered-states-2.cpp)

target_include_directories(${PROJECT_NAME}
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
# ------------------------------
# Build Configuration
include(cmake/CompilerWarnings.cmake)
include(cmake/Sanitizers.cmake)

myproject_set_project_warnings(${PROJECT_NAME} TRUE "X" "" "" "X")

add_compile_options(-pipe -fPIC)
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-NDDEBUG)
endif()
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # myproject_enable_include_what_you_use() myproject_enable_cppcheck(FALSE "X")
    gcc_analyzer_enable()
    myproject_enable_sanitizers(${PROJECT_NAME} TRUE TRUE TRUE FALSE TRUE)
endif()
