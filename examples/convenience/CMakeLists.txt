add_executable(convenience-server convenience-server.cpp)
target_link_libraries(convenience-server sdbus-c++)

add_executable(convenience-client convenience-client.cpp)
target_link_libraries(convenience-client sdbus-c++)
