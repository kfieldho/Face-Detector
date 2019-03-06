#ifndef ARROWS_OCV_FACE_DETECTOR_H
#define ARROWS_OCV_FACE_DETECTOR_H

#include <arrows/ocv/kwiver_algo_ocv_export.h>

#include <vital/algo/image_object_detector.h>

namespace kwiver {
namespace arrows {
namespace ocv {

class KWIVER_ALGO_OCV_EXPORT face_detection
  : public vital::algorithm_impl< face_detection, vital::algo::image_object_detector>
{
public:
  face_detection();
  virtual ~face_detection();

  virtual vital::config_block_sptr get_configuration() const;
  virtual void set_configuration(vital::config_block_sptr config);
  virtual bool check_configuration(vital::config_block_sptr config) const;

  // Main detection method
  virtual vital::detected_object_set_sptr detect( vital::image_container_sptr image_data) const;

private:
  class priv;
  const std::unique_ptr<priv> d;
};

} } } // end namespace

#endif /* ARROWS_OCV_FACE_DETECTOR_H */
