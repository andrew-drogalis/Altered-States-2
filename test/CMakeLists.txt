cmake_minimum_required(VERSION 3.20)
project(Altered-States-2-Test)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(GNUInstallDirs)

cmake_path(
  GET
  CMAKE_CURRENT_SOURCE_DIR
  PARENT_PATH
  PARENT_DIR)

add_executable(${PROJECT_NAME} validate-score.cpp)

target_include_directories(${PROJECT_NAME}
                           PRIVATE ${PARENT_DIR}/include)
# ------------------------------
# Build Configuration
include(${PARENT_DIR}/cmake/CompilerWarnings.cmake)
include(${PARENT_DIR}/cmake/Sanitizers.cmake)

myproject_set_project_warnings(${PROJECT_NAME} TRUE "X" "" "" "X")

add_compile_options(-pipe -fPIC)
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-NDDEBUG)
endif()
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # myproject_enable_include_what_you_use() myproject_enable_cppcheck(FALSE "X")
    # gcc_analyzer_enable()
    myproject_enable_sanitizers(${PROJECT_NAME} TRUE TRUE TRUE FALSE TRUE)
endif()
