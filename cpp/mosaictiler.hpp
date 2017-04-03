#ifndef IMOSAIC_TILER_HPP
#define IMOSAIC_TILER_HPP

#include <stdlib.h>
#include <thread>
#include "procon.hpp"

namespace imosaic {
/// Naive for loop implementation of tiler.
/// FillPolicy:
///   Defines a function 'void replaceRegion(const cv::Mat& source, cv::Mat&
///     destination) which uses information in lhs to
///     write to rhs; creating the mosaic effect.
template<typename FillPolicy>
class ForTiler : public FillPolicy{
protected:
  ~ForTiler() {}
protected:
  void replaceAll(const std::vector<cv::Mat>& source
    , std::vector<cv::Mat>& destination) {
    size_t size = destination.size();
    printf("no threaded\n");
    for(int i = 0; i < size; i++) {
      FillPolicy::replaceRegion(source[i], destination[i]);
    }
  }
};


/// Threaded implementation of tiler.
/// FillPolicy:
///   Defines a function 'void replaceRegion(const cv::Mat& source, cv::Mat&
///     destination) which uses information in lhs to
///     write to rhs; creating the mosaic effect.
template<typename FillPolicy>
class ThreadedTiler : public FillPolicy {
protected:
  ~ThreadedTiler() {}

private:
  std::deque<imosaic::ImageSegment> imageSegments_;
  std::mutex dequeMutex_;
  bool finished_;

protected:
  void replaceAll(const std::vector<cv::Mat>& source
    , std::vector<cv::Mat>& destination) {
    printf("I'm threaded\n");
    finished_ = false;
    /*std::thread consumer(consumeImageSegments,std::ref(imageSegments),
      std::ref(dequeMutex),std::ref(result),std::ref(finished));
    std::thread producer(produceImageSegments,std::ref(imageSegments),
      std::ref(dequeMutex),std::cref(hsv), std::cref(querors), std::ref(finished),std::cref(root));
    producer.join();
    consumer.join();*/
  }
};
}

#endif //IMOSAIC_TILER_HPP
