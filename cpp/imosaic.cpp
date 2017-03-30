#include <cstdio>
#include <cstdint>
#include <opencv2/opencv.hpp>
#include "metafile.hpp"
#include "queror.hpp"

#define NUM_BINS (20)
#define HUE_MAX (180)

int main(int argc, char **argv){
  if(argc != 3){
    printf("usage: %s [Image File] [Image Bank]\n",argv[0]);
    return -1;
  }

  std::string root(argv[2]);

  std::vector<imosaic::Queror> querors;

  /* read metafiles and initialize querors */
  for (unsigned int i = 0; i < NUM_BINS; ++i){
    const unsigned int bin = i*(HUE_MAX/NUM_BINS);
    std::string metafilename(root + std::to_string(bin) + "/meta.txt");
    imosaic::MetaFile metafile(bin,metafilename);
    imosaic::Queror queror(metafile);
    querors.emplace_back(metafile);
  }

  cv::Mat test(1,3,CV_32F);
  test.at<float>(0,0) = 60.0f;
  test.at<float>(0,1) = 120.0f;
  test.at<float>(0,2) = 115.0f;

  for(unsigned int i = 0; i < querors.size();++i){
    const unsigned int bin = i*(HUE_MAX/NUM_BINS);
    imosaic::Query q = querors[i].query(test);
    printf("Best match in bin %u: %s",bin,q.filename.c_str());
  }

  const cv::Mat image = cv::imread(argv[1],1);

  if(!image.data){
    printf("No image data\n");
    return -1;
  }

  cv::namedWindow("Image",cv::WINDOW_AUTOSIZE);
  cv::imshow("Image",image);

  cv::waitKey(0);

  return 0;
}
