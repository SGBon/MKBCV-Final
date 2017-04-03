cmake_minimum_required(VERSION 2.8)
project( ImageMosaic )

# configure library for the common functions shared between executables
set(COMMON_DIR "common")
include_directories(${COMMON_DIR})
add_subdirectory(${COMMON_DIR})

# set up the trackbar demo
set(TRACKBAR_SRC trackbar.cpp mosaictiler.cpp mosaicsplitter.cpp)
find_package( OpenCV REQUIRED )
add_executable( Trackbar ${TRACKBAR_SRC} )
target_link_libraries( Trackbar ${OpenCV_LIBS} ${COMMON_DIR})
set_property(TARGET Trackbar PROPERTY CXX_STANDARD 11)

############ Mosaic Generator
# set up the image mosaic generator
set(IMOSAIC_SRC imosaic.cpp metafile.cpp queror.cpp procon.cpp mosaictiler.cpp mosaicsplitter.cpp)
find_package(OpenCV REQUIRED)
find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()
add_executable( ImageMosaic ${IMOSAIC_SRC} )
target_link_libraries( ImageMosaic ${OpenCV_LIBS} ${COMMON_DIR})
set_property(TARGET ImageMosaic PROPERTY CXX_STANDARD 11)

########### preprocessor
# configure preprocessor
set(PREPROC_DIR "preprocessor")
set(PREPROC_SRC ${PREPROC_DIR}/preprocessor.cpp)


# only build preprocessor if opencl is setup on device
add_executable(im_preproc ${PREPROC_SRC})
target_link_libraries(im_preproc ${OpenCV_LIBS} ${COMMON_DIR})
set_property(TARGET im_preproc PROPERTY CXX_STANDARD 11)

########## tests
set(METATEST_SRC test/metafiletest.cpp metafile.cpp queror.cpp)
add_executable(MetafileTest ${METATEST_SRC})
target_link_libraries(MetafileTest ${OpenCV_LIBS} ${COMMON_DIR})
set_property(TARGET MetafileTest PROPERTY CXX_STANDARD 11)

set(QUERORTEST_SRC test/querortest.cpp metafile.cpp queror.cpp)
add_executable(QuerorTest ${QUERORTEST_SRC})
target_link_libraries(QuerorTest ${OpenCV_LIBS} ${COMMON_DIR})
set_property(TARGET QuerorTest PROPERTY CXX_STANDARD 11)
