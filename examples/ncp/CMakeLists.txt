# Use the sdbus-c++-xml2cpp in SDBusCpp namespace to generate the headers
add_custom_command(
    OUTPUT ncp-client-glue.h ncp-server-glue.h
    COMMAND sdbus-c++-xml2cpp ${CMAKE_CURRENT_SOURCE_DIR}/ConsentCtaDbus.xml
        --proxy=ncp-client-glue.h --adaptor=ncp-server-glue.h
    DEPENDS ConsentCtaDbus.xml
    COMMENT "Generating D-Bus interfaces for Consent Container."
)

add_executable(ncp-server ncp-server.cpp ncp-server-glue.h)
target_link_libraries(ncp-server sdbus-c++)

target_include_directories(ncp-server
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

add_executable(ncp-client ncp-client.cpp ncp-client-glue.h)
target_link_libraries(ncp-client sdbus-c++)

target_include_directories(ncp-client
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)
