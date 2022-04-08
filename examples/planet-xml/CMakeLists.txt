# Use the sdbus-c++-xml2cpp in SDBusCpp namespace to generate the headers
add_custom_command(
    OUTPUT planet-client-glue.h planet-server-glue.h
    COMMAND sdbus-c++-xml2cpp ${CMAKE_CURRENT_SOURCE_DIR}/planet.xml
        --proxy=planet-client-glue.h --adaptor=planet-server-glue.h
    DEPENDS planet.xml
    COMMENT "Generating D-Bus interfaces for Planet."
)

add_executable(obj-manager-server obj-manager-server.cpp planet-server-glue.h)
target_link_libraries(obj-manager-server sdbus-c++)

target_include_directories(obj-manager-server
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

add_executable(obj-manager-client obj-manager-client.cpp planet-client-glue.h)
target_link_libraries(obj-manager-client sdbus-c++)

target_include_directories(obj-manager-client
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)
