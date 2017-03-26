#include "mosaicbuilder.hpp"

namespace imosaic {
void UniformSplitter::setTilesize(cv::Size tilesize) {
  tilesize_ = tilesize;
}

std::vector<cv::Rect2i> UniformSplitter::split(cv::Size size) {
  std::vector<cv::Rect2i> list;
  cv::Size tilesize(tilesize_.area() == 0 ? cv::Size(1,1) : tilesize_);
  cv::Size cell_count(size.width/tilesize.width, size.height/tilesize.height);
  cv::Size offset(size.width - tilesize.width*cell_count.width, size.height - tilesize.height*cell_count.height);
  offset = offset/2;
  for(int i = 0; i < cell_count.height; i++) {
    for(int j = 0; j < cell_count.width; j++) {
      list.push_back(cv::Rect2i(offset.width + tilesize.width*j, offset.height + tilesize.height*i, tilesize.width
        , tilesize.height));
    }
  }
  return list;
}

void NonUniformSplitter::setTilesize(cv::Size tilesize) {
  tilesize_ = tilesize;
}

std::vector<cv::Rect2i> NonUniformSplitter::split(cv::Size size) {
  std::vector<cv::Rect2i> list;
  cv::Size tilesize(tilesize_.area() == 0 ? cv::Size(1,1) : tilesize_);
  cv::Size cell_count(1+(size.width/tilesize.width), size.height/tilesize.height);
  cv::Size offset;
  for(int i = 0; i < cell_count.height; i++) {
    cv::Size cell_size(tilesize);
    if(i == cell_count.height/2) {
      cell_size.height = size.height - (cell_count.height-1)*tilesize.height;
      if(cell_size.height == 0)
        continue;
    }
    for(int j = 0; j < cell_count.width; j++) {
      cell_size.width = tilesize.width;
      if(j == cell_count.width/2) {
        cell_size.width = size.width - (cell_count.width-1)*tilesize.width;
        if(cell_size.width == 0)
          continue;
      }
      list.push_back(cv::Rect2i(offset, cell_size));
      offset.width += cell_size.width;
    }
    offset.width = 0;
    offset.height += cell_size.height;
  }

  return list;
}

void AverageTiler::replaceRegion(const cv::Mat& source, cv::Mat& dest) {
  dest = cv::mean(source);
}
}
