#include <ncurses.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#define MAX_FILES 256

void splash_screen(void) {
    clear();
    attron(A_BOLD);
    mvprintw(0, (COLS - 17) / 2, "RPZ2W GAME BOY ADVANCE");
    attroff(A_BOLD);
    refresh();
}

int main(void) {
    char *files[MAX_FILES];
    int count = 0;
    char savename[256];

    DIR *d = opendir("/usr/games");
    struct dirent *ent;
    while ((ent = readdir(d)) && count < MAX_FILES) {
        if (strstr(ent->d_name, ".gba"))
            files[count++] = strdup(ent->d_name);
    }
    closedir(d);

    initscr();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);        // Make the cursor invisible (0)

    splash_screen();

    int sel = 0, ch;
    while (1) {
        
        for (int i = 0; i < count; i++) {
            if (i == sel) attron(A_REVERSE);
            mvprintw(2+ i, (COLS - 17)/2, files[i]);
            if (i == sel) attroff(A_REVERSE);
        }

        ch = getch();
        if (ch == KEY_UP && sel > 0) sel--;
        if (ch == KEY_DOWN && sel < count-1) sel++;
        if (ch == '\n') break;
    }

    strncpy(savename, files[sel], sizeof(savename));
    savename[sizeof(savename) - 1] = '\0';

    char *dot = strrchr(savename, '.');
    if (dot && strcmp(dot, ".gba") == 0) {
        strcpy(dot, ".sav");
    }

    endwin();

    if (access(savename, F_OK) == 0) {
        execl("/usr/bin/mgba", "mgba", files[sel], "-t", savename, NULL);
    } else {
        execl("/usr/bin/mgba", "mgba", files[sel], NULL);
    }
    
    
}