/*
** EPITECH PROJECT, 2022
** makemap.c
** File description:
** makes map
*/

#include "include/struct.h"
#include "include/my.h"
#include <sys/stat.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
int make2d(map_t *map);
int main_soko(map_t *map);

int engageloop(map_t *map)
{
    int errval = 0;

    errval = make2d(map);
    if (errval == 84)
        return (errval);
    initscr();
    return (main_soko(map));
}

void freemap(map_t *map)
{
    int i;

    for (i = 0; i < map->sizey; i ++) {
        free(map->map[i]);
        free(map->omap[i]);
    }
    free(map->map);
    free(map->omap);
    free(map->sizex);
}

int is_good_size(map_t *map)
{
    int i;
    int x = 0;
    int y = 0;
    int max_map_x = 0;
    getmaxyx(stdscr, x, y);
    int posx = 0;

    for (i = 0; i < map->sizey; i ++)
        if (max_map_x < map->sizex[i])
            max_map_x = map->sizex[i];
    if (y >= max_map_x && x >= map->sizey) {
        return (0);
    } else {
        if (y >= 22)
            posx = (y / 2) - 11;
        clear();
        mvwprintw(stdscr, x / 2 , posx, "please enlarge terminal");
        refresh();
        return (1);
    }
}
