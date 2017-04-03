#ifndef IMOSAIC_MOSAIC_HPP
#define IMOSAIC_MOSAIC_HPP

#include <opencv2/opencv.hpp>

namespace imosaic {
/// class Mosaic
/// CutterPolicy:
///   Defines a function 'std::vector<cv::Mat> cutUp(const cv::Mat&)'
///   to split up an image into regions.
/// FillPolicy:
///   Defines a function 'void replaceRegion(const cv::Mat& source, cv::Mat&
///     destination) which uses information in lhs to
///     write to rhs; creating the mosaic effect.
/// TilerPolicy:
///   Defines a function 'void replaceAll(const std::vector<cv::Mat>& source
///   , std::vector<cv::Mat>& destination)
///   Which defines how to apply a fill policy across all mats.
///   ... potentially.
template <typename CutterPolicy, typename FillPolicy>
class Mosaic : public CutterPolicy, public FillPolicy  {
public:
  void build(const cv::Mat& source_hsv, cv::Mat* dest_hsv) {
    *dest_hsv = 0;
    std::vector<cv::Mat> dest_regions(CutterPolicy::cutUp(*dest_hsv));
    std::vector<cv::Mat> source_regions(CutterPolicy::cutUp(source_hsv));
    size_t size = dest_regions.size();
    for(int i = 0; i < size; i++) {
      FillPolicy::replaceRegion(source_regions[i], dest_regions[i]);
    }
  }
};
}

#endif //IMOSAIC_MOSAIC_HPP
