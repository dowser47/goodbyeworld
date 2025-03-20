# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\energy_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\energy_autogen.dir\\ParseCache.txt"
  "energy_autogen"
  )
endif()
