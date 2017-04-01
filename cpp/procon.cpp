#include <cstdio>
#ifdef _OPENMP
  #include <omp.h>
#else
  #define omp_get_thread_num() 0
#endif
#include "procon.hpp"

namespace imosaic{
  /* consume image segments from dequeue. On consumption, an image is loaded from
   * the path specified by the image segment and placed into the resulting image
   * with the x and y parameters of the image segment
   * this process continues until both the dequeue is empty AND the producers signal
   * that there is no more image data to process (the condition of the while loop)
   */
  void consumeImageSegments(std::deque<ImageSegment> &imageSegments,
      std::mutex &dequeMutex, cv::Mat &result, bool &finished)
  {
    while(!finished && !imageSegments.empty()){
      if(!imageSegments.empty()){
        /* critical section, reading an image segment from dequeue */
        dequeMutex.lock();
        const ImageSegment currentSegment = imageSegments.front();
        imageSegments.pop_front();
        dequeMutex.unlock();

        cv::Mat image = cv::imread(currentSegment.filename);

        printf("consuming:%s to place at (%u,%u)\n",currentSegment.filename.c_str(),currentSegment.x,currentSegment.y);
        /* TODO: place loaded image segment into result image */
      }
    }
  }

  /* produce image segments from source image. iterates over every subregion in image
   * and queries the nearest neighbour for a substitute image. enqueues substitute
   * into the shared dequeue
   * uses OMP to leverage multiple producers
   * sets the finished variable to false when finished
   */
   void produceImageSegments(std::deque<ImageSegment> &imageSegments,
       std::mutex &dequeMutex, const cv::Mat &source,
       const std::vector<Queror *> &querors, bool &finished)
  {
    const unsigned int rdim = source.rows;
    const unsigned int cdim = source.cols;

    const unsigned int step = 4;

    #pragma omp parallel
    {
      #pragma omp for collapse(2)
      for (unsigned int r = 0; r < rdim; r += step){
        for(unsigned int c = 0; c < cdim; c += step){
          printf("Producing segment for (%u,%u)\n",r,c);
        }
      }
    }

    finished = true;
  }

} // namespace imosaic
