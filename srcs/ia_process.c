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

void		ia_think(t_game *curr)
{
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
	  if (curr->goban[h][l].ia_prio > prio)
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
	}
      return (1);
    }
  return (0);
}

int		ia_play(t_game *curr)
{
  int		ret;

  reset_forbidden(curr);
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
