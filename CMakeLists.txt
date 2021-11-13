cmake_minimum_required(VERSION 3.17)
project(CAL-Project)

# Build the Google tests
set(GRAPHVIEWER_PATH lib/GraphViewerCpp)
add_subdirectory(${GRAPHVIEWER_PATH})

include_directories(lib/GraphViewerCpp/include)

file(GLOB Proj_Files CONFIGURE_DEPENDS
        "*.cpp" "*.h"
        )

add_executable(Proj
        main.cpp
        ${Proj_Files}
        )

target_link_libraries(Proj graphviewer)
