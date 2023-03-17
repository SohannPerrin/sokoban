/*
** EPITECH PROJECT, 2022
** map_drawing.c
** File description:
** draws map
*/

#include "include/windowsfuncs.h"
#include "include/structmap.h"
#include "include/struct.h"
#include "include/my.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void iscrate(map_t *map, sfVector2i pos, sprite_t *crate, win_t *win)
{
    if (map->map[pos.y][pos.x] == 'X' && map->omap[pos.y][pos.x] == 'O') {
        setspritepos(crate, (double)((pos.x - map->playerx) * 75 + 910),
        (double)((pos.y - map->playery) * 75 + 540));
        if (crate->frame != 1){
            roll_anim(win, crate);
        }
        sfRenderWindow_drawSprite(win->window, crate->sprite, NULL);
    }
    if (map->map[pos.y][pos.x] != 'X' && map->omap[pos.y][pos.x] == 'O') {
        setspritepos(crate, (double)((pos.x - map->playerx) * 75 + 910),
        (double)((pos.y - map->playery) * 75 + 540));
        if (crate->frame != 0){
            roll_anim(win, crate);
        }
        sfRenderWindow_drawSprite(win->window, crate->sprite, NULL);
    }
}

void drawcrates(map_t *map, sprite_t *crate, win_t *win)
{
    int i;
    int j;
    sfVector2i pos;

    for (i = 0; i < map->sizey; i ++){
        for (j = 0; j < map->sizex[i]; j ++){
            pos.x = j;
            pos.y = i;
            iscrate(map, pos, crate, win);
        }
    }
}

void iswall(map_t *map, sfVector2i pos, sprite_t *tree, win_t *win)
{

    if (map->omap[pos.y][pos.x] == '#') {
        setspritepos(tree, (double)((pos.x - map->playerx) * 75 + 910),
        (double)((pos.y - map->playery) * 75 + 515));
        if (((pos.x + 1) * (pos.y + 1)) % 2 == 1){
            roll_anim(win, tree);
        }
        sfRenderWindow_drawSprite(win->window, tree->sprite, NULL);
    }
}

void drawwalls(map_t *map, sprite_t *tree, win_t *win)
{
    int i;
    int j;
    sfVector2i pos;

    if (tree->frame != 0)
        roll_anim(win, tree);
    for (i = 0; i < map->sizey; i ++){
        for (j = 0; j < map->sizex[i]; j ++){
            pos.x = j;
            pos.y = i;
            iswall(map, pos, tree, win);
        }
    }
}

void drawfloor(map_t *map, win_t *win)
{
    setspritepos(win->bg, (double)((0 - map->playerx) * 75),
    (double)((0 - map->playery) * 75));
    sfRenderWindow_drawSprite(win->window, win->bg->sprite, NULL);
}