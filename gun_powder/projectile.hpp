#pragma once
#include <string>

class Projectile {
    public:
        char shape;
        std::string body; // for more complex projectiles

        float curr_velocity_i,
              curr_velocity_j;
        
        float accl_i,
              accl_j;
        
        float curr_pos_i,
              curr_pos_j;
        
        std::string color;
        // in case I decide to do something with Linked Lists
        struct Projectile *next;


        // constructor
        Projectile (char shape, int curr_pos_i, int curr_pos_j) {
            this -> shape = shape;
            
            this -> curr_velocity_i = 0;
            this -> curr_velocity_j = 0;
            
            this -> accl_i = 0.00;
            this -> accl_j = 9.80;

            this -> curr_pos_i = curr_pos_i;
            this -> curr_pos_j = curr_pos_j;
        }

        Projectile (char shape, float curr_velocity_i, float curr_velocity_j, float accl_i, float accl_j, int curr_pos_i, int curr_pos_j) {
            this -> shape = shape;

            this -> curr_velocity_i = curr_velocity_i;
            this -> curr_velocity_j = curr_velocity_j;

            this -> accl_i = accl_i;
            this -> accl_j = accl_j;

            this -> curr_pos_i = curr_pos_i;
            this -> curr_pos_j = curr_pos_j;
        }
};