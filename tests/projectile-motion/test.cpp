#include <iostream>
#include <string>
#include "./colormod.hpp"


int main (int argc, char **argv) {
    
    std::string rocket = "/\\\n||\n||\n";
    Color::Modifier blue(Color::FG_BLUE);
    Color::Modifier def(Color::FG_DEFAULT);
    // std::cout << "This ->" << blue << "ro" << def << "<- is red." << std::endl;
    std::cout << blue << rocket << std::endl;
    return 0;
}