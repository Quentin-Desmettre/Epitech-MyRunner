/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** main.c
*/

#include "runner.h"

void rescale_all(window_t *win)
{
    move_buttons(win->mode, win->home_screen->buttons);
    rescale_home(win->home_screen, win->mode);
    scale_rtex_lpick(win);
    rescale_settings(win->settings, win);
    rescale_select(win);
    scale_pause(win->pause, win);
    sfSprite_setScale(win->comp_spr, (sfVector2f)
    {win->mode.width / 1834.8, win->mode.width / 1834.8});
    sfSprite_setPosition(win->comp_spr, (sfVector2f)
    {win->mode.width / 2.0, win->mode.height / 2.7});
    sfSprite_setPosition(win->program_name, (sfVector2f)
    {win->mode.width / 2.0, win->mode.height * 0.23});
    sfSprite_setScale(win->program_name, (sfVector2f)
    {win->mode.width / 1655.0 / 1.25, win->mode.width / 1655.0 / 1.25});
}

void create_window_musics(window_t *win)
{
    win->lobby_music = sfMusic_createFromFile(LOBBY_MUSIC);
    win->lvl_complete = init_sound(LVL_COMPLETE);
    win->fps = 0;
    if (win->lobby_music)
        sfMusic_setLoop(win->lobby_music, 1);
    if (win->lobby_music)
        sfMusic_play(win->lobby_music);
    win->death_sound = init_sound(DEATH_SOUND);
    sfRenderWindow_setFramerateLimit(win->window, FRAMERATE);
    win->settings = init_settings(win);
    win->pause = init_pause(win);
    win->comp_spr = init_sprite_from_file(COMPLETE_PNG);
    win->coin = init_sound("assets/sfx/coin.ogg");
    win->oof = init_sound("assets/sfx/oof.ogg");
    sfSprite_setOrigin(win->comp_spr, (sfVector2f){764.5, 89.5});
    win->program_name = init_sprite_from_file("assets/sprites/game_name.png");
    sfSprite_setOrigin(win->program_name, (sfVector2f){827.5, 89.5});
    srand(time(NULL));
    win->skin_select = init_skin_select(win);
}

window_t *create_window(char *map)
{
    window_t *win = malloc(sizeof(window_t));

    win->mode = (sfVideoMode){800, 600, 32};
    win->window = sfRenderWindow_create(win->mode, "My runner", sfClose, NULL);
    win->home_screen = init_home_screen(&win->mode);
    win->state = 0;
    win->state_clock = sfClock_create();
    win->is_transition = 0;
    win->lum = (sfColor){255, 255, 255, 255};
    win->lpick = create_level_pick(win);
    win->next_state = -1;
    win->play_level = 0;
    win->framerate = FRAMERATE;
    win->death_effet = sfTexture_createFromFile(DEATH_EFFET, NULL);
    win->player = 0;
    create_window_musics(win);
    rescale_all(win);
    if (map)
        open_map(win, map);
    return win;
}

int main(int ac, char **av)
{
    window_t *win;

    if (ac == 3 && !my_strcmp(av[1], "-o"))
        return editor_main(sfVideoMode_getDesktopMode(), 1, av[2]);
    if (ac == 2 && my_strcmp(av[1], "-h") == 0)
        return usage();
    if (ac > 2)
        return dprint(2, BAD_ARGS);
    if (ac == 2 && !is_file_valid(av[1]))
        return dprint(2, "Invalid map: '%s'\n", av[1]) ? 84 : 84;
    win = create_window(ac == 2 ? av[1] : NULL);
    while (sfRenderWindow_isOpen(win->window)) {
        poll_events(win);
        draw(win);
    }
    destroy_musics(win);
    return (win->next_state == EDITOR_STATE) ? editor_main(win->mode,
    win->settings->full_screen->is_checked, NULL) : 0;
}
