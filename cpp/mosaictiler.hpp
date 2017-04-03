/**
* Tiler Policy Implementations
**/
#ifndef IMOSAIC_TILER_HPP
#define IMOSAIC_TILER_HPP

#include <opencv2/opencv.hpp>

namespace imosaic {
/// Assigns the average of source region to dest.
class AverageTiler {
protected:
  ~AverageTiler() {}
protected:
  void replaceRegion(const cv::Mat& source, cv::Mat& dest);
};
}

#endif //IMOSAIC_TILER_HPP
