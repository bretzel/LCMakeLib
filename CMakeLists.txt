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
    CMakeTemplate.c++
    FindCMakeTemplate.c++
)

FILE(GLOB LCMAKE_HDR
    Target.h
    CMakeTemplate.h
    FindCMakeTemplate.h
    File.h
)

FILE(GLOB LCMAKE_RESOURCES Resources/*)
message("Resources: " ${LCMAKE_RESOURCES} )

add_library(
    LCMakeLib
    SHARED
    ${LCMAKE_SRC}
)

target_link_libraries(LCMakeLib ${LUS_LIBRARY})

add_executable(LCMake.App main.c++)
target_link_libraries(LCMake.App LCMakeLib ${LUS_LIBRARY})


INSTALL(TARGETS LCMake.App LCMakeLib RUNTIME DESTINATION Libraries/LCMakeLib/Bin LIBRARY DESTINATION Libraries )

INSTALL(FILES ${LCMAKE_HDR} DESTINATION  Libraries/LCMakeLib/Include )
INSTALL(FILES FindLCMakeLib.cmake DESTINATION  ${CMAKE_MODULE_PATH} )
INSTALL(FILES ${LCMAKE_RESOURCES} DESTINATION Libraries/LCMakeLib/Resources)
