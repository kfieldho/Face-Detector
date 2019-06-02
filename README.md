# Face Detection #

This project demonstrates a face detector based on KWIVER using the [Haar Cascade classifier](https://docs.opencv.org/2.4/modules/objdetect/doc/cascade_classification.html). Specifically, this project uses the [frontal face classifier](haarcascade_frontalface_alt.xml). The detector is demonstrated in two languages, C++ and Python. The C++ example implements a [detection arrow](https://github.com/Kitware/kwiver/blob/master/doc/manuals/arrows/opencv.rst) that offers both image and video options. The Python example is a KWIVER process. 

Test Code Snippet:

https://raw.githubusercontent.com/kfieldho/Face-Detector/master/CMakeLists.txt#L7-L9

https://github.com/kfieldho/Face-Detector/blob/e0675b12bbb564b0ed246d7d58e5a97654e07d23/CMakeLists.txt#L7-L9

# Organization #

File Name                             |  Description
--------------------------------------|------------------------------------------------------------------------------------------
[face_detection.pipe](https://github.com/hdefazio/face_detection/blob/master/image/face_detection.pipe) | Sprokit pipeline file that runs the face detector on a list of input images
[face_detection_images.txt](https://github.com/hdefazio/face_detection/blob/master/image/face_detection_images.txt) | Text file that lists the input images' locations 
[face_detection.cxx](https://github.com/hdefazio/face_detection/blob/master/image/face_detection.cxx) | Face detector written in C++
[face_detection.h](https://github.com/hdefazio/face_detection/blob/master/image/face_detection.h) | Face detector header file written in C++
[CMakeLists.txt (C++)](https://github.com/hdefazio/face_detection/blob/master/image/CMakeLists.txt) | Face detector source and header files added
[images](https://github.com/hdefazio/face_detection/blob/master/image/images) | Directory where the sample images are stored 
[videos](https://github.com/hdefazio/face_detection/blob/master/video/videos) | Directory where the sample videos are stored
[haarcascade_frontalface_alt.xml](https://github.com/hdefazio/face_detection/blob/master/haarcascade_frontalface_alt.xml) | The Haarcascade classifier used
[face_detection_video.pipe](https://github.com/hdefazio/face_detection/blob/master/video/face_detection_video.pipe) | Sprokit pipeline file that runs the face detector on a video
[faceDetection.py](https://github.com/hdefazio/face_detection/blob/master/python/faceDetection.py) | Face detector written in Python
[face_detection_python.pipe](https://github.com/hdefazio/face_detection/blob/master/python/face_detection_python.pipe) | Sprokit pipeline file that runs the python face detector on a list of input images
[CMakeLists.txt (Python)](https://github.com/hdefazio/face_detection/blob/master/python/CMakeLists.txt) | Face detector source file added
 

# Building #
  In a bash terminal in the project directory::
  
    cmake .
  
  
    make -j7
  
# Running #

## C++ ##

  To use an image, in <path/to/kwiver/build>/release/bin::
  
    ./pipeline_runner -p ../examples/pipelines/face_detection.pipe
  
  After it has finished running, the annotated image will be in ../release/examples/pipelines/output

---------------------------------------------------------------------------------------------------------------------
  
  To use a video, in <path/to/kwiver/build>/release/bin::
  
    ./pipeline_runner -p ../examples/pipelines/face_detection_video.pipe 
  
  After it has finished running, the annotated frames will be in ../release/examples/pipelines/face_detection_output

## Python ##

  In <path/to/kwiver/build>/release/bin::
  
    ./pipeline_runner -p ../examples/pipelines/face_detection_python.pipe
  
  After it has finished running, the annotated image will be in ../release/examples/pipelines/output
