# --- concurrency/CMakeLists.txt ---
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

qt_add_library(concurrency_lib STATIC
    Semaphore.h
    Semaphore.cpp
    ProducerConsumer.h
    ProducerConsumer.cpp
    ReadersWriters.h
    ReadersWriters.cpp
    SleepingBarber.h
    SleepingBarber.cpp
    SemaphoreDemo.h
    SemaphoreDemo.cpp
)

target_include_directories(concurrency_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(concurrency_lib PRIVATE Qt6::Core Qt6::Widgets)
