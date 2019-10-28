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
		board[i].reserve(width);
	}
	generateInitial();
}

agof::Board::Board(unsigned int width, unsigned int height)
{
	for (unsigned int i = 0; i != height; i++) {
		board[i].reserve(width);
	}
	generateInitial();
}

/* Public functions. */

agof::Board::State agof::Board::at(int x, int y)
{
	if ((x < 0 || x > board[0].size())
	    || (y < 0 || y > board.size())) {
		return agof::Board::State::OutOfBound;
	}
	return board[y][x];
}

/* Private functions. */

void agof::Board::generateInitial()
{
	// TODO create some pattern in the board for generation 0.
}

void agof::Board::next()
{
	// TODO mutate board's cells.
}
