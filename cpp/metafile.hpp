#ifndef IMOSAIC_METAFILE_HPP
#define IMOSAIC_METAFILE_HPP

#include <opencv2/opencv.hpp>
#include <string>

namespace imosaic{
  /* represents a metafile in memory
   * format of metafiles are multiple lines of:
   * filename,value,value,value,....
   * all lines should have the same amount of tokens
   */
  class MetaFile{
  public:
    MetaFile();
    MetaFile(unsigned int bin, const std::string &filename);

    /* parse a meta file into class members */
    void parseMetaFile(const std::string &filename);

    /* print this metafile to console */
    void print() const;

    /* setter for bin */
    void setbin(unsigned int bin);

    cv::Mat getFeatureVectors() const;

    std::vector<std::string> getLabels() const;


  private:
    cv::Mat featureVectors; /* feature vectors in this metafile, of type CV_32F/float */
    std::vector<std::string> labels; /* filenames that map to feature vectors */
    unsigned int bin; /* bin this metafile pertains to */
  };
} /* namespace imosaic */

#endif
