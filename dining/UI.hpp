#pragma once
#include <ncurses.h>
#include <string>
#include <array>
#include <thread>
#include "Table.hpp"
#include "OutputCoords.hpp"

class UI
{
public:
	UI(const std::array<Philosopher, 7>& philosophers, Table& table);
	~UI();

	const std::array<Philosopher, 7>& philosophers;
	Table& table;
    std::mutex changeMutex;
    bool ifStart = false;

private:
    std::array<OutputCoords, 7> outputCoords; 

    std::unique_ptr<std::thread> refreshThread;
    std::unique_ptr<std::thread> keyboardThread;

    WINDOW* window;

    void checkWindowSize();
    void initializeWindow();
    void destroyWindow(WINDOW* window);
    void refreshView();
    void refreshStates();
    void refreshState(WINDOW *win, int y, int x, float progress,  std::string name, std::string status);  

    void waitForPressedKey();




};
