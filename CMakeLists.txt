cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(romcalc LANGUAGES C VERSION 0.0.1)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

enable_testing()

add_library(romcalc src/parse.c src/unparse.c src/calculator.c)
target_include_directories(romcalc
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_compile_options(romcalc PRIVATE -Werror)

add_subdirectory(test)
