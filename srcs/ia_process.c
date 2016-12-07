#include	"gomoku.h"

void		ia_rand(t_game *curr)
{
  time_t	seed;

  time(&seed);
  srand(seed);
  curr->cursy = rand() % curr->h;
  curr->cursx = rand() % curr->l;
}

int		ia_play(t_game *curr)
{
  return (0);
}

int		ia_process(t_game *curr)
{
  if (ia_play(curr) == 0)
    ia_rand(curr);
  return (0);
}
