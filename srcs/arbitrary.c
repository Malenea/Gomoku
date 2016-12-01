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

int		d_for_hl(t_game *curr, int y, int x)
{
  if (x > 0 && y > 0 && curr->goban[y - 1][x - 1].cont == (curr->player.state == true ? PLAYER_SPOT : IA_SPOT))
    {
      if (x > 1 && y > 1 && curr->goban[y - 2][x - 2].cont == (curr->player.state == true ? IA_SPOT : PLAYER_SPOT)
	  && x < curr->l && y < curr->h && curr->goban[y + 1][x + 1].cont == EMPTY_SPOT)
	{
	  curr->y_calc = y + 1;
	  curr->x_calc = x + 1;
	  return (1);
	}
      if (x < curr->l && y < curr->h && curr->goban[y + 1][x + 1].cont == (curr->player.state == true ? IA_SPOT : PLAYER_SPOT)
	  && x > 1 && y > 1 && curr->goban[y - 2][x - 2].cont == EMPTY_SPOT)
	{
	  curr->y_calc = y - 2;
	  curr->x_calc = x - 2;
	  return (1);
	}
    }
  if (x < curr->l && y < curr->h && curr->goban[y + 1][x + 1].cont == (curr->player.state == true ? PLAYER_SPOT : IA_SPOT))
    {
      if (x > 0 && y > 0 && curr->goban[y - 1][x - 1].cont == (curr->player.state == true ? IA_SPOT : PLAYER_SPOT)
	  && x < curr->l - 1 && y < curr->h - 1 && curr->goban[y + 2][x + 2].cont == EMPTY_SPOT)
	{
	  curr->y_calc = y + 2;
	  curr->x_calc = x + 2;
	  return (1);
	}
      if (x < curr->l - 1 && y < curr->h - 1 && curr->goban[y + 2][x + 2].cont == (curr->player.state == true ? IA_SPOT : PLAYER_SPOT)
	  && x > 0 && y > 0 && curr->goban[y - 1][x - 1].cont == EMPTY_SPOT)
	{
	  curr->y_calc = y - 1;
	  curr->x_calc = x - 1;
	  return (1);
	}
    }
  if (x < curr->l && y > 0 && curr->goban[y - 1][x + 1].cont == (curr->player.state == true ? PLAYER_SPOT : IA_SPOT))
    {
      if (x > 0 && y < curr->l && curr->goban[y + 1][x - 1].cont == (curr->player.state == true ? IA_SPOT : PLAYER_SPOT)
	  && x < curr->l - 1 && y > 1 && curr->goban[y - 2][x + 2].cont == EMPTY_SPOT)
	{
	  curr->y_calc = y - 2;
	  curr->x_calc = x + 2;
	  return (1);
	}
      if (x < curr->l - 1 && y > 1 && curr->goban[y - 2][x + 2].cont == (curr->player.state == true ? IA_SPOT : PLAYER_SPOT)
	  && x > 0 && y < curr->l && curr->goban[y + 1][x - 1].cont == EMPTY_SPOT)
	{
	  curr->y_calc = y + 1;
	  curr->x_calc = x - 1;
	  return (1);
	}
    }
  if (x < curr->l && y > 0 && curr->goban[y + 1][x - 1].cont == (curr->player.state == true ? PLAYER_SPOT : IA_SPOT))
    {
      if (x > 1 && y < curr->l - 1 && curr->goban[y + 2][x - 2].cont == (curr->player.state == true ? IA_SPOT : PLAYER_SPOT)
	  && x < curr->l && y > 0 && curr->goban[y - 1][x + 1].cont == EMPTY_SPOT)
	{
	  curr->y_calc = y - 1;
	  curr->x_calc = x + 1;
	  return (1);
	}
      if (x < curr->l && y > 0 && curr->goban[y - 1][x + 1].cont == (curr->player.state == true ? IA_SPOT : PLAYER_SPOT)
	  && x > 1 && y < curr->l - 1 && curr->goban[y + 2][x - 2].cont == EMPTY_SPOT)
	{
	  curr->y_calc = y + 2;
	  curr->x_calc = x - 2;
	  return (1);
	}
    }
  return (0);
}

