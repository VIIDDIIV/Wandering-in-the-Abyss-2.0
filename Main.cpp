#include "Board.h"
#include <Windows.h>
#include "Drawing.h"
#include <sstream>
int main(int argc, char* argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::string path(argv[0]);
    {
        int i = path.length() - 1;
        for (; path[i] != '\\'; i--)
        {
        }
        path.resize(i + 1);
    }
    for (int i = 0; i < path.length(); i++)
    {
        if (path[i] == '\\')
        {
            path.insert(i, "\\");
            i++;
        }
    }
    srand(static_cast<unsigned int>(time(0)));
    rand();

    sf::RenderWindow window(sf::VideoMode(780, 950), L"Странствия в бездне 2");
    window.setPosition(sf::Vector2i(550, 45));
    window.setFramerateLimit(30);
    Board board(13, 15, window, path);
    const int w = 60;
    sf::Event event;
   
    while (window.isOpen())
    {
       
        sf::Vector2i pos = sf::Mouse::getPosition(window);
        int x = pos.x / w;
        int y = pos.y / w;

        bool mot = false;//может ли игрок двинуться в выбпанную сторону

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
                
                if (event.key.code == sf::Keyboard::W)
                {
                    board.ResetIllumination();
                    mot = moveP(Object::Direction::Up, board);
                    break;
                }
                else if (event.key.code == sf::Keyboard::S)
                {
                    board.ResetIllumination();
                    mot = moveP(Object::Direction::Down, board);
                    break;
                }
                else if (event.key.code == sf::Keyboard::A)
                {
                    board.ResetIllumination();
                    mot = moveP(Object::Direction::Left, board);
                    break;
                }
                else if (event.key.code == sf::Keyboard::D)
                {
                    board.ResetIllumination();
                    mot = moveP(Object::Direction::Right, board);
                    break;
                }
                else if (event.key.code == sf::Keyboard::R)
                {
                    board.ResetIllumination();
                    board.SetupBoard();
                    drawing(board, window, w);
                    window.display();
                }
                else if (event.key.code == sf::Keyboard::Num1)
                {
                    board.setSkills(Object::Jump);
                }
                else if (event.key.code == sf::Keyboard::Num2)
                {
                    board.setSkills(Object::Shock);
                }
            if (event.type == sf::Event::MouseButtonPressed)

                if (event.key.code == sf::Mouse::Left)
                {
                    board.ResetIllumination();
                    mot = board.Skills(y, x);
                }
                else if (event.key.code == sf::Mouse::Right)
                {
                    board.ResetIllumination();
                    board.setIllumination(y, x);
                }
        }
 
        if (mot)
            board.moveM(window);
       
        drawing(board, window, w);
        if (board.EndGame())
        {
            sf::Font font;
            font.loadFromFile(board.m_path + "chiller_regular.ttf");
            sf::Text text;

            text.setFont(font);

            std::string str;
            std::ostringstream ss;
            ss << " Level : " << "\t" << board.getLevel();
            str = ss.str();
            text.setString(str);
            ss.str("");
            ss << "KILL MONSTER :" << "\t"  << board.getKillMonster();
            str = ss.str();
            text.setCharacterSize(40);


            text.setFillColor(sf::Color::Red);
            text.setPosition(330, 300);

            window.clear(sf::Color(0, 0, 0));
            window.draw(text);
          
            text.setString(str);
            text.setPosition(250, 400);
            window.draw(text);

            window.display();
            while (window.isOpen())
            {
                sf::Event event;
                while (window.pollEvent(event))
                    if (event.type == sf::Event::Closed)
                        window.close();
               

            }

        }
        window.display();
        Sleep(100);
    }

    return 0;
}

