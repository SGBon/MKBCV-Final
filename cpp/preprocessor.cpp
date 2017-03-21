/* image mosaic preprocessor
 * Converts an image to HSV, analyses their hue, and writes them to
 * the folder with the range that the hue value falls into
 * as well as keeping track of its metadata to write to file
 */

#include <stdio.h>
#include <string>
#include <opencv2/opencv.hpp>
#include <CL/cl.h>

#include "util.hpp"

int main(int argc, char **argv){
  if(argc < 3){
    printf("Usage: %s [Image File] [Output Directory]\n",argv[0]);
    return -1;
  }

  std::string filename(argv[1]);
  std::string root(argv[2]);

  /* get just the filename of image */
  std::vector<std::string> tokens = tokenize(filename,'/');

  for(unsigned int i = 0; i < tokens.size(); ++i){
    printf("%s\n",tokens[i].c_str());
  }

  return 0;
}
