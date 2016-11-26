find_package(cpplocate REQUIRED)

project("minesweeper_sweeper" CXX)

# ---------------	METADATA

set(META_PROJECT_NAME ${PROJECT_NAME})
set(META_PROJECT_NAMESPACE ${META_PROJECT_NAME})
set(META_PROJECT_VERSION_MAJOR 0)
set(META_PROJECT_VERSION_MINOR 1)
set(META_BINARY_NAME ${META_PROJECT_NAME})
set(META_BINARY_PATH ${CMAKE_BINARY_DIR})

# ---------------	GROUP FILES

file(GLOB_RECURSE sources *.cpp *.hpp *.h)
file(GLOB_RECURSE resources resources/*)
source_group(Resources FILES ${resources})

# ---------------	BUILD

add_executable(${PROJECT_NAME} 
	${sources} 
	${resources}
)
# On build, copy resource-files to output folder
add_custom_command(TARGET ${PROJECT_NAME} 
	POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${PROJECT_SOURCE_DIR}/resources"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)

# ---------------	CONFIGURE

configure_file(
    ${PROJECT_SOURCE_DIR}/config/config.h.in
    ${PROJECT_BINARY_DIR}/config/config.h
)
configure_file(
    ${PROJECT_SOURCE_DIR}/config/resources.h.in
    ${PROJECT_BINARY_DIR}/config/resources.h
)

# ---------------	INCLUDE DIRECTORIES

target_include_directories(${PROJECT_NAME}
	PRIVATE
	${PROJECT_BINARY_DIR}/config
	${MAIN_PROJECT_DIR}
)

# ---------------	LINKING

target_link_libraries(${PROJECT_NAME} 
	PRIVATE
	${MAIN_PROJECT_NAME}
	cpplocate
)