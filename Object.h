#pragma once
#include <SFML/Graphics.hpp>
class Board;
class Object
{
public:
	enum Skills
	{
		Jump,
		Shock
	};
	enum TypeObject
	{
		Emptiness,
		Lava,
		Wall,
		Portal,
		Player,
		MonsterMelee,
		Magician,
		MagicianDiagonal,
		
	};
	enum Direction
	{
		Up,
		Down,
		Left,
		Right,
		LeftUp,
		LeftDown,
		RightUp,
		RightDown
	};
	enum Curses
	{
		NotCurse,
		Stun
	};
protected:
	TypeObject m_symbol;
	int m_helth;
	bool m_illumination;// параметр для подсветки атаки
	Curses m_curses;
	int m_time;//время действия проклятия

public:
	Object(TypeObject symbol= Emptiness,int helth = 1);
	TypeObject getSymbol() noexcept { return m_symbol; }
	void setSymbol(TypeObject c) noexcept {  m_symbol = c; }
	int getHelth() noexcept { return m_helth; }
	bool getIllumination() { return m_illumination; }
	void illuminationF() { m_illumination = false; }
	void illuminationT() { m_illumination = true; }
	Curses getCurses() { return m_curses; }
	void setCurses(Curses curses, int time) { m_curses = curses; m_time = time; }
	
public:
	virtual void setHelth(int c) noexcept { m_helth -= c; }
	virtual Direction LogicLogic(int row, int col, int Mrow, int Mcol, Board& board);//выбор пути к точки
	virtual Direction Logic(int row, int col, Board& board) { return Up; }//выбор точки для атаки
	virtual bool motion(int row, int col, Direction dir, Board &board);
	virtual bool CheckLogic(int row, int col, Object::Direction dir, Board& board);//смотрим, можно ли двинуться в этом напрвлении
	virtual bool skill(int row, int col, Skills s) { return true; }
	virtual int Comparison(int Mrow, int Mcol, Board& board) { return 0; } // количество ходов необходимых для перекрытия точки
	virtual void setIllumination(int row, int col, Board& board) { }
	virtual void animation (sf::RenderWindow & window, int row, int col, Board& board) { }
};
class Player : public Object
{
//public:
	int m_maxEnergy;
	int m_energy;
	int m_energyJump;
	int m_energyShock;

public:
	Player (TypeObject symbol= Object::Player, int helth = 3) noexcept : Object(symbol,helth), m_maxEnergy(100), m_energy(m_maxEnergy), m_energyJump (20), m_energyShock(20)  {}
	virtual bool motion(int row, int col, Direction dir, Board &board);
	void attackMove(int row, int col, Direction dir, Board& board);
	virtual bool skill(int row, int col, Skills s, Board& board);
	
public:
	int getMaxEnergy() { return m_maxEnergy; }
	int getEnergy() { return m_energy; }
	void ResetEnergy() { m_energy = m_maxEnergy; }
	void setEnergy(int a) { m_maxEnergy += a; }

};
class MonsterMelee : public Object
{
public:
	MonsterMelee(TypeObject symbol = Object::MonsterMelee, int helth = 1) noexcept : Object(symbol, helth) {}
public:
	void ProverkaHelth() noexcept { m_symbol = (m_helth > 0) ? m_symbol : Emptiness; }
	bool attack(int row, int col, Board& board);
	bool ProverkaPoint(int a, Board& board);
	void setPoint(int i, int* number);

public:
	virtual void setHelth(int c) noexcept { m_helth -= c;  ProverkaHelth(); }
	virtual bool motion(int row, int col, Direction dir, Board& board);
	virtual Direction Logic(int Mrow, int Mcol, Board& board);
	virtual int Comparison(int Mrow, int Mcol, Board& board);
	virtual void setIllumination(int row, int col, Board& board);
};
class Magician : public Object
{
public:
	Magician (TypeObject symbol = Object::Magician, int helth = 1) noexcept : Object(symbol, helth) {}

public:
	void ProverkaHelth() noexcept { m_symbol = (m_helth > 0) ? m_symbol : Emptiness; }
	bool attack(int row, int col, Board& board);
	bool ProverkaPoint(int a, Board& board);
	void setPoint(int i, int* number);
public:
	virtual void setHelth(int c) noexcept { m_helth -= c;  ProverkaHelth(); }
	virtual bool motion(int row, int col, Direction dir, Board& board);
	virtual Direction Logic(int Mrow, int Mcol, Board& board);
	virtual int Comparison(int Mrow, int Mcol, Board& board);
	virtual void setIllumination(int row, int col, Board& board);
	virtual void animation(sf::RenderWindow& window, int row, int col, Board& board);
};
class MagicianDiagonal : public Object
{
public:
	MagicianDiagonal(TypeObject symbol = Object::MagicianDiagonal, int helth = 1) noexcept : Object(symbol, helth) {}

public:
	void ProverkaHelth() noexcept { m_symbol = (m_helth > 0) ? m_symbol : Emptiness; }
	bool attack(int row, int col, Board& board);
	bool ProverkaPoint(int a, Board& board);
	void setPoint(int i, int* number);
public:
	virtual void setHelth(int c) noexcept { m_helth -= c;  ProverkaHelth(); }
	virtual bool motion(int row, int col, Direction dir, Board& board);
	virtual Direction Logic(int Mrow, int Mcol, Board& board);
	virtual int Comparison(int Mrow, int Mcol, Board& board);
	virtual void setIllumination(int row, int col, Board& board);
	virtual void animation(sf::RenderWindow& window, int row, int col, Board& board);
};