#
# CMake file for the arrows.ocv.cascade_classifier
#
cmake_minimum_required(VERSION 3.3)

# The name of this KWIVER Package
set( kwiver_plugin_cascade_classifier "kwiver_cascade_classifier" )


link_directories("${KWIVER_LIBRARY_DIRS}")

set( sources
  register_cascade_classifier.cxx
  cascade_classifier.cxx
  )

set( headers
  cascade_classifier.h
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
kwiver_make_module_path( ${CMAKE_BINARY_DIR} ${kwiver_plugin_cascade_classifier} )
kwiver_add_module_path( ${kwiver_module_path_result} )

###
# Create the  Face Detection Plugin
kwiver_add_plugin( kwiver_algo_ocv_cascade_classifier
  SUBDIR       ${kwiver_plugin_cascade_classifier}
  SOURCES      ${sources} ${headers}
  PRIVATE      kwiver_algo_ocv
               ${KWIVER_LIBRARIES}
               ${OpenCV_LIBS}
)

