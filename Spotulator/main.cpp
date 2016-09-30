#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <random>

#include <SFML/Graphics.hpp>

enum class Direction {none, up, down, right, left};

void assert_strings(const std::vector <std::string>& a_strings)
{
    const int size = static_cast<int>(a_strings.size());
    assert(size > 0);

    for (int count{0}; count < size; ++count)
    {
        assert(a_strings[count] != "");
    }
}

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

sf::Vector2i sprite_dims(sf::Sprite& sprite)
{
    const sf::IntRect bounds{sprite.getLocalBounds()};

    assert(bounds.width > 0);
    assert(bounds.height > 0);

    return sf::Vector2i(bounds.width, bounds.height);
}

sf::Vector2i cell_dimensions(const std::vector <std::string>& image_names)
{
    const int size{static_cast<int>(image_names.size())};
    assert(size > 0);

    const sf::Vector2u null_dims{0, 0};
    assert(null_dims == sf::Vector2u(0, 0));

    int check{0};
    assert(check == 0);

    sf::Vector2i cell_dims{sf::Vector2i(0, 0)};
    assert(cell_dims == sf::Vector2i(0, 0));


    if (size > 0)
    {
        for (int count{0}; count < size; ++ count)
        {
            assert(image_names[count] != "");
        }

        std::vector <sf::Vector2u> image_dims;

        for (int count{0}; count < size; ++count)
        {
            image_dims.push_back(img_dims(image_names[count]));
        }

        assert(image_dims.size() == static_cast<unsigned int>(size));

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

        if (check == size)
        {
            cell_dims = static_cast<sf::Vector2i>(image_dims[0]);
        }
    }

    return cell_dims;
}

bool square_vec(const sf::Vector2i& vec)
{
    if (vec.x > 0 && vec.x == vec.y)
    {
        return true;
    }

    return false;
}

bool equal_vecs(const sf::Vector2i& vec_a, const sf::Vector2i& vec_b)
{
    if (vec_a == vec_b)
    {
        return true;
    }

    return false;
}

Direction rando_dir()
noexcept
{
    std::random_device rand;

    const unsigned int decide{rand()};

    const unsigned int quart{rand.max()/4};

    Direction dir;

    if (decide < quart)
    {
        dir = Direction::up;
    }
    else if (decide < 2*quart)
    {
        dir = Direction::down;
    }
    else if (decide < 3*quart)
    {
        dir = Direction::right;
    }
    else
    {
        dir = Direction::left;
    }

    return dir;
}

sf::Vector2i dir_to_vec(const Direction& dir, const int step)
noexcept
{
    assert(step > 0);

    sf::Vector2i vec{0,0};

    if (step > 0)
    {
        switch (dir)
        {
            case Direction::none:
                vec = sf::Vector2i(0, 0);
                break;
            case Direction::up:
                vec = sf::Vector2i(0, -step);
                break;
            case Direction::down:
                vec = sf::Vector2i(0, step);
                break;
            case Direction::right:
                vec = sf::Vector2i(step, 0);
                break;
            case Direction::left:
                vec = sf::Vector2i(-step, 0);
                break;
            default:
                vec = sf::Vector2i(0, 0);
        }
    }

    return vec;
}

void dir_change(Direction& dir, Direction& oldir)
{
    oldir = dir;
    dir = rando_dir();
}

void oldrase(Direction& oldir)
{
    oldir = Direction::none;
}

class arrow
{
    const std::string m_image_name;

    Direction m_dir;

    Direction m_oldir{Direction::none};

    const sf::Vector2i m_posit;

    const sf::Color m_color;

    sf::Texture m_texture;

    sf::Sprite m_sprite;

    sf::Vector2i m_dims;

    void texturize()
    {
        assert(m_image_name != "");

        if (!m_texture.loadFromFile(m_image_name))
        {
            std::cout << m_image_name << " not found!\n";
        }
    }

    void set_texture()
    {
        m_sprite.setTexture(m_texture);
    }

    void set_dims()
    {
        m_dims = sprite_dims(m_sprite);
    }

    void set_origin()
    {
        m_sprite.setOrigin(0.5f*static_cast<sf::Vector2f>(m_dims));
    }

    void set_posit()
    {
        m_sprite.setPosition(static_cast<sf::Vector2f>(m_posit));
    }

    void randir()
    {
        m_dir = rando_dir();
    }

    public:

    sf::Vector2i show_posit()
    {
        return m_posit;
    }

    void display(sf::RenderWindow& window)
    {
        window.draw(m_sprite);
    }

    arrow(const std::string& image_name, const sf::Vector2i& posit,
         const sf::Color& color)
        : m_image_name(image_name), m_dir(), m_posit(posit), m_color(color),
          m_texture(), m_sprite(), m_dims()
    {
        texturize();
        set_texture();
        set_dims();
        set_origin();
        set_posit();
        randir();
    }

    ~arrow()
    {
    }
};

class spot
{
    const std::string m_image_name;
    const int m_type;

    Direction m_dir{Direction::none};
    sf::Vector2i m_posit;

    int m_moves{0};
    sf::Vector2i m_vec{sf::Vector2i (0, 0)};

    const sf::Color m_color;

    sf::Texture m_texture;
    sf::Sprite m_sprite;
    sf::Vector2i m_dims;

    const int m_frames{0};

    int m_step{0};

