/*
** EPITECH PROJECT, 2022
** struct.h
** File description:
** struct.h
*/

#ifndef STRUCT_H_
    #define STRUCT_H_

    typedef struct map {
        char *map1d;
        char **map;
        char **omap;
        int *sizex;
        int maxsizex;
        int sizey;
        int playerx;
        int playery;
        int isplayer;
        int crateratio;
        int cratenum;
    }map_t;

#endif /* STRUCT_H_ */
