#pragma once
#include <ncurses.h>
#include <string>
#include <array>
#include <thread>
#include "Table.hpp"
#include "OutputCoords.hpp"
#define PBAR "##################################################"
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
    static constexpr int barHeight = 3;
    static constexpr int barWidth = 40;

    bool ready = false;
    std::array<OutputCoords, 7> outputCoords; 

    std::unique_ptr<std::thread> viewThread;
    std::unique_ptr<std::thread> keyboardThread;

    WINDOW* mainWindow;

    void checkWindowSize();

    void initializeMainWindow();
    void initializeStatusWindow();
    void initializePhilosopherStatuses();
    void initializeProgressBars();

    void destroyWindow(WINDOW* window);
    void destroyProgressBars();

    void refreshView();
    void refreshStates();
    void refreshState(WINDOW *win, int y, int x, float progress,  std::string name, std::string status);  

    void waitForPressedKey();




};
