#
# CMake file for the arrows.ocv.face_detections
#
cmake_minimum_required(VERSION 3.3)

# The name of this KWIVER Package
set( kwiver_plugin_face_detection "kwiver_face_detection" )

#
# We'll use fletch to get our 3rd party dependencies (like OpenCV),
# KWIVER, and OpenCV
#
find_package(fletch REQUIRED)
find_package(kwiver REQUIRED)
find_package(OpenCV REQUIRED)

link_directories("${KWIVER_LIBRARY_DIRS}")

# Utilties that make it easy to cmake KWIVER components
include(kwiver-utils)

# Compiler flag settings used by KWIVER
include(kwiver-flags)

# Check to be sure that the compiler supports features required by KWIVEr
include(kwiver-configcheck)

set( sources
  register_face_detection.cxx
  face_detection.cxx
  )

set( headers
  face_detection.h
  )

#
# We'll treat KWIVER as a System Component
#
include_directories( SYSTEM ${KWIVER_INCLUDE_DIRS} )

#
# Make sure we can find our own include files
#
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} )

###
# Create and use a Plugin Path for this package
kwiver_make_module_path( ${CMAKE_BINARY_DIR} ${kwiver_plugin_face_detection} )
kwiver_add_module_path( ${kwiver_module_path_result} )

###
# Create the  Face Detection Plugin
kwiver_add_plugin( kwiver_algo_ocv_face_detection
  SUBDIR       ${kwiver_plugin_face_detection}
  SOURCES      ${sources} ${headers}
  PRIVATE      kwiver_algo_ocv
               ${KWIVER_LIBRARIES}
               ${OpenCV_LIBS}
)

