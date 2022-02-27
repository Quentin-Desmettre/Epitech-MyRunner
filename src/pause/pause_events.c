/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** pause_events.c
*/

#include "runner.h"

void free_player(player_t *player)
{
    sfClock_destroy(player->jump_clock);
    sfClock_destroy(player->anim_clock);
    sfClock_destroy(player->move_clock);
    sfSprite_destroy(player->skin);
    if (player->tex)
        sfTexture_destroy(player->tex);
    free(player);
}

void exit_game(window_t *win)
{
    win->is_transition = 1;
    win->next_state = LEVEL_STATE;
    if (win->lobby_music)
        sfMusic_play(win->lobby_music);
    win->play_level->is_pause = 0;
    free_player(win->player);
    win->player = 0;
    actu_percentage(win);
    sfRenderWindow_setMouseCursorVisible(win->window, 1);
}

void pause_move(window_t *win, sfEvent *ev)
{
    sfFloatRect r = sfSprite_getGlobalBounds(win->pause->quit->sprite);
    float x = ev->mouseMove.x - win->mode.width * 0.05;
    float y = ev->mouseMove.y - win->mode.height * 0.05;
    int reset = 1;

    if (sfFloatRect_contains(&r, x, y)) {
        hover_button(win->pause->quit, 1);
        hover_button(win->pause->resume, 0);
        reset = 0;
    }
    r = sfSprite_getGlobalBounds(win->pause->resume->sprite);
    if (sfFloatRect_contains(&r, x, y)) {
        hover_button(win->pause->resume, 1);
        hover_button(win->pause->quit, 0);
        reset = 0;
    }
    if (reset) {
        hover_button(win->pause->quit, 0);
        hover_button(win->pause->resume, 0);
    }
}

void pause_press(window_t *win, sfEvent *ev)
{
    sfFloatRect r = sfSprite_getGlobalBounds(win->pause->quit->sprite);
    float x = ev->mouseButton.x - win->mode.width * 0.05;
    float y = ev->mouseButton.y - win->mode.height * 0.05;
    int reset = 1;

    if (sfFloatRect_contains(&r, x, y)) {
        press_button(win->pause->quit, 1);
        press_button(win->pause->resume, 0);
        reset = 0;
    }
    r = sfSprite_getGlobalBounds(win->pause->resume->sprite);
    if (sfFloatRect_contains(&r, x, y)) {
        press_button(win->pause->resume, 1);
        press_button(win->pause->quit, 0);
        reset = 0;
    }
    if (reset) {
        press_button(win->pause->quit, 0);
        press_button(win->pause->resume, 0);
    }
}

void pause_release(window_t *win, sfEvent *ev)
{
    sfFloatRect r = sfSprite_getGlobalBounds(win->pause->quit->sprite);
    float x = ev->mouseButton.x - win->mode.width * 0.05;
    float y = ev->mouseButton.y - win->mode.height * 0.05;

    if (sfFloatRect_contains(&r, x, y))
        exit_game(win);
    r = sfSprite_getGlobalBounds(win->pause->resume->sprite);
    if (sfFloatRect_contains(&r, x, y))
        resume(win);
    press_button(win->pause->quit, 0);
    press_button(win->pause->resume, 0);
}
