#include	"gomoku.h"

int		ia_rand(t_game *curr)
{
  time_t	seed;

  time(&seed);
  srand(seed);
  curr->cursy = rand() % curr->h;
  curr->cursx = rand() % curr->l;
  if (arbitrary(AUTHORITY, curr) != 0)
    return (ia_rand(curr));
  curr->goban[curr->cursy][curr->cursx].cont = IA_SPOT;
  curr->player.player2_tokens -= 1;
  return (0);
}

void		reset_forbidden(t_game *curr)
{
  for (int h = 0; h < curr->h; h++)
    for (int l = 0; l < curr->l; l++)
      if (curr->goban[h][l].forbidden == true)
	curr->goban[h][l].forbidden = false;
}

int		check_prio_h(t_game *curr, int h, int l)
{
  int		tokens = 0;

  if ((h < curr->h - 2 && curr->goban[h + 3][l].cont != PLAYER_SPOT
       && curr->goban[h + 2][l].cont == IA_SPOT && curr->goban[h + 1][l].cont == IA_SPOT
       && (h > 0 && curr->goban[h - 1][l].cont != PLAYER_SPOT))
      || (h < curr->h - 1 && curr->goban[h + 2][l].cont != PLAYER_SPOT
	  && curr->goban[h + 1][l].cont == IA_SPOT
	  && (h > 1 && curr->goban[h - 1][l].cont == IA_SPOT && curr->goban[h - 2][l].cont != PLAYER_SPOT))
      || (h > 2 && curr->goban[h - 3][l].cont != PLAYER_SPOT
	  && curr->goban[h - 2][l].cont == IA_SPOT && curr->goban[h - 1][l].cont == IA_SPOT
	  && (h < curr->h && curr->goban[h + 1][l].cont != PLAYER_SPOT)))
    tokens += curr->h * 50;
  if ((h < curr->h - 3 && curr->goban[h + 4][l].cont != IA_SPOT
       && curr->goban[h + 3][l].cont == PLAYER_SPOT && curr->goban[h + 2][l].cont == PLAYER_SPOT
       && curr->goban[h + 1][l].cont == PLAYER_SPOT)
      || (h > 3 && curr->goban[h - 4][l].cont != IA_SPOT
	  && curr->goban[h - 3][l].cont == PLAYER_SPOT && curr->goban[h - 2][l].cont == PLAYER_SPOT
	  && curr->goban[h - 1][l].cont == PLAYER_SPOT))
    tokens += curr->h * 40;
  if ((h < curr->h - 2 && curr->goban[h + 3][l].cont == IA_SPOT
       && curr->goban[h + 2][l].cont == PLAYER_SPOT && curr->goban[h + 1][l].cont == PLAYER_SPOT)
      || (h > 2 && curr->goban[h - 3][l].cont == IA_SPOT
	  && curr->goban[h - 2][l].cont == PLAYER_SPOT && curr->goban[h - 1][l].cont == PLAYER_SPOT))
    {
      if (curr->player.player2_capture > curr->player.player1_capture)
	tokens += curr->h * 30;
      else
	tokens += curr->h * 20;
    }
  if ((h < curr->h - 2 && curr->goban[h + 3][l].cont == PLAYER_SPOT
       && curr->goban[h + 2][l].cont == IA_SPOT && curr->goban[h + 1][l].cont == IA_SPOT)
      || (h > 2 && curr->goban[h - 3][l].cont == PLAYER_SPOT
	  && curr->goban[h - 2][l].cont == IA_SPOT && curr->goban[h - 1][l].cont == IA_SPOT))
    {
      if (curr->player.player2_capture > curr->player.player1_capture)
	tokens += curr->h * 20;
      else
	tokens += curr->h * 30;
    }
  return (tokens);
}

