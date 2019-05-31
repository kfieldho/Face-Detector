#include "face_detection.h"
#include <vector>
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <kwiversys/SystemTools.hxx>
#include <iostream>
#include <arrows/ocv/image_container.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

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


  bool check_config(vital::config_block_sptr const &config,
                    vital::logger_handle_t const &logger) const
  {
    bool valid = true;

		if( !kwiversys::SystemTools::FileExists(m_classifier_file) )
		{
			LOG_ERROR( logger, "Specified classifier_file, " << m_classifier_file << ", does not exist" );
			return( false );
	  }
    return valid;
  }

	std::string m_classifier_file = "haarcascade_frontalface_default.xml";
	std::string m_classification_name = "Face";

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

  config->set_value( "classifier_file", d->m_classifier_file,
                     "Path of OpenCV CascadeClassifier classifier XML file such as haarcascade_frontalface_default.xml. "
                     "Typically found in share/OpenCV/haarcascades/ of the OpenCV install directory." );

  config->set_value( "classification_name", d->m_classification_name,
                     "The classification label that should used in the output detections for this classifier.  "
                     "Default is 'face'" );

  return config;
}

// ------------------------------------------------------------------
void
face_detection::
set_configuration(vital::config_block_sptr in_config)

{
  vital::config_block_sptr config = this->get_configuration();
  config->merge_config(in_config);
  d->m_classifier_file         = config->get_value<std::string>( "classifier_file" );
  d->m_classification_name      = config->get_value<std::string>( "classification_name" );
}

// ------------------------------------------------------------------
bool face_detection::
check_configuration(vital::config_block_sptr in_config) const
{
  LOG_DEBUG( logger(), "CHECK CONFIGURATION CALLED" );
  vital::config_block_sptr config = get_configuration();
  config->merge_config(in_config);
  return  d->check_config( config, logger() );
}

// ------------------------------------------------------------------
kwiver::vital::detected_object_set_sptr
face_detection::
detect( vital::image_container_sptr image_data) const
{
  CascadeClassifier face_cascade;
  String face_cascade_path = d->m_classifier_file;
  auto detected_set = std::make_shared< kwiver::vital::detected_object_set>();
  using namespace kwiver::arrows::ocv;
  cv::Mat frame = image_container::vital_to_ocv( image_data->get_image(),
                                               image_container::RGB_COLOR );
  cv::Mat frame_gray;
  std::vector<Rect> faces;

  LOG_DEBUG( logger(), "Attempting to load " << face_cascade_path );
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
    dot->set_score( d->m_classification_name, 1.0 );

    detected_set->add( std::make_shared< kwiver::vital::detected_object >( bbox, 1.0, dot ) );
  } // end for

  return detected_set;
}

} } } // end namespace

