cmake_minimum_required(VERSION 2.8)
project( ImageMosaic )

# configure library for the common functions shared between executables
set(COMMON_DIR "common")
include_directories(${COMMON_DIR})
add_subdirectory(${COMMON_DIR})

# set up the trackbar demo
set(IMOSAIC_SRC trackbar.cpp mosaicbuilder.cpp)
find_package( OpenCV REQUIRED )
add_executable( Trackbar ${IMOSAIC_SRC} )
target_link_libraries( Trackbar ${OpenCV_LIBS} ${COMMON_DIR})
set_property(TARGET Trackbar PROPERTY CXX_STANDARD 11)

# configure preprocessor
set(PREPROC_DIR "preprocessor")
set(PREPROC_SRC ${PREPROC_DIR}/preprocessor.cpp)


# only build preprocessor if opencl is setup on device
add_executable(im_preproc ${PREPROC_SRC})
target_link_libraries(im_preproc ${OpenCV_LIBS} ${COMMON_DIR})
