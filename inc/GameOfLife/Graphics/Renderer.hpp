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
 * @file Renderer.hpp
 * Display and IO handler.
 */

#pragma once


#include "GameOfLife/Board.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <condition_variable>
#include <mutex>
#include <future>
#include <functional>
#include <chrono>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <termios.h>
#include <X11/Xlib.h>
#include <stdlib.h>
#endif

/**
 * Maximum perimeter/radius of a cell shape.
 */
const unsigned int CELL_OUTER_BOUND = 15;

namespace agof {
  namespace Graphics {

    /**
     * Displays manager.
     * Represent visually the Game of Life, 
     * in a X or X-less environment.
     */
    class Renderer {
    public:
      /**
       * Default constructor.
       * Generates a new board.
       */
      Renderer();
      /**
       * Parametric construtor.
       * Uses and mutates the given board.
       */
      Renderer(agof::Board &board);

      /**
       * Start the display and the IO handling.
       * Starts either a graphic windows or a terminal-only
       * representation of the Game of Life.
       */
      int display(bool nox);
    private:
      int startX();
      int displayX(sf::RenderWindow &window);
      void renderGrid(sf::RenderWindow &window, sf::Color color = sf::Color(255, 0, 0, 178));
      void renderBoard(sf::RenderWindow &window);

      int startNox();
      int displayNox();

      bool checkCondition();

      bool stopExecution;
      agof::Board board;
      std::condition_variable executionCV;
    };
  }
}