int		is_exception(t_game *curr, int y, int x, char is)
{
  if (curr->goban[y][x].cont == (curr->player.state == true ? PLAYER_SPOT : IA_SPOT))
    {
      if (is == 'h')
	{
	  if (x > 0 && curr->goban[y][x - 1].cont == (curr->player.state == true ? PLAYER_SPOT : IA_SPOT))
	    {
	      if (x > 1 && curr->goban[y][x - 2].cont == (curr->player.state == true ? IA_SPOT : PLAYER_SPOT)
		  && x < curr->l && curr->goban[y][x + 1].cont == EMPTY_SPOT)
		{
		  curr->y_calc = y;
		  curr->x_calc = x + 1;
		  return (1);
		}
	      if (x < curr->l && curr->goban[y][x + 1].cont == (curr->player.state == true ? IA_SPOT : PLAYER_SPOT)
		  && x > 1 && curr->goban[y][x - 2].cont == EMPTY_SPOT)
		{
		  curr->y_calc = y;
		  curr->x_calc = x - 2;
		  return (1);
		}
	    }
	  if (x < curr->l && curr->goban[y][x + 1].cont == (curr->player.state == true ? PLAYER_SPOT : IA_SPOT))
	    {
	      if (x > 0 && curr->goban[y][x - 1].cont == (curr->player.state == true ? IA_SPOT : PLAYER_SPOT)
		  && x < curr->l - 1 && curr->goban[y][x + 2].cont == EMPTY_SPOT)
		{
		  curr->y_calc = y;
		  curr->x_calc = x + 2;
		  return (1);
		}
	      if (x < curr->l - 1 && curr->goban[y][x + 2].cont == (curr->player.state == true ? IA_SPOT : PLAYER_SPOT)
		  && x > 0 && curr->goban[y][x + 1].cont == EMPTY_SPOT)
		{
		  curr->y_calc = y;
		  curr->x_calc = x + 1;
		  return (1);
		}
	    }
	  if ((d_for_hl(curr, y, x)) == 1)
	    return (1);
	}
      else if (is == 'l')
	{
	  if (y > 0 && curr->goban[y - 1][x].cont == (curr->player.state == true ? PLAYER_SPOT : IA_SPOT))
	    {
	      if (y > 1 && curr->goban[y - 2][x].cont == (curr->player.state == true ? IA_SPOT : PLAYER_SPOT)
		  && y < curr->h && curr->goban[y + 1][x].cont == EMPTY_SPOT)
		{
		  curr->y_calc = y + 1;
		  curr->x_calc = x;
		  return (1);
		}
	      if (y < curr->h && curr->goban[y + 1][x].cont == (curr->player.state == true ? IA_SPOT : PLAYER_SPOT)
		  && y > 1 && curr->goban[y - 2][x].cont == EMPTY_SPOT)
		{
		  curr->y_calc = y - 2;
		  curr->x_calc = x;
		  return (1);
		}
	    }
	  if (y < curr->h && curr->goban[y + 1][x].cont == (curr->player.state == true ? PLAYER_SPOT : IA_SPOT))
	    {
	      if (y > 0 && curr->goban[y - 1][x].cont == (curr->player.state == true ? IA_SPOT : PLAYER_SPOT)
		  && y < curr->h - 1 && curr->goban[y + 2][x].cont == EMPTY_SPOT)
		{
		  curr->y_calc = y + 2;
		  curr->x_calc = x;
		}
	      if (y < curr->h - 1 && curr->goban[y + 2][x].cont == (curr->player.state == true ? IA_SPOT : PLAYER_SPOT)
		  && y > 0 && curr->goban[y + 1][x].cont == EMPTY_SPOT)
		{
		  curr->y_calc = y + 1;
		  curr->x_calc = x;
		  return (1);
		}
	    }
	  if ((d_for_hl(curr, y, x)) == 1)
	    return (1);
	}
    }
  return (0);
}

