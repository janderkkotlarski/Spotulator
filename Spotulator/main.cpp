#include <iostream>
#include <cassert>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

class spot
{

};

int window_maker(const std::string& program_name)
{
    const std::string spot_name{"Spot.png"};
    assert(spot_name != "");

    const std::string arrow_name{"Arrow.png"};
    assert(arrow_name != "");



    return 1;
}

int main()
{
    const std::string program_name{"Spotulator"};
    assert(program_name != "");

    return window_maker(program_name);
}

