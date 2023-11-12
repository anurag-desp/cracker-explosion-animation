#include <iostream>
#include <vector>
#include <cmath>
#include <string>

#include "./globals.hpp"
// #include "./projectile.hpp"
#include "./animation.hpp"



int main (int argc, char **argv) {
    std::string color = "blue";
    Animation anime(HEIGHT, WIDTH, true, '*', color);

    anime.set_initial_velocity(5.0, -5.0);
    anime.set_acceleration(0.0, .98);
    anime.set_initial_positions(19.0, 0.0);
    // anime.set_color("red");
    std::pair<int, int> dims = anime.get_plane_size();
    std::cout << dims.first << "\t" << dims.second << std::endl;
    anime.animate();

    return 0;
}