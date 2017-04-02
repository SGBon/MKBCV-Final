/* test for queror class
 * reads in all of the metafiles and queries a vector to each of them
 */

#include <cstdio>
#include <opencv2/opencv.hpp>
#include "../queror.hpp"

#define NUM_BINS (20)
#define HUE_MAX (180)

int main(int argc, char **argv){
  if(argc != 2){
    printf("usage: %s [Image Bank]\n",argv[0]);
    return -1;
  }

  std::string root(argv[1]);

  std::vector<imosaic::Queror *> querors;

  /* read metafiles and initialize querors */
  for (unsigned int i = 0; i < NUM_BINS; ++i){
    const unsigned int bin = i*(HUE_MAX/NUM_BINS);
    std::string metafilename(root + std::to_string(bin) + "/meta.txt");
    /* allocate memory for queror from heap */
    imosaic::Queror *queror = new imosaic::Queror(bin,metafilename);
    querors.push_back(queror);
  }

  cv::Mat test(1,3,CV_32F);
  test.at<float>(0,0) = 60.0f;
  test.at<float>(0,1) = 120.0f;
  test.at<float>(0,2) = 115.0f;

  for(unsigned int i = 0; i < querors.size();++i){
    const unsigned int bin = i*(HUE_MAX/NUM_BINS);
    imosaic::Query q = querors[i]->query(test);
    printf("Best match in bin %u: %s with distance of %f\n",bin,q.filename.c_str(),q.distance);
  }

  /* deallocate queror memory */
  for(unsigned int i = 0; i < querors.size();++i){
    delete querors[i];
  }
  querors.clear();

  return 0;
}