int		count_h(t_game *curr, int h, int l, bool state)
{
  int		h_save;
  int		res = 0;
  bool		ex = false;

  if (h < 0  || l < 0)
    return (0);
  while (h > 0 && curr->goban[h][l].cont == (state == true ? PLAYER_SPOT : IA_SPOT))
    h -= 1;
  if (h > 0 && curr->goban[h][l].cont != (state == true ? PLAYER_SPOT : IA_SPOT))
    h += 1;
  h_save = h;
  while (h < curr->h && curr->goban[h][l].cont == (state == true ? PLAYER_SPOT : IA_SPOT))
    {
      if (is_exception(curr, h, l, 'h') == 1 && (state == true ? curr->player.p1_w5_cond : curr->player.p2_w5_cond) == false)
	ex = true;
      res += 1;
      h += 1;
    }
  if (h == curr->h && curr->goban[h][l].cont == (state == true ? PLAYER_SPOT : IA_SPOT))
    res += 1;

  if (ex == true && res >= 5)
    {
      if (state == true)
	{
	  curr->player.player1_y_win = h_save;
	  curr->player.player1_x_win = curr->cursx;
	}
      else
	{
	  curr->player.player2_y_win = h_save;
	  curr->player.player2_x_win = curr->cursx;
	}
      if (state == true)
	curr->player.p1_w5_cond = true;
      else
	curr->player.p2_w5_cond = true;
      curr->goban[curr->y_calc][curr->x_calc].prio = PRIO_DENY;
      curr->y_calc = -1;
      curr->x_calc = -1;
      return (0);
    }
  if (res >= 5)
    return (1);
  return (0);
}

int		count_l(t_game *curr, int h, int l, bool state)
{
  int		l_save;
  int		res = 0;
  bool		ex = false;

  if (h < 0  || l < 0)
    return (0);
  while (l > 0 && curr->goban[h][l].cont == (state == true ? PLAYER_SPOT : IA_SPOT))
    l -= 1;
  if (l > 0 && curr->goban[h][l].cont != (state == true ? PLAYER_SPOT : IA_SPOT))
    l += 1;
  l_save = l;
  while (l < curr->l && curr->goban[h][l].cont == (state == true ? PLAYER_SPOT : IA_SPOT))
    {
      if (is_exception(curr, h, l, 'l') == 1 && (state == true ? curr->player.p1_w5_cond : curr->player.p2_w5_cond) == false)
	ex = true;
      res += 1;
      l += 1;
    }
  if (l == curr->l && curr->goban[h][l].cont == (state == true ? PLAYER_SPOT : IA_SPOT))
    res += 1;

  if (ex == true && res >= 5)
    {
      if (state == true)
	{
	  curr->player.player1_y_win = curr->cursy;
	  curr->player.player1_x_win = l_save;
	}
      else
	{
	  curr->player.player2_y_win = curr->cursy;
	  curr->player.player2_x_win = l_save;
	}
      if (state == true)
	curr->player.p1_w5_cond = true;
      else
	curr->player.p2_w5_cond = true;
      curr->goban[curr->y_calc][curr->x_calc].prio = PRIO_DENY;
      curr->y_calc = -1;
      curr->x_calc = -1;
      return (0);
    }
  if (res >= 5)
    return (1);
  return (0);
}

