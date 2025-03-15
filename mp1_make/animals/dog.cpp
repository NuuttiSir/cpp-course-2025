/**
 * @file dog.cpp
 * @author Lisa Sproat
 */

#include "dog.hpp"


Dog::Dog(const std::string& name_)
    : name(name_), age(0), x(0), y(0) {  
    std::cout << "[Dog::Dog] Congratulations on your new dog!\n";
}

void Dog::bark() const {
    std::cout << "[Dog::bark] " << name << " says, \"Woof!\"\n";
}

void Dog::run(int x_, int y_){
    std::cout << "[Dog::run] Your dog is running away!\n";
    x = x_;
    y = y_;
}

void Dog::read_tag() const{
    std::cout << "[Dog::read_tag] Hi, my name is " << name
              << std::endl;
}

std::pair<int, int> Dog::radio_collar() const{
    std::cout << "[Dog::radio_collar] Locating your dog...\n";
    return std::make_pair(x, y);
}
