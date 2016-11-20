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

void		print_options(t_game *curr, WINDOW *win)
{
  wprintw(win, "%sPlayer options :\n\n", TABS);
  if (curr->options.state == 0)
    {
      wprintw(win, "%s ", TABS);
      wattron(win, COLOR_PAIR(1));
      wprintw(win, "Playing against IA:");
      wattroff(win, COLOR_PAIR(1));
      wprintw(win, "\t");
      wattron(win, COLOR_PAIR(curr->options.vs_ia == true ? 1 : 2));
      wprintw(win, "%s\n", curr->options.vs_ia == true ? "ON" : "OFF");
      wattroff(win, COLOR_PAIR(curr->options.vs_ia == true ? 1 : 2));
    }
  else
    {
      wprintw(win, "%s Playing against IA:\t", TABS);
      wattron(win, COLOR_PAIR(curr->options.vs_ia == true ? 1 : 2));
      wprintw(win, "%s\n", curr->options.vs_ia == true ? "ON" : "OFF");
      wattroff(win, COLOR_PAIR(curr->options.vs_ia == true ? 1 : 2));
    }
  if (curr->options.state == 1)
    {
      wprintw(win, "%s ", TABS);
      wattron(win, COLOR_PAIR(1));
      wprintw(win, "Player starting:");
      wattroff(win, COLOR_PAIR(1));
      wprintw(win, "\t");
      wattron(win, COLOR_PAIR(curr->player.first == true ? 1 : 2));
      wprintw(win, "%s\n", curr->player.first == true ? "Player 1" : "Player 2/IA");
      wattroff(win, COLOR_PAIR(curr->player.first == true ? 1 : 2));
    }
  else
    {
      wprintw(win, "%s Player starting:\t", TABS);
      wattron(win, COLOR_PAIR(curr->player.first == true ? 1 : 2));
      wprintw(win, "%s\n", curr->player.first == true ? "Player 1" : "Player 2/IA");
      wattroff(win, COLOR_PAIR(curr->player.first == true ? 1 : 2));
    }
  wprintw(win, "\n\n%sRules :\n\n", TABS);
  if (curr->options.state == 2)
    {
      wprintw(win, "%s ", TABS);
      wattron(win, COLOR_PAIR(1));
      wprintw(win, "Enable rule of three:");
      wattroff(win, COLOR_PAIR(1));
      wprintw(win, "\t");
      wattron(win, COLOR_PAIR(curr->rules.r3 == true ? 1 : 2));
      wprintw(win, "%s\n", curr->rules.r3 == true ? "Yes" : "No");
      wattroff(win, COLOR_PAIR(curr->rules.r3 == true ? 1 : 2));
    }
  else
    {
      wprintw(win, "%s Enable rule of three:\t", TABS);
      wattron(win, COLOR_PAIR(curr->rules.r3 == true ? 1 : 2));
      wprintw(win, "%s\n", curr->rules.r3 == true ? "Yes" : "No");
      wattroff(win, COLOR_PAIR(curr->rules.r3 == true ? 1 : 2));
    }
  if (curr->options.state == 3)
    {
      wprintw(win, "%s ", TABS);
      wattron(win, COLOR_PAIR(1));
      wprintw(win, "Enable capture of two:");
      wattroff(win, COLOR_PAIR(1));
      wprintw(win, "\t");
      wattron(win, COLOR_PAIR(curr->rules.c2 == true ? 1 : 2));
      wprintw(win, "%s\n", curr->rules.c2 == true ? "Yes" : "No");
      wattroff(win, COLOR_PAIR(curr->rules.c2 == true ? 1 : 2));
    }
  else
    {
      wprintw(win, "%s Enable capture of two:\t", TABS);
      wattron(win, COLOR_PAIR(curr->rules.c2 == true ? 1 : 2));
      wprintw(win, "%s\n", curr->rules.c2 == true ? "Yes" : "No");
      wattroff(win, COLOR_PAIR(curr->rules.c2 == true ? 1 : 2));
    }
  wprintw(win, "\n");
  if (curr->options.state == OPTIONS_NB)
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
  wprintw(win, "Tokens own: %d\n", (curr->player.state == true ? curr->player.player1_capture : curr->player.player2_capture));
  wprintw(win, "Y : %d / X : %d", curr->cursy + 1, curr->cursx + 1);
  wattroff(win, COLOR_PAIR(curr->player.state == true ? 3 : 4));
}

void		prompt_options(t_game *curr, WINDOW *win)
{
  char		ch[4];
  int		ch_sum;

  curr->options.state = 0;
  display_title(curr, win);
  print_options(curr, win);
  wrefresh(win);
  reset_key(ch);
  while (read(0, ch, 4))
    {
      ch_sum = ch[0] + ch[1] + ch[2] + ch[3];
      if (ch_sum == SPACE_KEY)
	{
	  if (curr->options.state == 0)
	    curr->options.vs_ia = (curr->options.vs_ia == true ? false : true);
	  else if (curr->options.state == 1)
	    curr->player.first = (curr->player.first == true ? false : true);
	  else if (curr->options.state == 2)
	    curr->rules.r3 = (curr->rules.r3 == true ? false : true);
	  else if (curr->options.state == 3)
	    curr->rules.c2 = (curr->rules.c2 == true ? false : true);
	  else
	    {
	      wclear(win);
	      wrefresh(win);
	      return ;
	    }
	}
      else if (ch_sum == ARROW_UP_KEY)
	curr->options.state = (curr->options.state == 0 ? OPTIONS_NB : curr->options.state - 1);
      else if (ch_sum == ARROW_DOWN_KEY)
	curr->options.state = (curr->options.state == OPTIONS_NB ? 0 : curr->options.state + 1);
      wclear(win);
      display_title(curr, win);
      print_options(curr, win);
      wrefresh(win);
      reset_key(ch);
    }
}

int		prompt_menu(t_game *curr, WINDOW *win)
{
  int		ret;

  ret = print_menu(curr, win);
  if (ret == NEW_GAME)
    new_game(curr, win);
  else if (ret == OPTIONS)
    {
      prompt_options(curr, win);
      return (prompt_menu(curr, win));
    }
  else if (ret == END_GAME)
    return (END_GAME);
  return (0);
}
