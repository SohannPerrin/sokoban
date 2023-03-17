/*
** EPITECH PROJECT, 2022
** makemap2.c
** File description:
** continues making map
*/

#include "include/my.h"
#include "include/struct.h"
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int defmap2(map_t *map, int y, int x, int passed)
{
    if (map->map1d[(passed + x)] == 'X') {
        map->map[y][x] = 'X';
        map->omap[y][x] = ' ';
        map->crateratio -= 1;
        map->cratenum += 1;
    }
    if (map->map1d[(passed + x)] == 'P') {
        map->map[y][x] = 'P';
        map->omap[y][x] = ' ';
        map->playerx = x;
        map->playery = y;
        map->isplayer += 1;
    }
    if (map->map1d[(passed + x)] == '\n')
        map->map[y][x] = map->omap[y][x] = '\n';
    if (map->crateratio == 0 && map->isplayer == 1) {
        return (0);
    } else
        return (84);
}

int defmap(map_t *map, int y, int x)
{
    int i = 0;
    int passed = 0;

    while (i < y){
        passed += map->sizex[i];
        i ++;
    }
    if (map->map1d[(passed + x)] == '#') {
        map->map[y][x] = '#';
        map->omap[y][x] = '#';
    }
    if (map->map1d[(passed + x)] == ' ')
        map->map[y][x] = map->omap[y][x] = ' ';
    if (map->map1d[(passed + x)] == 'O') {
        map->map[y][x] = ' ';
        map->omap[y][x] = 'O';
        map->crateratio += 1;
    }
    return (defmap2(map, y, x, passed));
}

int make2d2(map_t *map)
{
    int i, j, errval;

    map->isplayer = map->cratenum = map->crateratio = 0;
    for (i = 0; i < map->sizey; i ++){
        for (j = 0; j < map->sizex[i]; j ++)
            errval = defmap(map, i, j);
    }
    if (errval == 84) {
        write(2, "incorect player number or inequal number of ", 44);
        write(2, "objectives and crates\n", 22);
        return (errval);
    }
    return (errval);
}

int mallocsize(map_t *map)
{
    int h;
    int i = 0;

    map->maxsizex = 0;
    map->sizex = malloc(map->sizey * 4);
    for (h = 0; h < map->sizey; h ++) {
        map->sizex[h] = 0;
        for (i; map->map1d[i] != '\n' && map->map1d[i] != '\0'; i ++)
            map->sizex[h] += 1;
        i ++;
        map->sizex[h] += 1;
        if (map->maxsizex < map->sizex[h])
            map->maxsizex = map->sizex[h];
        map->map[h] = malloc(map->sizex[h]);
        map->omap[h] = malloc(map->sizex[h]);
    }
    return (make2d2(map));
}
