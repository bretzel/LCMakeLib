# my cmake `skeleton` for (my own) common little local projects that uses the gcc compilers's new 2011 features
# @2012,@2016 Serge Lussier (bretzelus@outlook.com)
#

SET(HROOT $ENV{HOME}/Applications)

add_definitions( -std=c++17 -Wall)
add_definitions( -Wno-write-strings )

set (CMAKE_MODULE_PATH ${HROOT}/CMakeModules)
set (CMAKE_INSTALL_PREFIX ${HROOT})

add_custom_target(uninstall
    "${CMAKE_COMMAND}" -P "${CMAKE_MODULE_PATH}/cmake_uninstall.cmake"
)


