#include "UI.hpp"
#include <iostream>
#include <string.h>
#include <math.h>
#include "State.hpp"

UI::UI(const std::array<Philosopher, 7>& philosophers, Table& table, const std::array<Chopstick, 7>& chopsticks) : philosophers(philosophers), table(table), chopsticks(chopsticks)
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

	initializeWindow();
	refreshThread = std::make_unique<std::thread>(&UI::refreshView, this);
    keyboardThread = std::make_unique<std::thread>(&UI::endVisualisation, this);   

}

UI::~UI()
{
	keyboardThread->join();
	refreshThread->join();
	destroyWindow(window);
	endwin();
}

void UI::destroyWindow(WINDOW* window)
{
	wborder(window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(window);
	delwin(window);
}


void UI::initializeWindow()
{
	window = newwin(LINES, COLS, 0, 0);
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
        outputCoordsPhil[i] = {{ rowIndex, colIndex +5}};
    }

    for (size_t i = 0; i < chopsticks.size(); i++)
    {
        const int rowIndex = rowGap * (7+i) + 9 ;
        outputCoordsChop[i] = {{ rowIndex, colIndex + 15 }};
    }

    for (size_t i = 0; i < philosophers.size(); i++)
    {
        const int rowIndex = rowGap * i + 3 ;
        outputCoordsHungry[i] = {{ rowIndex, colIndex + 85 }};
    }

    wrefresh(window);
}

