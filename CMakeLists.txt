cmake_minimum_required(VERSION 3.16)
project(ZeroDamMap CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

add_executable(ZeroDamMap
    main.cpp
    src/MapView.cpp
)
target_include_directories(ZeroDamMap PRIVATE include)
target_compile_options(ZeroDamMap PRIVATE -Wall -Wextra -Wpedantic)
target_link_libraries(ZeroDamMap sfml-graphics sfml-window sfml-system)

add_custom_command(TARGET ZeroDamMap POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:ZeroDamMap>/data
)
