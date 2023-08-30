#include "Object.h"
#include "Drawing.h"
#include <Windows.h>
#include <utility>
template < class T>
void swap(T & x, T & y)
{
 T tmp{ std::move(x) };
 x = std::move(y);
 y = std::move(tmp);
}
Object::Object(TypeObject symbol , int helth):m_symbol(symbol), m_helth(helth), m_curses(NotCurse), m_time(0)
{
}
bool Object::motion(int row, int col, Direction dir, Board& board)
{
	if (dir == Up)
	{
		if (row - 1 < 0 || ( board.m_arrBoard[row - 1][col]->getSymbol() > Emptiness && board.m_arrBoard[row - 1][col]->getSymbol() <= Player ))
			return false;
		swap(board.m_arrBoard[row][col], board.m_arrBoard[row - 1][col]);
		board.m_arrBoard[row][col]->setSymbol(Emptiness);


	}
	else if (dir == Down)
	{
		if (row + 1 > board.m_Rows || (board.m_arrBoard[row + 1][col]->getSymbol() > Emptiness && board.m_arrBoard[row + 1][col]->getSymbol() <= Player))
			return false;
		swap(board.m_arrBoard[row][col], board.m_arrBoard[row + 1][col]);
		board.m_arrBoard[row][col]->setSymbol(Emptiness);

	}
	else if (dir == Left)
	{
		if (col - 1 < 0 || (board.m_arrBoard[row][col - 1]->getSymbol() > Emptiness && board.m_arrBoard[row][col - 1]->getSymbol() <= Player))
			return false;
		swap(board.m_arrBoard[row][col], board.m_arrBoard[row][col - 1]);
		board.m_arrBoard[row][col]->setSymbol(Emptiness);

	}
	else if (dir == Right)
	{
		if (col + 1 > board.m_Columns || (board.m_arrBoard[row][col + 1]->getSymbol() > Emptiness && board.m_arrBoard[row][col + 1]->getSymbol() <= Player))
			return false;
		swap(board.m_arrBoard[row][col], board.m_arrBoard[row][col + 1]);
		board.m_arrBoard[row][col]->setSymbol(Emptiness);

	}
	return true;
}
bool Player::motion(int row, int col, Direction dir, Board &board)
{
	
	if (dir == Up)
	{
		if (row - 1 < 0 || board.m_arrBoard[row - 1][col]->getSymbol() == Lava || board.m_arrBoard[row - 1][col]->getSymbol() == Wall) 
			return false;
		if (board.m_arrBoard[row - 1][col]->getSymbol() == Portal)
		{
			board.m_level++;
			if(board.m_level % 3 == 0)
				board.LevelUp();
			board.SetupBoard();
			return false;
		}
		else
		{
			swap(board.m_arrBoard[row][col], board.m_arrBoard[row - 1][col]);
			if(board.m_arrBoard[row][col]->getSymbol() > Object::Player)
				++board.m_killMonster;
			board.m_arrBoard[row][col]->setSymbol(Emptiness);
		}
		
	}
	else if (dir == Down)
	{
		if (row + 1 >= board.m_Rows || board.m_arrBoard[row + 1][col]->getSymbol() == Lava || board.m_arrBoard[row + 1][col]->getSymbol() == Wall)
			return false;
		if (board.m_arrBoard[row + 1][col]->getSymbol() == Portal)
		{
			board.m_level++;
			if (board.m_level % 3 == 0)
				board.LevelUp();
			board.SetupBoard();
			return false;
		}
		else
		{
			swap(board.m_arrBoard[row][col], board.m_arrBoard[row + 1][col]);
			if (board.m_arrBoard[row][col]->getSymbol() > Object::Player)
				++board.m_killMonster;
			board.m_arrBoard[row][col]->setSymbol(Emptiness);
		}
	}
	else if (dir == Left)
	{
		if (col - 1 < 0 || board.m_arrBoard[row][col-1]->getSymbol() == Lava || board.m_arrBoard[row][col-1]->getSymbol() == Wall)
			return false;
		if (board.m_arrBoard[row][col - 1]->getSymbol() == Portal)
		{
			board.m_level++;
			if (board.m_level % 3 == 0)
				board.LevelUp();
			board.SetupBoard();
			return false;
		}
		else
		{
			swap(board.m_arrBoard[row][col], board.m_arrBoard[row][col - 1]);
			if (board.m_arrBoard[row][col]->getSymbol() > Object::Player)
				++board.m_killMonster;
			board.m_arrBoard[row][col]->setSymbol(Emptiness);
		}
	}
	else if (dir == Right)
	{
		if (col + 1 >= board.m_Columns || board.m_arrBoard[row][col + 1]->getSymbol() == Lava || board.m_arrBoard[row][col + 1]->getSymbol() == Wall)
			return false;
		if (board.m_arrBoard[row][col + 1]->getSymbol() == Portal)
		{
			board.m_level++;
			if (board.m_level % 3 == 0)
				board.LevelUp();
			board.SetupBoard();
			return false;
		}
		else
		{
			swap(board.m_arrBoard[row][col], board.m_arrBoard[row][col + 1]);
			if (board.m_arrBoard[row][col]->getSymbol() > Object::Player)
				++board.m_killMonster;
			board.m_arrBoard[row][col]->setSymbol(Emptiness);
		}
	}
	attackMove(row, col, dir, board);
	return true;
}
void Player::attackMove(int row, int col, Direction dir, Board& board)
{
	if (dir == Down)
	{

		if (col + 1 < board.m_Columns && board.m_arrBoard[row][col + 1]->getSymbol() > 4)
		{
			board.m_arrBoard[row][col + 1]->setHelth(1);
			++board.m_killMonster;
		}
		if (col - 1 >= 0 && board.m_arrBoard[row][col - 1]->getSymbol() > 4)
		{
			board.m_arrBoard[row][col - 1]->setHelth(1);
			++board.m_killMonster;
		}
		if (row + 1 < board.m_Rows && col + 1 < board.m_Columns && board.m_arrBoard[row + 1][col + 1]->getSymbol() > 4)
		{
			board.m_arrBoard[row + 1][col + 1]->setHelth(1);
			++board.m_killMonster;
		}
		if (row + 1 < board.m_Rows && col - 1 >= 0 && board.m_arrBoard[row + 1][col - 1]->getSymbol() > 4)
		{
			board.m_arrBoard[row + 1][col - 1]->setHelth(1);
			++board.m_killMonster;
		}
	}
	if (dir == Up)
	{

		if (col + 1 < board.m_Columns && board.m_arrBoard[row][col + 1]->getSymbol() > 4)
		{
			board.m_arrBoard[row][col + 1]->setHelth(1);
			++board.m_killMonster;
		}
		if (col - 1 >= 0 && board.m_arrBoard[row][col - 1]->getSymbol() > 4)
		{
			board.m_arrBoard[row][col - 1]->setHelth(1);
			++board.m_killMonster;
		}
		if (row - 1 >= 0 && col + 1 < board.m_Columns && board.m_arrBoard[row - 1][col + 1]->getSymbol() > 4)
		{
			board.m_arrBoard[row - 1][col + 1]->setHelth(1);
			++board.m_killMonster;
		}
		if (row - 1 >= 0 && col - 1 >= 0 && board.m_arrBoard[row - 1][col - 1]->getSymbol() > 4)
		{
			board.m_arrBoard[row - 1][col - 1]->setHelth(1);
			++board.m_killMonster;
		}
	}
	if (dir == Left)
	{

		if (row + 1 < board.m_Rows && board.m_arrBoard[row + 1][col]->getSymbol() > 4)
		{
			board.m_arrBoard[row + 1][col]->setHelth(1);
			++board.m_killMonster;
		}
		if (row - 1 >= 0 && board.m_arrBoard[row - 1][col]->getSymbol() > 4)
		{
			board.m_arrBoard[row - 1][col]->setHelth(1);
			++board.m_killMonster;
		}
		if (row + 1 < board.m_Rows && col - 1 >= 0 && board.m_arrBoard[row + 1][col - 1]->getSymbol() > 4)
		{
			board.m_arrBoard[row + 1][col - 1]->setHelth(1);
			++board.m_killMonster;
		}
		if (row - 1 >= 0 && col - 1 >= 0 && board.m_arrBoard[row - 1][col - 1]->getSymbol() > 4)
		{
			board.m_arrBoard[row - 1][col - 1]->setHelth(1);
			++board.m_killMonster;
		}
	}
	if (dir == Right)
	{
	
		if (row + 1 < board.m_Rows && board.m_arrBoard[row + 1][col]->getSymbol() > 4)
		{
			board.m_arrBoard[row + 1][col]->setHelth(1);
			++board.m_killMonster;
		}
		if (row - 1 >= 0 && board.m_arrBoard[row - 1][col]->getSymbol() > 4)
		{
			board.m_arrBoard[row - 1][col]->setHelth(1);
			++board.m_killMonster;
		}
		if (row + 1 < board.m_Rows && col + 1 < board.m_Columns && board.m_arrBoard[row + 1][col + 1]->getSymbol() > 4)
		{
			board.m_arrBoard[row + 1][col + 1]->setHelth(1);
			++board.m_killMonster;
		}
		if (row - 1 >= 0 && col + 1 < board.m_Columns && board.m_arrBoard[row - 1][col + 1]->getSymbol() > 4)
		{
			board.m_arrBoard[row - 1][col + 1]->setHelth(1);
			++board.m_killMonster;
		}
	}
}
bool MonsterMelee::motion(int row, int col, Direction dir, Board& board)
{
	if (m_curses == Stun && m_time == 0)
	{
		m_curses = NotCurse;
	}
	else if (m_curses == Stun)
		{
			--m_time;
			return false;
		}
	bool boo = false;
	boo = attack(row, col, board);
	if(!boo)
		Object::motion(row, col, dir, board);
	return false;
}
bool MonsterMelee::attack(int row, int col, Board& board)
{
	if (col + 1 < board.m_Columns && board.m_arrBoard[row][col + 1]->getSymbol() == Player)
	{
		board.m_arrBoard[row][col + 1]->setHelth(1);
		return true;
	}
	if (col - 1 >= 0 && board.m_arrBoard[row][col - 1]->getSymbol() == Player)
	{
		board.m_arrBoard[row][col - 1]->setHelth(1);
		return true;
	}
	if (row + 1 < board.m_Rows && board.m_arrBoard[row + 1][col]->getSymbol() == Player)
	{
		board.m_arrBoard[row + 1][col]->setHelth(1);
		return true;
	}
	if (row - 1 >= 0 && board.m_arrBoard[row - 1][col]->getSymbol() == Player)
	{
		board.m_arrBoard[row - 1][col]->setHelth(1);
		return true;
	}
	return false;
}
void MonsterMelee::setIllumination(int row, int col, Board& board)
{
	if (col + 1 < board.m_Columns && board.m_arrBoard[row][col + 1]->getSymbol() != Wall)
		board.m_arrBoard[row][col + 1]->illuminationT();
	if (col - 1 >= 0 && board.m_arrBoard[row][col - 1]->getSymbol() != Wall)
		board.m_arrBoard[row][col - 1]->illuminationT();
	if (row + 1 < board.m_Rows && board.m_arrBoard[row + 1][col]->getSymbol() != Wall)
		board.m_arrBoard[row + 1][col]->illuminationT();
	if (row - 1 >= 0 && board.m_arrBoard[row - 1][col]->getSymbol() != Wall)
		board.m_arrBoard[row - 1][col]->illuminationT();
}
bool Object::CheckLogic(int row, int col, Object::Direction dir, Board &board)
{
	if (dir == Object::Direction::Up)
	{
		if (row - 1 < 0)
			return false;
		switch (board.m_arrBoard[row - 1][col]->getSymbol())
		{
		case Lava:
			return false;
		case Portal:
			return false;
		case Wall:
			return false;
		default:
			if (board.m_arrBoard[row - 1][col]->getSymbol() >= Object::Player)
				return false;
			return true;
		}
	}

	if (dir == Object::Direction::Down)
	{
		if (row + 1 >= board.m_Rows)
			return false;
		switch (board.m_arrBoard[row + 1][col]->getSymbol())
		{
		case Lava:
			return false;
		case Portal:
			return false;
		case Wall:
			return false;
		default:
			if (board.m_arrBoard[row + 1][col]->getSymbol() >= Object::Player)
				return false;
			return true;
		}
	}

	if (dir == Object::Direction::Left)
	{
		if (col - 1 < 0)
			return false;

		switch (board.m_arrBoard[row][col-1]->getSymbol())
		{
		case Lava:
			return false;
		case Portal:
			return false;
		case Wall:
			return false;
		default:
			if (board.m_arrBoard[row][col-1]->getSymbol() >= Object::Player)
				return false;
			return true;
		}

	}

	if (dir == Object::Direction::Right)
	{
		if (col + 1 >= board.m_Columns) 
			return false;

		switch (board.m_arrBoard[row][col+1]->getSymbol())
		{
		case Lava:
			return false;
		case Portal:
			return false;
		case Wall:
			return false;
		default:
			if (board.m_arrBoard[row][col + 1]->getSymbol() >= Object::Player)
				return false;
			return true;
		}
	}
	return false;
}
 Object::Direction MonsterMelee::Logic(int Mrow, int Mcol, Board& board)
{
	 int Prow = board.getPlayer().row;
	 int Pcol = board.getPlayer().col;
	 
	 Board::RowCol r[4];//задаем точки, которые атакуются монстром

	 r[0].row = Mrow - (Prow + 2);

	 r[0].col = Mcol - (Pcol);

	 r[1].row = Mrow - (Prow - 2);

	 r[1].col = Mcol - (Pcol);

	 r[2].row = Mrow - (Prow);

	 r[2].col = Mcol - (Pcol - 2);

	 r[3].row = Mrow - (Prow);

	 r[3].col = Mcol - (Pcol + 2);

	 int row = 1000;
	 int col = 1000;
	 int ii = 0;
	 for (int i = 0; i < 4; i++)
		 if (abs(r[i].row) + abs(r[i].col) == 0)
			 continue;
		 else if (abs(r[i].row) + abs(r[i].col) < abs(row) + abs(col) && ProverkaPoint(i, board))
		 {
			 row = r[i].row;
			 col = r[i].col;
			 ii = i;
		 }
	 if ( row == 1000)
	  for (int& i = ii; i < 4; i++)
		  if (abs(r[i].row) + abs(r[i].col) == 0)
			  continue;
		  else if (abs(r[i].row) + abs(r[i].col) < abs(row) + abs(col))
			 {
				 row = r[i].row;
				 col = r[i].col;
				 ii = i;
			 }
	 setPoint(ii, board.m_number);
	 return LogicLogic(row, col, Mrow, Mcol, board);
}
Object::Direction Object::LogicLogic(int row, int col, int Mrow, int Mcol, Board& board)
{
	if (abs(row) > abs(col))
	{
		if (row > 0 && CheckLogic(Mrow, Mcol, Up, board))
			return Up;
		else if (CheckLogic(Mrow, Mcol, Down, board))
			return Down;
	}
	else if (abs(row) < abs(col))
	{
		if (col > 0 && CheckLogic(Mrow, Mcol, Left, board))
			return Left;
		else if (CheckLogic(Mrow, Mcol, Right, board))
			return Right;
	}
	else
	{
		if (rand() % 2)
		{
			if (row > 0 && CheckLogic(Mrow, Mcol, Up, board))
				return Up;

			else if (CheckLogic(Mrow, Mcol, Down, board))
				return Down;
		}
		else if (col > 0 && CheckLogic(Mrow, Mcol, Left, board))
			return Left;

		else if (CheckLogic(Mrow, Mcol, Right, board))
			return Right;
	}
	return static_cast<Object::Direction> (rand() % 4);
}
bool Magician::motion(int row, int col, Direction dir, Board& board)
{
	if (m_curses == Stun && m_time == 0)
	{
		m_curses = NotCurse;
	}
	else if (m_curses == Stun)
	{
		--m_time;
		return false;
	}
	bool boo = false;
	boo = attack(row, col, board);
	if (!boo)
		Object::motion(row, col, dir, board);
	return boo;
}
bool Magician::attack(int row, int col, Board& board)
{
	for (int i = 2; row + i < board.m_Rows && i < 5; i++)
		if (board.m_arrBoard[row + i][col]->getSymbol() == Player)
		{
			board.m_arrBoard[row + i][col]->setHelth(1);
			return true;
		}
		else if (board.m_arrBoard[row + i][col]->getSymbol() != Emptiness && board.m_arrBoard[row + i][col]->getSymbol() != Lava)
			break;
	for (int i = 2; row - i >= 0 && i < 5; i++)
		if (board.m_arrBoard[row - i][col]->getSymbol() == Player)
		{
			board.m_arrBoard[row - i][col]->setHelth(1);
			return true;
		}
		else if (board.m_arrBoard[row - i][col]->getSymbol() != Emptiness && board.m_arrBoard[row - i][col]->getSymbol() != Lava)
			break;
	for (int i = 2; col + i < board.m_Columns && i < 5; i++)
		if (board.m_arrBoard[row][col + i]->getSymbol() == Player)
		{
			board.m_arrBoard[row][col + i]->setHelth(1);
			return true;
		}
		else if (board.m_arrBoard[row][col + i]->getSymbol() != Emptiness && board.m_arrBoard[row][col + i]->getSymbol() != Lava)
			break;
	for (int i = 2; col - i >= 0 && i < 5; i++)
		if (board.m_arrBoard[row][col - i]->getSymbol() == Player)
		{
			board.m_arrBoard[row][col - i]->setHelth(1);
			return true;
		}
		else if (board.m_arrBoard[row][col - i]->getSymbol() != Emptiness && board.m_arrBoard[row][col - i]->getSymbol() != Lava)
			break;
	return false;
}
Object::Direction Magician::Logic(int Mrow, int Mcol, Board& board)
{

	const int Prow = board.getPlayer().row;
	const int Pcol = board.getPlayer().col;

	Board::RowCol r[12];


	r[0].row = Mrow - (Prow + 1);

	r[0].col = Mcol - (Pcol - 4);

	r[1].row = Mrow - (Prow);

	r[1].col = Mcol - (Pcol - 3);

	r[2].row = Mrow - (Prow + 1);

	r[2].col = Mcol - (Pcol - 4);

	r[3].row = Mrow - (Prow - 4);

	r[3].col = Mcol - (Pcol - 1);

	r[4].row = Mrow - (Prow - 3);

	r[4].col = Mcol - (Pcol);

	r[5].row = Mrow - (Prow - 4);

	r[5].col = Mcol - (Pcol + 1);

	r[6].row = Mrow - (Prow - 1);

	r[6].col = Mcol - (Pcol + 4);

	r[7].row = Mrow - (Prow);

	r[7].col = Mcol - (Pcol + 3);

	r[8].row = Mrow - (Prow + 1);

	r[8].col = Mcol - (Pcol + 4);

	r[9].row = Mrow - (Prow + 4);

	r[9].col = Mcol - (Pcol + 1);

	r[10].row = Mrow - (Prow + 3);

	r[10].col = Mcol - (Pcol);

	r[11].row = Mrow - (Prow + 4);

	r[11].col = Mcol - (Pcol - 1);

	int row = 1000;
	int col = 1000;
	int ii = 0;
	for (int i = 0; i < 12; i++)
		if (abs(r[i].row) + abs(r[i].col) == 0)
			continue;
		else if (abs(r[i].row) + abs(r[i].col) < abs(row) + abs(col) && ProverkaPoint(i, board))
		{
			row = r[i].row;
			col = r[i].col;
			ii = i;
		}
	if (row == 1000)
		for (int& i = ii; i < 12; i++)
			if (abs(r[i].row) + abs(r[i].col) == 0)
				continue;
			else if (abs(r[i].row) + abs(r[i].col) < abs(row) + abs(col))
			{
				row = r[i].row;
				col = r[i].col;
				ii = i;
			}
	setPoint(ii, board.m_number);
	return LogicLogic(row, col, Mrow, Mcol, board);
}
bool Player::skill(int row, int col, Skills s, Board& board)
{
	board.m_r = board.getPlayer();

	if(s==Jump && m_energy >= m_energyJump)
		switch (board.m_arrBoard[row][col]->getSymbol())
		{
		case Lava:
		case Wall:
			return false;
		case Portal:
			board.m_level++;
			if (board.m_level % 3 == 0)
				board.LevelUp();
			board.SetupBoard();
			return false;
		default:
			if (abs(row - board.m_r.row) + abs(col - board.m_r.col) == 3 && abs(row - board.m_r.row) > 0 && abs(col - board.m_r.col) > 0)
			{
				if (board.m_arrBoard[row][col]->getSymbol() > Object::Player)
					return false;

				swap(board.m_arrBoard[row][col], board.m_arrBoard[board.m_r.row][board.m_r.col]);
				m_energy -= m_energyJump;
				return true;
			}
			return false;
		}
	if (s == Shock && m_energy >= m_energyShock)
	{
		if (board.m_arrBoard[row][col]->getSymbol() > Object::Player)
		{
			board.m_arrBoard[row][col]->setCurses(Stun, 2);
			m_energy -= m_energyShock;
			return true;
		}
		return false;
	}
	return false;
}
bool MagicianDiagonal::motion(int row, int col, Direction dir, Board& board)
{
	if (m_curses == Stun && m_time == 0)
	{
		m_curses = NotCurse;
	}
	else if (m_curses == Stun)
	{
		--m_time;
		return false;
	}
	bool boo = false;
	boo = attack(row, col, board);
	if (!boo)
		Object::motion(row, col, dir, board);
	return boo;
}
bool MagicianDiagonal::attack(int row, int col, Board& board)
{
	for (int i = 1; col + i < board.m_Columns && row + i < board.m_Rows && i < 5; i++)
		if (board.m_arrBoard[row + i][col+i]->getSymbol() == Player)
		{
			board.m_arrBoard[row + i][col+i]->setHelth(1);
			return true;
		}
		else if (board.m_arrBoard[row + i][col+i]->getSymbol() != Emptiness && board.m_arrBoard[row + i][col+i]->getSymbol() != Lava)
			break;
	for (int i = 1; col - i >= 0 && row - i >= 0 && i < 5; i++)
		if (board.m_arrBoard[row - i][col-i]->getSymbol() == Player)
		{
			board.m_arrBoard[row - i][col-i]->setHelth(1);
			return true;
		}
		else if (board.m_arrBoard[row - i][col-i]->getSymbol() != Emptiness && board.m_arrBoard[row - i][col-i]->getSymbol() != Lava)
			break;
	for (int i = 1; row - i >= 0 && col + i < board.m_Columns && i < 5; i++)
		if (board.m_arrBoard[row - i][col + i]->getSymbol() == Player)
		{
			board.m_arrBoard[row-i][col + i]->setHelth(1);
			return true;
		}
		else if (board.m_arrBoard[row-i][col + i]->getSymbol() != Emptiness && board.m_arrBoard[row-i][col + i]->getSymbol() != Lava)
			break;
	for (int i = 1; row + i < board.m_Rows && col - i >= 0 && i < 5; i++)
		if (board.m_arrBoard[row+i][col - i]->getSymbol() == Player)
		{
			board.m_arrBoard[row+i][col - i]->setHelth(1);
			return true;
		}
		else if (board.m_arrBoard[row+i][col - i]->getSymbol() != Emptiness && board.m_arrBoard[row+i][col - i]->getSymbol() != Lava)
			break;
	return false;
}
Object::Direction MagicianDiagonal::Logic(int Mrow, int Mcol, Board& board)
{
	const int Prow = board.getPlayer().row;
	const int Pcol = board.getPlayer().col;

	Board::RowCol r[8];


	r[0].row = Mrow - (Prow + 4);

	r[0].col = Mcol - (Pcol - 3);

	r[1].row = Mrow - (Prow + 3);

	r[1].col = Mcol - (Pcol - 4);

	r[2].row = Mrow - (Prow - 3);

	r[2].col = Mcol - (Pcol - 4);

	r[3].row = Mrow - (Prow - 4);

	r[3].col = Mcol - (Pcol - 3);

	r[4].row = Mrow - (Prow - 4);

	r[4].col = Mcol - (Pcol + 3);

	r[5].row = Mrow - (Prow - 3);

	r[5].col = Mcol - (Pcol + 4);

	r[6].row = Mrow - (Prow + 3);

	r[6].col = Mcol - (Pcol + 4);

	r[7].row = Mrow - (Prow + 4);

	r[7].col = Mcol - (Pcol + 3);

	int row = 1000;
	int col = 1000;
	int ii = 0;
	for (int i = 0; i < 8; i++)
		if (abs(r[i].row) + abs(r[i].col) == 0)
			continue;
		else if (abs(r[i].row) + abs(r[i].col) < abs(row) + abs(col) && ProverkaPoint(i, board))
		{
			row = r[i].row;
			col = r[i].col;
			ii = i;
		}
	if (row == 1000)
		for (int& i = ii; i < 8; i++)
			if (abs(r[i].row) + abs(r[i].col) == 0)
				continue;
			else if (abs(r[i].row) + abs(r[i].col) < abs(row) + abs(col))
			{
				row = r[i].row;
				col = r[i].col;
				ii = i;
			}
	setPoint(ii, board.m_number);
	return LogicLogic(row, col, Mrow, Mcol, board);

}
bool MonsterMelee::ProverkaPoint(int a, Board& board)
{
	board.setExcluded();
		switch (a)
		{
		case 0:
			
			if (( !board.m_number[1] && board.getExcluded(1)) || ( !board.m_number[10] && board.getExcluded(10)) || (!board.m_number[11] && board.getExcluded(11)))
				return true;
			return false;
		case 1:
			if ((!((board.m_number[6])? board.m_number[6]-1:0) && board.getExcluded(6)) || (!((board.m_number[2]) ? board.m_number[2] - 1 : 0) && board.getExcluded(2)) || (((board.m_number[7]) ? board.m_number[7] - 1 : 0) && board.getExcluded(7)))
				return true;
			return false;
		case 2:
			if ((!board.m_number[5] && board.getExcluded(5)) || (!board.m_number[4] && board.getExcluded(4)) || (!board.m_number[9] && board.getExcluded(9)))
				return true;
			return false;
		case 3:
			if ((!board.m_number[3] && board.getExcluded(3)) || (!board.m_number[8] && board.getExcluded(8)) || (!board.m_number[12] && board.getExcluded(12)))
				return true;
			return false;
		}
	return false;
}
void MonsterMelee::setPoint(int i, int* number)
{
	switch (i)
	{
	case 0:
		number[1]++;
		number[10]++;
		number[11]++;
		break;
	case 1:
		number[6]++;
		number[2]++;
		number[7]++;
		break;
	case 2:
		
		number[5]++;
		number[4]++;
		number[9]++;
		break;
	case 3:
		number[3]++;
		number[8]++;
		number[12]++;
		break;
	}
}
int MonsterMelee::Comparison(int Mrow, int Mcol, Board& board)
{
	int Prow = board.getPlayer().row;
	int Pcol = board.getPlayer().col;

	Board::RowCol r[4];

	r[0].row = Mrow - (Prow + 2);

	r[0].col = Mcol - (Pcol);

	r[1].row = Mrow - (Prow - 2);

	r[1].col = Mcol - (Pcol);

	r[2].row = Mrow - (Prow);

	r[2].col = Mcol - (Pcol - 2);

	r[3].row = Mrow - (Prow);

	r[3].col = Mcol - (Pcol + 2);

	int row = 1000;
	int col = 1000;
	
	for (int i = 0; i < 4; i++)
		if (abs(r[i].row) + abs(r[i].col) == 0)
			continue;
		else if (abs(r[i].row) + abs(r[i].col) < abs(row) + abs(col) && ProverkaPoint(i, board))
		{
			row = r[i].row;
			col = r[i].col;
			
		}
	if (row == 1000)
		for (int i = 0; i < 4; i++)
			if (abs(r[i].row) + abs(r[i].col) == 0)
				continue;
			else if (abs(r[i].row) + abs(r[i].col) < abs(row) + abs(col))
			{
				row = r[i].row;
				col = r[i].col;
				
			}
	return abs(row) + abs(col);
}
int Magician::Comparison(int Mrow, int Mcol, Board& board)
{
	const int Prow = board.getPlayer().row;
	const int Pcol = board.getPlayer().col;

	Board::RowCol r[12];


	r[0].row = Mrow - (Prow + 1);

	r[0].col = Mcol - (Pcol - 4);

	r[1].row = Mrow - (Prow);

	r[1].col = Mcol - (Pcol - 3);

	r[2].row = Mrow - (Prow + 1);

	r[2].col = Mcol - (Pcol - 4);

	r[3].row = Mrow - (Prow - 4);

	r[3].col = Mcol - (Pcol - 1);

	r[4].row = Mrow - (Prow - 3);

	r[4].col = Mcol - (Pcol);

	r[5].row = Mrow - (Prow - 4);

	r[5].col = Mcol - (Pcol + 1);

	r[6].row = Mrow - (Prow - 1);

	r[6].col = Mcol - (Pcol + 4);

	r[7].row = Mrow - (Prow);

	r[7].col = Mcol - (Pcol + 3);

	r[8].row = Mrow - (Prow + 1);

	r[8].col = Mcol - (Pcol + 4);

	r[9].row = Mrow - (Prow + 4);

	r[9].col = Mcol - (Pcol + 1);

	r[10].row = Mrow - (Prow + 3);

	r[10].col = Mcol - (Pcol);

	r[11].row = Mrow - (Prow + 4);

	r[11].col = Mcol - (Pcol - 1);

	int row = 1000;
	int col = 1000;
	
	for (int i = 0; i < 12; i++)
		if (abs(r[i].row) + abs(r[i].col) == 0)
			continue;
		else if (abs(r[i].row) + abs(r[i].col) < abs(row) + abs(col) && ProverkaPoint(i, board))
		{
			row = r[i].row;
			col = r[i].col;
			
		}
	if (row == 1000)
		for (int i = 0; i < 12; i++)
			if (abs(r[i].row) + abs(r[i].col) == 0)
				continue;
			else if (abs(r[i].row) + abs(r[i].col) < abs(row) + abs(col))
			{
				row = r[i].row;
				col = r[i].col;
			}
	return abs(row) + abs(col);
}
bool Magician::ProverkaPoint(int a, Board& board)
{
	board.setExcluded();
	switch (a)
	{
	case 0:
		if ((!board.m_number[1] && board.getExcluded(1)) || (!board.m_number[9] && board.getExcluded(9)))
			return true;
		return false;
	case 1:
		if ((!((board.m_number[4]) ? board.m_number[4]-1:0) && board.getExcluded(4)) || (!((board.m_number[0]) ? board.m_number[0]-1 : 0) && board.getExcluded(0)) || (!((board.m_number[3])? board.m_number[3]-1:0) && board.getExcluded(3)))
			return true;
		return false;
	case 2:
		if ((!board.m_number[5] && board.getExcluded(5)) || (!board.m_number[2] && board.getExcluded(2)))
			return true;
		return false;
	case 3:
		if ((!board.m_number[6] && board.getExcluded(6)) || (!board.m_number[4] && board.getExcluded(4)))
			return true;
		return false;
	case 4:
		if ((!((board.m_number[2]) ? board.m_number[2] - 1 : 0) && board.getExcluded(2)) || (!((board.m_number[0]) ? board.m_number[0] - 1 : 0) && board.getExcluded(0)) || (!((board.m_number[1]) ? board.m_number[1] - 1 : 0) && board.getExcluded(1)))
			return true;
		return false;
	case 5:
		if ((!board.m_number[7] && board.getExcluded(7)) || (!board.m_number[3] && board.getExcluded(3)))
			return true;
		return false;
	case 6:
		if ((!board.m_number[8] && board.getExcluded(8)) || (!board.m_number[2] && board.getExcluded(2)))
			return true;
		return false;
	case 7:
		if ((!((board.m_number[4]) ? board.m_number[4] - 1 : 0) && board.getExcluded(4)) || (!((board.m_number[0]) ? board.m_number[0] - 1 : 0) && board.getExcluded(0)) || (!((board.m_number[3]) ? board.m_number[3] - 1 : 0) && board.getExcluded(3)))
			return true;
		return false;
	case 8:
		if ((!board.m_number[1] && board.getExcluded(1)) || (!board.m_number[12] && board.getExcluded(12)))
			return true;
		return false;
	case 9:
		if ((!board.m_number[11] && board.getExcluded(11)) || (!board.m_number[3] && board.getExcluded(3)))
			return true;
		return false;
	case 10:
		if ((!((board.m_number[2]) ? board.m_number[2] - 1 : 0) && board.getExcluded(2)) || (!((board.m_number[0]) ? board.m_number[0] - 1 : 0) && board.getExcluded(0)) || (!((board.m_number[1]) ? board.m_number[1] - 1 : 0) && board.getExcluded(1)))
			return true;
		return false;
	case 11:
		if ((!board.m_number[10] && board.getExcluded(10)) || (!board.m_number[4] && board.getExcluded(4)))
			return true;
		return false;
	}
	return false;
}
void Magician::setPoint(int i, int* number)
{
	switch (i)
	{
	case 0:
		++number[1];
		++number[9];
		break;
	case 1:
		++number[4];
		++number[0];
		++number[3];
		break;
	case 2:
		++number[5];
		++number[2];
		break;
	case 3:
		++number[6];
		++number[4];
		break;
	case 4:
		++number[2];
		++number[0];
		++number[1];
		break;
	case 5:
		++number[7];
		++number[3];
		break;
	case 6:
		++number[8];
		++number[2];
		break;
	case 7:
		++number[4];
		++number[0];
		++number[3];
		break;
	case 8:
		++number[1];
		++number[12];
		break;
	case 9:
		++number[11];
		++number[3];
		break;
	case 10:
		++number[2];
		++number[0];
		++number[1];
		break;
	case 11:
		++number[10];
		++number[4];
		break;
	}
}
int MagicianDiagonal::Comparison(int Mrow, int Mcol, Board& board)
{
	const int Prow = board.getPlayer().row;
	const int Pcol = board.getPlayer().col;

	Board::RowCol r[8];


	r[0].row = Mrow - (Prow + 4);

	r[0].col = Mcol - (Pcol - 3);

	r[1].row = Mrow - (Prow + 3);

	r[1].col = Mcol - (Pcol - 4);

	r[2].row = Mrow - (Prow - 3);

	r[2].col = Mcol - (Pcol - 4);

	r[3].row = Mrow - (Prow - 4);

	r[3].col = Mcol - (Pcol - 3);

	r[4].row = Mrow - (Prow - 4);

	r[4].col = Mcol - (Pcol + 3);

	r[5].row = Mrow - (Prow - 3);

	r[5].col = Mcol - (Pcol + 4);

	r[6].row = Mrow - (Prow + 3);

	r[6].col = Mcol - (Pcol + 4);

	r[7].row = Mrow - (Prow + 4);

	r[7].col = Mcol - (Pcol + 3);

	int row = 1000;
	int col = 1000;
	for (int i = 0; i < 8; i++)
		if (abs(r[i].row) + abs(r[i].col) == 0)
			continue;
		else if (abs(r[i].row) + abs(r[i].col) < abs(row) + abs(col) && ProverkaPoint(i, board))
		{
			row = r[i].row;
			col = r[i].col;
		}
	if (row == 1000)
		for (int i = 0; i < 8; i++)
			if (abs(r[i].row) + abs(r[i].col) == 0)
				continue;
			else if (abs(r[i].row) + abs(r[i].col) < abs(row) + abs(col))
			{
				row = r[i].row;
				col = r[i].col;
			}
	return abs(row) + abs(col);
}
bool MagicianDiagonal::ProverkaPoint(int a, Board& board)
{
	board.setExcluded();
	switch (a)
	{
	case 0:
		if ((!board.m_number[10] && board.getExcluded(10)) || (!board.m_number[1] && board.getExcluded(1)) || (!board.m_number[3] && board.getExcluded(3)))
			return true;
		return false;
	case 1:
		if ((!board.m_number[9] && board.getExcluded(9)) || (!board.m_number[4] && board.getExcluded(4)) || (!board.m_number[2] && board.getExcluded(2)))
			return true;
		return false;
	case 2:
		if ((!board.m_number[5] && board.getExcluded(5)) || (!board.m_number[4] && board.getExcluded(4)) || (!board.m_number[1] && board.getExcluded(1)))
			return true;
		return false;
	case 3:
		if ((!board.m_number[6] && board.getExcluded(6)) || (!board.m_number[2] && board.getExcluded(2)) || (!board.m_number[3] && board.getExcluded(3)))
			return true;
		return false;
	case 4:
		if ((!board.m_number[7] && board.getExcluded(7)) || (!board.m_number[2] && board.getExcluded(2)) || (!board.m_number[4] && board.getExcluded(4)))
			return true;
		return false;
	case 5:
		if ((!board.m_number[8] && board.getExcluded(8)) || (!board.m_number[3] && board.getExcluded(3)) || (!board.m_number[1] && board.getExcluded(1)))
			return true;
		return false;
	case 6:
		if ((!board.m_number[12] && board.getExcluded(12)) || (!board.m_number[2] && board.getExcluded(2)) || (!board.m_number[3] && board.getExcluded(3)))
			return true;
		return false;
	case 7:
		if ((!board.m_number[11] && board.getExcluded(11)) || (!board.m_number[4] && board.getExcluded(4)) || (!board.m_number[1] && board.getExcluded(1)))
			return true;
		return false;
	}
	return false;
}
void MagicianDiagonal::setPoint(int i, int* number)
{
	switch (i)
	{
	case 0:
		++number[1];
		++number[10];
		++number[3];
		break;
	case 1:
		++number[9];
		++number[4];
		++number[2];
		break;
	case 2:
		++number[5];
		++number[4];
		++number[1];
		break;
	case 3:
		++number[6];
		++number[3];
		++number[2];
		break;
	case 4:
		++number[7];
		++number[4];
		++number[2];
		break;
	case 5:
		++number[1];
		++number[8];
		++number[3];
		break;
	case 6:
		++number[12];
		++number[3];
		++number[2];
		break;
	case 7:
		++number[11];
		++number[4];
		++number[1];
		break;
	}
}
void Magician::setIllumination(int row, int col, Board& board)
{
	for (int i = 2; row + i < board.m_Rows && i < 5; i++)
	{
		if(board.m_arrBoard[row + i][col]->getSymbol() >= Player)
			board.m_arrBoard[row + i][col]->illuminationT();

		if (board.m_arrBoard[row + i][col]->getSymbol() != Emptiness && board.m_arrBoard[row + i][col]->getSymbol() != Lava)
			break;
		board.m_arrBoard[row + i][col]->illuminationT();
		
	}
	for (int i = 2; row - i >= 0 && i < 5; i++)
	{
		if (board.m_arrBoard[row - i][col]->getSymbol() >= Player)
			board.m_arrBoard[row - i][col]->illuminationT();

		if (board.m_arrBoard[row - i][col]->getSymbol() != Emptiness && board.m_arrBoard[row - i][col]->getSymbol() != Lava)
			break;
		board.m_arrBoard[row - i][col]->illuminationT();
		
	}
			
	for (int i = 2; col + i < board.m_Columns && i < 5; i++)
	{
		if (board.m_arrBoard[row][col + i]->getSymbol() >= Player)
			board.m_arrBoard[row][col + i]->illuminationT();

		if (board.m_arrBoard[row][col + i]->getSymbol() != Emptiness && board.m_arrBoard[row][col + i]->getSymbol() != Lava)
			break;
		board.m_arrBoard[row][col + i]->illuminationT();
	}
		
	for (int i = 2; col - i >= 0 && i < 5; i++)
	{
		if (board.m_arrBoard[row][col - i]->getSymbol() >= Player)
			board.m_arrBoard[row][col - i]->illuminationT();

		if (board.m_arrBoard[row][col - i]->getSymbol() != Emptiness && board.m_arrBoard[row][col - i]->getSymbol() != Lava)
			break;
		board.m_arrBoard[row][col - i]->illuminationT();
	}
			
}
void MagicianDiagonal::setIllumination(int row, int col, Board& board)
{
	for (int i = 1; col + i < board.m_Columns && row + i < board.m_Rows && i < 5; i++)
	{
		if (board.m_arrBoard[row + i][col + i]->getSymbol() >= Player)
			board.m_arrBoard[row + i][col + i]->illuminationT();

		if (board.m_arrBoard[row + i][col + i]->getSymbol() != Emptiness && board.m_arrBoard[row + i][col + i]->getSymbol() != Lava)
			break;
		board.m_arrBoard[row + i][col + i]->illuminationT();
	}

	for (int i = 1; col - i >= 0 && row - i >= 0 && i < 5; i++)
	{
		if(board.m_arrBoard[row - i][col - i]->getSymbol() >= Player)
			board.m_arrBoard[row - i][col - i]->illuminationT();

		if (board.m_arrBoard[row - i][col - i]->getSymbol() != Emptiness && board.m_arrBoard[row - i][col - i]->getSymbol() != Lava)
			break;
		board.m_arrBoard[row - i][col - i]->illuminationT();
	}
			
	for (int i = 1; row - i >= 0 && col + i < board.m_Columns && i < 5; i++)
	{
		if (board.m_arrBoard[row - i][col + i]->getSymbol() >= Player)
			board.m_arrBoard[row - i][col + i]->illuminationT();

		if (board.m_arrBoard[row - i][col + i]->getSymbol() != Emptiness && board.m_arrBoard[row - i][col + i]->getSymbol() != Lava)
			break;
		board.m_arrBoard[row - i][col + i]->illuminationT();
	}

	for (int i = 1; row + i < board.m_Rows && col - i >= 0 && i < 5; i++)
	{
		if (board.m_arrBoard[row + i][col - i]->getSymbol() >= Player)
			board.m_arrBoard[row + i][col - i]->illuminationT();

		if (board.m_arrBoard[row + i][col - i]->getSymbol() != Emptiness && board.m_arrBoard[row + i][col - i]->getSymbol() != Lava)
			break;
		board.m_arrBoard[row + i][col - i]->illuminationT();
	}
}
void Magician::animation(sf::RenderWindow& window, int row, int col, Board& board)
{
	sf::Texture Ball;
	Ball.loadFromFile(board.m_path + "шар.png");
	sf::Sprite ball(Ball);

	sf::Texture Explosion;
	Explosion.loadFromFile(board.m_path + "взрыв.png");
	sf::Sprite explosion(Explosion);

	const int w = 60;
	//drawing(board, window, w);
	if (row < board.m_r.row)
	{
		for (int i = 2; row + i < board.m_r.row; i++)
		{
			drawing(board, window, w);
			ball.setPosition(col * w, (row + i) * w);
			window.draw(ball);
			window.display();
			Sleep(500);

		}
		
	}
	else if (row > board.m_r.row)
	{
		for (int i = 2; row - i > board.m_r.row; i++)
		{
			drawing(board, window, w);
			ball.setPosition(col * w, (row - i) * w);
			window.draw(ball);
			window.display();
			Sleep(500);

		}
	}
	else if (col < board.m_r.col)
		for (int i = 2; col + i < board.m_r.col; i++)
		
		{
			drawing(board, window, w);
			ball.setPosition((col + i) * w, row * w);
			window.draw(ball);
			window.display();
			Sleep(500);

		}

	else if (col > board.m_r.col)
	{
		for (int i = 2; col - i > board.m_r.col; i++)
		{
			drawing(board, window, w);
			ball.setPosition((col - i) * w, row * w);
			window.draw(ball);
			window.display();
			Sleep(500);

		}
	}
	drawing(board, window, w);
	explosion.setPosition(board.m_r.col * w, (board.m_r.row) * w);
	window.draw(explosion);
	window.display();
	Sleep(500);
}
void MagicianDiagonal::animation(sf::RenderWindow& window, int row, int col, Board& board)
{
	sf::Texture Arrow;
	Arrow.loadFromFile(board.m_path + "стрела.png");
	sf::Sprite arrow(Arrow);
	const int w = 60;
	if (row < board.m_r.row && col < board.m_r.col)
	{
		for (int i = 2; row + i <= board.m_r.row; i++)
		{
			drawing(board, window, w);
			arrow.setRotation(270.f);
			arrow.setPosition((col + i) * w, (row + i + 1) * w);
			window.draw(arrow);
			window.display();
			Sleep(500);
		}
	}
	else if (row > board.m_r.row && col > board.m_r.col)
	{
		for (int i = 2; row - i >= board.m_r.row; i++)
		{
			drawing(board, window, w);
			arrow.setRotation(90.f);
			arrow.setPosition((col - i + 1) * w, (row - i) * w);
			window.draw(arrow);
			window.display();
			Sleep(500);
		}
	}
	else if (row < board.m_r.row && col > board.m_r.col)
	{
		for (int i = 2; row + i <= board.m_r.row; i++)
		{
			drawing(board, window, w);
			arrow.setPosition((col - i) * w, (row + i) * w);
			window.draw(arrow);
			window.display();
			Sleep(500);
		}
	}
	else if (row > board.m_r.row && col < board.m_r.col)
	{
		for (int i = 2; row - i >= board.m_r.row; i++)
		{
			drawing(board, window, w);
			arrow.setRotation(180.f);
			arrow.setPosition((col + i + 1) * w , (row - i + 1) * w);
			window.draw(arrow);
			window.display();
			Sleep(500);
		}
	}

}
