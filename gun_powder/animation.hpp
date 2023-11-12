#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <thread>
#include <string>

#include "./projectile.hpp"
#include "./colormod.hpp"
#define clear_screen() std::cout << "\033[H\033[2J\033[3J"


class Animation {
    private:
        std::vector<std::vector<char>> plane;
        int height,
            width;

        Color::Modifier color_modifier;
        bool keep_path;

        char curr_projectile_shape;

        std::vector<std::string> color_list = {"red", "blue", "green", "yellow", "megenta", "cyan", "white"};

    
        /* can be any shape of projectile. Ball just seems a little intuitive. 
           So, I'm going with the name 'ball'.*/
        Projectile *ball;

        void move_in_x_direction (int time) {
            // s = ut
            ( this -> ball -> curr_pos_i) += ( ( this -> ball -> curr_velocity_i ) * ( (float) time ) );
        }

        void update_velocity_in_x_direction (int time) {
            // v = u + at;
            this -> ball -> curr_velocity_i = ( this -> ball -> curr_velocity_i ) + ( ( this -> ball -> accl_i ) * ( (float) time ) );
        }

        void move_in_y_direction (int time) {
            // s = ut + 1/2(a * pow(t, 2))
            ( this -> ball -> curr_pos_j ) += ( ( ( this -> ball -> curr_velocity_j ) * (float) time ) * ( 0.5 * ( this -> ball -> accl_j ) * ( (float) std::pow(time, 2) ) ) );
        }

        void update_velocity_in_y_direction (int time) {

            // v = u + at;
            this -> ball -> curr_velocity_j = ( this -> ball -> curr_velocity_j ) + ( ( this -> ball -> accl_j ) * time );
        }

        bool are_valid (int new_x_pos, int new_y_pos) {
            bool valid_x = false;
            bool valid_y = false;

            if ( ( new_x_pos >= 0 ) && ( new_x_pos < ( this -> width ) ) ) {
                valid_x = true;
            }

            if ( ( new_y_pos >= 0 ) && ( new_y_pos < ( this -> height ) ) ) {
                valid_y = true;
            }

            return valid_x & valid_y;
        }

        void sleep () {
            using namespace std::chrono_literals;
            const auto start = std::chrono::high_resolution_clock::now();
            std::this_thread::sleep_for(25ms);
            const auto end = std::chrono::high_resolution_clock::now();
            const std::chrono::duration<double, std::milli> elapsed = end - start;
        }

    public:
        Animation (int height, int width, bool keep_path, char projectile_shape, std::string projectile_color) {
            this -> height = height;
            this -> width  = width; 
            this -> keep_path = keep_path;
            plane.resize(height, std::vector<char>(width, ' '));
            this -> curr_projectile_shape = projectile_shape;


            this -> ball = new Projectile(projectile_shape, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);
            
            this -> ball -> color = projectile_color;
            this -> set_projectile_color(this -> ball -> color);
            
            this -> plane[(int) this -> ball -> curr_pos_i][(int) this -> ball -> curr_pos_j] = (this -> ball -> shape); 
        }

        void set_initial_velocity (float vel_i, float vel_j) {
            (this -> ball -> curr_velocity_i) = vel_i;
            (this -> ball -> curr_velocity_j) = vel_j;
        }

        void set_acceleration (float accl_i, float accl_j) {
            (this -> ball -> accl_i) = accl_i;
            (this -> ball -> accl_j) = accl_j;
        }

        void set_initial_positions (float position_y, float position_x) {
            (this -> ball -> curr_pos_i) = position_x;
            (this -> ball -> curr_pos_j) = position_y;
            this -> plane[0][0] = ' '; 
            this -> plane[(int) this -> ball -> curr_pos_j][(int) this -> ball -> curr_pos_i] = (this -> ball -> shape); 
        }

        void set_projectile_color (std::string color) {
            
            /*
                if you're wondering why I didn't use
                switch statements, this is because 'string'
                is not really identified as a data type in Cpp.
                Hence, it makes it difficult to check for equality
                in switch statements.

                error thrown when making swtich cases with strings:
                    `expression must have integral or enum type` 
            */

            (this -> ball -> color) = color;
            if (color == "red") {
                color_modifier.set_color(Color::Code::FG_RED);
            } else if (color == "green") {
                color_modifier.set_color(Color::Code::FG_GREEN);
            } else if (color == "blue") {
                color_modifier.set_color(Color::Code::FG_BLUE);
            } else if (color == "yellow") {
                color_modifier.set_color(Color::Code::FG_YELLOW);
            } else if (color == "megenta") {
                color_modifier.set_color(Color::Code::FG_MEGENTA);
            } else if (color == "cyan") {
                color_modifier.set_color(Color::Code::FG_CYAN);
            } else if (color == "black") {
                color_modifier.set_color(Color::Code::FG_BLACK);
            } else if (color== "white") {
                color_modifier.set_color(Color::Code::FG_WHITE);
            } else {
                color_modifier.set_color(Color::Code::FG_DEFAULT);
            }
        }

        int move_projectile (int time) {

            int old_x_pos = (this -> ball -> curr_pos_i);
            int old_y_pos = (this -> ball -> curr_pos_j);
            // update the curr x position
            move_in_x_direction(time);
            update_velocity_in_x_direction(time);
            
            // update the curr y position
            move_in_y_direction(time);
            update_velocity_in_y_direction(time);

            int new_x_pos = (int) (this -> ball -> curr_pos_i);
            int new_y_pos = (int) (this -> ball -> curr_pos_j);


            if (this -> keep_path == false)
                this -> plane[old_y_pos][old_x_pos] = ' ';

            if (are_valid(new_x_pos, new_y_pos)) {
                this -> plane[new_y_pos][new_x_pos] = (this -> ball -> shape); 
                return 0;
            }
            return 1;
        };

        void print_frame() {
            int num_colors = this -> color_list.size();
            for (int i = 0; i < (int)(this -> plane.size()); i++) {
                // std::cout << "\t\t";
                for (int j = 0; j < (int)(this -> plane[0].size()); j++) {
                this -> set_projectile_color(this -> color_list[(j % num_colors)]);
                std::cout << this -> color_modifier;

                    if (this -> plane[i][j] == curr_projectile_shape) {
                        this -> plane[i][j] = '.';
                    } else if (this -> plane[i][j] == '.') {
                        this -> plane[i][j] = curr_projectile_shape;
                    }
                    std::cout << this -> plane[i][j];
                }
                std::cout << std::endl;
            }
        }

        void print_data () {
            // this -> set_projectile_color("default");
            std::cout << color_modifier;
            std::cout << "pos i: " << this -> ball -> curr_pos_i << std::endl;
            std::cout << "pos j: " << this -> ball -> curr_pos_j << std::endl;
            std::cout << "vel i: " << this -> ball -> curr_velocity_i << std::endl;
            std::cout << "vel j: " << this -> ball -> curr_velocity_j << std::endl;
            std::cout << "acc i: " << this -> ball -> accl_i << std::endl;
            std::cout << "acc j: " << this -> ball -> accl_j << std::endl;
        }
        
        // for projectiles
        int animate () {
            int time = 1; // 1 sec
            do {
                clear_screen();
                sleep();
                this ->  print_frame();
                this -> print_data();
                sleep();

                // std::cout << std::endl;
                // clear_screen();
                // getchar();getchar();
                // std::cout << std::flush;

            } while(this -> move_projectile(time) == 0);
     
            return 0;
        }

        std::pair<int, int> get_plane_size () {
            return {this -> plane.size(), this -> plane[0].size()}; 
        } 
};
