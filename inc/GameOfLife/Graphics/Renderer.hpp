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


#pragma once

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
