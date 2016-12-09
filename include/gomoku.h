#ifndef		_GOMOKU_H_
# define	_GOMOKU_H_

# include	<sys/types.h>
# include	<sys/stat.h>
# include	<fcntl.h>
# include	<stdio.h>
# include	<stdlib.h>
# include	<string.h>
# include	<unistd.h>
# include	<stdbool.h>
# include	<errno.h>
# include	<getopt.h>
# include	<ncurses.h>
# include	<time.h>
# include	"trace.h"

/*
** Defines
*/

# define	DEFAULT_VALUE (19)
# define	MENU_H (150)
# define	MENU_L (150)
# define	TITLE_H (18)
# define	TITLE_L (117)

# define	TITLE_PATH ("/srcs/div/title")
# define	DEF_READ (117)
# define	TABS ("\t\t\t\t\t\t\t")

# define	RULE_OF_TWO (-2)
# define	RULE_OF_THREE (-3)

# define	RESUME (10)
# define	NEW_GAME (1)
# define	OPTIONS (2)
# define	OPTIONS_NB (6)
# define	END_GAME (42)

# define	SPACE_KEY (32)
# define	ARROW_UP_KEY (183)
# define	ARROW_DOWN_KEY (184)
# define	ARROW_RIGHT_KEY (185)
# define	ARROW_LEFT_KEY (186)
# define	ESC_KEY (27)

# define	EMPTY_SPOT ('-')
# define	PLAYER_SPOT ('o')
# define	IA_SPOT ('x')

# define	DRAW_GAME (11)
# define	WIN_GAME (42)

# define	H (1)
# define	L (2)
# define	D1 (3)
# define	D2 (4)

# define	NO_PRIO (1)

# define	PRIO_CAPTURE (2)
# define	PRIO_LOSE (3)
# define	PRIO_DENY (4)
# define	PRIO_WIN (5)

# define	ADD_TOKEN (1)
# define	AVOID_TOKEN (-1)

# define	IA (1)
# define	PLAYER (2)

/*
** Enum
*/

typedef enum
  {
    AUTHORITY,
    CHECK,
    SCORE
  }		arbitrary_type;

/*
** Structures
*/

typedef struct	s_menu
{
  bool		title_state;
  char		**title;
  int		state;
}		t_menu;

typedef struct	s_options
{
  bool		vs_ia;
  int		state;
}		t_options;

typedef struct	s_rules
{
  bool		c2;
  bool		r3;
  bool		w5;
}		t_rules;

typedef struct	s_player
{
  bool		help;
  bool		first;
  bool		state;
  int		player1_tokens;
  int		player2_tokens;
  int		player1_capture;
  int		player2_capture;
  //Win options for 5 with c2 possible
  bool		p1_w5_cond;
  int		player1_y_win;
  int		player1_x_win;
  bool		p2_w5_cond;
  int		player2_y_win;
  int		player2_x_win;
}		t_player;

typedef struct	s_case
{
  char		cont;
  int		prio;
  int		prio_color;

  int		ia_prio;
  bool		forbidden;
}		t_case;

typedef struct	s_game
{
  int		h;
  int		l;
  int		cursy;
  int		cursx;
  int		y_calc;
  int		x_calc;

  int		state;
  t_menu	menu;
  t_options	options;
  t_rules	rules;
  t_player	player;
  t_case	**goban;
}		t_game;

/*
** Title functions
*/

int		get_title(t_game *curr);
void		display_title(t_game *curr, WINDOW *win);

/*
** Initialization functions
*/

void		reset_goban(t_game *curr);
void		new_game(t_game *curr, WINDOW *win);
void		init_ncurses(WINDOW *win);
void		init_cursor(t_game *curr);
void		init_players(t_game *curr);
void		init_game(t_game *curr);
int		init_goban(t_game *curr);

/*
** Cmds functions
*/

int		player_cmds(t_game *curr, WINDOW *win);
int		ia_cmds(t_game *curr, WINDOW *win);

/*
** IA functions
*/

int		goban_reader(t_game *curr);
void		ia_process(t_game *curr);

/*
** Arbitrary functions
*/

void		game_results(WINDOW *win, int is);
int		score_arbitrary(t_game *curr);
int		arbitrary(arbitrary_type is, t_game *curr);

/*
** Rules functions
*/

int		authorize_rule_of_three(t_game *curr);
int		capture_two(t_game *curr);
int		count_h(t_game *curr, int h, int l, bool state);
int		count_l(t_game *curr, int h, int l, bool state);
int		count_d1(t_game *curr, int h, int l, bool state);
int		count_d2(t_game *curr, int h, int l, bool state);
int		is_exception(t_game *curr, int y, int x, char is);

/*
** Print functions
*/

void		root_menu(t_game *curr, WINDOW *win);
void		print_options(t_game *curr, WINDOW *win);
int		print_menu(t_game *curr, WINDOW *win);
void		update_goban(t_game *curr);
void		print_goban(t_game *curr, WINDOW *win);
void		print_infos(t_game *curr, WINDOW *win);
void		prompt_options(t_game *curr, WINDOW *win);
int		prompt_menu(t_game *curr, WINDOW *win);

/*
** Key functions
*/

void		reset_key(char *key);

/*
** Close functions
*/

int		end_game(t_game *curr, WINDOW *win);
void		free_goban(t_game *curr);
void		end_ncurses();

#endif		/* _GOMOKU_H_ */
