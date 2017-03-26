cmake_minimum_required(VERSION 2.8)
project( ImageMosaic )

# configure library for the common functions shared between executables
set(COMMON_DIR "common")
include_directories(${COMMON_DIR})
add_subdirectory(${COMMON_DIR})

# set up the image mosaic generator
set(IMOSAIC_SRC imosaic.cpp metafile.cpp queror.cpp)
find_package( OpenCV REQUIRED )
add_executable( ImageMosaic ${IMOSAIC_SRC} )
target_link_libraries( ImageMosaic ${OpenCV_LIBS} ${COMMON_DIR})

# configure preprocessor
set(PREPROC_DIR "preprocessor")
set(PREPROC_SRC ${PREPROC_DIR}/preprocessor.cpp)

# only build preprocessor if opencl is setup on device
add_executable(im_preproc ${PREPROC_SRC})
target_link_libraries(im_preproc ${OpenCV_LIBS} ${COMMON_DIR})