int		check_prio_l(t_game *curr, int h, int l)
{
  int		tokens = 0;

  if ((l < curr->l - 2 && curr->goban[h][l + 3].cont != PLAYER_SPOT
       && curr->goban[h][l + 2].cont == IA_SPOT && curr->goban[h][l + 1].cont == IA_SPOT
       && (l > 0 && curr->goban[h][l - 1].cont != PLAYER_SPOT))
      || (l < curr->l - 1 && curr->goban[h][l + 2].cont != PLAYER_SPOT
	  && curr->goban[h][l + 1].cont == IA_SPOT
	  && (l > 1 && curr->goban[h][l - 1].cont == IA_SPOT && curr->goban[h][l - 2].cont != PLAYER_SPOT))
      || (l > 2 && curr->goban[h][l - 3].cont != PLAYER_SPOT
	  && curr->goban[h][l - 2].cont == IA_SPOT && curr->goban[h][l - 1].cont == IA_SPOT
	  && (l < curr->l && curr->goban[h][l + 1].cont != PLAYER_SPOT)))
    tokens += curr->h * 50;
  if ((l < curr->l - 3 && curr->goban[h][l + 4].cont != IA_SPOT
       && curr->goban[h][l + 3].cont == PLAYER_SPOT && curr->goban[h][l + 2].cont == PLAYER_SPOT
       && curr->goban[h][l + 1].cont == PLAYER_SPOT)
      || (l > 3 && curr->goban[h][l - 4].cont != IA_SPOT
	  && curr->goban[h][l - 3].cont == PLAYER_SPOT && curr->goban[h][l - 2].cont == PLAYER_SPOT
	  && curr->goban[h][l - 1].cont == PLAYER_SPOT))
    tokens += curr->h * 40;
  if ((l < curr->l - 2 && curr->goban[h][l + 3].cont == IA_SPOT
       && curr->goban[h][l + 2].cont == PLAYER_SPOT && curr->goban[h][l + 1].cont == PLAYER_SPOT)
      || (l > 2 && curr->goban[h][l - 3].cont == IA_SPOT
	  && curr->goban[h][l - 2].cont == PLAYER_SPOT && curr->goban[h][l - 1].cont == PLAYER_SPOT))
    {
      if (curr->player.player2_capture > curr->player.player1_capture)
	tokens += curr->h * 30;
      else
	tokens += curr->h * 20;
    }
  if ((l < curr->l - 2 && curr->goban[h][l + 3].cont == PLAYER_SPOT
       && curr->goban[h][l + 2].cont == IA_SPOT && curr->goban[h][l + 1].cont == IA_SPOT)
      || (l > 2 && curr->goban[h][l - 3].cont == PLAYER_SPOT
	  && curr->goban[h][l - 2].cont == IA_SPOT && curr->goban[h][l - 1].cont == IA_SPOT))
    {
      if (curr->player.player2_capture > curr->player.player1_capture)
	tokens += curr->h * 20;
      else
	tokens += curr->h * 30;
    }
  return (tokens);
}

