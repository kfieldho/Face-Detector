#
# CMake file for the arrows.ocv.face_detections
#

set( sources
  register_face_detection.cxx

  face_detection.cxx
  )

set( headers
  face_detection.h
  )

###
# Add our plugin path to the default list
include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

###
# Add path to face_detections so plugin loader can find them
kwiver_make_module_path( ${KWIVER_BINARY_DIR} ${kwiver_plugin_face_detection} )
kwiver_add_module_path( ${kwiver_module_path_result} )


###
# Add face_detection plugin
kwiver_add_plugin( kwiver_algo_ocv_face_detection
  SUBDIR       ${kwiver_plugin_face_detection}
  SOURCES      ${sources} ${headers}
  PRIVATE      kwiver_algo_ocv
               #kwiver_tools_face_detection
               kwiversys
)