void UI::refreshView()
{
    while (table.getIsDinner())
    {
        clear();
		refreshStatuses();
        wrefresh(window);
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
}

void UI::refreshStatuses()
{
    attron(COLOR_PAIR(4)); 
    start_color();
    init_color(COLOR_RED, 500, 0, 0);
    init_color(COLOR_MAGENTA, 400, 600, 900);                   
    init_pair(1, COLOR_RED, -1);
    init_pair(2, COLOR_GREEN, -1);
    init_pair(3, COLOR_MAGENTA, -1);
    init_pair(4, COLOR_WHITE, -1);
    std::string stateHeader = "PHILOSOPHER STATUS:";
    std::string state1Header = "RESOURCE STATUS:";
    std::string stateProgressHeader = "STATE PROGRESS:";
    std::string starvationHeader = "PHILOSOPHER'S HUNGER IN RELATION TO THE ENTIRE HUNGER:";
    std::string starvation1Header = "HUNGRY IN RELATION TO THE THINKING AND EATING:";
    mvwprintw(stdscr, 1, 5, stateHeader.c_str());
    mvwprintw(stdscr, 14, 25, state1Header.c_str());
    mvwprintw(stdscr, 14, 73, starvation1Header.c_str());
    mvwprintw(stdscr, 1, 42, stateProgressHeader.c_str());
    mvwprintw(stdscr, 1, 80, starvationHeader.c_str());
    for (size_t i = 0; i < philosophers.size(); i++)
    {        
        
        const auto& philosopher = philosophers.at(i);
        switch (philosopher.getState())
	    {
	    case State::hungry:
            hungry[i]++;
            hungryAll++;
            //attron(COLOR_PAIR(1)); 
	    	break;
	    case State::eating:
            notHungryAll++;
            //attron(COLOR_PAIR(2)); 
	    	break;
	    case State::thinking:
            notHungryAll++;
            //attron(COLOR_PAIR(3)); 
	    	break;
	    }
        attron(COLOR_PAIR(4)); 
        std::pair<int, int> coords = outputCoordsPhil.at(i).coords;
        refreshState(stdscr, coords.first, coords.second, philosopher.getProgress(),philosopher.getName(),philosopher.getStateString());

    }

    for (unsigned i = 0; i < chopsticks.size(); i++)
    {        
        const auto& chopstick = chopsticks.at(i);
        std::pair<int, int> coords = outputCoordsChop.at(i).coords;
        int owner = chopstick.getOwner();
        refreshOwner(stdscr, coords.first, coords.second, i, owner);
    }
    refreshHungryBar(stdscr);
    refreshHungryBars(stdscr);
}

void UI::refreshHungryBar(WINDOW *win)
{
        std::string finString;
        float result;
        int barLength = 30;
        if(notHungryAll!=0 && hungryAll !=0)
            result =static_cast<float>(hungryAll) / static_cast<float>(notHungryAll);
        else
            result = 0;

        int lpad = std::round(result * barLength);
        int rpad = barLength - lpad;
        result = result * 100;
        std::string hungryInPercent = std::to_string((int)std::round(result));

        finString = "\t"+hungryInPercent;
        if(hungryInPercent.size()==3)
        {
            finString = finString + "% [";
        }
        else if(hungryInPercent.size()==2)
        {
            finString = finString + " % [";
        }
        else
        {
            finString = finString + "  % [";
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
;
        if(result>30)
            attron(COLOR_PAIR(1)); 
        else
            attron(COLOR_PAIR(2)); 
        std::scoped_lock lock(changeMutex);
        mvwprintw(win, 19, 75, finString.c_str());
        refresh();

}
void UI::refreshState(WINDOW *win, int y, int x, float progress, std::string name, std::string status)
{   
    int barLength = 30;
    std::string finString;
    std::string progressInPercent = std::to_string((int)std::round(progress * 100));
    int lpad = std::round(progress * barLength);
    int rpad = barLength - lpad;
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

void UI::refreshOwner(WINDOW *win, int y, int x, unsigned i, int owner)
{   

    std::string name;
    switch(owner)
    {
    case 1:
        name = "Austin";
        break;
    case 2:
        name = "Barnie";
        break;
    case 3:
        name = "Cedric";
        break;
    case 4:
        name = "Darren";
        break;
    case 5:
        name = "Elijah";
        break;
    case 6:
        name = "Freddy";
        break;
    case 7:
        name = "George";
        break;
    }
    init_color(COLOR_CYAN, 200, 700, 900);                   
    init_pair(4, COLOR_WHITE, -1);
    attron(COLOR_PAIR(4)); 
    std::string finString = "Chopstick number " + std::to_string(i) + " is owned by " + name;
    std::scoped_lock lock(changeMutex);
    mvwprintw(win, y, x, finString.c_str());

    refresh();
}

void UI::refreshHungryBars(WINDOW *win)
{         
    init_pair(1, COLOR_RED, -1);
    init_pair(2, COLOR_GREEN, -1);
    float result;
    std::string finString="";
    for (unsigned i = 0; i < philosophers.size(); i++)
    {        
        int barLength = 30;
        if(hungry[i]!=0 && hungryAll !=0)
            result =static_cast<float>(hungry[i]) / static_cast<float>(hungryAll);
        else
            result = 0;

        int lpad = std::round(result * barLength);
        int rpad = barLength - lpad;
        result = result * 100;
        std::string hungryInPercent = std::to_string((int)std::round(result));

        finString = "\t"+hungryInPercent;
        if(hungryInPercent.size()==3)
        {
            finString = finString + "% [";
        }
        else if(hungryInPercent.size()==2)
        {
            finString = finString + " % [";
        }
        else
        {
            finString = finString + "  % [";
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

        std::pair<int, int> coords = outputCoordsHungry.at(i).coords;
        if(result>100/7)
            attron(COLOR_PAIR(1)); 
        else
            attron(COLOR_PAIR(2)); 
        std::scoped_lock lock(changeMutex);
        mvwprintw(win, coords.first, coords.second, finString.c_str());
        refresh();
    }
}


void UI::endVisualisation()
{
    while (table.getIsDinner())
    {
        int keyPressed = wgetch(window);

        switch (keyPressed)
        {
            case 27: // ESCAPE KEY
                table.dinnerStop();
                break;
        }
    }
}