int		check_prio_d1(t_game *curr, int h, int l)
{
  int		tokens = 0;

  if ((h < curr->h - 2 && l < curr->l - 2 && curr->goban[h + 3][l + 3].cont != PLAYER_SPOT
       && curr->goban[h + 2][l + 2].cont == IA_SPOT && curr->goban[h + 1][l + 1].cont == IA_SPOT
       && (h > 0 && l > 0 && curr->goban[h - 1][l - 1].cont != PLAYER_SPOT))
      || (h < curr->h - 1 && l < curr->l - 1 && curr->goban[h + 2][l + 2].cont != PLAYER_SPOT
	  && curr->goban[h + 1][l + 1].cont == IA_SPOT
	  && (h > 1 && l > 1 &&  curr->goban[h - 1][l - 1].cont == IA_SPOT && curr->goban[h - 2][l - 2].cont != PLAYER_SPOT))
      || (h > 2 && l > 2 && curr->goban[h - 3][l - 3].cont != PLAYER_SPOT
	  && curr->goban[h - 2][l - 2].cont == IA_SPOT && curr->goban[h - 1][l - 1].cont == IA_SPOT
	  && (h < curr->h && l < curr->l && curr->goban[h + 1][l + 1].cont != PLAYER_SPOT)))
    tokens += curr->h * 50;
  if ((h < curr->h - 3 && l < curr->l - 3 && curr->goban[h + 4][l + 4].cont != IA_SPOT
       && curr->goban[h + 3][l + 3].cont == PLAYER_SPOT && curr->goban[h + 2][l + 2].cont == PLAYER_SPOT
       && curr->goban[h + 1][l + 1].cont == PLAYER_SPOT)
      || (h > 3 && l > 3 && curr->goban[h - 4][l - 4].cont != IA_SPOT
	  && curr->goban[h - 3][l - 3].cont == PLAYER_SPOT && curr->goban[h - 2][l - 2].cont == PLAYER_SPOT
	  && curr->goban[h - 1][l - 1].cont == PLAYER_SPOT))
    tokens += curr->h * 40;
  if ((h < curr->h - 2 && l < curr->h - 2 && curr->goban[h + 3][l + 3].cont == IA_SPOT
       && curr->goban[h + 2][l + 2].cont == PLAYER_SPOT && curr->goban[h + 1][l + 1].cont == PLAYER_SPOT)
      || (h > 2 && l > 2 && curr->goban[h - 3][l - 3].cont == IA_SPOT
	  && curr->goban[h - 2][l - 2].cont == PLAYER_SPOT && curr->goban[h - 1][l - 1].cont == PLAYER_SPOT))
    {
      if (curr->player.player2_capture > curr->player.player1_capture)
	tokens += curr->h * 30;
      else
	tokens += curr->h * 20;
    }
  if ((h < curr->h - 2 && l < curr->l - 2 && curr->goban[h + 3][l + 3].cont == PLAYER_SPOT
       && curr->goban[h + 2][l + 2].cont == IA_SPOT && curr->goban[h + 1][l + 1].cont == IA_SPOT)
      || (h > 2 && l > 2 && curr->goban[h - 3][l - 3].cont == PLAYER_SPOT
	  && curr->goban[h - 2][l - 2].cont == IA_SPOT && curr->goban[h - 1][l - 1].cont == IA_SPOT))
    {
      if (curr->player.player2_capture > curr->player.player1_capture)
	tokens += curr->h * 20;
      else
	tokens += curr->h * 30;
    }
  return (tokens);
}

int		check_prio_d2(t_game *curr, int h, int l)
{
  int		tokens = 0;

  if ((h > 2 && l < curr->l - 2 && curr->goban[h - 3][l + 3].cont != PLAYER_SPOT
       && curr->goban[h - 2][l + 2].cont == IA_SPOT && curr->goban[h - 1][l + 1].cont == IA_SPOT
       && (h < curr->h && l > 0 && curr->goban[h + 1][l - 1].cont != PLAYER_SPOT))
      || (h > 1 && l < curr->l - 1 && curr->goban[h - 2][l + 2].cont != PLAYER_SPOT
	  && curr->goban[h - 1][l + 1].cont == IA_SPOT
	  && (h < curr->h - 1 && l > 1 &&  curr->goban[h + 1][l - 1].cont == IA_SPOT && curr->goban[h + 2][l - 2].cont != PLAYER_SPOT))
      || (h < curr->h - 2 && l > 2 && curr->goban[h + 3][l - 3].cont != PLAYER_SPOT
	  && curr->goban[h + 2][l - 2].cont == IA_SPOT && curr->goban[h + 1][l - 1].cont == IA_SPOT
	  && (h > 0 && l < curr->l && curr->goban[h - 1][l + 1].cont != PLAYER_SPOT)))
    tokens += curr->h * 50;
  if ((h > 3 && l < curr->l - 3 && curr->goban[h - 4][l + 4].cont != IA_SPOT
       && curr->goban[h - 3][l + 3].cont == PLAYER_SPOT && curr->goban[h - 2][l + 2].cont == PLAYER_SPOT
       && curr->goban[h - 1][l + 1].cont == PLAYER_SPOT)
      || (h < curr->h - 3 && l > 3 && curr->goban[h + 4][l - 4].cont != IA_SPOT
	  && curr->goban[h + 3][l - 3].cont == PLAYER_SPOT && curr->goban[h + 2][l - 2].cont == PLAYER_SPOT
	  && curr->goban[h + 1][l - 1].cont == PLAYER_SPOT))
    tokens += curr->h * 40;
  if ((h > 2 && l < curr->h - 2 && curr->goban[h - 3][l + 3].cont == IA_SPOT
       && curr->goban[h - 2][l + 2].cont == PLAYER_SPOT && curr->goban[h - 1][l + 1].cont == PLAYER_SPOT)
      || (h < curr->h - 2 && l > 2 && curr->goban[h + 3][l - 3].cont == IA_SPOT
	  && curr->goban[h + 2][l - 2].cont == PLAYER_SPOT && curr->goban[h + 1][l - 1].cont == PLAYER_SPOT))
    {
      if (curr->player.player2_capture > curr->player.player1_capture)
	tokens += curr->h * 30;
      else
	tokens += curr->h * 20;
    }
  if ((h > 2 && l < curr->l - 2 && curr->goban[h - 3][l + 3].cont == PLAYER_SPOT
       && curr->goban[h - 2][l + 2].cont == IA_SPOT && curr->goban[h - 1][l + 1].cont == IA_SPOT)
      || (h < curr->h - 2 && l > 2 && curr->goban[h + 3][l - 3].cont == PLAYER_SPOT
	  && curr->goban[h + 2][l - 2].cont == IA_SPOT && curr->goban[h + 1][l - 1].cont == IA_SPOT))
    {
      if (curr->player.player2_capture > curr->player.player1_capture)
	tokens += curr->h * 20;
      else
	tokens += curr->h * 30;
    }
  return (tokens);
}

