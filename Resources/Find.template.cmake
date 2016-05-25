   # - Find %LibName library and includes
   # Find the %LibName includes and library
   # This module defines
   #  %Include, where to find %IncludeFile
   #  %Library, the library needed to use %LibFile.
   #  %Found, If false, do not try to use %Library.
   #
   # Copyright (c) %YEAR, %Author (%Alias), <%Email>
   #
   # Redistribution and use is allowed according to the terms of the BSD license.
   # For details see the accompanying COPYING-CMAKE-SCRIPTS file.

if(%Include AND %Library)
     set(%Found TRUE)

else(%Include AND %Library)

    find_file(%`LibName`_INCLUDE_DIR <Insert filename> ${HROOT}/Libraries/%LibName/include  /usr/include/%LibName/ /usr/local/include/%LibName/)
    message(STATUS ${%[LibName]_INCLUDE_DIR})
    find_library(%Library NAMES lib%`LibName`.so PATHS /usr/lib /usr/local/lib)

    message(STATUS ${%Library} ${%Include})

    if(%Include AND %LibName)
      set(%Found TRUE)
      message(STATUS "Found %LibName: ${%Include}, ${%LibName},  ${%LibName}")
    else(%Include AND %Library )
      set(%Found FALSE)
      message(FATAL_ERROR "%LibName not found.")
    endif(%Include AND %Library)

    mark_as_advanced(%Include %Library)

endif(%Include AND %Library)

