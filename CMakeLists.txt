cmake_minimum_required(VERSION 3.16)
project(SO_Suite LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# Subdirectorios
add_subdirectory(core)
add_subdirectory(scheduler)
add_subdirectory(concurrency)
add_subdirectory(memory)
add_subdirectory(ui)

# Archivos principales
set(SRC
    main.cpp
    mainwindow.cpp
    mainwindow.ui
)

add_executable(SO_Suite ${SRC})

target_link_libraries(SO_Suite
    Qt6::Core
    Qt6::Widgets
    core_lib
    scheduler_lib
    concurrency_lib
    memory_lib
    ui_lib
)
