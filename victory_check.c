/*
** EPITECH PROJECT, 2022
** victory_check.c
** File description:
** checks for victory and loss
*/

#include "include/struct.h"

int checkwin(map_t *map, int i, int j)
{
    if (map->map[i][j] == 'X' && map->omap[i][j] == 'O')
        return (1);
    return (0);
}

int checklost(map_t *map, int i, int j)
{
    if (map->map[i][j] == 'X' && (((map->map[i - 1][j] == '#' ||
    map->map[i - 1][j] == 'X') && (map->map[i][j - 1] == '#' ||
    map->map[i][j - 1] == 'X')) || ((map->map[i - 1][j] == '#' ||
    map->map[i - 1][j] == 'X') && (map->map[i][j + 1] == '#' ||
    map->map[i][j + 1] == 'X')) || ((map->map[i + 1][j] == '#' ||
    map->map[i + 1][j] == 'X') && (map->map[i][j - 1] == '#' ||
    map->map[i][j - 1] == 'X')) || ((map->map[i + 1][j] == '#' ||
    map->map[i + 1][j] == 'X') && (map->map[i][j + 1] == '#' ||
    map->map[i][j + 1] == 'X'))))
        return (1);
    return (0);
}

int checkstate(map_t *map)
{
    int i;
    int j;
    int goodboxes = 0;
    int islost = 0;

    for (i = 0; i < map->sizey; i ++)
        for (j = 0; j < map->sizex[i]; j ++) {
            goodboxes += checkwin(map, i, j);
            islost += checklost(map, i, j);
        }
    if (goodboxes == map->cratenum)
        return (1);
    if (islost == map->cratenum)
        return (2);
    return (0);
}
