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

int		score_arbitrary(t_game *curr)
{
  if ((curr->player.state == true ? curr->player.player1_capture : curr->player.player2_capture)
      >= 10)
    return (WIN_GAME);
  if ((curr->player.state == true ? curr->player.player1_tokens : curr->player.player2_tokens)
      <= 0)
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
