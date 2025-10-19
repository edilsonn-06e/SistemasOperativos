find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

qt_add_library(ui_lib STATIC
    GanttView.h GanttView.cpp
    MetricsView.h MetricsView.cpp
    ConcurrencyView.h ConcurrencyView.cpp
)

target_include_directories(ui_lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
           ${CMAKE_SOURCE_DIR}/concurrency
           ${CMAKE_SOURCE_DIR}/core
)

target_link_libraries(ui_lib PRIVATE Qt6::Core Qt6::Widgets concurrency_lib)