    void texturize()
    {
        assert(m_image_name != "");

        if (!m_texture.loadFromFile(m_image_name))
        {
            std::cout << m_image_name << " not found!\n";
        }
    }

    void set_texture()
    {
        m_sprite.setTexture(m_texture);
    }

    void set_dims()
    {
        m_dims = sprite_dims(m_sprite);
    }

    void set_origin()
    {
        m_sprite.setOrigin(0.5f*static_cast<sf::Vector2f>(m_dims));
    }

    void set_posit()
    {
        m_sprite.setPosition(static_cast<sf::Vector2f>(m_posit));
    }

    void set_step()
    {
        m_step = m_dims.x/m_frames;
    }

    void update_posit()
    {
        m_posit = m_posit + m_vec;
    }

    void update_vec()
    {
        m_vec = dir_to_vec(m_dir, m_step);
    }

    public:

    void arrow_check(arrow& pointer)
    {
        if (m_posit == pointer.show_posit() &&
            m_type == 1)
        {
            m_moves = m_frames;
        }
    }

    void move_frame()
    {
        if (m_moves > 0)
        {
            update_posit();
            set_posit();
            --m_moves;
        }
    }

    void display(sf::RenderWindow& window)
    {
        window.draw(m_sprite);
    }

    spot(const std::string& image_name, const int type, const sf::Vector2i& posit,
         const sf::Color& color, const int frames)
        : m_image_name(image_name), m_type(type), m_posit(posit),
          m_color(color), m_texture(), m_sprite(), m_dims(), m_frames(frames),
          m_step()
    {
        texturize();
        set_texture();
        set_dims();
        set_origin();
        set_posit();
        set_step();
    }

    ~spot()
    {
    }
};

bool escaper()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
}

bool poller(sf::RenderWindow& window, sf::Event& event)
{
    return window.pollEvent(event);
}

bool closer(sf::Event& event)
{
    return event.type == sf::Event::Closed;

}

int closing(sf::RenderWindow& window)
{
    window.close();
    return 0;
}

bool traving(sf::Clock& clock, sf::Time& time, const float travis)
{
    assert(travis > 0.0f);

    if (travis > 0.0f)
    {
        time = clock.getElapsedTime();

        if (time.asSeconds() >= travis)
        {
            return true;
        }
    }

    return false;
}

void timing(sf::Clock& watch, sf::Time& timer, const float spf)
{
    assert(spf> 0.0f);
    timer = watch.getElapsedTime();

    while(timer.asSeconds() < spf)
    {
        timer = watch.getElapsedTime();
    }
}

int window_maker(const std::string& program_name,
                 std::vector <std::string>& image_names,
                 const int win_dim, const sf::Vector2i& cell_dims,
                 const float spf, const float travis, const int frames)
{
    assert(program_name != "");
    assert(is_strings(image_names));
    assert(win_dim > 0);
    assert(spf > 0.0f);

    const sf::Vector2i null_vect{0, 0};
    assert(equal_vecs(null_vect, sf::Vector2i(0, 0)));

    assert(square_vec(cell_dims));

    const sf::Color white{255, 255, 255};
    assert(white == sf::Color(255, 255, 255));

    sf::RenderWindow window(sf::VideoMode(win_dim, win_dim), program_name, sf::Style::Default);

    const sf::Vector2i posit{win_dim/2, win_dim/2};

    spot spode(image_names[0], 0, posit, white, frames);

    sf::Clock clock;
    sf::Time time;

    while (window.isOpen())
    {
        sf::Clock watch;
        sf::Time timer;

        sf::Event event;

        window.clear();

        spode.display(window);

        window.display();

        if(escaper())
        {
            return closing(window);
        }

        while (poller(window, event))
        {
            if (closer(event))
            {
                return closing(window);
            }
        }

        timing(watch, timer, spf);

        if (traving(clock, time, travis))
        {
            return 0;
        }
    }

    return 1;
}

int initiator(const std::string& program_name)
{
    const float travis{3.0f};

    assert(program_name != "");

    std::vector <std::string> image_names;

    int size{0};

    image_names.push_back("Spot.png");
    assert(image_names[size] != "");
    ++size;

    image_names.push_back("Arrow.png");
    assert(image_names[size] != "");
    ++size;

    /* const */ sf::Vector2i cell_dims{cell_dimensions(image_names)};
    assert(cell_dims.x == cell_dims.y);

    /**/ ++cell_dims.x;

    const int cells{11};
    assert(cells > 0);

    const int win_dim{cells*cell_dims.x};

    const float fps{50.0f};
    assert(fps > 0.0f);

    const float spf{1.0f/fps};

    const float timeout{30.0f};
    assert(timeout > 0.0f);

    const int frames = 16;

    if (cell_dims != sf::Vector2i(0, 0))
    {
        return window_maker(program_name, image_names, win_dim,
                            cell_dims, spf, travis, frames);
    }

    return 1;
}

class Kip
{
public:
    void SetX(int x) { this->m_x = x; }
    int GetX() { return (*this).m_x; }

private:
    int m_x;
};

int main()
{
    Kip k;
    k.SetX(42);
    assert(k.GetX() == 42);

    const std::string program_name{"Spotulator"};
    assert(program_name != "");

    std::cout << program_name << '\n';

    const int output{initiator(program_name)};

    std::cout << "Output == " << output << '\n';

    return output;
}


