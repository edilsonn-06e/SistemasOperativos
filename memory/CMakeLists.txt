
add_library(memory_lib
    PageTable.h PageTable.cpp
    TLB.h TLB.cpp
    ReplacementPolicy.h
    FIFO.h FIFO.cpp
    LRU.h LRU.cpp
    OPT.h OPT.cpp
)
target_include_directories(memory_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
