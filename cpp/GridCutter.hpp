#ifndef IMOSAIC_GRIDCUTTER_HPP
#define IMOSAIC_GRIDCUTTER_HPP

#include <opencv2/opencv.hpp>

namespace imosaic {
/// class GridCutter
/// RectangleSplitterPolicy:
///   defines 'std::vector<cv::Rect2i> split(cv::Size)'.
///   divides area defined by cv::Size into subrectangles.
template<typename RectangleSplitterPolicy>
class GridCutter : public RectangleSplitterPolicy {
public:
  ~GridCutter() {}
  std::vector<cv::Mat> cutUp(const cv::Mat& mat) {
    std::vector<cv::Mat> cells;
    std::vector<cv::Rect2i> subrects(RectangleSplitterPolicy::split(mat.size()));
    std::for_each(subrects.begin(), subrects.end(), [&cells, &mat]
      (cv::Rect2i roi) {
      cells.push_back(cv::Mat(mat, roi));
    });
    return cells;
  }
};
}

#endif //IMOSAIC_GRIDCUTTER_HPP
