/*
** EPITECH PROJECT, 2021
** runner
** File description:
** defines.h
*/

#ifndef DEFINES_EDIT_H
    #define DEFINES_EDIT_H
    #include <SFML/Graphics.h>
    #include <SFML/Graphics.h>
    #include <SFML/System.h>
    #include <SFML/Window.h>

    #define NB_BLOCK 29
    #define BLOCK_WIDTH 122
    #define BLOCK_HEIGHT 122
    #define ERASE 1
    #define SAVE 2
    #define CLEAR_ALL 3

    #define SAVE_SUCCESS "assets/sfx/success.ogg"
    #define SAVE_FAILURE "assets/sfx/failure.ogg"
    #define GRID "assets/sprites/grid.png"
    #define BACKGROUND "assets/sprites/background.png"
    #define BLOCK_SHEET "assets/sprites/ssheet.png"
    #define ABS(x) (((x) < 0) ? -(x) : (x))

    // Files
    #define SEPARATOR_CHAR '-'
    #define SEPARATOR_STR "-"
    #define NB_STRUCT 17

static const sfIntRect block_rects[NB_BLOCK + 3] = {
    // settings buttons
    {1463, 122, BLOCK_WIDTH, BLOCK_HEIGHT},
    {1340, 122, 122, 122},
    {0, 429, BLOCK_WIDTH, BLOCK_HEIGHT},
    {610, 429, 122, 122},

    // black blocks
    {0, 0, BLOCK_WIDTH, BLOCK_HEIGHT},
    {122, 0, BLOCK_WIDTH, BLOCK_HEIGHT},
    {244, 0, BLOCK_WIDTH, BLOCK_HEIGHT},
    {366, 0, BLOCK_WIDTH, BLOCK_HEIGHT},
    {488, 0, BLOCK_WIDTH, BLOCK_HEIGHT},
    {610, 0, BLOCK_WIDTH, BLOCK_HEIGHT},
    {732, 0, BLOCK_WIDTH, BLOCK_HEIGHT},
    {854, 0, BLOCK_WIDTH, BLOCK_HEIGHT},
    {976, 0, BLOCK_WIDTH, BLOCK_HEIGHT},
    {1098, 0, BLOCK_WIDTH, BLOCK_HEIGHT},
    {1220, 0, BLOCK_WIDTH, BLOCK_HEIGHT},
    {1342, 0, BLOCK_WIDTH, BLOCK_HEIGHT},

    // brick blocks
    {1464, 0, BLOCK_WIDTH, BLOCK_HEIGHT},
    {0, 244, BLOCK_WIDTH, BLOCK_HEIGHT},
    {122, 244, BLOCK_WIDTH, BLOCK_HEIGHT},
    {244, 244, BLOCK_WIDTH, BLOCK_HEIGHT},
    {366, 244, BLOCK_WIDTH, BLOCK_HEIGHT},
    {488, 244, BLOCK_WIDTH, BLOCK_HEIGHT},
    {610, 244, BLOCK_WIDTH, BLOCK_HEIGHT},
    {732, 244, BLOCK_WIDTH, BLOCK_HEIGHT},
    {854, 244, BLOCK_WIDTH, BLOCK_HEIGHT},
    {976, 244, BLOCK_WIDTH, BLOCK_HEIGHT},
    {1098, 244, BLOCK_WIDTH, BLOCK_HEIGHT},
    {1220, 244, BLOCK_WIDTH, BLOCK_HEIGHT},

    {366, 122, BLOCK_WIDTH, BLOCK_HEIGHT}, // spike

    {1342, 244, BLOCK_WIDTH, BLOCK_HEIGHT},
    {1464, 244, BLOCK_HEIGHT, BLOCK_HEIGHT},
    {0, 0, 0, 0}
};

#endif
