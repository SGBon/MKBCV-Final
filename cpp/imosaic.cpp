#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "metafile.hpp"
#include "queror.hpp"

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

  /* test metafile */
  imosaic::MetaFile meta1(0,argv[2]);
  meta1.print();

  /* test queror */
  imosaic::Queror queror1(meta1);
  cv::Mat test(1,3,CV_32F);
  test.at<float>(0,0) = 60.0f;
  test.at<float>(0,1) = 120.0f;
  test.at<float>(0,2) = 115.0f;
  imosaic::Query query1 = queror1.query(test);

  printf("Query returned %s as a suitable candidate with distance of %f\n",query1.filename.c_str(),query1.distance);

  cv::namedWindow("Image",cv::WINDOW_AUTOSIZE);
  cv::imshow("Image",image);

  cv::waitKey(0);

  return 0;
}
