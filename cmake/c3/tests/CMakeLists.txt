#set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)
add_executable(test2 test2.c)
target_link_libraries(test2 PRIVATE k1-static)
target_include_directories(test2 PRIVATE ${PROJECT_SOURCE_DIR})
