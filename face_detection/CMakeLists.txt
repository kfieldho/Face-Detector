cmake_minimum_required(VERSION 3.10)

project(face_detection)

find_package( kwiver REQUIRED )
include_directories( ${KWIVER_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR})
message(${KWIVER_INCLUDE_DIRS})
include( kwiver-utils )
link_directories( ${KWIVER_LIBRARY_DIR} )
list( INSERT CMAKE_MODULE_PATH  0         "${KWIVER_CMAKE_DIR}" )

if( IS_DIRECTORY ${fletch_DIR} )
  find_package( fletch NO_MODULE )
  list( APPEND CMAKE_PREFIX_PATH  "${fletch_DIR}" )
endif()

set( sources
  register_face_detection.cxx

  face_detection.cxx
  )

set( headers
  face_detection.h
  )

kwiver_add_library(face_detection
${headers}
${sources}
)

target_link_libraries(face_detection
PUBLIC		vital_algo
		kwiver_algo_ocv
		kwiver_algo_core
		${OpenCV_LIBS}
PRIVATE		${KWIVER_LIBRARIES}
		kwiversys
)

algorithms_create_plugin(face_detection
  register_face_detection.cxx
  )

