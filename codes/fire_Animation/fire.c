// Originally written by Matthew Simpson in Python: https://gist.github.com/msimpson/1096950
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

static int *b = NULL;
static int width;
static int height;
static int size;

static void sizechanged()
{
	getmaxyx(stdscr, height, width);
	size = width * height;
	b = (int *)realloc(b, (size + width + 1) * sizeof(int));
	memset(b, 0, (size + width + 1) * sizeof(int));
	clear();
}

int main()
{
	initscr();

	const char *charz[] = {" ", ".", ":", "^", "*", "x", "s", "S", "#", "$"};

	curs_set(0);
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);

	sizechanged();

	while (1)
	{
		for (int i = 0; i < width / 9; i++)
			b[(rand() % width) + width * (height - 1)] = 65;
		for (int i = 0; i < size; i++)
		{
			b[i] = (b[i] + b[i + 1] + b[i + width] + b[i + width + 1]) / 4;
			int color = ((b[i] > 15) ? 4 : ((b[i] > 9) ? 3 : ((b[i] > 4) ? 2 : 1)));
			if (i < size - 1)
			{
				attrset(COLOR_PAIR(color) | A_BOLD);
				move(i / width, i % width);
				addstr(charz[((b[i] > 9) ? 9 : b[i])]);
			}
		}

		refresh();
		timeout(30);
		int ch = getch();
		if ((ch != -1) && (ch != KEY_RESIZE))
			break;
		if (ch == KEY_RESIZE)
			sizechanged();
	}
	endwin();
	return 0;
}
