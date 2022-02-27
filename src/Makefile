##
## EPITECH PROJECT, 2021
## runner
## File description:
## Makefile
##

DRAW = draw/draw_actu_level.c \
	draw/draw_level_pick.c \
	draw/draw.c \
	draw/draw_play_level.c \
	draw/draw_loop.c

EVENTS = events/button_event.c \
	events/key_press.c \
	events/mouse_move.c \
	events/poll_events.c \
	events/press_event.c \
	events/release_events.c

FILES = files/file_validity.c \
	files/init_single_level.c

INIT = init/create_button.c \
	init/home_screen.c \
	init/init_level_basic.c \
	init/init_level_graphic.c \
	init/init_level_pick.c \
	init/init_play_level.c \
	init/player.c

UPDATES = updates/anim_player.c \
	updates/play_level_utility.c \
	updates/resize_buttons.c \
	updates/sprite_transfos.c \
	updates/up_player_pos.c \
	updates/update_blocks.c \
	updates/update_percentage.c \
	updates/update_all_percentages.c

SETTINGS = settings/checkbox.c \
	settings/settings.c \
	settings/draw_settings.c \
	settings/move_settings.c \
	settings/scale_settings.c \
	settings/set_evt_manager.c \
	settings/rendering_evt.c \
	settings/sound_evt.c \
	settings/visu_updates.c

SKIN_SELECT = \
	skin_select/draw_select.c \
	skin_select/skin_select.c \
	skin_select/replace_skin_select.c \
	skin_select/select_event.c

PAUSE = \
	pause/init_pause.c \
	pause/pause_events.c

EDITOR = \
	level_editor/block_pick.c \
	level_editor/events.c \
	level_editor/level_editor.c \
	level_editor/level.c \
	level_editor/llist.c \
	level_editor/main.c \
	level_editor/save.c \
	level_editor/add_level_to_list.c \
	level_editor/open_map.c

INFINITE =\
	infinite/infinite.c \
	infinite/add_malus_to_column.c

SRC = $(DRAW) \
	$(EVENTS) \
	$(FILES) \
	$(INIT) \
	$(UPDATES) \
	$(SETTINGS) \
	$(SKIN_SELECT) \
	$(PAUSE) \
	$(EDITOR) \
	$(INFINITE) \
	collision.c \
	main.c \
	progress_bar.c \
	sounds.c \
	init_sprites.c \
	spike_collision.c \
	fps_counter.c \
	usage.c


OBJ = $(SRC:.c=.o)

SFML = -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio -lm

MY_LIB = -L ../lib/my/ -lmy

CFLAGS = -Wall -Wextra -g

INCLUDES = -I ../include

NAME = a.out

all:
	make -s -C ../lib/my/
	gcc $(CFLAGS) $(SRC) $(INCLUDES) $(SFML) $(MY_LIB)

clean:
	rm -f $(OBJ)

fclean:
	$(MAKE) clean

re:
	$(MAKE) clean
	$(MAKE) all
