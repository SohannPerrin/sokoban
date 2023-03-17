/*
** EPITECH PROJECT, 2022
** input_manage.c
** File description:
** manages keyboard inputs
*/

#include "include/windowsfuncs.h"
#include "include/structmap.h"
#include "include/struct.h"
#include "include/my.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

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

void keyevent(win_t *win, map_t *map, sprite_t *aj)
{
    if (win->event.key.code == 73 || win->event.key.code == 25){
        movep(map, 0, -1);
        set_anim_to(win, aj, 2);
    }
    if (win->event.key.code == 74 || win->event.key.code == 18){
        movep(map, 0, 1);
        set_anim_to(win, aj, 1);
    }
    if (win->event.key.code == 71 || win->event.key.code == 16){
        movep(map, -1, 0);
        set_anim_to(win, aj, 3);
    }
    if (win->event.key.code == 72 || win->event.key.code == 3){
        movep(map, 1, 0);
        set_anim_to(win, aj, 0);
    }
    if (win->event.key.code == 57){
        make2d(map);
    }
}