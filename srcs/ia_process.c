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

int		ia_think(t_game *curr)
{
  return (1);
}

int		ia_play(t_game *curr)
{
  int		ret;

  reset_forbidden(curr);
  while ((arbitrary(AUTHORITY, curr)) != 0)
    ret = ia_think(curr);
  if (ret == 1)
    return (0);
  return (1);
}

void		ia_process(t_game *curr)
{
  if (ia_play(curr) == 0)
    ia_rand(curr);
}
