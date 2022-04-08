# Use the sdbus-c++-xml2cpp in SDBusCpp namespace to generate the headers
add_custom_command(
    OUTPUT planet-client-glue.h planet-server-glue.h
    COMMAND sdbus-c++-xml2cpp ${CMAKE_CURRENT_SOURCE_DIR}/planet.xml
        --proxy=planet-client-glue.h --adaptor=planet-server-glue.h
    DEPENDS planet.xml
    COMMENT "Generating D-Bus interfaces for Planet."
)

add_executable(xml-server xml-server.cpp planet-server-glue.h)
target_link_libraries(xml-server sdbus-c++)

target_include_directories(xml-server
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

add_executable(xml-client xml-client.cpp planet-client-glue.h)
target_link_libraries(xml-client sdbus-c++)

target_include_directories(xml-client
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)
