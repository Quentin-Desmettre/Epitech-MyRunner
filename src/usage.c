/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** usage.c
*/

#include <unistd.h>

void my_print(void)
{
    write(1,
    "LEVEL EDITOR INTERACTIONS\n"
    "    LEFT_CLICK              pose / delete / "
    "chose block - save your level\n"
    "    LEFT_CLICK & MOUSE_MOVE pose a block\n"
    "    LEFT_KEY / RIGHT_KEY    move view to the left / right\n\n"
    "LEVEL PICK INTERACTIONS\n"
    "    LEFT_CLICK play current level / select a different level / go back\n"
    "    LEFT_KEY   go to the previous level\n"
    "    RIGHT_KEY  go to the next level\n"
    "    SPACE      play current level\n"
    "    ENTER      play current level\n"
    "    ESCAPE     go back to main menu\n\n"
    "PAUSE MENU INTERACTIONS\n"
    "    ESCAPE     resume\n"
    "    SPACE      resume\n"
    "    ENTER      resume\n"
    "    LEFT_CLICK resume / go back to level pick\n\n", 613);
}

void print_how_to_play(void)
{
    write(1,
    "GLOBAL INTERACTIONS\n"
    "    F3    show / hide FPS\n\n"
    "IN-GAME INTERACTIONS\n"
    "    SPACE_KEY  jump\n"
    "    LEFT_CLICK jump\n"
    "    ESCAPE     pause/resume\n"
    "    Holding the jump key will make you jump as soon"
    " as you hit the floor.\n\n"
    "MAIN MENU INTERACTIONS\n"
    "    LEFT_CLICK chose a menu\n\n"
    "SETTINGS INTERACTIONS\n"
    "    LEFT_CLICK modify a parameter or go back\n"
    "    ESCAPE     go back to the main menu\n\n"
    "SKIN SELECT INTERACTIONS\n"
    "    LEFT_CLICK select your skin or go back\n"
    "    ESCAPE     go back to the main menu\n\n", 480);
    my_print();
}

int usage(void)
{
    write(1, "\nGeometry dash-like runner, created with CSFML.\n\n"
    "USAGE\n"
    "    ./my_runner [-o edit_map]\n"
    "        edit_map: the map you want to modify."
    " The -o option opens edit_map inside the level editor.\n"
    "    ./my_runner [map]\n"
    "        map: The file containing the level you want to play.\n"
    "          It must be correctly formated.\n"
    "          See .legend for more information.\n"
    "     If no map is provided, the game will launch into"
    " its normal mode.\n"
    "     If more than one map is provided, the program will"
    " print an error message and exit.\n\n"
    "OPTIONS\n"
    "    -h Print usage and exit.\n\n", 552);
    print_how_to_play();
    return 0;
}
