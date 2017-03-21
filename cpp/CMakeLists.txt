cmake_minimum_required(VERSION 2.8)
project( ImageMosaic )

find_package( OpenCV REQUIRED )
add_executable( ImageMosaic imosaic.cpp )
target_link_libraries( ImageMosaic ${OpenCV_LIBS} )

find_package(OpenCL)

# only build preprocessor if opencl is setup on device
if(OPENCL_FOUND)
  add_executable(im_preproc preprocessor.cpp util.cpp)
  target_link_libraries(im_preproc ${OpenCL_Libraries} ${OpenCV_LIBS})
endif(OPENCL_FOUND)
