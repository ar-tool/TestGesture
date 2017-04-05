cmake_minimum_required(VERSION 3.4.1)

# now build app's shared lib
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

add_library(libHiarSi SHARED IMPORTED )
set_target_properties(libHiarSi PROPERTIES IMPORTED_LOCATION
    ${CMAKE_SOURCE_DIR}/../jniLibs/${ANDROID_ABI}/libHiarSi.so)

#add_library(libHeadCount SHARED IMPORTED )
#set_target_properties(libHeadCount PROPERTIES IMPORTED_LOCATION
#    ${CMAKE_SOURCE_DIR}/../jniLibs/${ANDROID_ABI}/libHeadCount.so)

#add_library(libutil SHARED IMPORTED )
#set_target_properties(libutil PROPERTIES IMPORTED_LOCATION
#    ${CMAKE_SOURCE_DIR}/../jniLibs/${ANDROID_ABI}/libutil.so)

add_library(libopencv_core SHARED IMPORTED )
set_target_properties(libopencv_core PROPERTIES IMPORTED_LOCATION
    ${CMAKE_SOURCE_DIR}/../jniLibs/${ANDROID_ABI}/libopencv_core.so)

add_library(libopencv_highgui SHARED IMPORTED )
set_target_properties(libopencv_highgui PROPERTIES IMPORTED_LOCATION
     ${CMAKE_SOURCE_DIR}/../jniLibs/${ANDROID_ABI}/libopencv_highgui.so)

add_library(libopencv_imgproc SHARED IMPORTED )
set_target_properties(libopencv_imgproc PROPERTIES IMPORTED_LOCATION
     ${CMAKE_SOURCE_DIR}/../jniLibs/${ANDROID_ABI}/libopencv_imgproc.so)

add_library(libopencv_objdetect SHARED IMPORTED )
set_target_properties(libopencv_objdetect PROPERTIES IMPORTED_LOCATION
     ${CMAKE_SOURCE_DIR}/../jniLibs/${ANDROID_ABI}/libopencv_objdetect.so)

add_library(libopencv_ml SHARED IMPORTED )
set_target_properties(libopencv_ml PROPERTIES IMPORTED_LOCATION
     ${CMAKE_SOURCE_DIR}/../jniLibs/${ANDROID_ABI}/libopencv_ml.so)

add_library(libtbb SHARED IMPORTED )
set_target_properties(libtbb PROPERTIES IMPORTED_LOCATION
     ${CMAKE_SOURCE_DIR}/../jniLibs/${ANDROID_ABI}/libtbb.so)

set(TRADITION_SRC tradition.cpp HiarSiFunction.cpp)
add_library(tradition SHARED ${TRADITION_SRC})

# add lib dependencies
target_link_libraries(tradition
                      android
                      log
                      EGL
                      GLESv2
                      libHiarSi
                      libopencv_objdetect
                      libopencv_core
                      libopencv_highgui
                      libopencv_imgproc
                      libopencv_ml
                      libtbb)

