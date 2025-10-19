# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\SO_Suite_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\SO_Suite_autogen.dir\\ParseCache.txt"
  "SO_Suite_autogen"
  "concurrency\\CMakeFiles\\concurrency_lib_autogen.dir\\AutogenUsed.txt"
  "concurrency\\CMakeFiles\\concurrency_lib_autogen.dir\\ParseCache.txt"
  "concurrency\\concurrency_lib_autogen"
  "core\\CMakeFiles\\core_lib_autogen.dir\\AutogenUsed.txt"
  "core\\CMakeFiles\\core_lib_autogen.dir\\ParseCache.txt"
  "core\\core_lib_autogen"
  "memory\\CMakeFiles\\memory_lib_autogen.dir\\AutogenUsed.txt"
  "memory\\CMakeFiles\\memory_lib_autogen.dir\\ParseCache.txt"
  "memory\\memory_lib_autogen"
  "scheduler\\CMakeFiles\\scheduler_lib_autogen.dir\\AutogenUsed.txt"
  "scheduler\\CMakeFiles\\scheduler_lib_autogen.dir\\ParseCache.txt"
  "scheduler\\scheduler_lib_autogen"
  "ui\\CMakeFiles\\ui_lib_autogen.dir\\AutogenUsed.txt"
  "ui\\CMakeFiles\\ui_lib_autogen.dir\\ParseCache.txt"
  "ui\\ui_lib_autogen"
  )
endif()
