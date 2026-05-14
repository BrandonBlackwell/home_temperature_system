add_library(rgb_controller STATIC rgbController.cpp)

target_include_directories(rgb_controller PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})