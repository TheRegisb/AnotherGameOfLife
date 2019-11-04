// Copyright 2019 Régis Berthelot

// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#include "GameOfLife/Board.hpp"

/* Constructors. */

agof::Board::Board()
{
	unsigned int width = agof::Parameters::get().getWidth();
	unsigned int height = agof::Parameters::get().getHeight();

	for (unsigned int i = 0; i != height; i++) {
		board[i].insert(board[i].begin(), width, agof::Board::State::Dead);
	}
	std::srand((unsigned int) std::time(nullptr));
	generateInitial();
}

agof::Board::Board(unsigned int width, unsigned int height)
{
	for (unsigned int i = 0; i != height; i++) {
		board[i].insert(board[i].begin(), width, agof::Board::State::Dead);
	}
	std::srand((unsigned int ) std::time(nullptr));
	generateInitial();
}

/* Public functions. */

agof::Board::State agof::Board::at(int x, int y)
{
	if ((x < 0 || x > board[0].size())
	    || (y < 0 || y > board.size() - 1)) {
		return agof::Board::State::OutOfBound;
	}
	return board[y][x];
}

/* Private functions. */

void agof::Board::generateInitial()
{
  const unsigned int xCenter = (unsigned int) board[0].size() / 2;
  const unsigned int yCenter = (unsigned int) board.size() / 2;
  int pattern = std::rand() % 3;

  if (pattern == 0) { // Vertical line of random height.
    asVLine(xCenter, yCenter);
  } else if (pattern == 1) { // Horizontal of random width.
    asHLine(xCenter, yCenter);
  } else { // Pure random centered square.
    asBox(xCenter, yCenter);
  }
}

inline void agof::Board::asVLine(const unsigned int xCenter, const unsigned int yCenter)
{
    int height = rand() % board.size();

    for (unsigned int i = 0; i != height; i++) {
      board[i - (height / 2) + yCenter][xCenter] = agof::Board::State::Alive;
    }
}

inline void agof::Board::asHLine(const unsigned int xCenter, const unsigned int yCenter)
{
  int width = std::rand() % board[0].size();

  for (unsigned int i = 0; i != width; i++) {
    board[yCenter][i - (width / 2) + xCenter] = agof::Board::State::Alive;
  }
}

inline void agof::Board::asBox(const unsigned int xCenter, const unsigned int yCenter)
{
  int size = std::rand() % (board.size() < board[0].size() // Uses either width or height property depending on the smallest value.
			    ? board.size()
			    : board[0].size());

  for (int y = 0; y != size; y++) {
    for (int x = 0; x != size; x++) {
      board[y - (size / 2) + yCenter][x - (size / 2) + xCenter] =
	(std::rand() % 2 == 0 ? agof::Board::State::Alive : agof::Board::State::Dead); // Set at random the cells either as alive or as dead.
    }
  }
}

void agof::Board::next()
{
  std::unordered_map<unsigned int, std::vector<agof::Board::State>> boardCopy;

  for (unsigned int i = 0; i != agof::Parameters::get().getHeight(); i++) {
    boardCopy[i] = board[i];
  }
  for (unsigned int y = 0; y != board.size(); y++) {
    for (unsigned int x = 0; x != board[y].size(); x++) {
      /* Representation of the neighboor in the map,
       * where (i, x) is the current cell:
       *
       *  (y-1, x-1)(y-1, x  )(y-1, x+1)
       *  (y  , x-1)(y  , x  )(y  , x+1)
       *  (y+1, x-1)(y+1, x  )(y+1, x+1)
       *
       */
      int livingNeighbor =
	(this->at(x - 1, y - 1) == agof::Board::State::Alive) + // Return 1 if true, 0 otherwise.
	(this->at(x + 0, y - 1) == agof::Board::State::Alive) +
      	(this->at(x + 1, y - 1) == agof::Board::State::Alive) +
      	(this->at(x - 1, y + 0) == agof::Board::State::Alive) +
      	(this->at(x + 1, y + 0) == agof::Board::State::Alive) +
      	(this->at(x - 1, y + 1) == agof::Board::State::Alive) +
      	(this->at(x + 0, y + 1) == agof::Board::State::Alive) +
      	(this->at(x + 1, y + 1) == agof::Board::State::Alive);
      
      if (this->at(x, y) == agof::Board::State::Dead && livingNeighbor == 3) {
      	boardCopy[y][x] = agof::Board::State::Alive; // Dead cells surrounded by 3 living cells get born.
      } else if (this->at(x, y) == agof::Board::State::Alive
      		 && !(livingNeighbor == 2 || livingNeighbor == 3)) {
      	boardCopy[y][x] = agof::Board::State::Dead; // Alive cells surrounded by less than 2 or more than 3 cells die.
      }
    }
  }
  board = boardCopy;
}

void agof::Board::dumpCurrent()
{
	std::cout << "+";
	for (unsigned int i = 0; i != board[0].size(); i++) {
		std::cout << "-";
	}
	std::cout << "+" << std::endl;
	for (unsigned int i = 0; i != board.size(); i++) {
		std::cout << "|";
		for (unsigned int j = 0; j != board[i].size(); j++) {
		  switch (board[i][j]) {
		  case agof::Board::State::Alive:
		    std::cout << "@";
		    break;
		  case agof::Board::State::ToBeBorn:
		    std::cout << "+";
		    break;
		  default:
		    std::cout << " ";
		  }
		}
		std::cout << "|" << std::endl;
	}
	std::cout << "+";
	for (unsigned int i = 0; i != board[0].size(); i++) {
		std::cout << "-";
	}
	std::cout << "+" << std::endl;
}
