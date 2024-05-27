#include <ncurses.h>
#include <sys/param.h>

int main()
{
	initscr();
	printw("Press WASD to move the cross, Q to quit\n");
	int x = 10;
	int y = 10;
	refresh();
	int ch = 0;
	noecho();
	while (ch != 'q')
	{
		ch = getch();
		int sy, sx;
		getmaxyx(stdscr, sy, sx);
		move(y, x);
		delch();
		if (ch == 'w')
			y--;
		if (ch == 's')
			y++;
		if (ch == 'a')
			x--;
		if (ch == 'd')
			x++;
		y = MAX(1, MIN(sy - 1, y));
		x = MAX(0, MIN(sx - 1, x));
		move(y, x);
		addch('X');
		refresh();
	}
	endwin();
	return 0;
}
// CPU Governor was here 2:57 Am
