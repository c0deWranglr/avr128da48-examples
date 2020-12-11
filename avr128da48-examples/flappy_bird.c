#include "include/config.h"
#include "include/logging.h"
#include "include/switch.h"
#include "include/display.h"
#include "include/OLEDC_colors.h"

#include <time.h>

#define		PLAYER_COLOR		OLEDC_COLOR_WHITE
#define		PLAYER_SIZE			3
#define		OBSTACLE_COLOR		OLEDC_COLOR_DARKRED
#define		NUM_OBSTACLE		3
#define		SCORE_COLOR			OLEDC_COLOR_WHITE
#define		GAME_PROGRESS_SPEED 5

typedef struct pos {
	int x;
	int y;
} pos_t;

pos_t player_pos;
pos_t obstacle_pos[NUM_OBSTACLE];
bool game_over;
int obs_cleared;

void paint_obstacles(void);
void paint_player(void);
void paint_score(void);
void evaluate_rules(void);
void reset(void);
void paint_game_over(void);

int main(void)
{
	logging_init();
	display_init();
	switch_init();

	time_t t;
	srand((unsigned) time(&t));

	reset();
	game_over = true;
	draw_str(10, UPPER/3.5, 1, 2, "PRESS TO START", SCORE_COLOR);

	while (1)
	{
		if (!game_over) {
			paint_player();
			paint_obstacles();
			paint_score();
			evaluate_rules();
		} else {
			evaluate_press();
			if (is_change()) {
				reset();
			}
		}
	}
}

void reset() {
	clear_screen();
	player_pos.x = PLAYER_SIZE;
	player_pos.y = UPPER/2;
	for (int i = 0; i < NUM_OBSTACLE; i++) {
		obstacle_pos[i].y = 0;
		obstacle_pos[i].x = (UPPER / NUM_OBSTACLE) * i;
	}

	game_over = false;
	obs_cleared = -3;
}

void evaluate_rules() {
	int player_half = PLAYER_SIZE / 2;

	for (int i = 0; i < NUM_OBSTACLE; i++) {
		pos_t o = obstacle_pos[i];

		if (player_pos.x + player_half >= o.x) {
			if (o.y >= UPPER/2) {
				if (player_pos.y + player_half >= o.y) {
					game_over = true;
					paint_game_over();
				}
			} else {
				if (player_pos.y - player_half <= o.y) {
					game_over = true;
					paint_game_over();
				}
			}
		}
	}
}

void paint_obstacles() {
	for (int i = 0; i < NUM_OBSTACLE; i++) {
		pos_t* p = obstacle_pos + i;
		
		pos_t next;
		if (p->x <= 0) {
			next.y = (rand() % (UPPER - 30)) + 15;
			next.x = p->x + UPPER;
			obs_cleared += 1;
		} else {
			int speed = obs_cleared / GAME_PROGRESS_SPEED;
			if (speed < GAME_PROGRESS_SPEED) {
				speed = GAME_PROGRESS_SPEED;
			}
			next.x = p->x - speed;
			next.y = p->y;
		}

		//Remove previous line
		if (p->y >= UPPER/2) {
			oledC_DrawLine(p->y, UPPER - p->x, UPPER, UPPER - p->x, 1, BACKGROUND);
		} else {
			oledC_DrawLine(LOWER, UPPER - p->x, p->y, UPPER - p->x, 1, BACKGROUND);
		}

		//Draw new line
		if (next.y >= UPPER/2) {
			oledC_DrawLine(next.y, UPPER - next.x, UPPER, UPPER - next.x, 1, OBSTACLE_COLOR);
		} else {
			oledC_DrawLine(LOWER, UPPER - next.x, next.y, UPPER - next.x, 1, OBSTACLE_COLOR);
		}

		p->x = next.x;
		p->y = next.y;
	}
}

void paint_player() {
	if (is_pressed()) {
		if (player_pos.y < UPPER - 10) {
			oledC_DrawCircle(player_pos.y, UPPER - player_pos.x, PLAYER_SIZE, BACKGROUND);
			player_pos.y += 8;
		}
	} else {
		if (player_pos.y > LOWER + 10) {
			oledC_DrawCircle(player_pos.y, UPPER - player_pos.x, PLAYER_SIZE, BACKGROUND);
			player_pos.y -= 5;
		}
	}
	oledC_DrawCircle(player_pos.y, UPPER - player_pos.x, PLAYER_SIZE, PLAYER_COLOR);
}

void paint_score() {
	int score = obs_cleared;
	if (score < 0) {
		score = 0;
	}

	char str[10];
	sprintf(str, "%d", score-1);
	draw_str(5, 5, 1, 2, str, BACKGROUND);
	
	sprintf(str, "%d", score);
	draw_str(5, 5, 1, 2, str, SCORE_COLOR);
}

void paint_game_over() {
	clear_screen();
	draw_str(25, UPPER/3.5, 1, 2, "GAME OVER", SCORE_COLOR);
	
	char str[10];
	sprintf(str, "%d", obs_cleared);
	draw_str(50, UPPER/1.5, 1, 2, str, SCORE_COLOR);
}