int		check_prio(t_game *curr, int h, int l)
{
  int		tokens = 0;

  tokens += check_prio_h(curr, h, l);
  tokens += check_prio_l(curr, h, l);
  tokens += check_prio_d1(curr, h, l);
  tokens += check_prio_d2(curr, h, l);
  return (tokens);
}

int		check_play_h(t_game *curr, int h, int l)
{
}

int		check_play_l(t_game *curr, int h, int l)
{
}

int		check_play_d1(t_game *curr, int h, int l)
{
}

int		check_play_d2(t_game *curr, int h, int l)
{
}

int		check_play(t_game *curr, int h, int l)
{
}

void		check_around(t_game *curr, int h, int l)
{
  curr->goban[h][l].ia_prio += check_prio(curr, h, l);
  curr->goban[h][l].ia_prio += check_play(curr, h, l);
}

void		ia_think(t_game *curr)
{
  for (int h = 0; h < curr->h; h++)
    for (int l = 0; l < curr->l; l++)
      if (curr->goban[h][l].cont == EMPTY_SPOT)
	check_around(curr, h, l);
}

int		ia_action(t_game *curr)
{
  int		prio = NO_PRIO;
  int		y_save = -1;
  int		x_save = -1;

  ia_think(curr);
  for (int h = 0; h < curr->h; h++)
    {
      for (int l = 0; l < curr->l; l++)
	{
	  if (curr->goban[h][l].ia_prio > prio
	      && curr->goban[h][l].cont == EMPTY_SPOT
	      && curr->goban[h][l].forbidden == false)
	    {
	      prio = curr->goban[h][l].ia_prio;
	      y_save = h;
	      x_save = l;
	    }
	}
    }
  if (prio != NO_PRIO)
    {
      if (y_save != -1 && x_save != -1)
	{
	  curr->cursy = y_save;
	  curr->cursx = x_save;
	  if (arbitrary(AUTHORITY, curr) != 0)
	    {
	      curr->goban[curr->cursy][curr->cursx].forbidden = true;
	      return (ia_action(curr));
	    }
	  curr->goban[curr->cursy][curr->cursx].cont = IA_SPOT;
	  curr->player.player2_tokens -= 1;
	}
      return (1);
    }
  return (0);
}

void		clean_prio(t_game *curr)
{
  for (int h = 0; h < curr->h; h++)
    for (int l = 0; l < curr->l; l++)
      curr->goban[h][l].ia_prio = NO_PRIO;
}

int		ia_play(t_game *curr)
{
  int		ret;

  reset_forbidden(curr);
  clean_prio(curr);
  ret = ia_action(curr);
  if (ret == 0)
    return (0);
  return (1);
}

void		ia_process(t_game *curr)
{
  if (ia_play(curr) == 0)
    ia_rand(curr);
}
