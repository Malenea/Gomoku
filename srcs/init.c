#include	"gomoku.h"

void		reset_goban(t_game *curr)
{
  int		h;
  int		l;

  for (h = 0; h < curr->h; h++)
    for (l = 0; l < curr->l; l++)
      {
	curr->goban[h][l].cont = EMPTY_SPOT;
	curr->goban[h][l].prio = NO_PRIO;
	curr->goban[h][l].ia_prio = NO_PRIO;
	curr->goban[h][l].forbidden = false;
      }
  curr->y_calc = -1;
  curr->x_calc = -1;
}

void		new_game(t_game *curr, WINDOW *win)
{
  wresize(win, curr->h + 6, curr->l + 1);
  init_players(curr);
  reset_goban(curr);
  init_cursor(curr);
  curr->state = 1;
}

void		init_ncurses(WINDOW *win)
{
  initscr();
  curs_set(0);
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_GREEN);
  init_pair(2, COLOR_WHITE, COLOR_RED);
  init_pair(3, COLOR_BLUE, COLOR_BLACK);
  init_pair(4, COLOR_RED, COLOR_BLACK);
  // For the helper
  init_pair(5, COLOR_BLACK, COLOR_CYAN);
  init_pair(6, COLOR_CYAN, COLOR_GREEN);
  init_pair(7, COLOR_BLACK, COLOR_RED);
  init_pair(8, COLOR_RED, COLOR_GREEN);
}

void		init_cursor(t_game *curr)
{
  curr->cursy = 0;
  curr->cursx = 0;
}

void		init_players(t_game *curr)
{
  curr->player.player1_tokens = 60;
  curr->player.player2_tokens = 60;
  curr->player.player1_capture = 0;
  curr->player.player2_capture = 0;
  curr->player.state = (curr->player.first == true ? true : false);
  curr->player.p1_w5_cond = false;
  curr->player.p2_w5_cond = false;
  curr->player.player1_y_win = -1;
  curr->player.player1_x_win = -1;
  curr->player.player2_y_win = -1;
  curr->player.player2_x_win = -1;
}

void		init_options(t_game *curr)
{
  curr->options.vs_ia = true;
  curr->options.debug = false;
}

void		init_game(t_game *curr)
{
  curr->state = 0;
  curr->rules.c2 = true;
  curr->rules.r3 = true;
  curr->rules.w5 = true;
  curr->h = DEFAULT_VALUE;
  curr->l = DEFAULT_VALUE;
  init_cursor(curr);
  curr->player.help = false;
  curr->player.first = true;
  init_players(curr);
  init_options(curr);
  get_title(curr);
}

int		init_goban(t_game *curr)
{
  int		h;
  int		l;
  void		*ret;

  ret = (curr->goban = malloc(sizeof(t_case *) * curr->h));
  if (ret == NULL)
    return (-ENOMEM);
  for (h = 0; h < curr->h; h++)
    {
      ret = (curr->goban[h] = malloc(sizeof(t_case) * curr->l));
      for (l = 0; l < curr->l; l++)
	curr->goban[h][l].cont = EMPTY_SPOT;
    }
  curr->l -= 1;
  curr->h -= 1;
  return (0);
}
