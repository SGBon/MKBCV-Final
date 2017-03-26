#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "mosaicbuilder.hpp"

struct trackbar_data_t {
  const cv::Mat* orig_hsv;
  cv::Mat dest;
  std::string window;
  int tile_length;
};

void buildMosaic(trackbar_data_t* trackbar_data, int tile_length) {
  using namespace imosaic;
  Mosaic<GridCutter<NonUniformSplitter>, AverageTiler> mosaic;
  mosaic.setTilesize(cv::Size(tile_length,tile_length));
  mosaic.build(*trackbar_data->orig_hsv, &trackbar_data->dest);
}

void onTrackbar(int tile_length, void* p_trackbar_data) {
  if(tile_length < 8)
    tile_length = 0;
  trackbar_data_t* trackbar_data = (trackbar_data_t*)p_trackbar_data;
  buildMosaic(trackbar_data, tile_length);
  cv::cvtColor(trackbar_data->dest, trackbar_data->dest, CV_HSV2BGR);
  cv::imshow(trackbar_data->window, trackbar_data->dest);
}

int main(int argc, char **argv){

  // Print usage if arguments are malformed
  if(argc != 2){
    printf("usage: %s [Image File]\n",argv[0]);
    return -1;
  }

  // Load in HSV image.
  cv::Mat image = cv::imread(argv[1],1);
  if(!image.data){
    printf("No image data\n");
    return -1;
  }
  cv::cvtColor(image, image, CV_BGR2HSV);

  // display result
  trackbar_data_t trackbar_data{&image, cv::Mat::zeros(image.size(), CV_8UC3), "Result"};
  int tilesize = 16;
  int max_pixel_size = std::fmin(image.size().width, image.size().height)/2;
  cv::namedWindow(trackbar_data.window,cv::WINDOW_AUTOSIZE);
  cv::createTrackbar("Threshold", trackbar_data.window
    , &tilesize, max_pixel_size
    , onTrackbar, &trackbar_data);
  onTrackbar(tilesize, &trackbar_data);
  cv::waitKey();
  return 0;
}
