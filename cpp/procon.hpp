#ifndef IMOSAIC_PROCON_HPP
#define IMOSAIC_PROCON_HPP

#include <mutex>
#include <deque>
#include <opencv2/opencv.hpp>
#include "queror.hpp"

namespace imosaic{
  /* image segment which gets produced/consumed */
  struct ImageSegment{
    std::string filename;
    unsigned int x;
    unsigned int y;
  };

  /* callback function for consumer thread.
   * consumes image data sent from a producer thread
   * and loads images into the result matrix.
   * imageSegments: dequeu shared with producers from which to consume imagedata
   * dequeMutex: synchronization primitive shared with producers for the deque
   * result: output image
   * finished: boolean shared with producers signifying end of data
   */
  void consumeImageSegments(std::deque<ImageSegment> &imageSegments,
      std::mutex &dequeMutex, cv::Mat &result, bool &finished);

  /* callback function for producer master thread
   * produces image data from source matrix into shared deque with consumer
   * imageSegments: dequeu shared with consumer from which to produce imagedata
   * dequeMutex: synchronization primitive shared with consumer for the deque
   * source: input image
   * querors: queror array to query substitute images with
   * finished: boolean shared with consumer signifying end of data
   */
  void produceImageSegments(std::deque<ImageSegment> &imageSegments,
      std::mutex &dequeMutex, const cv::Mat &source,
      const std::vector<Queror *> &querors, bool &finished);

} // namespace imosaic
#endif // header guard
