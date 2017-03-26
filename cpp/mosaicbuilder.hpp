/**
* This is the data for creating the new image.
**/
#ifndef IMOSAIC_MOSAIC_BUILDER_HPP
#define IMOSAIC_MOSAIC_BUILDER_HPP

#include <unordered_map>
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
  void setTilesize(cv::Size tilesize) {
    tilesize_ = tilesize;
  }

protected:
  std::vector<cv::Rect2i> split(cv::Size size) {
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
};

/// splits area into cells defined by 'tilesize'.
/// If size % tilesize != 0, certain cells are truncated.
class NonUniformSplitter {
private:
  cv::Size tilesize_;

protected:
  ~NonUniformSplitter() {}

public:
  void setTilesize(cv::Size tilesize) {
    tilesize_ = tilesize;
  }

protected:
  std::vector<cv::Rect2i> split(cv::Size size) {
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
};

template<typename RectangleSplitterPolicy>
class GridCutter : public RectangleSplitterPolicy {
protected:
  ~GridCutter() {}
protected:
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

class AverageTiler {
protected:
  ~AverageTiler() {}
protected:
  void replaceRegion(const cv::Mat& source, cv::Mat& dest) {
    dest = cv::mean(source);
  }
};

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

#endif //IMOSAIC_MOSAIC_BUILDER_HPP
