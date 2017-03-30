#ifndef IMOSAIC_QUEROR_HPP
#define IMOSAIC_QUEROR_HPP

#include <opencv2/features2d.hpp>
#include "metafile.hpp"

/* object to run queries on to lookup tiles
 * contains a KDTree where queries are run
 * in the future will handle bookkeeping to reduce
 * repetition of tiles
 */
namespace imosaic{
  /* result of Queror::query
   * filename: image file associated with k-nearest neighbour of a query
   * distance: distance of k-nearest neighbour to input vector
   */
  struct Query{
    std::string filename;
    float distance;
  };

  class Queror{
  public:
    /* constructor
     * metafile: metafile to initialize this queror with
     */
    Queror(const MetaFile &metafile);

    /* constructor that initializes metafile from filename
     * bin: bin of metafile
     * filename: path to metafile
     */
    Queror(const unsigned int bin, const std::string &filename);

    /* deconstructor */
    ~Queror();

    /* query a feature vector for the k-nearest neighbour
    * featureVector: input vector to find the k-nearest neighbour for
    * returns a query object associated with the k-nearest neighbour
    */
    Query query(const cv::Mat &featureVector);

  private:
    cv::FlannBasedMatcher matcher_;
    MetaFile metafile_;

    /* initializes the flann matcher */
    void initializeMatcher();
  };
} /* namespace imosaic */

#endif
