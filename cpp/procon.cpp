#include <cstdio>
#include <string>
#include <unordered_map>
#ifdef _OPENMP
  #include <omp.h>
#else
  #define omp_get_thread_num() 0
#endif
#include "procon.hpp"
#include "mosaiccutter.hpp"
#include "mosaicsplitter.hpp"
#include "mosaicfill.hpp"
#include "mosaic.hpp"

namespace imosaic{

/// I said I'd reduce hardcoding. And so, here is some reduced hardcoding.
class ProconCutter : public GridCutter<UniformSplitter> {
public:
  ProconCutter() {
    static const int tilesize = 16;
    GridCutter::setTilesize(cv::Size(tilesize,tilesize));
  }
};


  /// ctor
  ImageSegment::ImageSegment(const std::string filename, cv::Rect2i region):
    filename(filename),
    region(region){};

  /// ctor
  ImageSegment::ImageSegment(const std::string filename, unsigned int x,
    unsigned int y, unsigned int width, unsigned int height):
    ImageSegment(filename, cv::Rect2i(x,y,width,height)){};

  /* consume image segments from dequeue. On consumption, an image is loaded from
   * the path specified by the image segment and placed into the resulting image
   * with the x and y parameters of the image segment
   * this process continues until both the dequeue is empty AND the producers signal
   * that there is no more image data to process (the condition of the while loop)
   */
  void consumeImageSegments(std::deque<ImageSegment> &imageSegments,
      std::mutex &dequeMutex, cv::Mat &result, std::atomic_bool &finished)
  {
    /* preloaded images to forgo having to read from disk */
    std::unordered_map<std::string,cv::Mat> preloaded;

    // let's get some cells.
    ProconCutter gridCutter;
    std::vector<cv::Mat> cells = gridCutter.cutUp(result);

    while(!finished || !imageSegments.empty()){
      if(!imageSegments.empty()){
        /* critical section, reading an image segment from dequeue */
        dequeMutex.lock();
        const ImageSegment currentSegment = imageSegments.front();
        imageSegments.pop_front();
        dequeMutex.unlock();

        /* load image, first check if it's not yet loaded then load from file otherwise
         * load from map
         */
        cv::Mat& dest = cells[currentSegment.index];
        cv::Mat image(dest.size(), dest.type());
        std::unordered_map<std::string,cv::Mat>::iterator finder = preloaded.find(currentSegment.filename);
        if(finder == preloaded.end()){
          cv::Mat loaded_image = cv::imread(currentSegment.filename);
          cv::resize(loaded_image,image,dest.size());
          preloaded[currentSegment.filename] = image;
        }else{
          image = finder->second;
        }

        // put into dest
        image.copyTo(dest);
      }
    }
  }


void produceImageSegmentsFromRegions(std::deque<ImageSegment> &imageSegments,
    std::mutex &dequeMutex, const std::vector<cv::Mat> &cells,
    const std::vector<Queror *> &querors, std::atomic_bool &finished
    , const std::string &root) {
  #pragma omp parallel
  {
    #pragma omp for
    for (unsigned int i = 0; i < cells.size(); ++i){
      //const int x = i % source.cols;
      //const int y = (i - x) / source.cols;
      const cv::Mat mean(cv::mean(cells[i]));
      cv::Mat other;
      mean.convertTo(other,CV_32F);

      const cv::Mat query_vector = other.rowRange(0,3);
      const unsigned int bin = query_vector.at<float>(0,0) / 9.0;

      Query query;

      query = querors[bin]->query(query_vector.t());

      const std::string path(root + std::to_string(bin*9) + "/" + query.filename);

      ImageSegment segment(path,0,0,cells[i].size().width, cells[i].size().height);
      segment.index = i;
      /* critical section, push segment onto shared deque */
      dequeMutex.lock();
      {
        imageSegments.push_back(segment);
      }
      dequeMutex.unlock();
    }
  }
  finished = true;
}

  /* produce image segments from source image. iterates over every subregion in image
   * and queries the nearest neighbour for a substitute image. enqueues substitute
   * into the shared dequeue
   * uses OMP to leverage multiple producers
   * sets the finished variable to false when finished
   */
   void produceImageSegments(std::deque<ImageSegment> &imageSegments,
       std::mutex &dequeMutex, const cv::Mat &source,
       const std::vector<Queror *> &querors, std::atomic_bool &finished, const std::string &root)
  {
    ProconCutter gridCutter;
    const std::vector<cv::Mat> cells = gridCutter.cutUp(source);
    produceImageSegmentsFromRegions(imageSegments, dequeMutex, cells, querors, finished, root);
  }

} // namespace imosaic
