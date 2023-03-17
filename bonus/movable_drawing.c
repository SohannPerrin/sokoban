/*
** EPITECH PROJECT, 2022
** movable_drawing.c
** File description:
** draws movable objects
*/

#include "include/windowsfuncs.h"
#include "include/structmap.h"
#include "include/struct.h"
#include "include/my.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void isappul(map_t *map, sfVector2i pos, sprite_t *apple, win_t *win)
{
    if (map->map[pos.y][pos.x] == 'X' && map->omap[pos.y][pos.x] != 'O') {
        setspritepos(apple, (double)((pos.x - map->playerx)* 75 + 940),
        (double)((pos.y - map->playery) * 75 + 570));
        sfRenderWindow_drawSprite(win->window, apple->sprite, NULL);
    }
}

void isaj(map_t *map, sfVector2i pos, sprite_t *aj, win_t *win)
{
    if (map->map[pos.y][pos.x] == 'P') {
        setspritepos(aj, (double)(910), (double)(540));
        sfRenderWindow_drawSprite(win->window, aj->sprite, NULL);
    }
}

void drawmovable(map_t *map, sprite_t *aj, sprite_t *apple, win_t *win)
{
    int i;
    int j;
    sfVector2i pos;

    for (i = 0; i < map->sizey; i ++){
        for (j = 0; j < map->sizex[i]; j ++){
            pos.x = j;
            pos.y = i;
            isaj(map, pos, aj, win);
            isappul(map, pos, apple, win);
        }
    }
}