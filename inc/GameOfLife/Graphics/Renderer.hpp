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

#pragma once


#include "GameOfLife/Board.hpp"
#include "GameOfLife/Parameters.hpp"

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
#endif

const unsigned int CELL_OUTER_BOUND = 15; // in pixels;

namespace agof {
  namespace Graphics {

    class Renderer {
    public:
      Renderer();
      Renderer(agof::Board &board);

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
