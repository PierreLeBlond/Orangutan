

	find_path(
	  nfd_INCLUDE_DIRS
	  NAMES nfd.h
	  PATHS /usr/include/
	)

	find_library(
	  nfd_LIBRARIES
	  NAMES libnfd.so
	  PATHS /usr/lib/
	)

	if (nfd_INCLUDE_DIRS AND nfd_LIBRARIES)
	  SET(nfd_FOUND TRUE)
	ENDIF (nfd_INCLUDE_DIRS AND nfd_LIBRARIES)

	if (nfd_FOUND)
	  if (NOT nfd_FIND_QUIETLY)
		message(STATUS "Found nfd library: ${nfd_LIBRARIES}")
	  endif (NOT nfd_FIND_QUIETLY)
	else (nfd_FOUND)
	  if (nfd_FIND_REQUIRED)
		message(FATAL_ERROR "Could not find nfd library")
	  endif (nfd_FIND_REQUIRED)
	endif (nfd_FOUND)
