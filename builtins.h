#include <string>
#include <vector>
#include <iostream>
#include <pwd.h>
#include <unistd.h>
#ifndef BUILTINS_H
#define BUILTINS_H

namespace builtins {

  bool sh_cd(char**);
  bool sh_exit(char**);
  bool sh_help(char**);
  int num_builtins(void);
    std::string newsh_builtins [] = {
      "cd",
      "exit",
      "help"
    }; //for command lookup
int num_builtins(){
  return sizeof(newsh_builtins) / sizeof(std::string);
}
  bool (*sh_builtins[])(char**) = {
    &sh_cd,
    &sh_exit,
    &sh_help
  };
  extern bool sh_cd (char** args){
    if (args[2] != NULL){
      std::cerr << "error - cd expects only one argument" << std::endl;
    }
    if (args[1] == NULL){
      struct passwd *p = getpwuid(getuid()); //return a struct that contains users uid
      const char* home_dir = p->pw_dir; //get users home  directory path
      chdir(home_dir); //change directory to the home dir. This is to mimic the functionality of most shells which change directory to home if no arguments are given
    }else {
      chdir(args[1]);
    }
    return true;
  }

  extern bool sh_exit (char** code){
    return false; //simply returning false will exit the reading input loop.
  }

  extern bool sh_help(char**) {
    std::cout << "Welcome to newsh, a very basic shell utility. "
              << "Built in commands are cd, exit, and help. "
              << "for more information on a program, please refer to the manual, by executing man"
              << std::endl;
              return true;
  }
} //end namespace builtins

#endif
