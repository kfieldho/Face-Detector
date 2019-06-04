# ckwg +29
# Copyright 2019 by Kitware, Inc.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
#  * Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer.
#
#  * Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
#  * Neither name of Kitware, Inc. nor the names of any contributors may be used
#    to endorse or promote products derived from this software without specific
#    prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
from __future__ import print_function
from vital.algo import ImageObjectDetector
from vital.types import DetectedObjectSet, DetectedObject, BoundingBox, DetectedObjectType
import cv2
import numpy as np
import os

class CascadeClassifier(ImageObjectDetector):
    """
    Implementation of ImageObjectDetector that uses opencv implementation of
    haar cascade classifier to detect faces in an image
    """
    def __init__(self):
        ImageObjectDetector.__init__(self)
        self.classifier_file = ""
        self.scale_factor = 1.1
        self.min_neighbor = 3
        self.face_cascade = None

    def get_configuration(self):
        # Inherit from the base class
        cfg = super(ImageObjectDetector, self).get_configuration()
        cfg.set_value( "classifier_file", self.classifier_file )
        cfg.set_value( "scale_factor", str(self.scale_factor) )
        cfg.set_value( "min_neighbor", str(self.min_neighbor) )
        return cfg

    def set_configuration( self, cfg_in ):
        cfg = self.get_configuration()
        cfg.merge_config(cfg_in)
        self.classifier_file = cfg.get_value( "classifier_file" )
        self.scale_factor = float(cfg.get_value( "scale_factor" ))
        self.min_neighbor = int(cfg.get_value( "min_neighbor" ))

    def check_configuration( self, cfg):
        #TODO: Check validity of scale factor and min_neigbor
        if not cfg.has_value("classifier_file"):
            return False
        elif cfg.has_value("classifier_file") and \
                not os.path.exists(cfg.get_value("classifier_file")):
            return False
        else:
            return True

    def detect(self, image_c):
	cascade_classifier = cv2.CascadeClassifier(self.classifier_file)
        image = image_c.image().asarray().astype(np.uint8)
	detected_object_set = DetectedObjectSet()
        # NOTE: assarray() function return an rgb representation of the image
	gray_image = cv2.cvtColor(image, cv2.COLOR_RGB2GRAY)
	gray_image = cv2.equalizeHist(gray_image)
	faces = cascade_classifier.detectMultiScale(gray_image, self.scale_factor,
                                                self.min_neighbor)

	for (x, y, w, h) in faces:
            bbox = BoundingBox(x, y, x+w, y+h)
            dot = DetectedObjectType("face", 1.0)
            detected_object_set.add(DetectedObject(bbox, 1.0, dot))
        return detected_object_set

def __vital_algorithm_register__():
    from vital.algo import algorithm_factory
    # Register Algorithm
    implementation_name  = "CascadeClassifier"
    if algorithm_factory.has_algorithm_impl_name(
                                CascadeClassifier.static_type_name(),
                                implementation_name):
        return
    algorithm_factory.add_algorithm( implementation_name,
                                "Opencv implementation of Haar cascade classifier",
                                 CascadeClassifier )
    algorithm_factory.mark_algorithm_as_loaded( implementation_name )
