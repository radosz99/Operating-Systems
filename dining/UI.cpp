#include "UI.hpp"
#include <iostream>
#include <string.h>
#include <math.h>
#include "State.hpp"

UI::UI(const std::array<Philosopher, 7>& philosophers, Table& table) : philosophers(philosophers), table(table)
{
	initscr();
    keypad(stdscr, TRUE);
    curs_set(0);
    cbreak();
    noecho();
    start_color();
    use_default_colors();
    init_pair(1, COLOR_MAGENTA, -1);
    init_pair(2, COLOR_GREEN, -1);
    init_pair(3, COLOR_RED, -1);

    initializeMainWindow();
    viewThread = std::make_unique<std::thread>(&UI::refreshView, this);
    keyboardThread = std::make_unique<std::thread>(&UI::waitForPressedKey, this);   

}

UI::~UI()
{
}


void UI::initializeMainWindow()
{
    mainWindow = newwin(LINES, COLS, 0, 0);
    const std::string centerHeader = "DINING PHILOSOPHERS USING CHANDI-MISRA ALGORITHM";
    const std::string rightHeader = "Radoslaw Lis SO2 19/20";

    mvprintw(0, COLS - centerHeader.length(), centerHeader.c_str());
    mvprintw(LINES-1, COLS - rightHeader.length(), rightHeader.c_str());

    const std::string warningLine1 = "CLICK [ENTER] TO START VISUALISATION";
    
    const int rowIndex = LINES / 2;
    mvprintw(rowIndex, (COLS - warningLine1.length()) / 2-1, warningLine1.c_str());

    while (getch() != 10);

    const int rowGap = LINES / (philosophers.size()* 2.5);
    constexpr int colIndex = 0;

    for (size_t i = 0; i < philosophers.size(); i++)
    {
        const int rowIndex = rowGap * i + 3 ;
        outputCoords[i] = {{ rowIndex, colIndex + 10 }};
    }

    wrefresh(mainWindow);
}

void UI::refreshView()
{
    while (table.getIsDinner())
    {
        clear();
        refreshStates();
        wrefresh(mainWindow);
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
}

void UI::refreshStates()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    start_color();
    init_color(COLOR_RED, 400, 0, 0);
    init_color(COLOR_MAGENTA, 400, 600, 900);                   
    init_pair(1, COLOR_RED, -1);
    init_pair(2, COLOR_GREEN, -1);
    init_pair(3, COLOR_MAGENTA, -1);

    for (size_t i = 0; i < philosophers.size(); i++)
    {        
        
        const auto& philosopher = philosophers.at(i);
        switch (philosopher.getState())
	    {
	    case State::hungry:
            attron(COLOR_PAIR(1)); 
	    	break;
	    case State::eating:
            attron(COLOR_PAIR(2)); 
	    	break;
	    case State::thinking:
            attron(COLOR_PAIR(3)); 
	    	break;
	    }
        std::pair<int, int> coords = outputCoords.at(i).coords;
        refreshState(stdscr, coords.first, coords.second, philosopher.getProgress(),philosopher.getName(),philosopher.getStateString());

    }
}
void UI::refreshState(WINDOW *win, int y, int x, float progress, std::string name, std::string status)
{   
    if(ifStart==false){
    mvwprintw(win, y, x, name.c_str());
    refresh();
}

    std::string finString;
    std::string progressInPercent = std::to_string((int)std::round(progress * 100));
    int lpad = std::round(progress * 30);
    int rpad = 30 - lpad;
    if(status.compare("hungry") != 0)
    {
        finString = name + " is " + status + "\t\t"+progressInPercent;
        if(progressInPercent.size()==2)
        {
            finString = finString + "% [";
        }
        else
        {
            finString = finString + " % [";
        }
        for(int i=0; i<lpad; i++)
        {
            finString = finString + "#";
        }
        for(int i=0; i<rpad; i++)
        {
            finString = finString + " ";
        }
        finString = finString + "]";
    }   
    else
    {
        finString = name + " is " + status;
    }
    std::scoped_lock lock(changeMutex);
    mvwprintw(win, y, x, finString.c_str());
    refresh();
}




void UI::waitForPressedKey()
{
    while (table.getIsDinner())
    {
        int keyPressed = wgetch(mainWindow);

        switch (keyPressed)
        {
            case 27: // ESCAPE KEY
                table.dinnerStop();
                break;
        }
    }
}





