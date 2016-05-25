   # - Find LCMakeLib library and includes
   # Find the LCMakeLib includes and library
   # This module defines
   #  LCMAKELIB_INCLUDE_DIR, where to find LCMakeLib.h
   #  LCMAKELIB_LIBRARY, the library needed to use LCMakeLib.
   #  LCMAKELIB_FOUND, If false, do not try to use LCMakeLib.
   #
   # Copyright (c) 2010;2016, Serge Lussier, <lussier.serge@gmail.com>
   #
   # Redistribution and use is allowed according to the terms of the BSD license.
   # For details see the accompanying COPYING-CMAKE-SCRIPTS file.

if(LCMAKELIB_INCLUDE_DIR AND LCMAKELIB_LIBRARY)# AND LCMAKELIB_STATIC_LIB)
     set(LCMAKELIB_FOUND TRUE)

else(LCMAKELIB_INCLUDE_DIR AND LCMAKELIB_LIBRARY)# AND LCMAKELIB_STATIC_LIB)

    find_path(LCMAKELIB_INCLUDE_DIR NAMES LObject.h PATHS ${HROOT}/Libraries/LCMakeLib/Include /usr/include/LCMakeLib/ /usr/local/include)
    message(STATUS ${LCMAKELIB_INCLUDE_DIR})

 
    find_library(LCMAKELIB_LIBRARY NAMES libLCMakeLib.so PATHS ${HROOT}/Libraries /usr/lib /usr/local/lib)
 
    message(STATUS ${LCMAKELIB_LIBRARY} ${LCMAKELIB_STATIC_LIB})

    if(LCMAKELIB_INCLUDE_DIR AND LCMAKELIB_LIBRARY)# AND LCMAKELIB_STATIC_LIB)
      set(LCMAKELIB_FOUND TRUE)
      message(STATUS "Found LCMakeLib: ${LCMAKELIB_INCLUDE_DIR}, ${LCMAKELIB_LIBRARY},  ${LCMAKELIB_STATIC_LIB}")
    else(LCMAKELIB_INCLUDE_DIR AND LCMAKELIB_LIBRARY ) # AND LCMAKELIB_STATIC_LIB)
      set(LCMAKELIB_FOUND FALSE)
      message(FATAL_ERROR "LCMakeLib not found.")
    endif(LCMAKELIB_INCLUDE_DIR AND LCMAKELIB_LIBRARY)# AND LCMAKELIB_STATIC_LIB)

    mark_as_advanced(LCMAKELIB_INCLUDE_DIR LCMAKELIB_LIBRARY)# LCMAKELIB_STATIC_LIB)

endif(LCMAKELIB_INCLUDE_DIR AND LCMAKELIB_LIBRARY)# AND LCMAKELIB_STATIC_LIB)
