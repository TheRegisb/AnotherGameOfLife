// Copyright 2019 R�gis Berthelot

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

#include "GameOfLife/Graphics/Renderer.hpp"

agof::Graphics::Renderer::Renderer()
	: board(agof::Board()), stopExecution(false)
{
  
}

agof::Graphics::Renderer::Renderer(agof::Board &board)
	: stopExecution(false)
{
	this->board = board;
}

int agof::Graphics::Renderer::display(bool nox)
{
	if (nox) {
		return startNox();
	}
	return startX();
}

/* Private function */

int agof::Graphics::Renderer::startX()
{
	sf::RenderWindow window(sf::VideoMode(board.size().X * CELL_OUTER_BOUND,
					      board.size().Y * CELL_OUTER_BOUND),
				"Another Game of Life");

	window.setFramerateLimit(60);
	window.setActive(false);
	std::future<int> displayTask = std::async(&agof::Graphics::Renderer::displayX, this, std::ref(window));
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

int agof::Graphics::Renderer::displayX(sf::RenderWindow &window)
{
	std::mutex mtx;
	std::unique_lock<std::mutex> lck(mtx);
  
	do {
		window.clear(sf::Color(1, 36, 86));
		renderGrid(window);
		renderBoard(window);
		window.display();
		board.next();
	} while (executionCV.wait_for(lck, std::chrono::seconds(1), [this]{ return checkCondition(); }) == false); // Waits for one second OR for stopExecution to be true.
	return EXIT_SUCCESS;
}

void agof::Graphics::Renderer::renderGrid(sf::RenderWindow &window, sf::Color color)
{
	for (unsigned int i = 1; i != board.size().X; i++) {
		sf::Vertex line[] = {sf::Vertex(sf::Vector2f((float) i * CELL_OUTER_BOUND, 0), color),
				     sf::Vertex(sf::Vector2f((float) i * CELL_OUTER_BOUND, (float) window.getSize().y), color)};
    
		window.draw(line, 2, sf::Lines);
	}
	for (unsigned int i = 1; i != board.size().Y; i++) {
		sf::Vertex line[] = {sf::Vertex(sf::Vector2f(0, (float) i * CELL_OUTER_BOUND), color),
				     sf::Vertex(sf::Vector2f((float) window.getSize().x, (float) i * CELL_OUTER_BOUND), color)};
    
		window.draw(line, 2, sf::Lines);
	}
}

void agof::Graphics::Renderer::renderBoard(sf::RenderWindow &window)
{
	for (std::size_t y = 0; y != board.size().Y; y++) {
		for (std::size_t x = 0; x != board.size().X; x++) {
			if (board.at((int) x, (int) y) == agof::Board::State::Alive) {
				sf::CircleShape circle(CELL_OUTER_BOUND / 2);

				circle.setPosition((float) x * CELL_OUTER_BOUND,
						   (float) y * CELL_OUTER_BOUND);
				circle.setFillColor(sf::Color::White);
				circle.setOutlineColor(sf::Color::Yellow);
				circle.setOutlineThickness(-2);
				window.draw(circle);
			}
		}
	}
}

int agof::Graphics::Renderer::startNox()
{
	char ch;
	std::future<int> displayTask = std::async(&agof::Graphics::Renderer::displayNox, this);

	#ifdef _WIN32
	while ((ch = _getch()) != EOF && ch != 'q');
	#else
	struct termios old, current;
	
	tcgetattr(0, &old);
	current = old;
	current.c_lflag &= ~ICANON;
	current.c_lflag &= ~ECHO;
	tcsetattr(0, TCSANOW, &current);
	while ((ch = getchar()) != EOF && ch != 'q');
	tcsetattr(0, TCSANOW, &old);
	#endif
	stopExecution = true;
	executionCV.notify_one();
	return displayTask.get();
}

int agof::Graphics::Renderer::displayNox()
{
	/* Get the console cursor position (OS dependant). */
#ifdef _WIN32
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	COORD initialCursorPosition;

	if (!GetConsoleScreenBufferInfo(hConsole, &cbsi)) {
		return EXIT_FAILURE;
	}
	initialCursorPosition = cbsi.dwCursorPosition;
	initialCursorPosition.Y += 1;
#endif

	std::mutex mtx;
	std::unique_lock<std::mutex> lck(mtx);
	agof::Board board;
	long int i = 0;
  
	std::cout << "Press 'q' to quit." << std::endl;
	do {
		/* Reset the position of the cursor (OS dependant) to overwrite the previous board. */
#ifdef _WIN32
		SetConsoleCursorPosition(hConsole, initialCursorPosition);
#endif
    
		std::cout << "Generation: " << i++ << std::endl;
		board.dumpCurrent();
#ifndef _WIN32
		std::cout << "\x1b[" << board.size().Y + 3<< "A"; // Uses ANSI term code to move the cursor back up.
		std::cout.flush();
#endif
		board.next();
		std::cout.flush();
	} while (executionCV.wait_for(lck, std::chrono::seconds(1), [this]{ return checkCondition(); }) == false); // Waits for one second OR for stopExecution to be true.
	return EXIT_SUCCESS;
}

bool agof::Graphics::Renderer::checkCondition()
{
	return stopExecution;
}
