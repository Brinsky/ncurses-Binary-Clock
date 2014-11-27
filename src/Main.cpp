#include <ctime>
#include <string>
#include <sstream>
#include <ncurses.h>
#include "BinaryClock.h"

const std::clock_t UPDATE_INTERVAL = 0.1 * CLOCKS_PER_SEC;

const int NAME_LENGTH = 12;
const int BIN_LENGTH = 12;
const int NUM_LENGTH = 6; // An example would be "(2014)"

void drawNumber(int x, int y, int number)
{
	std::ostringstream convert;
	convert << number;
	std::string result = convert.str();

	mvwaddch(stdscr, y, x, '(' | COLOR_PAIR(4));

	for( int i = 1; i < result.length(); ++i )
		mvwaddch(stdscr, y, x + i, result[i] | COLOR_PAIR(4));

	mvwaddch(stdscr, y, x + result.length(), ')' | COLOR_PAIR(4));
}

void drawWord(int x, int y, std::string word)
{
	for( int i = 0; i < word.length(); ++i )
		mvwaddch(stdscr, y, x + i, word[i] | COLOR_PAIR(4));
}

void drawBits(int x, int y, int length, std::string binary)
{
	int offset = 0;

	// If the width is longer than our binary number, fill in the leading
	// spaces with zeros
	if( binary.length() < length )
	{
		offset = length - binary.length();

		for( int i = 0; i < offset; ++i )
			mvwaddch(stdscr, y, x + i, '0' | COLOR_PAIR(1));
	}

	for( int i = 0; i < binary.length(); ++i )
	{
		if( binary[i] == '1' )
		{
			mvwaddch(stdscr, y, x + offset + i, '1'
				| COLOR_PAIR(2));
		}
		else
		{
			mvwaddch(stdscr, y, x + offset + i, '0'
				| COLOR_PAIR(3));
		}
	}		
}

int main()
{
	// ncurses setup
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	start_color();
	curs_set(FALSE);

	// Set our color pairs
	init_pair(1, COLOR_BLUE, COLOR_BLACK); // Insignificant zero color
	init_pair(2, COLOR_GREEN, COLOR_BLACK); // Significant one color
	init_pair(3, COLOR_RED, COLOR_BLACK); // Significant zero color
	init_pair(4, COLOR_WHITE, COLOR_BLACK); // Word color

	drawWord(4, 1, "Simple Binary Clock");

	BinaryClock binClock;

	int input;
	std::clock_t lastTime = clock();
	bool running = true;	
	
	while( running )
	{
		// Input loop, exit on pressing 'q' or 'Q'
		while( (input = getch()) != ERR )
			if( input == 'q' || input == 'Q' )
				running = false;
	
		// Run the update at every UPDATE_INTERVAL
		if( clock() - lastTime > UPDATE_INTERVAL )
		{
			lastTime = clock();

			// Update the BinClock
			binClock.updateTime();

			// Draw the BinClock
			drawWord(1, 3, "Second:");
			drawBits(15, 3, 12, binClock.getSecond());

			drawWord(1, 5, "Minute:");
			drawBits(15, 5, 12, binClock.getMinute());

			drawWord(1, 7, "Hour:");
			drawBits(15, 7, 12, binClock.getHour());

			drawWord(1, 9, "Weekday:");
			drawBits(15, 9, 12, binClock.getWeekday());
			
			drawWord(1, 11, "Day of Month:");
			drawBits(15, 11, 12, binClock.getMonthDay());

			drawWord(1, 13, "Month:");
			drawBits(15, 13, 12, binClock.getMonth());

			drawWord(1, 15, "Year:");
			drawBits(15, 15, 12, binClock.getYear());
		}		
	}

	endwin();
}
