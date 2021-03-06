#include <stdlib.h> 
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "getch.h"
#include "game.h"
#include "ui.h"

static void ui_display(ui_t *ui)
{
	game_t *g = ui->g;

	for (int y = 0; y < ui->stage_hgt; ++y) {
		for (int x = 0; x < ui->stage_wid; ++x) {
			switch (ui->stage[x][y]) {
			case WALL_H: printf("="); break;
			case WALL_V: printf("|"); break;
			case FIELD: printf(" "); break;
			case SNAKE:printf("\e[32m+\e[0m"); break;
			case FOOD: printf("\e[31m@\e[0m");
			}
		}
		printf("\n");
	}

	if (g->pause)
		printf("pause : press 'p' to continue\n");
	else 
		printf("your length is %d\n", snake_len(g->snake));
}


int ui_init(ui_t **ui, game_t *g)
{

	open_termios();
	*ui = malloc(sizeof(ui_t));

	if (!(*ui)) {
		perror("malloc"); 
		return 1;
	}

	(*ui)->g = g;
	(*ui)->stage = game_get_stage(g);

	game_stage_size(g, &(*ui)->stage_wid, &(*ui)->stage_hgt);
	game_set_ui(g, *ui);

	return 0;
}


void ui_free(ui_t *ui) 
{
	close_termios();
	free(ui);
}


void *ui_loop(void *v)
{
	ui_t *ui = v;
	ui->active = 1;

	while (ui->active) {
		system("clear");
		ui_display(ui);
	
		if (kbhit()) {
			char key = getch();
			game_key_add(ui->g, key);
		}
		usleep(70000);
	}

	return NULL;
}

void ui_stop(ui_t *ui)
{
	ui->active = 0;
}



void ui_start(ui_t *ui)
{
	pthread_create(&ui->handle, NULL, ui_loop, ui);
	pthread_detach(ui->handle);
}


