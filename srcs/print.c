#include	"gomoku.h"

void		root_menu(t_game *curr, WINDOW *win)
{
  if (curr->state == 1 && curr->menu.state == 0)
    {
      wprintw(win, "%s", TABS);
      wattron(win, COLOR_PAIR(1));
      wprintw(win, "Resume\n");
      wattroff(win, COLOR_PAIR(1));
    }
  else if (curr->state == 1)
    wprintw(win, "%sResume\n", TABS);
  if (curr->menu.state == (curr->state == 1 ? 1 : 0))
    {
      wprintw(win, "%s", TABS);
      wattron(win, COLOR_PAIR(1));
      wprintw(win, "New Game\n");
      wattroff(win, COLOR_PAIR(1));
    }
  else
    wprintw(win, "%sNew Game\n", TABS);
  if (curr->menu.state == (curr->state == 1 ? 2 : 1))
    {
      wprintw(win, "%s", TABS);
      wattron(win, COLOR_PAIR(1));
      wprintw(win, "Options\n");
      wattroff(win, COLOR_PAIR(1));
    }
  else
    wprintw(win, "%sOptions\n", TABS);
  if (curr->menu.state == (curr->state == 1 ? 3 : 2))
    {
      wprintw(win, "%s", TABS);
      wattron(win, COLOR_PAIR(1));
      wprintw(win, "Exit\n");
      wattroff(win, COLOR_PAIR(1));
    }
  else
    wprintw(win, "%sExit\n", TABS);
}

int		print_menu(t_game *curr, WINDOW *win)
{
  char		ch[4];
  int		ch_sum;

  wclear(win);
  curr->menu.state = 0;
  wresize(win, MENU_H, MENU_L);
  display_title(curr, win);
  root_menu(curr, win);
  wrefresh(win);
  reset_key(ch);
  while (read(0, ch, 4))
    {
      ch_sum = ch[0] + ch[1] + ch[2] + ch[3];
      if (ch_sum == SPACE_KEY)
	{
	  wclear(win);
	  wrefresh(win);
	  if (curr->state == 0)
	    return ((curr->menu.state == 0 ? NEW_GAME : (curr->menu.state == 1 ? OPTIONS : END_GAME)));
	  else if (curr->state == 1)
	    return ((curr->menu.state == 0 ? RESUME : (curr->menu.state == 1 ? NEW_GAME : (curr->menu.state == 2 ? OPTIONS : END_GAME))));
	}
      else if (ch_sum == ARROW_UP_KEY)
	curr->menu.state = (curr->menu.state == 0 ? (curr->state == 1 ? 3 : 2) : curr->menu.state - 1);
      else if (ch_sum == ARROW_DOWN_KEY)
	curr->menu.state = (curr->menu.state == (curr->state == 1 ? 3 : 2) ? 0 : curr->menu.state + 1);
      wclear(win);
      display_title(curr, win);
      root_menu(curr, win);
      wrefresh(win);
      reset_key(ch);
    }
  return (0);
}

void		print_goban(t_game *curr, WINDOW *win)
{
  int		h;
  int		l;

  for (h = 0; h < curr->h; h++)
    {
      for (l = 0; l < curr->l; l++)
	{
	  if (curr->cursy == h && curr->cursx == l)
	    {
	      wattron(win, COLOR_PAIR(1));
	      wprintw(win, "%c", curr->goban[h][l].cont);
	      wattroff(win, COLOR_PAIR(1));
	    }
	  else
	    wprintw(win, "%c", curr->goban[h][l].cont);
	}
      wprintw(win, "\n");
    }
}

void		print_infos(t_game *curr, WINDOW *win)
{
  wattron(win, COLOR_PAIR(curr->player.state == true ? 3 : 4));
  wprintw(win, "Player %d's turn\n", (curr->player.state == true ? 1 : 2));
  wprintw(win, "Tokens left: %d\n", (curr->player.state == true ? curr->player.player1_tokens : curr->player.player2_tokens));
  wprintw(win, "Tokens own: %d", (curr->player.state == true ? curr->player.player1_capture : curr->player.player2_capture));
  wattroff(win, COLOR_PAIR(curr->player.state == true ? 3 : 4));
}
