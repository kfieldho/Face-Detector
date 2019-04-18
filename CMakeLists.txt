#
# CMakeLists.txt for KWIVER Use Case repository
#
cmake_minimum_required(VERSION 3.3)
add_subdirectory(src)

configure_file(${CMAKE_SOURCE_DIR}/setup_face_detection.sh.in
               ${CMAKE_BINARY_DIR}/setup_face_detection.sh
               @ONLY)
