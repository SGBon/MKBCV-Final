#include <cstdio>
#include <thread>
#include <opencv2/opencv.hpp>
#include "metafile.hpp"
#include "procon.hpp"

#define NUM_BINS (20)
#define HUE_MAX (180)

int main(int argc, char **argv){
  if(argc != 3){
    printf("usage: %s [Image File] [Image Bank]\n",argv[0]);
    return -1;
  }

  std::string root(argv[2]);

  std::vector<imosaic::Queror *> querors;

  /* read metafiles and initialize querors */
  for (unsigned int i = 0; i < NUM_BINS; ++i){
    const unsigned int bin = i*(HUE_MAX/NUM_BINS);
    std::string metafilename(root + std::to_string(bin) + "/meta.txt");
    /* allocate memory for queror from heap */
    imosaic::Queror *queror = new imosaic::Queror(bin,metafilename);
    querors.push_back(queror);
  }

  const cv::Mat image = cv::imread(argv[1],1);

  if(!image.data){
    printf("No image data\n");
    return -1;
  }

  cv::Mat hsv;
  cv::cvtColor(image,hsv,CV_BGR2HSV);

  cv::Mat result(image.rows,image.cols,image.type());

  std::deque<imosaic::ImageSegment> imageSegments;
  std::mutex dequeMutex;
  bool finished = false;

  // get interval start
  int64 interval_start = cv::getTickCount();

  std::thread consumer(imosaic::consumeImageSegments,std::ref(imageSegments),
    std::ref(dequeMutex),std::ref(result),std::ref(finished));


  std::thread producer(imosaic::produceImageSegments,std::ref(imageSegments),
    std::ref(dequeMutex),std::cref(hsv), std::cref(querors), std::ref(finished),std::cref(root));

  producer.join();
  consumer.join();

  int64 interval_end = cv::getTickCount();
  printf("Created mosaic in %.8fs\n", (interval_end-interval_start)/cv::getTickFrequency());

  cv::namedWindow("Image",cv::WINDOW_AUTOSIZE);
  cv::imshow("Image", result);

  // print out image
  cv::imwrite("output.jpg", result);
  printf("Wrote result to 'output.jpg'\n");

  while(true) {
  int key = cv::waitKey(33);
  if(key == 27)
    break;
  }
  cv::destroyWindow("Image");

  /* deallocate queror memory */
  for(unsigned int i = 0; i < querors.size();++i){
    delete querors[i];
  }
  querors.clear();


  // done
  return 0;
}
