#include "queror.hpp"
#include <opencv2/opencv.hpp>

namespace imosaic{
  Queror::Queror(const MetaFile &metafile):
  metafile_(metafile)
  {
    matcher_.add(metafile.getFeatureVectors());
    matcher_.train();
  }

  Query Queror::query(const cv::Mat &featureVector){
    Query query;
    std::vector<cv::DMatch> matches;

    matcher_.match(featureVector,matches);

    int row = matches[0].trainIdx;
    query.distance = matches[0].distance;
    query.filename = metafile_.getLabels()[row];

    cv::Mat train = metafile_.getFeatureVectors().row(row);
    
    return query;
  }
}
