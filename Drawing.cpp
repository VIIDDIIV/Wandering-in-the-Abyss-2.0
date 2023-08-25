//#include <SFML/Graphics.hpp>
#include "Board.h"
#include <string>
#include <sstream>
void drawing(Board& board, sf::RenderWindow& window, const int w)//, sf::Sprite monster, sf::Sprite mag, sf::RectangleShape square, sf::Sprite lava, sf::Sprite portal, sf::Sprite wall, sf::Sprite bowman)
{
    sf::RectangleShape square(sf::Vector2f(60.f, 60.f));
    sf::Texture magg;
    magg.loadFromFile(board.m_path + "маг.png");
    sf::Sprite mag(magg);

    sf::Texture mon;
    mon.loadFromFile(board.m_path + "рыцарь.png");
    sf::Sprite monster(mon);

    sf::Texture Bowman;
    Bowman.loadFromFile(board.m_path + "лучник.png");
    sf::Sprite bowman(Bowman);

    sf::Texture Lava;
    Lava.loadFromFile(board.m_path + "лава.png");
    sf::Sprite lava(Lava);

    sf::Texture port;
    port.loadFromFile(board.m_path + "портал.png");
    sf::Sprite portal(port);

    sf::Texture Wall;
    Wall.loadFromFile(board.m_path + "камень1.png");
    sf::Sprite wall(Wall);

    sf::Texture pl;
    pl.loadFromFile(board.m_path + "игрок.png");
    sf::Sprite player(pl);

    sf::Texture Heart;
    Heart.loadFromFile(board.m_path + "сердце.png");
    sf::Sprite heart(Heart);

    window.clear();
    for (int row = 0; row < board.getRows(); row++)
        for (int col = 0; col < board.getColumns(); col++)
        {
            if (board.getIllumination(row, col))
            {
                square.setFillColor(sf::Color(10, 10, 10));
                square.setPosition(col * w, row * w);
                window.draw(square);
            }
            else if (board.getBoard(row, col) == Object::Emptiness)
            {
                square.setFillColor(sf::Color(0, 0, 0));
                square.setPosition(col * w, row * w);
                window.draw(square);
            }
        
            if (board.getBoard(row, col) == Object::Lava)
            {
                lava.setPosition(col * w, row * w);
                window.draw(lava);
            }
            else if (board.getBoard(row, col) == Object::Wall)
            {
                wall.setPosition(col * w, row * w);
                window.draw(wall);
            }
            else if (board.getBoard(row, col) == Object::Player)
            {
                player.setPosition(col * w, row * w);
                window.draw(player);
            }
            else if (board.getBoard(row, col) == Object::Portal)
            {
                portal.setPosition(col * w, row * w);
                window.draw(portal);
            }
            else if (board.getBoard(row, col) == Object::MonsterMeleeDiagonal)
            {
                square.setFillColor(sf::Color(50, 100, 0));
                square.setPosition(col * w, row * w);
                window.draw(square);
            }
            else if (board.getBoard(row, col) == Object::MonsterMelee)
            {
                monster.setPosition(col * w, row * w);
                window.draw(monster);
            }
            else if (board.getBoard(row, col) == Object::Mag)
            {
                mag.setPosition(col * w, row * w);
                window.draw(mag);
            }
            else if (board.getBoard(row, col) == Object::MagDiagonal)
            {
                bowman.setPosition(col * w, row * w);
                window.draw(bowman);
            }
            
        }
    for (int i = 0; i < board.getHelth() && i < 7; i++)
    {
        heart.setPosition(i * 39 + 10 + i*10,w*board.getRows() + 1);
        window.draw(heart);
    }
    sf::Font font;
    font.loadFromFile(board.m_path + "chiller_regular.ttf");
    sf::Text text;

    text.setFont(font);

    std::string energy;
    std::ostringstream ss;
    std::string str;
    
    ss << board.getEnergy() << "/" << board.getMaxEnergy();
    energy = ss.str();
    text.setString(energy);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::Blue);

    text.setPosition(w * (board.getColumns() - 2), w * board.getRows() + 10);
    window.draw(text);
    ss.str("");
    ss << " Level : " << " " << board.getLevel();
    str = ss.str();
    text.setString(str);
    text.setPosition(w * (board.getColumns()/2), w * board.getRows() + 10);
    text.setFillColor(sf::Color::Red);
    window.draw(text);
    
}