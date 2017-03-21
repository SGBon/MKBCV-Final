#include "util.hpp"

/* iterate over every character in string, every time a delimiter
 * is found, append the string between that delimeter and the delimiter
 * before
 */
std::vector<std::string> tokenize(const std::string &str, const char delimiter){
  std::vector<std::string> tokens;
  std::string currToken(""); // current string in iteration

  for(unsigned int i = 0; i < str.length(); ++i){
    const char currChar = str.at(i);
    /* if delimiter encountered, add current string to tokens */
    if(currChar == delimiter && currToken.length() > 0){
      tokens.push_back(currToken);
      currToken.clear();
    }
    /* if not a delimiter, append the character to the string */
    else{
      currToken.append(1,currChar);
    }
  }

  if(currToken.length() > 0){
    tokens.push_back(currToken);
  }

  return tokens;
}
