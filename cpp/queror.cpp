#include "queror.hpp"
#include <cstdio>
#include <opencv2/opencv.hpp>

namespace imosaic{
  /* adds our training data to the matcher and trains it so that future queries
   *  will be quick
   */
  Queror::Queror(const MetaFile &metafile):
  metafile_(metafile)
  {
    initializeMatcher();
  }

  Queror::Queror(const unsigned int bin, const std::string &filename):
  metafile_(bin,filename)
  {
    initializeMatcher();
  }

  void Queror::initializeMatcher(){
    matcher_.add(metafile_.getFeatureVectors());
    matcher_.train();
  }

  Queror::~Queror(){}


  /* using the FLANN matcher, gets the first best match for the feature vector
   * and returns a query object which has the filename and distance of the best
   * match. As we are only querying 1 match, we use the 0th index.
   */
  Query Queror::query(const cv::Mat &featureVector){
    Query query;
    std::vector<cv::DMatch> matches;

    if(featureVector.empty()){
      printf("feature vector empty\n");
    }

    if(matcher_.empty()){
      printf("Matcher empty\n");
    }
    
    matcher_.match(featureVector,matches);

    int row = matches[0].trainIdx;
    query.distance = matches[0].distance;
    query.filename = metafile_.getLabels()[row];

    cv::Mat train = metafile_.getFeatureVectors().row(row);

    return query;
  }
}
