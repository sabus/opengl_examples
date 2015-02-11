find_program(APITRACE apitrace)
find_program(QAPITRACE qapitrace)

if(EXISTS ${APITRACE})
    message("-- APITRACE found: ${APITRACE}")
else()
    message(FATAL_ERROR "-- APITRACE not found")
endif()

macro(APITRACE_OUTPUT target)

get_filename_component(name ${target} NAME_WE)

add_custom_target(
        apitrace_${target}
        DEPENDS ${target}
        COMMAND apitrace trace -o ${CMAKE_CURRENT_BINARY_DIR}/${name}.trace  ${CMAKE_CURRENT_BINARY_DIR}/${target} && qapitrace ${CMAKE_CURRENT_BINARY_DIR}/${name}.trace
)

endmacro(APITRACE_OUTPUT)

