#pragma once
#include "Object.h"
#include <vector>

class Board
{
public:
	struct RowCol
	{
		int row;
		int col;
	};

public:
	Object::Skills m_skill;
	sf::RenderWindow* m_window;
	std::string m_path;

private:
	
	int m_level;

protected:
	Object*** m_arrBoard;
	int m_Columns;
	int m_Rows;
	Player m_player;
	RowCol m_pointsPlayer[13];//точки, в которые может встать игрок
	std::vector<int> m_excluded;//точки, закрытые препятствиями
	int m_number[13];//количество монстров атакующих точку
	RowCol* m_universal;//позиции монстров
	RowCol m_r;//позиция игрока
	int m_killMonster;


public:
	
	Board(int columns, int rows, sf::RenderWindow &window, std::string path);
	void SetupBoard(bool boo = true);
	void CreateBoard();
	void DeleteBoard();

public:
	void moveM(sf::RenderWindow& window);
	bool EndGame() { return m_player.getHelth() <= 0; }
	bool Skills(int row, int col) { return m_player.skill(row, col, m_skill, *this); }
	void CreateUniversal();
	void sortUniversal(int a);//сортируем по близости к точкам, которые надо перекрыть
	void LevelUp();
	

public:
	int getColumns() { return m_Columns; }
	int getRows() { return m_Rows; }
	Object::TypeObject getBoard(int row, int col) { return m_arrBoard[row][col]->getSymbol(); }
	RowCol getPlayer();
	Object setBoard(int row, int col) { return *m_arrBoard[row][col]; }
	int getLevel() { return m_level; }
	void setSkills(Object::Skills s) { m_skill = s; }
	int getMonster();//подсчитываем количество монстров
	void setIllumination(int row, int col) { m_arrBoard[row][col]->setIllumination(row, col, *this); }
	bool getIllumination(int row, int col) { return m_arrBoard[row][col]->getIllumination(); }
	void ResetIllumination();
	void setPointsPlayer();
	void setExcluded();
	bool getExcluded(int a);
	int getHelth() noexcept { return m_player.getHelth(); }
	int getMaxEnergy() { return  m_player.getMaxEnergy(); }
	int getEnergy() { return  m_player.getEnergy(); }
	int getKillMonster() { return m_killMonster; }
	


public:
	
	friend bool  moveP(Object::Direction dir, Board& board)
	{
		return board.m_arrBoard[board.getPlayer().row][board.getPlayer().col]->motion(board.getPlayer().row, board.getPlayer().col, dir, board);
	}
	friend Object;
	friend Player;
	friend MonsterMelee;
	friend Magician;
	friend MagicianDiagonal;
};

