


project(VSOMEIP_SIMULATOR)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_BUILD_TYPE Debug)

# to update clang database.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include/configuration/
    ${CMAKE_SOURCE_DIR}/ExternalLibraries/json/include/
    ${CMAKE_SOURCE_DIR}/include/interfaces/
    ${CMAKE_SOURCE_DIR}/include/utilities/
    ${CMAKE_SOURCE_DIR}/include/app_manager/
    ${CMAKE_SOURCE_DIR}/include/apps_simulator/
    ${CMAKE_SOURCE_DIR}/include/simulator/
    ${Boost_INCLUDE_DIR}
    ${VSOMEIP_INCLUDE_DIRS}
)


# Source files
set(SOURCES
    src/simulator/Simulator.cpp
    src/main.cpp
    src/utilities/Json.cpp
    src/utilities/FileHandler.cpp
    src/configuration/ConfigurationAdapter.cpp
    src/apps_simulator/App.cpp
    
)

# Executable
add_executable(VSOMEIP_SIMULATOR ${SOURCES})
target_link_libraries(VSOMEIP_SIMULATOR libvsomeip3-sd.so.3.3.8 vsomeip3 ${Boost_LIBRARIES})
