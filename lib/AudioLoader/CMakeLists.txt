add_library(audioloader WavLoader.cpp)
target_include_directories(audioloader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
