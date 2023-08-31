#include "Board.h"
#include <cstdlib> // для rand() и srand()
#include <math.h>
#include <Windows.h>
#include <string>
#include <utility>
#include "Drawing.h"
template < class T>
void swap(T& x, T& y)
{
	T tmp{ std::move(x) };
	x = std::move(y);
	y = std::move(tmp);
}
Board::Board(int columns, int rows, sf::RenderWindow& window, std::string path) : m_Columns(columns), m_Rows(rows), m_level(1), m_skill(Object::Jump), m_window(&window), m_killMonster(0), m_path(path)
{
	m_r.row = m_Rows - 1;
	m_r.col = m_Columns / 2;
	
	
	CreateBoard();
	m_arrBoard[m_Rows - 1][m_Columns / 2] = &m_player;
	SetupBoard(false);
	ResetIllumination();
}
void Board::SetupBoard(bool boo)
{
	if (m_arrBoard != nullptr && boo)
		DeleteBoard();
	if (m_arrBoard == nullptr)
		CreateBoard();
	for (int row = 0; row < m_Rows; row++)
		for (int col = 0; col < m_Columns; col++)
			if (m_r.row == row && m_r.col == col)
				continue;
			else
				m_arrBoard[row][col] = new Object((rand() % 65 > ((row < 2) ? 0 : ((row < 5) ? 2 : ((row < 9) ? 4 : ((row < 13) ? 2 : 0))))) ? Object(Object::Emptiness) :((rand() % 2 == 0) ? Object( Object::Lava,1) : Object(Object::Wall,1)));

    delete  m_arrBoard[0][m_Columns / 2];
	
	swap(m_arrBoard[m_r.row][m_r.col], m_arrBoard[m_Rows - 1][m_Columns / 2]);
	
	m_arrBoard[0][m_Columns / 2] = new Object(Object::Portal);
	
	
	for (int i = 0; i < 1 + m_level;)
	{
		int row = rand() % (m_Rows - 3);
		int col = rand() % m_Columns;
		if (m_arrBoard[row][col]->getSymbol() == Object::Emptiness)
		{
			delete m_arrBoard[row][col];
			m_arrBoard[row][col] = new MonsterMelee;
			i++;
		}
	}
	for (int i = 0; i < 0 + m_level/2;)
	{
		int row = rand() % (m_Rows - 5);
		int col = rand() % m_Columns;
		if (m_arrBoard[row][col]->getSymbol() == Object::Emptiness)
		{
			delete m_arrBoard[row][col];
			m_arrBoard[row][col] = new Magician;
			i++;
		}
	}
	for (int i = 0; i < -1 + m_level / 2 + m_level % 2;)
	{
		int row = rand() % (m_Rows - 5);
		int col = rand() % m_Columns;
		if (m_arrBoard[row][col]->getSymbol() == Object::Emptiness)
		{
			delete m_arrBoard[row][col];
			m_arrBoard[row][col] = new MagicianDiagonal;
			i++;
		}
	}
	m_player.ResetEnergy();
	ResetIllumination();
	setPointsPlayer();
}
void Board::CreateBoard()
{
	if (m_arrBoard != nullptr)
		DeleteBoard();

	m_arrBoard = new Object ** [m_Rows];

	for (int row = 0; row < m_Rows; row++)
	{
		m_arrBoard[row] = new Object*[m_Columns];

	}
}
void Board::DeleteBoard(void)
{
	RowCol r = getPlayer();
	m_r = getPlayer();
	if (m_arrBoard != nullptr)
	{
		for (int row = 0; row < m_Rows; row++)
		{
			if (m_arrBoard[row] != nullptr)
			{
				for (int col = 0; col < m_Columns; col++)
				{
					if (r.row == row && r.col == col)
						continue;
					delete m_arrBoard[row][col];
					m_arrBoard[row][col] = nullptr;	
				}
				
			}
		}
	}
}

