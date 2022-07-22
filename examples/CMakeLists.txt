add_subdirectory(basic)
add_subdirectory(convenience)

# The following examples require the code generator.
if(BUILD_CODE_GEN)
    add_subdirectory(planet-xml)
    add_subdirectory(xml-based)
endif()
