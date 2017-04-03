#ifndef IMOSAIC_MOSAIC_HPP
#define IMOSAIC_MOSAIC_HPP

#include <opencv2/opencv.hpp>

namespace imosaic {
/// class Mosaic
/// CutterPolicy:
///   Defines a function 'std::vector<cv::Mat> cutUp(const cv::Mat&)'
///   to split up an image into regions.
/// TilerPolicy:
///   Defines a function 'void replaceAll(const std::vector<cv::Mat>& source
///   , std::vector<cv::Mat>& destination)
///   Which defines how to apply a fill policy across all mats.
///   ... potentially.
template <typename CutterPolicy, typename TilerPolicy>
class Mosaic : public CutterPolicy, public TilerPolicy  {
public:
  void build(const cv::Mat& source_hsv, cv::Mat* dest_hsv) {
    *dest_hsv = 0;
    std::vector<cv::Mat> dest_regions(CutterPolicy::cutUp(*dest_hsv));
    std::vector<cv::Mat> source_regions(CutterPolicy::cutUp(source_hsv));
    TilerPolicy::replaceAll(source_regions, dest_regions);
  }
};
}

#endif //IMOSAIC_MOSAIC_HPP
