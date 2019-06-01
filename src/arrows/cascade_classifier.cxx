#include "cascade_classifier.h"
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
class cascade_classifier::priv
{
public:
  // -- CONSTRUCTORS --
  priv(){}

  ~priv(){}


  bool check_config(vital::config_block_sptr const &config,
                    vital::logger_handle_t const &logger) const
  {
    bool valid = true;
    return valid;
  }

  std::string m_classifier_file = "haarcascade_frontalface_default.xml";
  std::string m_classification_name = "FrontalFace";

}; // end class cascade_classifier::priv

// ==================================================================
cascade_classifier::cascade_classifier(): d( new priv ){ }

cascade_classifier::~cascade_classifier(){ }

// ------------------------------------------------------------------
vital::config_block_sptr
cascade_classifier::
get_configuration() const {
  LOG_DEBUG( logger(), "get_configuration called." );
  // Get base config from base class
  vital::config_block_sptr config = vital::algorithm::get_configuration();

  config->set_value( "classifier_file", d->m_classifier_file,
                     "Path of OpenCV CascadeClassifier classifier XML file such as haarcascade_frontalface_default.xml. "
                     "Typically found in share/OpenCV/haarcascades/ of the OpenCV install directory." );

  config->set_value( "classification_name", d->m_classification_name,
                     "The classification label that should used in the output detections for this classifier.  "
                     "Default is 'FrontalFace'" );

  return config;
}

// ------------------------------------------------------------------
void
cascade_classifier::
set_configuration(vital::config_block_sptr in_config)

{
  LOG_DEBUG( logger(), "set_configuration called." );
  vital::config_block_sptr config = this->get_configuration();
  config->merge_config(in_config);
  d->m_classifier_file         = config->get_value<std::string>( "classifier_file" );
  d->m_classification_name      = config->get_value<std::string>( "classification_name" );


}

// ------------------------------------------------------------------
bool cascade_classifier::
check_configuration(vital::config_block_sptr in_config) const
{
  LOG_DEBUG( logger(), "check_configuration called." );
  vital::config_block_sptr config = get_configuration();
  config->merge_config(in_config);
  return  d->check_config( config, logger() );
}

// ------------------------------------------------------------------
kwiver::vital::detected_object_set_sptr
cascade_classifier::
detect( vital::image_container_sptr image_data) const
{
  CascadeClassifier cascade;
  String cascade_path = d->m_classifier_file;
  auto detected_set = std::make_shared< kwiver::vital::detected_object_set>();
  using namespace kwiver::arrows::ocv;
  cv::Mat frame = image_container::vital_to_ocv( image_data->get_image(),
                                               image_container::RGB_COLOR );
  cv::Mat frame_gray;
  std::vector<Rect> classifications;

  LOG_DEBUG( logger(), "Attempting to load " << cascade_path );

  if(!cascade.load(cascade_path))
  {
    LOG_ERROR( logger(), "Failed to load " << cascade_path );
  }

  cvtColor( frame, frame_gray, cv::COLOR_RGB2GRAY );  // Convert frame to gray
  equalizeHist(frame_gray, frame_gray); //improve contrast of gray frame
  cascade.detectMultiScale(frame_gray, classifications);

  LOG_DEBUG( logger(), "Detected " << classifications.size() << " classifications." );

  // process results
  for ( size_t i = 0; i < classifications.size(); ++i )
  {

    // Bounding box is upper left corner(x, y), botton right corner (x, y)
    kwiver::vital::bounding_box_d bbox( classifications[i].x, classifications[i].y,
                                        classifications[i].x + classifications[i].width,
                                        classifications[i].y + classifications[i].height );

    auto dot = std::make_shared< kwiver::vital::detected_object_type >();
    dot->set_score( d->m_classification_name, 1.0 );

    detected_set->add( std::make_shared< kwiver::vital::detected_object >( bbox, 1.0, dot ) );
  } // end for

  return detected_set;
}

} } } // end namespace

