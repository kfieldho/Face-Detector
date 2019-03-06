from __future__ import print_function
from sprokit.pipeline import process
from kwiver.kwiver_process import KwiverProcess
#from vital.types import Image
#from vital.types import ImageContainer
from vital.util.VitalPIL import from_pil, get_pil_image
from vital.types import DetectedObjectSet, BoundingBox, DetectedObject, DetectedObjectType
import numpy as np
import cv2

class faceDetection(KwiverProcess):
    # ----------------------------------------------
    def __init__(self, conf):
        KwiverProcess.__init__(self, conf)

        self.add_config_trait("output", "output", '.',
                              'The path of the file to output to.')

        self.declare_config_using_trait( 'output' )

        self.add_port_trait( 'detected_object_set', 'detected_object_set', '.' )

        # set up required flags
        optional = process.PortFlags()
        required = process.PortFlags()
        required.add(self.flag_required)

        #  declare our input port ( port-name,flags)
        self.declare_input_port_using_trait('image', required)

        self.declare_output_port_using_trait('detected_object_set', required )

    # ----------------------------------------------
    def _configure(self):
        print("[DEBUG] ----- configure")
        path = self.config_value('output')

        self._base_configure()

    # ----------------------------------------------
    def _step(self):
        print("[DEBUG] ----- start step")
        
	face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_alt.xml')
	# grab image container from port using traits
        frame_c = self.grab_input_using_trait('image')
	# Get image from container
        frame_in = frame_c.image()
	#convert generic image to PIL
	pil_image = get_pil_image(frame_in)
	#convert to matrix
	frame = np.array(pil_image)

	detected_set = DetectedObjectSet()
	gray_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
	gray_frame = cv2.equalizeHist(gray_frame)
	faces = face_cascade.detectMultiScale(gray_frame, 1.3, 5)
	for (x, y, w, h) in faces:
		bbox = BoundingBox(x, y, x+w, y+h)
	
		# get new image handle
        	#new_ic = ImageContainer( frame )
		dot = DetectedObjectType("face", 1.0)
		detected_set.add(DetectedObject(bbox, 1.0, dot))
        # push object to output port
        self.push_to_port_using_trait( 'detected_object_set', detected_set )

        self._base_step()

# ==================================================================
def __sprokit_register__():
    from sprokit.pipeline import process_factory

    module_name = 'python:kwiver.faceDetection'

    if process_factory.is_process_module_loaded(module_name):
        return

    process_factory.add_process('faceDetection', 'face detection', faceDetection)

    process_factory.mark_process_module_as_loaded(module_name)
