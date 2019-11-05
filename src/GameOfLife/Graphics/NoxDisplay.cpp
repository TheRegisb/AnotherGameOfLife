#include <condition_variable>
#include <mutex>
#include <future>
#include <chrono>

#ifdef _WIN32
	#include <conio.h>
	#include <windows.h>
#endif

#include "GameOfLife/Board.hpp"
#include "GameOfLife/Parameters.hpp"

/* Condition variable. */

static std::condition_variable executionCV;
static bool stopExecution = false;

/* Function declaration. Static for performance boost. */

static int display();
static bool checkCondition();

int gameOfLifeNox()
{

  char ch;
  std::future<int> displayTask = std::async(display);
  
  while ((ch = _getch()) != EOF && ch != 'q');
  stopExecution = true;
  executionCV.notify_one();
  return displayTask.get();
}

static int display()
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
  #else
    // TODO UNIX implementation
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
    #else
    // TODO UNIX implementation
    #endif
    
    std::cout << "Generation: " << i++ << std::endl;
    board.dumpCurrent();
    board.next();
    std::cout.flush();
  } while (executionCV.wait_for(lck, std::chrono::seconds(1), checkCondition) == false); // Waits for one second OR for stopExecution to be true.
  return EXIT_SUCCESS;
}

static bool checkCondition()
{
  return stopExecution;
}
