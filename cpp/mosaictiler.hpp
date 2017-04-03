#ifndef IMOSAIC_TILER_HPP
#define IMOSAIC_TILER_HPP

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
    for(int i = 0; i < size; i++) {
      FillPolicy::replaceRegion(source[i], destination[i]);
    }
  }
};
}

#endif //IMOSAIC_TILER_HPP
