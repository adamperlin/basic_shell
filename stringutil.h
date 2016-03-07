#include <string>
#include <vector>
#ifndef STRING_UTIL_H
#define STRING_UTIL_H
namespace stringutil {

char** str_vector_toCSTR(std::vector<std::string>&);
char** str_vector_toCSTR(std::vector<std::string>& vec){
  char** argv = new char* [vec.size()];
  char* p;
  for (int i = 0; i < vec.size(); i++){
    p = new char [vec[i].size()];
    strcpy(p, vec[i].c_str());
    argv[i] = p;
  }
  return argv;
}

}

#endif
