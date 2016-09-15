#include <iostream>
#include <cassert>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

sf::Vector2u img_dims(const std::string& img_name)
{
    assert(img_name != "");

    sf::Texture texture;

    if (!texture.loadFromFile(img_name))
    {
        std::cout << img_name << " not found!\n";
    }

    return texture.getSize();
}

sf::Vector2i cell_dimensions(const std::vector <std::string>& image_names)
{
    const int size{static_cast<int>(image_names.size())};
    assert(size > 0);

    const sf::Vector2u null_dims{0, 0};
    assert(null_dims == sf::Vector2u(0, 0));

    std::vector <sf::Vector2u> image_dims;

    for (int count{0}; count < size; ++count)
    {
        image_dims.push_back(img_dims(image_names[count]));
    }

    assert(image_dims.size() == static_cast<unsigned int>(size));

    int check{0};

    if (image_dims[0] != sf::Vector2u(0, 0))
    {
        ++check;
    }

    for (int count{1}; count < size; ++count)
    {
        if (image_dims[0] == image_dims[count])
        {
            ++check;
        }
    }

    sf::Vector2i cell_dims{sf::Vector2i(0, 0)};

    if (check == size)
    {
        cell_dims = static_cast<sf::Vector2i>(image_dims[0]);
    }

    return cell_dims;

}

class spot
{
    const std::string m_spot_name;

    const int m_type;

    const sf::Vector2i m_posit;

    const sf::Color m_color;

    const sf::Texture m_texture;

    const sf::Sprite m_sprite;




};

int window_maker(const std::string& program_name)
{
    std::vector <std::string> image_names;

    int size{0};

    image_names.push_back("Spot.png");
    assert(image_names[size] != "");
    ++size;

    image_names.push_back("Arrow.png");
    assert(image_names[size] != "");
    ++size;

    const sf::Vector2i cell_dims{cell_dimensions(image_names)};



    if (cell_dims != sf::Vector2i(0, 0))
    {
        std::cout << "Works!\n";
        return 0;
    }

    return 1;
}

int main()
{
    const std::string program_name{"Spotulator"};
    assert(program_name != "");

    return window_maker(program_name);
}

