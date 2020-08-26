cmake_minimum_required(VERSION 3.8)

project(ut3 C)

find_package(PkgConfig REQUIRED)

pkg_check_modules(ENET REQUIRED IMPORTED_TARGET libenet)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(
    ut3
    src/main.c
)

target_link_libraries(
    ut3
    PUBLIC
    PkgConfig::ENET
)