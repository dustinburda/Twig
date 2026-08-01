cmake_minimum_required(VERSION 3.27)
project(Twig)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file (GLOB SRC_FILES src/*.cpp)
list (REMOVE_ITEM SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

add_library(Twig_Lib ${SRC_FILES})

add_executable(${CMAKE_PROJECT_NAME} src/main.cpp)

if (MSVC)
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE /W4 /WX)
    target_compile_options(Twig_Lib PRIVATE /W4 /WX)
else()
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)
    target_compile_options(Twig_Lib PRIVATE -Wall -Wextra -Werror)
endif()


target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Twig_Lib)




include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)





enable_testing()

file (GLOB TEST_FILES test/*.cpp)
add_executable(
        twig_test
        ${TEST_FILES}
)

target_link_libraries(twig_test Twig_Lib)

target_link_libraries(
        twig_test
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(twig_test)
