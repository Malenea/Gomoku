#include	"gomoku.h"

int		end_game(t_game *curr, WINDOW *win)
{
  wresize(win, MENU_H, MENU_L);
  wclear(win);
  wprintw(win, "%sThank you for playing Gomoku.\n%sSee you soon.", TABS, TABS);
  wrefresh(win);
  wgetch(win);
  end_ncurses();
  free_goban(curr);
  return (0);
}

void		free_goban(t_game *curr)
{
  int		h;
  int		l;
  void		*ret;

  for (h = 0; h < curr->h; h++)
    free(curr->goban[h]);
  free(curr->goban);
}

void		end_ncurses()
{
  curs_set(1);
  endwin();
}
