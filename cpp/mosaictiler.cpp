#include "mosaictiler.hpp"

namespace imosaic {
void AverageTiler::replaceRegion(const cv::Mat& source, cv::Mat& dest) {
  dest = cv::mean(source);
}
}
