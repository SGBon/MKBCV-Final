/**
* This is the data for creating the new image.
**/
#ifndef IMOSAIC_MOSAIC_BUILDER_HPP
#define IMOSAIC_MOSAIC_BUILDER_HPP

#include <unordered_map>
#include <opencv2/opencv.hpp>
#include "features.hpp"

namespace imosaic {
/// wrapper around unordered_map.
/// because templates, that's why.
template<typename K, typename V>
class UnorderedMap {
private:
  std::unordered_map<K, V> map_;
public:
  UnorderedMap(const std::unordered_map<K, V>& map) : map_(map) {}
  const V& query(const K& k) const { return map_[k]; }
  void put(const K& k, V&& v) { map_[k] = v; }
};

/// Creates a mosaic from hsv using components from bank split into uniformly
///   aligned tiles.
class GridMosaicBuilder {
private:
  cv::Size tile_size_;

public:
  GridMosaicBuilder(cv::Size tile_size) : tile_size_(tile_size) {}

  template<template <class, class> typename Queror>
  cv::Mat build(const cv::Mat& hsv
    , const Queror<std::string, ImageFeatures>& bank) {
      cv::Size canvas_size = hsv.size();
      cv::Mat result = cv::Mat::zeros(canvas_size, hsv.type());
      for(int i = 0; i < canvas_size.height; i++) {
        for(int j = 0; j < canvas_size.width; j++) {
            //int ip = i/tile_size_.height;
            //int jp = j/tile_size_.width;
            result.at<double>(i, j) = hsv.at<double>(i,j);
        }
      }
      return result;
    }
};

/// createMosaic
/// hsv:      Image matrix, with HSV cells
/// bank:     Queror policy using filenames for keys and ImageFeatures for values.
/// tilesize: x/y length, in pixels, of each grid cell
///
/// Returns assembled mosaic image, coded as HSV.
template <template <class, class> typename Queror>
cv::Mat createMosaic(const cv::Mat& hsv
  , const Queror<std::string, ImageFeatures>& bank
  , cv::Size tilesize) {
    GridMosaicBuilder builder(tilesize);
    return builder.build(hsv, bank);
  }

}


#endif //IMOSAIC_MOSAIC_BUILDER_HPP
