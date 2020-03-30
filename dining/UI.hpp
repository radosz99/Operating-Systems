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
	UI(const std::array<Philosopher, 7>& philosophers, Table& table, const std::array<Chopstick, 7>& chopsticks);
	~UI();

	const std::array<Philosopher, 7>& philosophers;
    Table& table;
	const std::array<Chopstick, 7>& chopsticks;
	
    std::mutex changeMutex;
    bool ifStart = false;

private:
    std::array<OutputCoords, 7> outputCoordsPhil; 
    std::array<OutputCoords, 7> outputCoordsChop;
    std::array<OutputCoords, 7> outputCoordsHungry; 

    std::unique_ptr<std::thread> refreshThread;
    std::unique_ptr<std::thread> keyboardThread;

    WINDOW* window;
    long hungry[7]={0,0,0,0,0,0,0};
    long hungryAll=0;
    long notHungryAll=0;
    void initializeWindow();
    void destroyWindow(WINDOW* window);
    void refreshView();
    void refreshStatuses();
    void refreshHungryBar(WINDOW *win); 
    void refreshOwner(WINDOW *win, int y, int x, unsigned i, int owner);
    void refreshState(WINDOW *win, int y, int x, float progress,  std::string name, std::string status); 
    void refreshHungryBars(WINDOW *win); 
    void endVisualisation();




};