Board::RowCol Board::getPlayer()
{
	RowCol r;
	for (int row = 0; row < m_Rows; row++)
		for (int col = 0; col < m_Columns; col++)
			if (m_arrBoard[row][col]->getSymbol() == Object::Player)
			{
				r.row = row;
				r.col = col;
				return r;
			}

	r.row = m_Rows;//if the player is not found
	r.col = m_Columns;
	return  r;
}
void Board::moveM(sf::RenderWindow& window)
{
	for (int i = 0; i < 13; i++)
		m_number[i] = 0;
	setPointsPlayer();
	
	CreateUniversal();
	
	m_r = getPlayer();
	for (int i = 0; i < getMonster(); i++)
	{
			sortUniversal(i);
		if (m_arrBoard[m_universal[i].row][m_universal[i].col]
			->motion(m_universal[i].row, m_universal[i].col, m_arrBoard[m_universal[i].row][m_universal[i].col]
			->Logic(m_universal[i].row, m_universal[i].col, *this), *this))
			m_arrBoard[m_universal[i].row][m_universal[i].col]->animation(window, m_universal[i].row, m_universal[i].col, *this);
	}
	
}
int Board::getMonster()
{
	int a = 0;
	for (int row = 0; row < m_Rows; row++)
		for (int col = 0; col < m_Columns; col++)
			if (m_arrBoard[row][col]->getSymbol() > Object::Player)
				a++;
	return a;
}
void Board::setPointsPlayer()
{
	m_r = getPlayer();
	m_pointsPlayer[0] = m_r;

	m_pointsPlayer[1].row = m_r.row + 1;
	m_pointsPlayer[1].col = m_r.col;

	m_pointsPlayer[2].row = m_r.row - 1;
	m_pointsPlayer[2].col = m_r.col;

	m_pointsPlayer[3].row = m_r.row;
	m_pointsPlayer[3].col = m_r.col + 1;

	m_pointsPlayer[4].row = m_r.row;
	m_pointsPlayer[4].col = m_r.col - 1;

	m_pointsPlayer[5].row = m_r.row - 1;
	m_pointsPlayer[5].col = m_r.col - 2;

	m_pointsPlayer[6].row = m_r.row - 2;
	m_pointsPlayer[6].col = m_r.col - 1;

	m_pointsPlayer[7].row = m_r.row - 2;
	m_pointsPlayer[7].col = m_r.col + 1;

	m_pointsPlayer[8].row = m_r.row - 1;
	m_pointsPlayer[8].col = m_r.col + 2;

	m_pointsPlayer[9].row = m_r.row + 1;
	m_pointsPlayer[9].col = m_r.col - 2;

	m_pointsPlayer[10].row = m_r.row + 2;
	m_pointsPlayer[10].col = m_r.col - 1;

	m_pointsPlayer[11].row = m_r.row + 2;
	m_pointsPlayer[11].col = m_r.col + 1;

	m_pointsPlayer[12].row = m_r.row + 1;
	m_pointsPlayer[12].col = m_r.col + 2;
}
void Board::setExcluded()
{
	for (int i = 0; i < 13; i++)
		if (m_pointsPlayer[i].row < 0 || m_pointsPlayer[i].col < 0 || m_pointsPlayer[i].row >= m_Rows || m_pointsPlayer[i].col >= m_Columns)
			m_excluded.push_back(i);
		else
			switch (m_arrBoard[m_pointsPlayer[i].row][m_pointsPlayer[i].col]->getSymbol())
			{
			case Object::Lava:
			case Object::Wall:
				m_excluded.push_back(i);
			}
}
bool Board::getExcluded(int a)
{
	for (const auto& element : m_excluded)
		if (element == a)
			return false;
	return true;
}
void Board::CreateUniversal()
{
	if(m_universal != nullptr)
		delete[] m_universal;
	m_universal = new RowCol[getMonster()];
	int i = 0;
	 for (int row = 0; row < m_Rows; row++)
		for (int col = 0; col < m_Columns; col++)
			if (m_arrBoard[row][col]->getSymbol() > Object::Player)
			{
				m_universal[i].row = row;
				m_universal[i].col = col;
				i++;
			}
}
void Board::sortUniversal(int a)
{
	for (int i = a; i < getMonster() - 1; i++)
	{
		for(int j = i + 1; j < getMonster(); j++)
			if (m_arrBoard[m_universal[i].row][m_universal[i].col]->Comparison(m_universal[i].row, m_universal[i].col, *this)
				> m_arrBoard[m_universal[j].row][m_universal[j].col]->Comparison(m_universal[j].row, m_universal[j].col, *this))
				swap(m_universal[i], m_universal[j]);		
	}
}
void Board::ResetIllumination()
{
	for (int row = 0; row < m_Rows; row++)
		for (int col = 0; col < m_Columns; col++)
			m_arrBoard[row][col]->illuminationF();
}
void Board::LevelUp()
{
	m_r = getPlayer();
	sf::Texture Choice;
	Choice.loadFromFile(m_path + "окно.png");
	sf::Sprite choice(Choice);
	sf::RectangleShape square(sf::Vector2f(60.f, 60.f));

	sf::RenderWindow window1(sf::VideoMode(400, 300)," ", sf::Style::None);
	window1.setFramerateLimit(30);
	window1.draw(choice);
	square.setFillColor(sf::Color(0, 0, 0));
	square.setPosition(m_r.col * 60, m_r.row * 60);
	m_window->draw(square);
	m_window->display();
	window1.display();
	

	while (window1.isOpen())
	{
		sf::Event event;
		
		sf::Vector2i pos = sf::Mouse::getPosition(window1);
		int x = pos.x / 200;
		
		while (window1.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
				continue;

			if (event.type == sf::Event::MouseButtonPressed)
				if (event.key.code == sf::Mouse::Left)
				{
					if (x == 0)
					{
						m_player.setHelth(-1);
						window1.close();
					}
					else if (x == 1)
					{
						m_player.setEnergy(20);
						window1.close();
					}
			}
			
		}
	}
}
