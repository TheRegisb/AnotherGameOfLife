// Copyright 2018 Régis Berthelot

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

/**
 * @file Board.hpp
 * Container of the automated cells.
 */

#pragma once

#include "GameOfLife/Parameters.hpp"

#include <unordered_map>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

namespace agof {

  /**
   * Automated cells container.
   * Register cells on its intenal container and provoke
   * their mutation (generation growth).
   */
	class Board {
		
	public:
	  /**
	   * States of the cells.
	   * Represents the status of a cell on the board.
	   */
		enum class State {
				  Dead /** The cell is marked as dead. */,
				  Alive /** The cell is marked as alive. */,
				  OutOfBound /** The cell is NOT on the board. */
		};

	  /**
	   * Default constructor.
	   * Create the board using the value of the Parameters singleton.
	   * @see agof::Parameters
	   */
		Board();
	  /**
	   * Parametric constructor.
	   * Create the board using the given dimensions.
	   */
		Board(unsigned int width, unsigned int height);

	  /**
	   * Safely query one cell on the board.
	   * Query the state of the cell on a given location on the board.
	   * Invalid location, such as negative indexes, returns safely an OutOfBound value.
	   * @return The state of the cell at the given location.
	   * @see agof::Board::State
	   */
		State at(int x, int y);
	  /**
	   * Display the content of the board into stdout.
	   */
		void dumpCurrent();
	  /**
	   * Generate future generation.
	   * Replace the current generation of cells by the next one using
	   * the established rule of the Game of Life.
	   */
		void next();
	private:
		void generateInitial();
	  inline void asVLine(const unsigned int xCenter, const unsigned int yCenter);
	  inline void asHLine(const unsigned int xCenter, const unsigned int yCenter);
	  inline void asBox(const unsigned int xCenter, const unsigned int yCenter);
		std::unordered_map<unsigned int, std::vector<State>> board;
	};
}
