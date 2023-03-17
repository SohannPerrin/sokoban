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
int mallocsize(map_t *map);
int engageloop(map_t *map);

int make2d(map_t *map)
{
    int i;
    int len = my_strlen(map->map1d);
    map->sizey = 0;
    for (i = 0; i < len; i ++) {
        if (map->map1d[i] != 32 && map->map1d[i] != 10 && map->map1d[i] != 35
        && map->map1d[i] != 88 && map->map1d[i] != 79 && map->map1d[i] != 80){
            write(2, "A valid map can only contain the characters ", 44);
            write(2, "SPACE, '\\n', '#', 'X', 'O' and 'P'.\n", 36);
            return (84);
        }
        if (map->map1d[i] == '\n' || map->map1d[i] == '\0')
            map->sizey ++;
    }
    return (mallocsize(map));
}

int get_buffer(char *filepath)
{
    map_t map;
    struct stat stats;
    int size = 0;
    int fd = open(filepath, O_RDONLY);
    if (fd == -1){
        write(2, "file: '", 6);
        write(2, filepath, my_strlen(filepath));
        write(2, "' not found\n", 12);
        return (84);
    }
    stat(filepath, &stats);
    size = stats.st_size;
    char buff[size];
    read(fd, buff, size);
    close(fd);
    buff[size] = '\0';
    map.map1d = buff;
    map.map = malloc(size * 8);
    map.omap = malloc(size * 8);
    return (engageloop(&map));
}

int main(int ac, char **av)
{
    if (ac != 2){
        write(2, "my_sokoban takes one filename argument\n", 39);
        return (84);
    }
    if (av[1][0] == '-' && av[1][1] == 'h'){
        write(1, "USAGE\n", 6);
        write(1, "    ./my_sokoban map\n", 21);
        write(1, "DESCRIPTION\n", 12);
        write(1, "    map file representing the warehouse ", 40);
        write(1, "map, containing '#' for walls,\n", 31);
        write(1, "        'P' for the player, 'X' for boxes and ", 46);
        write(1, "'O' for storage locations.\n", 27);
        return (0);
    }
    return (get_buffer(av[1]));
}
