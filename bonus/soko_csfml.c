/*
** EPITECH PROJECT, 2022
** soko_csfml.c
** File description:
** graphical sokoban
*/

#include "include/windowsfuncs.h"
#include "include/structmap.h"
#include "include/struct.h"
#include "include/my.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void eventlisten(win_t* win, map_t *map, sprite_t *aj, int ismove)
{
    win->action = 0;
    win->mpos = sfRenderWindow_mapPixelToCoords(win->window\
    , sfMouse_getPosition(win->window), NULL);
    win->mbox.left = win->mpos.x;
    win->mbox.top = win->mpos.y;
    while (sfRenderWindow_pollEvent(win->window, &win->event)){
        if (win->event.type == sfEvtClosed){
            win->game_over = 0;
            win->isinit = 0;
            sfRenderWindow_close(win->window);
        }
        if (win->event.type == sfEvtMouseButtonPressed){
            win->click = 1;
        }
        if (win->event.type == sfEvtKeyPressed && ismove == 1)
            keyevent(win, map, aj);
    }
}

go_actions(win_t *win, map_t *map)
{
    sfFloatRect quit = {741, 635, 368, 117};
    sfFloatRect restart = {749, 500, 368, 134};
    if (win->click == 1 &&
    sfFloatRect_intersects(&win->mbox, &restart, NULL) == sfTrue){
        win->click = 0;
        win->game_over = 0;
        make2d(map);
    }
    if (win->click == 1 &&
    sfFloatRect_intersects(&win->mbox, &quit, NULL) == sfTrue){
        win->click = 0;
        win->game_over = 0;
        sfRenderWindow_close(win->window);
    }
}

void game_over(win_t *win, map_t *map, sprite_t *aj, sprite_t *panel)
{
    set_textscale(win->text, 1.30, 1.30);
    if (checkstate(map) == 1) {
        win->game_over = 1;
        sfText_setString(win->text, "good job you won");
    }
    if (checkstate(map) == 2){
        win->game_over = 1;
        sfText_setString(win->text, "all apples are stuck");
    }
    while (win->game_over == 1){
        eventlisten(win, map, aj, 0);
        sfRenderWindow_drawSprite(win->window, win->bg->sprite, NULL);
        sfRenderWindow_drawSprite(win->window, panel->sprite, NULL);
        sfRenderWindow_drawText(win->window, win->text, NULL);
        go_actions(win, map);
        displayfunc(win);
    }
}

int gameloop_one(map_t *map, win_t *win, sprite_t *aj, sprite_t *tree)
{
    sprite_t *crate = setsprite("sprites/barrels.png", 1.00, 1.00, 0);
    sprite_t *apple = setsprite("sprites/aj.png", 2.00, 2.00, 0);
    sprite_t *panel = setsprite("sprites/end_panel.png", 1.50, 1.50, 0);
    anim_t crate_anim[2], apple_anim[4];

    setspritepos(panel, 740.00, 0.00);
    set_textpos(win->text, 790.00, 415.00);
    make_anim(win, crate_anim, crate, "75 75 2 0 0 75 0");
    make_anim(win, apple_anim, apple, "9 9 4 6 437 17 437 28 437 39 437");
    while (sfRenderWindow_isOpen(win->window)) {
        eventlisten(win, map, aj, 1);
        drawfloor(map, win);
        drawcrates(map, crate, win);
        drawmovable(map, aj, apple, win);
        drawwalls(map, tree, win);
        displayfunc(win);
        game_over(win, map, aj, panel);
    }
    free_sprite(crate);
    free_sprite(apple);
}

int engageloop(map_t *map)
{
    int errval = 0;
    anim_t ani[2], aj_anim[5];
    win_t *win = setwin("sokoban", 1920, 1080, 32);
    win->bg = setsprite("sprites/grass.png", 1.00, 1.00, 1);
    sprite_t *aj = setsprite("sprites/aj.png", 2.00, 2.00, 0);
    sprite_t *tree = setsprite("sprites/rock.png", 1.00, 1.00, 0);
    make_anim(win, &ani, tree, "75 100 2 0 0 75 0");
    make_anim(win, &aj_anim, aj, "32 36 4 129 198 0 197 7 27 59 37");
    set_textcolorfont(win->text, "255 255 255 255", "font/awakening.ttf");
    errval = make2d(map);
    setspriterect(win->bg, "0 0", map->maxsizex * 400, map->sizey * 400);
    if (errval == 84)
        return (errval);
    errval = gameloop_one(map, win, aj, tree);
    free_sprite(win->bg);
    free_sprite(tree);
    free_sprite(aj);
    free_win(win);
    return (errval);
}