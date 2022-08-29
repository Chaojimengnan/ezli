project(ezli_lome_example)

add_executable(${PROJECT_NAME} main.cpp example_0.cpp example_1.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE .)
target_link_libraries(${PROJECT_NAME} PRIVATE ezli::helper ezli::hints)

