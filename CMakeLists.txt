
macro(build_unitest_lib MODULE )

    project(${MODULE})

    include_directories(./)

    FILE(GLOB_RECURSE DIR_SRCS "*.cpp")

    FILE(GLOB TARS_LIST "${CMAKE_CURRENT_SOURCE_DIR}/*.tars")

    set(TARS_LIST_DEPENDS)

    if (TARS_LIST)
        set(CLEAN_LIST)

        foreach (TARS_SRC ${TARS_LIST})
            get_filename_component(NAME_WE ${TARS_SRC} NAME_WE)

            set(TARS_H ${NAME_WE}.h)

            set(CUR_TARS_GEN ${CMAKE_CURRENT_SOURCE_DIR}/${TARS_H})
            LIST(APPEND TARS_LIST_DEPENDS ${CUR_TARS_GEN})
            
            add_custom_command(OUTPUT ${CUR_TARS_GEN}
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    DEPENDS ${TARS2CPP} 
                    COMMAND ${TARS2CPP} ${TARS_SRC}
                    COMMENT "${TARS2CPP} ${TARS_SRC}")

            list(APPEND CLEAN_LIST ${CMAKE_CURRENT_SOURCE_DIR}/${TARS_H})

        endforeach ()

        set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${CLEAN_LIST}")

        set(TARS_TARGET "TARS_${MODULE}")  
        add_custom_target(${TARS_TARGET} ALL DEPENDS ${TARS_LIST_DEPENDS} tars2cpp)

        add_library(${MODULE} ${DIR_SRCS})

        add_dependencies(${MODULE} ${TARS_TARGET})

    else(TARS_LIST)
        add_library(${MODULE} ${DIR_SRCS})
    endif(TARS_LIST)
                
endmacro()

macro(build_unitest MODULE )

    project(${MODULE})

    include_directories(./)

    FILE(GLOB_RECURSE DIR_SRCS "*.cpp")

    FILE(GLOB TARS_LIST "${CMAKE_CURRENT_SOURCE_DIR}/*.tars")

    set(TARS_LIST_DEPENDS)

    if (TARS_LIST)
        set(CLEAN_LIST)

        foreach (TARS_SRC ${TARS_LIST})
            get_filename_component(NAME_WE ${TARS_SRC} NAME_WE)

            set(TARS_H ${NAME_WE}.h)

            set(CUR_TARS_GEN ${CMAKE_CURRENT_SOURCE_DIR}/${TARS_H})
            LIST(APPEND TARS_LIST_DEPENDS ${CUR_TARS_GEN})
            
            add_custom_command(OUTPUT ${CUR_TARS_GEN}
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    DEPENDS ${TARS2CPP} 
                    COMMAND ${TARS2CPP} ${TARS_SRC}
                    COMMENT "${TARS2CPP} ${TARS_SRC}")

            list(APPEND CLEAN_LIST ${CMAKE_CURRENT_SOURCE_DIR}/${TARS_H})

        endforeach ()

        set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${CLEAN_LIST}")

        set(TARS_TARGET "TARS_${MODULE}")  
        add_custom_target(${TARS_TARGET} ALL DEPENDS ${TARS_LIST_DEPENDS} tars2cpp)

        add_executable(${MODULE} ${DIR_SRCS})

        add_dependencies(${MODULE} ${TARS_TARGET})

    else(TARS_LIST)
        add_executable(${MODULE} ${DIR_SRCS})
    endif(TARS_LIST)

    target_link_libraries(${MODULE} tarsservant tarsutil)

    if(TARS_SSL)
        target_link_libraries(${MODULE} tarsservant tarsutil ${LIB_SSL} ${LIB_CRYPTO})

        if(WIN32)
            target_link_libraries(${MODULE} Crypt32)
        endif()
    endif()

    if(TARS_HTTP2)
        target_link_libraries(${MODULE} ${LIB_HTTP2})
    endif()

    if(TARS_GPERF)
        target_link_libraries(${MODULE} ${LIB_GPERF})
    endif(TARS_GPERF)
                
endmacro()

#-----------------------------------------------------------------------

add_subdirectory(protocol/TarsTest/TestcaseServer)
add_subdirectory(protocol/TarsTest/UnitTest)
add_subdirectory(testcode)
add_subdirectory(framework)

#-----------------------------------------------------------------------
set(WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
add_custom_target(run-unittest
        WORKING_DIRECTORY ${WORKING_DIRECTORY}
        COMMAND ${WORKING_DIRECTORY}/../unittest/script/run_test.sh 
        COMMENT "call run unittest")
