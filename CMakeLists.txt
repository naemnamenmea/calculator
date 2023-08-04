cmake_minimum_required(VERSION 3.19)

include(FetchContent)

FetchContent_Declare(
    cmake-tutorial
    GIT_REPOSITORY https://github.com/naemnamenmea/cmake-tutorial.git
    GIT_TAG        main
)
FetchContent_MakeAvailable(cmake-tutorial)

option(MW_PROJECT_NAME_FROM_DIRECTORY "Use the directory name  of the source directory as project name" ON)
if(MW_PROJECT_NAME_FROM_DIRECTORY)
	mw_set_project_name_from_source_dir(project_name)
else()
	set(project_name "buildAll")
endif()
project(${project_name} LANGUAGES C CXX)

if (MSVC)
    # warning level 4
    add_compile_options(/W4 /WX)
else()
    # additional warnings
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

set(CMAKE_CXX_STANDARD 17)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_SUPPRESS_REGENERATION OFF)





add_executable(calculator)
file(GLOB SOURCE_FILES
    public/*.hpp
    public/*.h
    private/*.hpp
    private/*.h
    src/*.cpp
    src/*.c
    *.hpp
    *.h
    *.cpp
    *.c
)
target_sources(calculator PUBLIC ${SOURCE_FILES})

target_include_directories(calculator
    PUBLIC public
    PRIVATE private
    PRIVATE .
)
target_link_libraries(calculator PUBLIC my_testing_tools)
target_link_libraries(calculator PUBLIC math)