   # - Find %Name library and includes
   # Find the %Name includes and library
   # This module defines
   #  %'Name'_INCLUDE_DIR, where to find Include File
   #  %'Name'_LIBRARY, the library needed to use %Name.
   #  %'Name'_Found, If false, do not try to use %Name.
   #
   # Copyright (c) %YEAR, %Author (%Alias), <%Email> : In the master CMakeTemplate
   #
   # Redistribution and use is allowed according to the terms of the BSD license.
   # For details see the accompanying COPYING-CMAKE-SCRIPTS file.


#Name = Targetname = Templates  
#NAME ( TargetName converted in UPPPER CASE )

if(%'NAME'_INCLUDE_DIR AND %'NAME'_LIBRARY)
     set(%'NAME'_Found TRUE)

else(%'NAME'_INCLUDE_DIR AND %'NAME'_LIBRARY)

    find_file(%`NAME`_INCLUDE_DIR %Name.h PATHS ${HROOT}/Libraries/%Name/Include  /usr/include/%Name /usr/local/include/%Name)
    message(STATUS ${%'NAME'_INCLUDE_DIR})
    find_library(%'NAME'_LIBRARY NAMES lib%`Name`.so PATHS ${HROOT}/Libraries /usr/lib /usr/local/lib)

    message(STATUS ${%'NAME'_INCLUDE_DIR} ${%'NAME'_LIBRARY})

    if(%'NAME'_INCLUDE_DIR AND %'NAME'_LIBRARY)
      set(%'NAME'_Found TRUE)
      message(STATUS "Found %Name: ${%'NAME'_INCLUDE_DIR}, ${%'NAME'_LIBRARY}")
    else(%'NAME'_INCLUDE_DIR AND %'NAME'_LIBRARY)
      set(%'NAME'_Found FALSE)
      message(FATAL_ERROR "%Name not found.")
    endif(%'NAME'_INCLUDE_DIR AND %'NAME'_LIBRARY)

    mark_as_advanced(%'NAME'_INCLUDE_DIR %'NAME'_LIBRARY)

endif(%'NAME'_INCLUDE_DIR AND %'NAME'_LIBRARY)

