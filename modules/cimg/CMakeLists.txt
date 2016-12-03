cmake_minimum_required(VERSION 2.8.8)
project(cimg_builder CXX)
include(ExternalProject)
find_package(Git REQUIRED)

ExternalProject_Add(
    cimg
    PREFIX ${CMAKE_BINARY_DIR}/cimg
    GIT_REPOSITORY https://github.com/dtschump/CImg.git
	GIT_TAG v.179
    TIMEOUT 10
    #UPDATE_COMMAND ${GIT_EXECUTABLE} fetch --tags
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
   )
   
# Expose required variable (CIMG_INCLUDE_DIR) to parent scope
ExternalProject_Get_Property(cimg source_dir)
set(CIMG_INCLUDE_DIR ${source_dir} CACHE INTERNAL "Path to include folder for CImg")