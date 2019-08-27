#
# CMakeLists.txt for KWIVER Use Case repository
#
cmake_minimum_required(VERSION 3.3)

# Use CMake's ExternalData
include(ExternalData)

set(DATA_KITWARE_COM "https://data.kitware.com/api/v1/file/hashsum/")

list(APPEND ExternalData_URL_TEMPLATES
  "${DATA_KITWARE_COM}/%(algo)/%(hash)/download"
  )

ExternalData_Expand_Arguments(external_data
  faces_mp4
  DATA{data/faces.mp4}
)

ExternalData_Add_Target(external_data)

#
# We'll use fletch to get our 3rd party dependencies (like OpenCV),
# KWIVER, and OpenCV
#
find_package(fletch REQUIRED)
find_package(kwiver REQUIRED)
find_package(OpenCV REQUIRED)

# Utilties that make it easy to cmake KWIVER components
include(kwiver-utils)
include(kwiver-setup-python)
# Compiler flag settings used by KWIVER
include(kwiver-flags)

# Check to be sure that the compiler supports features required by KWIVER
include(kwiver-configcheck)
set(kwiver_python_output_path "${CMAKE_BINARY_DIR}/lib/${kwiver_python_subdir}")

add_subdirectory(python)
add_subdirectory(src)

configure_file( ${CMAKE_SOURCE_DIR}/pipelines/cascade_classifier_video.pipe.in
                ${CMAKE_BINARY_DIR}/pipelines/cascade_classifier_video.pipe @ONLY )
configure_file( ${CMAKE_SOURCE_DIR}/pipelines/py_cascade_classifier_video.pipe.in
                ${CMAKE_BINARY_DIR}/pipelines/py_cascade_classifier_video.pipe @ONLY )
configure_file(${CMAKE_SOURCE_DIR}/setup_cascade_classifier.sh.in
               ${CMAKE_BINARY_DIR}/setup_cascade_classifier.sh
               @ONLY)
