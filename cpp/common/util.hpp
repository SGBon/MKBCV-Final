#ifndef IMOSAIC_UTIL_HPP
#define IMOSAIC_UTIL_HPP

#include <vector>
#include <string>

namespace imosaic {

/* return a vector of the tokens in a string
 * delimited by the delimiter
 */
std::vector<std::string> tokenize(
  const std::string &str,
  char delmiter);
} // namespace imosaic

#endif //IMOSAIC_UTIL_HPP
