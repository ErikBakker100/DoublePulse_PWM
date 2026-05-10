function(validate_choice VAR_NAME)
    set(valid FALSE)
    foreach(opt IN LISTS ARGN)
        if("${${VAR_NAME}}" STREQUAL "${opt}")
            set(valid TRUE)
        endif()
    endforeach()

    if(NOT valid)
        message(FATAL_ERROR
            "Invalid value for ${VAR_NAME}: '${${VAR_NAME}}'. Choose from: ${ARGN}"
        )
    endif()
endfunction()

function(print_choice VAR_NAME)
    set(args ${ARGN})
    list(LENGTH args argc)

    # Aantal arguments moet even zijn (key/value pairs)
    math(EXPR rem "${argc} % 2")
    if(NOT rem EQUAL 0)
        message(FATAL_ERROR "print_choice requires key/value pairs")
    endif()

    math(EXPR max "${argc} - 1")
    foreach(i RANGE 0 ${max} 2)
        math(EXPR j "${i} + 1")

        list(GET args ${i} key)
        list(GET args ${j} value)

        if("${${VAR_NAME}}" STREQUAL "${key}")
            message(STATUS "${value}")
            return()
        endif()
    endforeach()

    message(WARNING "No status message for ${VAR_NAME}=${${VAR_NAME}}")
endfunction()
