#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <unistd.h>
#include <strings.h>
#include <stdlib.h>
#include <vector>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>
#include "builtins.h"
#include "stringutil.h"
#define split_tokens " \t\r\n\a"

#ifndef NEWSH_H
#define NEWSH_H


class parser {
public:
    parser(){}
    virtual ~parser(){}
    static std::string parse(std::string);
    static std::vector<std::string> split_line(std::string);
};

class shell : public parser {
public:
    shell(){}
    virtual ~shell(){}
    static void main_loop();
    static std::string readline();
    static bool execute(std::vector<std::string>);
    static bool launch_process(std::vector<std::string>&);
};

std::vector<std::string> parser::split_line(std::string i){
    char* cstr = new char [i.length()];
    strcpy(cstr, i.c_str());
    //std::cout << strlen(cstr) << std::endl;
    char* tok = strtok(cstr, split_tokens);
    std::vector<char*> tokens;
    std::vector<std::string> ret;
    while(tok != NULL){
        tokens.push_back(tok);
        tok = strtok(NULL, split_tokens);
    }

    for (auto& i : tokens){
        ret.push_back(std::string(i));
    }
    return ret;
    delete[] cstr;
}
std::string parser::parse(std::string i){

}
bool shell::execute(std::vector<std::string> i){
if (i.size() == 0){
  return true;
}
for (int k = 0; k < builtins::num_builtins(); k++){
  if (builtins::newsh_builtins[k] == i[0]){
    return (*builtins::sh_builtins[k])(stringutil::str_vector_toCSTR(i));
  }
}
    auto& ref = i;
    return launch_process(ref);
}
std::string shell::readline(){
std::string ret;
std::getline(std::cin, ret);
    return ret;
}
void shell::main_loop(){
    bool status;
    std::string line;
    std::vector<std::string> args;
do {
  std::cout << "$ ";
  line = readline();
  args = split_line(line);
  status = execute(args);

} while(status);

}
bool shell::launch_process(std::vector<std::string>& args) {
  //const char* bin = args[0].c_str();
  //std::cout << bin << std::endl;
  //std::vector<char*> v;
  int status;
  /*for (const auto& k : args){
    char* buff = new char[k.size()+1];
    strcpy(buff, k.c_str());
    v.push_back(buff);
  }

  char** argv = new char* [v.size()+1];
  int count = 0;
  for (const auto& i : v){
    argv[count] = i;
    count++;
  }*/
  /*char** argv = new char* [args.size()];
  char* p;
  for (int i = 0; i < args.size(); i++){
    p = new char [args[i].size()];
    strcpy(p, args[i].c_str());
    argv[i] = p;
  }*/
  char** argv = stringutil::str_vector_toCSTR(args);
  pid_t pid, wpid;
  pid = fork();
  if (pid == 0){ //fork didn't work
      if (execvp(*argv, argv) <  0){
          std::cerr << "newsh: error: failed to execute ";
          for (int i = 0; i < args.size(); i++){
            std::cout << argv[i] << " ";
          }
      }
  for (int i = 0; i < args.size(); i++){
          if (argv[i] != NULL){
            delete [] argv[i];
        }
      }
      //exit(-1);
  } else if(pid < 0){
    std::cerr << "ERROR FORKING" << std::endl;
    return false;
  }else {
      do {
        wpid = waitpid(pid, &status, WUNTRACED);
      } while(!WIFEXITED(status) && !WIFSIGNALED(status));
  }
  for (int i = 0; i < args.size(); i++){
      if (argv[i] != NULL){
        delete [] argv[i];
    }
  }
  return true;
}

  #endif
