#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "MetaFile.hpp"

int main(int argc, char **argv){
  if(argc != 3){
    printf("usage: %s [Image File] [Image Bank]\n",argv[0]);
    return -1;
  }

  const cv::Mat image = cv::imread(argv[1],1);

  if(!image.data){
    printf("No image data\n");
    return -1;
  }

  imosaic::MetaFile meta1(0,argv[2]);

  meta1.print();

  cv::namedWindow("Image",cv::WINDOW_AUTOSIZE);
  cv::imshow("Image",image);

  cv::waitKey(0);

  return 0;
}