int		count_d1(t_game *curr, int h, int l, bool state)
{
  int		h_save;
  int		l_save;
  int		res = 0;
  bool		ex = false;

  if (h < 0  || l < 0)
    return (0);
  while (h > 0 && l > 0 && curr->goban[h][l].cont == (state == true ? PLAYER_SPOT : IA_SPOT))
    {
      h -= 1;
      l -= 1;
    }
  if (((h > 0 && h < curr->h) || (l > 0 && l < curr->l)) && curr->goban[h][l].cont != (state == true ? PLAYER_SPOT : IA_SPOT))
    {
      h += 1;
      l += 1;
    }
  h_save = h;
  l_save = l;
  while (h < curr->h && l < curr->l && curr->goban[h][l].cont == (state == true ? PLAYER_SPOT : IA_SPOT))
    {
      if ((is_exception(curr, h, l, 'l') == 1 || is_exception(curr, h, l, 'h') == 1) && (state == true ? curr->player.p1_w5_cond : curr->player.p2_w5_cond) == false)
	ex = true;
      res += 1;
      h += 1;
      l += 1;
    }
  if ((h == curr->h || l == curr->l) && curr->goban[h][l].cont == (state == true ? PLAYER_SPOT : IA_SPOT))
    res += 1;

  if (ex == true && res >= 5)
    {
      if (state == true)
	{
	  curr->player.player1_y_win = h_save;
	  curr->player.player1_x_win = l_save;
	}
      else
	{
	  curr->player.player2_y_win = h_save;
	  curr->player.player2_x_win = l_save;
	}
      if (state == true)
	curr->player.p1_w5_cond = true;
      else
	curr->player.p2_w5_cond = true;
      curr->goban[curr->y_calc][curr->x_calc].prio = PRIO_DENY;
      curr->y_calc = -1;
      curr->x_calc = -1;
      return (0);
    }
  if (res >= 5)
    return (1);
  return (0);
}

int		count_d2(t_game *curr, int h, int l, bool state)
{
  int		h_save;
  int		l_save;
  int		res = 0;
  bool		ex = false;

  if (h < 0  || l < 0)
    return (0);
  while (h < curr->h && l > 0 && curr->goban[h][l].cont == (state == true ? PLAYER_SPOT : IA_SPOT))
    {
      h += 1;
      l -= 1;
    }
  if (((h > 0 && h < curr->h) || (l > 0 && l < curr->l)) && curr->goban[h][l].cont != (state == true ? PLAYER_SPOT : IA_SPOT))
    {
      h -= 1;
      l += 1;
    }
  h_save = h;
  l_save = l;
  while (h > 0 && l < curr->l && curr->goban[h][l].cont == (state == true ? PLAYER_SPOT : IA_SPOT))
    {
      if ((is_exception(curr, h, l, 'l') == 1 || is_exception(curr, h, l, 'h') == 1) && (state == true ? curr->player.p1_w5_cond : curr->player.p2_w5_cond) == false)
	ex = true;
      res += 1;
      h -= 1;
      l += 1;
    }
  if ((h == 0 || l == curr->l) && curr->goban[h][l].cont == (state == true ? PLAYER_SPOT : IA_SPOT))
    res += 1;

  if (ex == true && res >= 5)
    {
      if (state == true)
	{
	  curr->player.player1_y_win = h_save;
	  curr->player.player1_x_win = l_save;
	}
      else
	{
	  curr->player.player2_y_win = h_save;
	  curr->player.player2_x_win = l_save;
	}
      if (state == true)
	curr->player.p1_w5_cond = true;
      else
	curr->player.p2_w5_cond = true;
      curr->goban[curr->y_calc][curr->x_calc].prio = PRIO_DENY;
      curr->y_calc = -1;
      curr->x_calc = -1;
      return (0);
    }
  if (res >= 5)
    return (1);
  return (0);
}

int		count_tokens(t_game *curr)
{
  if (count_h(curr, curr->cursy, curr->cursx, curr->player.state == true ? true : false) == 1)
    return (WIN_GAME);
  if (count_l(curr, curr->cursy, curr->cursx, curr->player.state == true ? true : false) == 1)
    return (WIN_GAME);
  if (count_d1(curr, curr->cursy, curr->cursx, curr->player.state == true ? true : false) == 1)
    return (WIN_GAME);
  if (count_d2(curr, curr->cursy, curr->cursx, curr->player.state == true ? true : false) == 1)
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
