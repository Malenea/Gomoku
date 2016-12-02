#include	"gomoku.h"

int		goban_reader(t_game *curr)
{
  int		prio = NO_PRIO;

  for (int h = 0; h < curr->h; h++)
    {
      for (int l = 0; l < curr->l; l++)
	{
	  if (curr->goban[h][l].prio > prio && curr->goban[h][l].cont == EMPTY_SPOT)
	    {
	      prio = curr->goban[h][l].prio;
	      curr->cursy = h;
	      curr->cursx = l;
	    }
	}
    }
  if (prio != NO_PRIO)
    return (1);
  return (0);
}
