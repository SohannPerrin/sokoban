/*
** EPITECH PROJECT, 2022
** popup.c
** File description:
** manages sokoban
*/

#include <ncurses.h>
#include "include/struct.h"
int make2d(map_t *map);
void freemap(map_t *map);

void movep(map_t *map, int x, int y)
{
    int canmove = 0;

    if (map->omap[map->playery + y][map->playerx + x] != '#')
        canmove = 1;
    if (map->map[map->playery + y][map->playerx + x] == 'X'
    && canmove == 1){
        if (map->omap[map->playery + (y * 2)][map->playerx + (x * 2)] == '#'
        || map->map[map->playery + (y * 2)][map->playerx + (x * 2)] == 'X')
            canmove = 0;
        if (canmove == 1)
            map->map[map->playery + (y * 2)][map->playerx + (x * 2)] = 'X';
    }
    if (canmove == 1){
        map->map[map->playery][map->playerx] = ' ';
        map->map[map->playery + y][map->playerx + x] = 'P';
        map->playerx += x;
        map->playery += y;
    }
}

void eventlisten(int ch, map_t *map)
{
    if (ch == 122 || ch == KEY_UP)
        movep(map, 0, -1);
    if (ch == 115 || ch == KEY_DOWN)
        movep(map, 0, 1);
    if (ch == 113 || ch == KEY_LEFT)
        movep(map, -1, 0);
    if (ch == 100 || ch == KEY_RIGHT)
        movep(map, 1, 0);
    if (ch == 32) {
        make2d(map);
    }
}

void soko_map(map_t *map, int i)
{
    int j;

    for (j = 0; j < map->sizex[i]; j ++) {
        if (map->map[i][j] == 'P' || map->map[i][j] == 'X'){
            printw("%c", map->map[i][j]);
        } else
            printw("%c", map->omap[i][j]);
    }
}

int main_soko(map_t *map)
{
    int i = 0, ch = 0, retval = 0;
    raw();
    noecho();
    keypad(stdscr, TRUE);
    while (retval == 0){
        clear();
        for (i = 0; i < map->sizey; i ++)
            soko_map(map, i);
        if (is_good_size(map) != 0)
            continue;
        ch = getch();
        eventlisten(ch, map);
        for (i = 0; i < map->sizey; i ++)
            soko_map(map, i);
        retval = checkstate(map);
        refresh();
    }
    endwin();
    freemap(map);
    return (retval - 1);
}
