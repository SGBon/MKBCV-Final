/**
* Policies for producing rectangular subregions.
**/
#ifndef IMOSAIC_SPLITTER_HPP
#define IMOSAIC_SPLITTER_HPP

#include <opencv2/opencv.hpp>

namespace imosaic {

/// splits area into cells defined by 'tilesize'.
/// If size % tilesize != 0, the extra area is discarded.
/// When tilesize's area is zero, the entire field is returned.
class UniformSplitter {
private:
  cv::Size tilesize_;

protected:
  ~UniformSplitter() {}

public:
  void setTilesize(cv::Size tilesize);

protected:
  std::vector<cv::Rect2i> split(cv::Size size);
};

/// splits area into cells defined by 'tilesize'.
/// If size % tilesize != 0, certain cells are truncated.
class NonUniformSplitter {
private:
  cv::Size tilesize_;

protected:
  ~NonUniformSplitter() {}

public:
  void setTilesize(cv::Size tilesize);

protected:
  std::vector<cv::Rect2i> split(cv::Size size);
};
}

#endif //IMOSAIC_SPLITTER_HPP
