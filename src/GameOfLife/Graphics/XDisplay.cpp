#include "GameOfLife/Board.hpp"
#include "GameOfLife/Parameters.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <vector>
#include <condition_variable>
#include <mutex>
#include <future>
#include <chrono>
#include <functional>

const unsigned int CELL_OUTER_BOUND = 15; // in pixels.

static std::condition_variable executionCV;
static bool stopExecution = false;

static int displayContent(sf::RenderWindow &window);
static void renderBoard(sf::RenderWindow &window, agof::Board &board);
static void renderGrid(sf::RenderWindow &window, sf::Color color = sf::Color(255, 0, 0, 178));
static bool checkCondition();

int gameOfLife()
{
  sf::RenderWindow window(sf::VideoMode(agof::Parameters::get().getWidth() * CELL_OUTER_BOUND,
					agof::Parameters::get().getHeight() * CELL_OUTER_BOUND),
			  "Another Game of Life");

  window.setFramerateLimit(60);
  window.setActive(false);
  std::future<int> displayTask = std::async(displayContent, std::ref(window));
  while (window.isOpen()) {
    sf::Event event;

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
    	stopExecution = true;
    	executionCV.notify_one();
    	window.close();
      }
    }
  }
  return displayTask.get();
}

static int displayContent(sf::RenderWindow &window)
{
  std::mutex mtx;
  std::unique_lock<std::mutex> lck(mtx);
  agof::Board board;

  
  do {
    window.clear(sf::Color(1, 36, 86));
    renderGrid(window);
    renderBoard(window, board);
    window.display();
    board.next();
  } while (executionCV.wait_for(lck, std::chrono::seconds(1), checkCondition) == false); // Waits for one second OR for stopExecution to be true.
  return EXIT_SUCCESS;
}

static void renderGrid(sf::RenderWindow &window, sf::Color color)
{
    for (unsigned int i = 1; i != agof::Parameters::get().getWidth(); i++) {
      sf::Vertex line[] = {sf::Vertex(sf::Vector2f((float) i * CELL_OUTER_BOUND, 0), color),
			   sf::Vertex(sf::Vector2f((float) i * CELL_OUTER_BOUND, (float) window.getSize().y), color)};
    
      window.draw(line, 2, sf::Lines);
    }
    for (unsigned int i = 1; i != agof::Parameters::get().getHeight(); i++) {
      sf::Vertex line[] = {sf::Vertex(sf::Vector2f(0, (float) i * CELL_OUTER_BOUND), color),
			   sf::Vertex(sf::Vector2f((float) window.getSize().x, (float) i * CELL_OUTER_BOUND), color)};
    
      window.draw(line, 2, sf::Lines);
    }
}

static void renderBoard(sf::RenderWindow &window, agof::Board &board)
{
  for (std::size_t y = 0; y != agof::Parameters::get().getHeight(); y++) {
    for (std::size_t x = 0; x != agof::Parameters::get().getWidth(); x++) {
      if (board.at(x, y) == agof::Board::State::Alive) {
	sf::CircleShape circle(CELL_OUTER_BOUND / 2);

	circle.setPosition(x * CELL_OUTER_BOUND,
			   y * CELL_OUTER_BOUND);
	circle.setFillColor(sf::Color::White);
	circle.setOutlineColor(sf::Color::Yellow);
	circle.setOutlineThickness(-2);
	window.draw(circle);
      }
    }
  }
}

static bool checkCondition()
{
  return stopExecution;
}
