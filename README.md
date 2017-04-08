# MKBCV-Final
McKay-Bonada final project for Computer Vision course at UOIT.

# Project
This is a project using openCV and openMP to create image mosaics.

## Drivers
ImageMosaic
  The main program that takes a bank directory and an image to make a mosaic.

Trackbar
  This is a demo with a slidebar. I believe it's expecting a file called 'download.jpg' in the root directory up here though...

## Image Mosaic
Mosaics are a form of art where larger images are built from many smaller images. We wrote a script to preprocess images to bins so that they are quicker to lookup. The script takes the HSV of an image, constructs a histogram of the hue values, and places the image into the folder representing the range of hue that it falls into. Preprocessor previously only “sorted” images into bins
Now we also create an index for each hue bin called a metafile which contains pre-computed feature vectors for substitute images.
This way we can load images as they are needed (the previous implementation was much more naive than this)

Now that potential images are reduced to feature vectors, we utilize nearest neighbour lookup when querying substitute tiles using the FLANN library.

Our program is divided into two parts, the first being the producer. The producer analyzes subregions of the source images and performs the lookup. It then pushes onto a queue the file path to the substitute tile as well as some extra parameters (namely location of substitution). The second part is the consumer. The consumer goes through the queue, loads the tile from file and places it into the resulting image at the location specified. The purpose of splitting up the work here is to separate the fast work (producing the file names) from the slow work (loading files from disk)

Similar regions likely map to similar tiles. To forgo unnecessary reads from disk (which is tremendously slow), we keep tiles in memory to use later using a hashmap. When tested on an image with 1600x1200 resolution, generation time went from around 30 seconds to within 1-2 seconds.

## Dependencies
Requires OpenCV 3.x, cmake,and a compiler which supports C++11 and OpenMP

### Build Instructions
In a terminal:
navigate to `cpp/`

`mkdir build`

`cd build/`

`cmake ..`

`make`
