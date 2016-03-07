#include "newsh.h"



/*int main(int argc, char* argv[]){

    do {
        std::cout << "> ";
        std::string line = shell::readline();
        std::string args = parser::split_line(line);
        status = shell::execute(args);
    }while(status);
return 0;
}*/

int main(int argc, char* argv[]){
shell::main_loop();
return 0;
}





