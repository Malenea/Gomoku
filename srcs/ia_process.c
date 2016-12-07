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
  return (0);
}

int		ia_read_goban(t_game *curr)
{
  int		prio = NO_PRIO;

  for (int h = 0; h < curr->h; h++)
    for (int l = 0; l < curr->l; l++)
      {
	if (curr->goban[h][l].ia_prio > prio)
	  prio = curr->goban[h][l].ia_prio;
      }
  if (prio != NO_PRIO)
    return (1);
  return (0);
}

int		ia_play(t_game *curr)
{
  int		ret;

  if (ia_read_goban(curr) == 0)
    return (0);
  while ((ret = arbitrary(AUTHORITY, curr)) != 0)
    {
      // here
    }
  return (1);
}

void		ia_process(t_game *curr)
{
  if (ia_play(curr) == 0)
    ia_rand(curr);
}
