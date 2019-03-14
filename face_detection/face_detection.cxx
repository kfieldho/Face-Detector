#include "face_detection.h"
#include <vector>
#include "opencv4/opencv2/objdetect.hpp"
#include "opencv4/opencv2/highgui.hpp"
#include "opencv4/opencv2/imgproc.hpp"
#include <iostream>
#include <arrows/ocv/image_container.h>
#include <opencv4/opencv2/core/core.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;

namespace kwiver {
namespace arrows {
namespace ocv {

// ----------------------------------------------------------------
class face_detection::priv
{
public:
  // -- CONSTRUCTORS --
  priv(){}

  ~priv(){}

}; // end class face_detection::priv

// ==================================================================
face_detection::face_detection(): d( new priv ){ }

face_detection::~face_detection(){ }

// ------------------------------------------------------------------
vital::config_block_sptr
face_detection::
get_configuration() const {
  // Get base config from base class
  vital::config_block_sptr config = vital::algorithm::get_configuration();
  return config;
}

// ------------------------------------------------------------------
void
face_detection::
set_configuration(vital::config_block_sptr config) {}

// ------------------------------------------------------------------
bool face_detection::
check_configuration(vital::config_block_sptr config) const { return true; }

// ------------------------------------------------------------------
kwiver::vital::detected_object_set_sptr
face_detection::
detect( vital::image_container_sptr image_data) const
{
  CascadeClassifier face_cascade;
  String face_cascade_path = "haarcascade_frontalface_alt.xml";
  auto detected_set = std::make_shared< kwiver::vital::detected_object_set>();
  using namespace kwiver::arrows::ocv;
  cv::Mat frame = image_container::vital_to_ocv( image_data->get_image(), 
                                               image_container::RGB_COLOR );
  cv::Mat frame_gray;
  std::vector<Rect> faces;

  if(!face_cascade.load(face_cascade_path)) cout << "Error loading face cascade.\n";

  cvtColor( frame, frame_gray, cv::COLOR_RGB2GRAY );  // Convert frame to gray
  equalizeHist(frame_gray, frame_gray); //improve contrast of gray frame
  face_cascade.detectMultiScale(frame_gray, faces);

  LOG_DEBUG( logger(), "Detected " << faces.size() << " people." );

  // process results
  for ( size_t i = 0; i < faces.size(); ++i )
  {

    // Bounding box is upper left corner(x, y), botton right corner (x, y)
    kwiver::vital::bounding_box_d bbox( faces[i].x, faces[i].y,
                                        faces[i].x + faces[i].width, faces[i].y + 										faces[i].height );

    auto dot = std::make_shared< kwiver::vital::detected_object_type >();
    dot->set_score( "face", 1.0 );

    detected_set->add( std::make_shared< kwiver::vital::detected_object >( bbox, 1.0, dot ) );
  } // end for

  return detected_set;
}

} } } // end namespace

