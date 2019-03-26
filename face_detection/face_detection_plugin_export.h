
#ifndef FACE_DETECTION_PLUGIN_EXPORT_H
#define FACE_DETECTION_PLUGIN_EXPORT_H

#ifdef FACE_DETECTION_PLUGIN_BUILD_AS_STATIC
#  define FACE_DETECTION_PLUGIN_EXPORT
#  define FACE_DETECTION_PLUGIN_NO_EXPORT
#else
#  ifndef FACE_DETECTION_PLUGIN_EXPORT
#    ifdef face_detection_plugin_EXPORTS
        /* We are building this library */
#      define FACE_DETECTION_PLUGIN_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define FACE_DETECTION_PLUGIN_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef FACE_DETECTION_PLUGIN_NO_EXPORT
#    define FACE_DETECTION_PLUGIN_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef FACE_DETECTION_PLUGIN_DEPRECATED
#  define FACE_DETECTION_PLUGIN_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef FACE_DETECTION_PLUGIN_DEPRECATED_EXPORT
#  define FACE_DETECTION_PLUGIN_DEPRECATED_EXPORT FACE_DETECTION_PLUGIN_EXPORT FACE_DETECTION_PLUGIN_DEPRECATED
#endif

#ifndef FACE_DETECTION_PLUGIN_DEPRECATED_NO_EXPORT
#  define FACE_DETECTION_PLUGIN_DEPRECATED_NO_EXPORT FACE_DETECTION_PLUGIN_NO_EXPORT FACE_DETECTION_PLUGIN_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef FACE_DETECTION_PLUGIN_NO_DEPRECATED
#    define FACE_DETECTION_PLUGIN_NO_DEPRECATED
#  endif
#endif

#endif