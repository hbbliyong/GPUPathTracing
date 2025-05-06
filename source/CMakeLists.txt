set(LIBRARY_NAME CPUPathTracing)

file(GLOB_RECURSE HEADER_FILES CONFIG_DEPENDS include/*.h*)
file(GLOB_RECURSE SOURCE_FILES CONFIG_DEPENDS src/*.c*)

add_executable(${LIBRARY_NAME} ${HEADER_FILES} ${SOURCE_FILES})

target_include_directories(${LIBRARY_NAME} PUBLIC include)

target_link_libraries(${LIBRARY_NAME} PRIVATE glm)