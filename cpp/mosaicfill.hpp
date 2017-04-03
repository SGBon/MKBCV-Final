/**
* Tiler Policy Implementations
**/
#ifndef IMOSAIC_MOSAIC_FILL_HPP
#define IMOSAIC_MOSAIC_FILL_HPP

#include <opencv2/opencv.hpp>

namespace imosaic {
/// Assigns the average of source region to dest.
class AverageFill {
protected:
  ~AverageFill() {}
protected:
  void replaceRegion(const cv::Mat& source, cv::Mat& dest);
};
}

#endif //IMOSAIC_MOSAIC_FILL_HPP
