# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/SO_Suite_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/SO_Suite_autogen.dir/ParseCache.txt"
  "SO_Suite_autogen"
  )
endif()
