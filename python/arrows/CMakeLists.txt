kwiver_create_python_init(example)
kwiver_create_python_init(example/arrows)

kwiver_add_python_module(${CMAKE_CURRENT_SOURCE_DIR}/cascade_classifier.py
  example/arrows
  cascade_classifier)
