#ifndef IMOSAIC_MOSAIC_HPP
#define IMOSAIC_MOSAIC_HPP

#include <opencv2/opencv.hpp>

namespace imosaic {
/// class Mosaic
/// CutterPolicy:
///   Defines a function 'std::vector<cv::Mat> cutUp(const cv::Mat&)'
///   to split up an image into regions.
/// TilerPolicy:
///   Defines a function 'void replaceRegion(const cv::Mat& lhs, cv::Mat& rhs)'
///   which uses information in lhs to write to rhs; creating the mosaic effect.
///   ([!] Maybe a feature vector and rect would be better for lhs...)
///
template <typename CutterPolicy, typename TilerPolicy>
class Mosaic : public CutterPolicy, public TilerPolicy  {
public:
  void build(const cv::Mat& source_hsv, cv::Mat* dest_hsv) {
    *dest_hsv = 0;
    std::vector<cv::Mat> dest_regions(CutterPolicy::cutUp(*dest_hsv));
    std::vector<cv::Mat> source_regions(CutterPolicy::cutUp(source_hsv));
    size_t size = dest_regions.size();
    for(int i = 0; i < size; i++) {
      TilerPolicy::replaceRegion(source_regions[i], dest_regions[i]);
    }
  }
};
}

#endif //IMOSAIC_MOSAIC_HPP
