add_executable(basic-server basic-server.cpp)
target_link_libraries(basic-server sdbus-c++)

add_executable(basic-client basic-client.cpp)
target_link_libraries(basic-client sdbus-c++)
