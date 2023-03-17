/*
** EPITECH PROJECT, 2022
** struct.h
** File description:
** struct.h
*/

#ifndef STRUCTMAP_H_
    #define STRUCTMAP_H_

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

#endif /* STRUCTMAP_H_ */