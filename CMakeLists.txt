cmake_minimum_required(VERSION 3.20)

set(APP_NAME "pypackager-app" CACHE STRING "The name of your packaged app")

project(${APP_NAME} LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME} src/main.c)

find_package(Python
    COMPONENTS Development.Embed
    REQUIRED
)

message(STATUS "Python_INCLUDE_DIRS: ${Python_INCLUDE_DIRS}")
message(STATUS "Python_LIBRARIES: ${Python_LIBRARIES}")

target_include_directories(${PROJECT_NAME} 
    PRIVATE 
    ${Python_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
    ${Python_LIBRARIES}
    crypt
    m
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
    PYTHON_FILE_PATH="app/__main__.py"
)

