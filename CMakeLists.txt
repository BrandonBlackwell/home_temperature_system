cmake_minimum_required(VERSION 3.10.0)
project(home_temperature_system VERSION 0.1.0 LANGUAGES C CXX)

# ... Arduino firmware code here ...

# Only include tests when building with native host compiler (not ARM embedded)
if(NOT CMAKE_SYSTEM_NAME STREQUAL "Generic")
    include(FetchContent)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.14.0
    )
    FetchContent_MakeAvailable(Catch2)

    include(CTest)
    enable_testing()

    add_subdirectory(src)
    add_subdirectory(test)
endif()