project (LCMake)

CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

include(setup_env.cmake)

find_package(Lus REQUIRED)
    

INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR} ${LUS_INCLUDE_DIR})


message("PREFIX:" ${CMAKE_INSTALL_PREFIX})
message("MODULES:" ${CMAKE_MODULE_PATH})




FILE(GLOB LCMAKE_SRC

    File.c++
    Target.c++
    Master.c++
)

FILE(GLOB LCMAKE_HDR
    Target.h
    Master.h
    File.h
)


add_library(
    LCMakeLib
    SHARED
    ${LCMAKE_SRC}
)

target_link_libraries(LCMakeLib ${LUS_LIBRARY})

add_executable(LCMake.App main.c++)
target_link_libraries(LCMake.App ${LUS_LIBRARY})


INSTALL(TARGETS LCMake.App RUNTIME DESTINATION Libraries/LCMakeLib/Bin )

INSTALL(FILES ${LCMAKE_HDR} DESTINATION  Libraries/LCMakeLib/Include )
INSTALL(FILES FindLCMakeLib.cmake DESTINATION  ${CMAKE_MODULE_PATH} )
