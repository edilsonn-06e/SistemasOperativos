
add_library(scheduler_lib
    Scheduler.h
    FCFS.h FCFS.cpp
    SJF.h SJF.cpp
    SRTF.h SRTF.cpp
    RR.h RR.cpp
    PRIORITY.h PRIORITY.cpp
)
target_include_directories(scheduler_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/core)
