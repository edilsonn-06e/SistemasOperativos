add_library(core_lib
    Process.h
    Metrics.h
)

target_include_directories(core_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
