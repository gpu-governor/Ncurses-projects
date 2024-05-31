#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define DELAY 50000

void init_colors() {
    start_color();
    for (int i = 1; i <= 7; ++i) {
        init_pair(i, i, COLOR_BLACK);
    }
}

void draw_visualizer(int max_y, int max_x, int *heights) {
    for (int x = 0; x < max_x; ++x) {
        int height = heights[x];
        for (int y = 0; y < max_y; ++y) {
            if (y < max_y - height) {
                mvaddch(y, x, ' '); // Clear above the height
            } else {
                attron(COLOR_PAIR((x % 7) + 1));
                mvaddch(y, x, ACS_CKBOARD); // Draw below the height with colors
                attroff(COLOR_PAIR((x % 7) + 1));
            }
        }
    }
    refresh();
}

void update_heights(int max_y, int max_x, int *heights, int *directions) {
    for (int x = 0; x < max_x; ++x) {
        if (directions[x] == 0) {
            directions[x] = (rand() % 2 == 0) ? 1 : -1; // Set initial direction
        }
        heights[x] += directions[x];
        if (heights[x] >= max_y) {
            heights[x] = max_y - 1;
            directions[x] = -1;
        } else if (heights[x] <= 0) {
            heights[x] = 1;
            directions[x] = 1;
        }
    }
}

int main() {
    // Initialize Ncurses
    initscr();
    noecho();
    curs_set(FALSE);
    timeout(0); // Non-blocking input

    // Initialize colors
    init_colors();

    // Get the size of the window
    int max_y = 0, max_x = 0;
    getmaxyx(stdscr, max_y, max_x);

    // Allocate memory for heights and directions arrays
    int *heights = (int*) malloc(max_x * sizeof(int));
    int *directions = (int*) malloc(max_x * sizeof(int));
    for (int i = 0; i < max_x; ++i) {
        heights[i] = rand() % max_y;
        directions[i] = (rand() % 2 == 0) ? 1 : -1;
    }

    while (1) {
        // Update the visualizer grid
        draw_visualizer(max_y, max_x, heights);
        
        // Update heights and directions for the next frame
        update_heights(max_y, max_x, heights, directions);

        // Delay for a short period
        usleep(DELAY);

        // Exit on key press
        if (getch() != ERR) break;
    }

    // End Ncurses mode
    endwin();

    // Free allocated memory
    free(heights);
    free(directions);

    return 0;
}
