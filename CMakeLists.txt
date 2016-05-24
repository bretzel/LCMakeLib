project (LCMake)

CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

include(setup_env.cmake)

find_package(Lus REQUIRED)
    

INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR} ${LUS_INCLUDE_DIR})


message("PREFIX:" ${CMAKE_INSTALL_PREFIX})
message("MODULES:" ${CMAKE_MODULE_PATH})

FILE(GLOB LCMAKE_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.c++)

add_executable(LCMake.app ${LCMAKE_SRC})

target_link_libraries(LCMake.app ${LUS_LIBRARY})

INSTALL(TARGETS LCMake.app RUNTIME DESTINATION LCMake.app/Bin )
#INSTALL(FILES ${LUS_HDR} DESTINATION  Libraries/Lus/Include )
