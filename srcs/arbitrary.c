#include	"gomoku.h"

void		game_results(WINDOW *win, int is)
{
  wresize(win, MENU_H, MENU_L);
  wclear(win);
  if (is == 0)
    wprintw(win, "%sNone of the players won the game.\n%sIt's a draw.", TABS, TABS);
  else if (is == 1)
    wprintw(win, "%sPlayer 1 won the game.\n%sAll hail Player 1.", TABS, TABS);
  else
    wprintw(win, "%sPlayer 2 won the game.\n%sAll hail Player 2.", TABS, TABS);
  wrefresh(win);
  wgetch(win);
}

int		is_exception(t_game *curr, int y, int x)
{
  return (0);
}

int		count_h(t_game *curr)
{
  int		h;
  int		l;
  int		h_save;
  int		res = 0;
  bool		ex = false;

  h = ((curr->player.state == true ? curr->player.p1_w5_cond : curr->player.p2_w5_cond) == true ? curr->player.player1_y_win : curr->cursy);
  l = ((curr->player.state == true ? curr->player.p1_w5_cond : curr->player.p2_w5_cond) == true ? curr->player.player1_x_win : curr->cursx);
  while (h > 0 && curr->goban[h][l].cont == (curr->player.state == true ? 'o' : 'x'))
    h -= 1;
  if (h > 0 && curr->goban[h][l].cont != (curr->player.state == true ? 'o' : 'x'))
    h += 1;
  h_save = h;
  while (h < curr->h && curr->goban[h][l].cont == (curr->player.state == true ? 'o' : 'x'))
    {
      ex = (is_exception(curr, h, l) == 0 ? false : true);
      res += 1;
      h += 1;
    }
  if (h == curr->h && curr->goban[h][l].cont == (curr->player.state == true ? 'o' : 'x'))
    res += 1;
  if (ex == true && res >= 5 && (curr->player.state == true ? curr->player.p1_w5_cond : curr->player.p2_w5_cond) == false)
    {
      curr->player.player1_y_win = h_save;
      curr->player.player2_x_win = curr->cursx;
      if (curr->player.state == true)
	curr->player.p1_w5_cond = true;
      else
	curr->player.p2_w5_cond = true;
      return (0);
    }
  if (ex == true && res >= 5 && (curr->player.state == true ? curr->player.p1_w5_cond : curr->player.p2_w5_cond) == true)
    {
      curr->player.player1_y_win = -1;
      curr->player.player2_x_win = -1;
      if (curr->player.state == true)
	curr->player.p1_w5_cond = false;
      else
	curr->player.p2_w5_cond = false;
      return (1);
    }
  if (res >= 5 && (curr->player.state == true ? curr->player.p1_w5_cond : curr->player.p2_w5_cond) == true)
    return (0);
  if (res >= 5)
    return (1);
  if (curr->player.state == true)
    curr->player.p1_w5_cond = false;
  else
    curr->player.p2_w5_cond = false;
  return (0);
}

int		count_l(t_game *curr)
{
  int		h;
  int		l;
  int		l_save;
  int		res = 0;
  bool		ex = false;

  h = ((curr->player.state == true ? curr->player.p1_w5_cond : curr->player.p2_w5_cond) == true ? curr->player.player1_y_win : curr->cursy);
  l = ((curr->player.state == true ? curr->player.p1_w5_cond : curr->player.p2_w5_cond) == true ? curr->player.player1_x_win : curr->cursx);
  while (l > 0 && curr->goban[h][l].cont == (curr->player.state == true ? 'o' : 'x'))
    l -= 1;
  if (l > 0 && curr->goban[h][l].cont != (curr->player.state == true ? 'o' : 'x'))
    l += 1;
  l_save = l;
  while (l < curr->l && curr->goban[h][l].cont == (curr->player.state == true ? 'o' : 'x'))
    {
      ex = (is_exception(curr, h, l) == 0 ? false : true);
      res += 1;
      l += 1;
    }
  if (l == curr->l && curr->goban[h][l].cont == (curr->player.state == true ? 'o' : 'x'))
    res += 1;
  if (ex == true && res >= 5 && (curr->player.state == true ? curr->player.p1_w5_cond : curr->player.p2_w5_cond) == false)
    {
      curr->player.player1_y_win = curr->cursy;
      curr->player.player2_x_win = l_save;
      if (curr->player.state == true)
	curr->player.p1_w5_cond = true;
      else
	curr->player.p2_w5_cond = true;
      return (0);
    }
  if (ex == true && res >= 5 && (curr->player.state == true ? curr->player.p1_w5_cond : curr->player.p2_w5_cond) == true)
    {
      curr->player.player1_y_win = -1;
      curr->player.player2_x_win = -1;
      if (curr->player.state == true)
	curr->player.p1_w5_cond = false;
      else
	curr->player.p2_w5_cond = false;
      return (1);
    }
  if (res >= 5 && (curr->player.state == true ? curr->player.p1_w5_cond : curr->player.p2_w5_cond) == true)
    return (0);
  if (res >= 5)
    return (1);
  if (curr->player.state == true)
    curr->player.p1_w5_cond = false;
  else
    curr->player.p2_w5_cond = false;
  return (0);
}

int		count_tokens(t_game *curr)
{
  if (count_l(curr) == 1
      || count_h(curr) == 1)
    return (WIN_GAME);
  return (0);
}

int		score_arbitrary(t_game *curr)
{
  if ((curr->player.state == true ? curr->player.player1_capture : curr->player.player2_capture) >= 10)
    return (WIN_GAME);
  if (count_tokens(curr) == WIN_GAME)
    return (WIN_GAME);
  if ((curr->player.state == true ? curr->player.player1_tokens : curr->player.player2_tokens) <= 0)
    return (DRAW_GAME);
  return (0);
}

int		arbitrary(arbitrary_type is, t_game *curr)
{
  int		ret = 0;

  if (is == AUTHORITY)
    {
      if (curr->rules.r3 == true)
	ret = authorize_rule_of_three(curr);
      return (ret);
    }
  else if (is == CHECK)
    {
      if (curr->rules.c2 == true)
	ret = capture_two(curr);
      return (ret);
    }
  else
    {
      ret = score_arbitrary(curr);
      return (ret);
    }
  return (ret);
}
