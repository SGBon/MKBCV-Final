#include "mosaicfill.hpp"

namespace imosaic {
void AverageFill::replaceRegion(const cv::Mat& source, cv::Mat& dest) {
  dest = cv::mean(source);
}
}
