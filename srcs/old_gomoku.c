#include	"gomoku.h"

/*
int		authorize_rule_of_two(t_game *curr)
{
  int		ret = 1;

  if (curr->cursx + 2 < curr->h && curr->cursx > 1)
    if (curr->goban[curr->cursy][curr->cursx + 1].cont == (curr->player.state == true ? 'o' : 'x')
	&& curr->goban[curr->cursy][curr->cursx + 2].cont == (curr->player.state == true? 'x' : 'o')
	&& curr->goban[curr->cursy][curr->cursx - 1].cont == (curr->player.state == true ? 'x' : 'o'))
      ret = RULE_OF_TWO;
  if (curr->cursx + 1 < curr->h && curr->cursx > 2)
    if (curr->goban[curr->cursy][curr->cursx - 1].cont == (curr->player.state == true ? 'o' : 'x')
	&& curr->goban[curr->cursy][curr->cursx - 2].cont == (curr->player.state == true? 'x' : 'o')
	&& curr->goban[curr->cursy][curr->cursx + 1].cont == (curr->player.state == true ? 'x' : 'o'))
      ret = RULE_OF_TWO;
  if (curr->cursy + 2 < curr->l && curr->cursy > 1)
    if (curr->goban[curr->cursy + 1][curr->cursx].cont == (curr->player.state == true ? 'o' : 'x')
	&& curr->goban[curr->cursy + 2][curr->cursx].cont == (curr->player.state == true? 'x' : 'o')
	&& curr->goban[curr->cursy - 1][curr->cursx].cont == (curr->player.state == true ? 'x' : 'o'))
      ret = RULE_OF_TWO;
  if (curr->cursy + 1 < curr->l && curr->cursy > 2)
    if (curr->goban[curr->cursy - 1][curr->cursx].cont == (curr->player.state == true ? 'o' : 'x')
	&& curr->goban[curr->cursy - 2][curr->cursx].cont == (curr->player.state == true? 'x' : 'o')
	&& curr->goban[curr->cursy + 1][curr->cursx].cont == (curr->player.state == true ? 'x' : 'o'))
      ret = RULE_OF_TWO;
  if (curr->cursy + 2 < curr->h && curr->cursx + 2 < curr->l && curr->cursy > 1 && curr->cursx > 1)
    if (curr->goban[curr->cursy - 1][curr->cursx - 1].cont == (curr->player.state == true ? 'x' : 'o')
	&& curr->goban[curr->cursy + 1][curr->cursx + 1].cont == (curr->player.state == true ? 'o' : 'x')
	&& curr->goban[curr->cursy + 2][curr->cursx + 2].cont == (curr->player.state == true ? 'x' : 'o'))
      ret = RULE_OF_TWO;
  if (curr->cursy > 2 && curr->cursx + 2 < curr->l && curr->cursy + 1 < curr->h && curr->cursx > 1)
    if (curr->goban[curr->cursy - 1][curr->cursx - 1].cont == (curr->player.state == true ? 'x' : 'o')
	&& curr->goban[curr->cursy + 1][curr->cursx + 1].cont == (curr->player.state == true ? 'o' : 'x')
	&& curr->goban[curr->cursy + 2][curr->cursx + 2].cont == (curr->player.state == true ? 'x' : 'o'))
      ret = RULE_OF_TWO;
  if (curr->cursy + 1 < curr->h && curr->cursx + 1 < curr->l && curr->cursy > 2 && curr->cursx > 2)
    if (curr->goban[curr->cursy + 1][curr->cursx + 1].cont == (curr->player.state == true ? 'x' : 'o')
	&& curr->goban[curr->cursy - 1][curr->cursx - 1].cont == (curr->player.state == true ? 'o' : 'x')
	&& curr->goban[curr->cursy - 2][curr->cursx - 2].cont == (curr->player.state == true ? 'x' : 'o'))
      ret = RULE_OF_TWO;
  if (curr->cursy > 1 && curr->cursx + 1 < curr->l && curr->cursy + 2 < curr->h && curr->cursx > 2)
    if (curr->goban[curr->cursy - 1][curr->cursx + 1].cont == (curr->player.state == true ? 'x' : 'o')
	&& curr->goban[curr->cursy + 1][curr->cursx - 1].cont == (curr->player.state == true ? 'o' : 'x')
	&& curr->goban[curr->cursy + 2][curr->cursx - 2].cont == (curr->player.state == true ? 'x' : 'o'))
      ret = RULE_OF_TWO;
  return (ret);
}
*/

void		end_board(t_game *curr)
{
  int		posh;
  int		pos = 0;

  if (curr->menu.is_title)
    {
      while (curr->menu.title[pos])
	{
	  free(curr->menu.title[pos]);
	  pos += 1;
	}
      free(curr->menu.title);
    }
  for (posh = 0; curr->board[posh]; posh++)
    if (curr->board[posh])
      free(curr->board[posh]);
  if (curr->board)
    free(curr->board);
  curs_set(1);
  endwin();
}

void		reset_player_tokens(t_game *curr)
{
  curr->player.player1_tokens = 60;
  curr->player.player2_tokens = 60;
  curr->player.player1_capture = 0;
  curr->player.player2_capture = 0;
}

void		init_game(t_game *curr)
{
  reset_player_tokens(curr);
  curr->player.first = true;
  curr->player.state = true;
  curr->state = 0;
  curr->h = 0;
  curr->l = 0;
  curr->cursy = 0;
  curr->cursx = 0;
  curr->options.vs_ia = false;
}

void		reset_board(t_game *curr)
{
  int		posh = 0;
  int		posl;

  while (curr->board[posh])
    {
      posl = 0;
      while (curr->board[posh][posl])
	{
	  curr->board[posh][posl] = '-';
	  posl += 1;
	}
      posh += 1;
    }
}

int		fill_board(t_game *curr)
{
  int		posh = 0;
  int		posl;

  if ((curr->board = malloc(sizeof(char *) * (curr->h + 1))) == NULL)
    return (-ENOMEM);
  while (posh < curr->h)
    {
      if ((curr->board[posh] = malloc(sizeof(char) * (curr->l + 1))) == NULL)
	return (-ENOMEM);
      posl = 0;
      while (posl < curr->l)
	{
	  curr->board[posh][posl] = '-';
	  posl += 1;
	}
      curr->board[posh][posl] = 0;
      posh += 1;
    }
  curr->board[posh] = NULL;
  return (1);
}

int		usage(void)
{
  MY_TRACE("This is the help");
  return (-1);
}

int		get_opt(int ac, char **av, t_game *curr, t_opt *opt)
{
  int		ret;
  int		trig;
  struct option	long_opts[] = {
    {"height",		required_argument,      NULL,                   'H'},
    {"lenght",		required_argument,      NULL,                   'L'},
    {"help",		no_argument,            0,                      'h'},
    {"verbose",		no_argument,            0,                      'v'},
    {0, 0, 0, 0}
  };
  int		optind = 0;

  optind = 0;
  while ((trig = getopt_long(ac, av, "A:L:hv", long_opts, &optind)) != -1)
    switch (trig)
      {
      case 'H':
        curr->h = atoi(optarg);
        break;
      case 'L':
        curr->l = atoi(optarg);
        break;
      case 'h':
        return (usage());
      case 'v':
        opt->is_verbose = true;
        break;
    }
  if (curr->h == 0)
    {
      if (opt->is_verbose)
	MY_WARN("You didn't specify height, default height is set to %d", DEFAULT_VALUE);
      curr->h = DEFAULT_VALUE;
    }
  if (curr->l == 0)
    {
      if (opt->is_verbose)
	MY_WARN("You didn't specify lenght, default lenght is set to %d", DEFAULT_VALUE);
      curr->l = DEFAULT_VALUE;
    }
  if (curr->h < DEFAULT_VALUE)
    {
      if (opt->is_verbose)
	MY_WARN("Specified height is too small, default height is set to %d", DEFAULT_VALUE);
      curr->h = DEFAULT_VALUE;
    }
  if (curr->l < DEFAULT_VALUE)
    {
      if (opt->is_verbose)
	MY_WARN("Specified lenght is too small, default lenght is set to %d", DEFAULT_VALUE);
      curr->l = DEFAULT_VALUE;
    }
  return (1);
}

void		init_opt(t_opt *opt)
{
  opt->is_verbose = false;
}

void		display_board(t_game *curr, WINDOW *win)
{
  unsigned int	posh;
  unsigned int	posl;

  posh = 0;
  while (curr->board[posh])
    {
      if (posh == curr->cursy)
	{
	  posl = 0;
	  while (curr->board[posh][posl])
	    {
	      if (posl == curr->cursx)
		{
		  wattron(win, COLOR_PAIR(1));
		  wprintw(win, "%c", curr->board[posh][posl]);
		  wattroff(win, COLOR_PAIR(1));
		}
	      else
		wprintw(win, "%c", curr->board[posh][posl]);
	      posl += 1;
	    }
	  wprintw(win, "\n");
	}
      else
	wprintw(win, "%s\n", curr->board[posh]);
      posh += 1;
    }
}

int		get_title(t_game *curr)
{
  char		*path = getenv("PWD");
  char		*title_path;
  int		fd;
  char		buffer[DEF_READ];
  unsigned int	h = 0;

  curr->menu.title = malloc(sizeof(char *) * TITLE_H);
  curr->menu.title[TITLE_H] = NULL;
  title_path = malloc(sizeof(char) * (strlen(path) + strlen(TITLE_PATH)));
  strcpy(title_path, path);
  strcat(title_path, TITLE_PATH);
  if ((fd = open(title_path, O_RDONLY)) < 0)
    {
      curr->menu.is_title = false;
      return (-EBADF);
    }
  while (read(fd, buffer, TITLE_L))
    {
      buffer[TITLE_L] = 0;
      curr->menu.title[h] = strdup(buffer);
      h += 1;
    }
  close(fd);
  if (title_path)
    free(title_path);
  curr->menu.is_title = true;
  return (0);
}

void		display_title(t_game *curr, WINDOW *win)
{
  int		pos = 0;

  if (curr->menu.is_title == true)
    {
      while (curr->menu.title[pos])
	{
	  wprintw(win, "%s", curr->menu.title[pos]);
	  pos += 1;
	}
    }
  wprintw(win, "\n\n");
}

void		print_options(t_game *curr, WINDOW *win)
{
  if (curr->options.state == 0)
    {
      wprintw(win, "%s", TABS);
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
      wprintw(win, "%sPlaying against IA:\t", TABS);
      wattron(win, COLOR_PAIR(curr->options.vs_ia == true ? 1 : 2));
      wprintw(win, "%s\n", curr->options.vs_ia == true ? "ON" : "OFF");
      wattroff(win, COLOR_PAIR(curr->options.vs_ia == true ? 1 : 2));
    }
  if (curr->options.state == 1)
    {
      wprintw(win, "%s", TABS);
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
      wprintw(win, "%sPlayer starting:\t", TABS);
      wattron(win, COLOR_PAIR(curr->player.first == true ? 1 : 2));
      wprintw(win, "%s\n", curr->player.first == true ? "Player 1" : "Player 2/IA");
      wattroff(win, COLOR_PAIR(curr->player.first == true ? 1 : 2));
    }
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

void		print_menu(t_game *curr, WINDOW *win)
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

void		reset_key(char *key)
{
  key[0] = 0;
  key[1] = 0;
  key[2] = 0;
  key[3] = 0;
}

void		display_options(t_game *curr, WINDOW *win)
{
  char		ch[4];
  int		ch_sum;

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

int		get_menu(t_game *curr, WINDOW *win)
{
  char		ch[4];
  int		ch_sum;

  wclear(win);
  display_title(curr, win);
  print_menu(curr, win);
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
      print_menu(curr, win);
      wrefresh(win);
      reset_key(ch);
    }
}

int		display_menu(t_game *curr, WINDOW *win)
{
  int		ret;

  curr->menu.state = 0;
  curr->options.state = 0;
  wresize(win, MENU_H, MENU_L);
  ret = get_menu(curr, win);
  if (ret == NEW_GAME)
    {
      curr->state = 1;
      return (NEW_GAME);
    }
  else if (ret == RESUME)
    return (RESUME);
  else if (ret == OPTIONS)
    {
      display_options(curr, win);
      return (display_menu(curr, win));
    }
  else if (ret == END_GAME)
    return (END_GAME);
  return (0);
}

int		check_tokens(t_game *curr)
{
  if (curr->player.state == true ? curr->player.player2_tokens == 0 : curr->player.player1_tokens == 0)
    return (DRAW_GAME);
  return (0);
}

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

void		capture_two(t_game *curr)
{
  //THREAD THIS
  if (curr->cursx + 2 < curr->l)
    {
      if (curr->board[curr->cursy][curr->cursx + 1] == (curr->player.state == true ? 'x' : 'o')
	  && curr->board[curr->cursy][curr->cursx + 2] == (curr->player.state == true ? 'x' : 'o')
	  && curr->board[curr->cursy][curr->cursx + 3] == (curr->player.state == true ? 'o' : 'x'))
	{
	  curr->board[curr->cursy][curr->cursx + 1] = '-';
	  curr->board[curr->cursy][curr->cursx + 2] = '-';
	  if (curr->player.state == true)
	    curr->player.player1_capture += 2;
	  else
	    curr->player.player2_capture += 2;
	}
    }
  if (curr->cursx > 2)
    {
      if (curr->board[curr->cursy][curr->cursx - 1] == (curr->player.state == true ? 'x' : 'o')
	  && curr->board[curr->cursy][curr->cursx - 2] == (curr->player.state == true ? 'x' : 'o')
	  && curr->board[curr->cursy][curr->cursx - 3] == (curr->player.state == true ? 'o' : 'x'))
	{
	  curr->board[curr->cursy][curr->cursx - 1] = '-';
	  curr->board[curr->cursy][curr->cursx - 2] = '-';
	  if (curr->player.state == true)
	    curr->player.player1_capture += 2;
	  else
	    curr->player.player2_capture += 2;
	}
    }
  if (curr->cursy + 2 < curr->h)
    {
      if (curr->board[curr->cursy + 1][curr->cursx] == (curr->player.state == true ? 'x' : 'o')
	  && curr->board[curr->cursy + 2][curr->cursx] == (curr->player.state == true ? 'x' : 'o')
	  && curr->board[curr->cursy + 3][curr->cursx] == (curr->player.state == true ? 'o' : 'x'))
	{
	  curr->board[curr->cursy + 1][curr->cursx] = '-';
	  curr->board[curr->cursy + 2][curr->cursx] = '-';
	  if (curr->player.state == true)
	    curr->player.player1_capture += 2;
	  else
	    curr->player.player2_capture += 2;
	}
    }
  if (curr->cursy > 2)
    {
      if (curr->board[curr->cursy - 1][curr->cursx] == (curr->player.state == true ? 'x' : 'o')
	  && curr->board[curr->cursy - 2][curr->cursx] == (curr->player.state == true ? 'x' : 'o')
	  && curr->board[curr->cursy - 3][curr->cursx] == (curr->player.state == true ? 'o' : 'x'))
	{
	  curr->board[curr->cursy - 1][curr->cursx] = '-';
	  curr->board[curr->cursy - 2][curr->cursx] = '-';
	  if (curr->player.state == true)
	    curr->player.player1_capture += 2;
	  else
	    curr->player.player2_capture += 2;
	}
    }
  if (curr->cursy + 2 < curr->h && curr->cursx + 2 < curr->l)
    {
      if (curr->board[curr->cursy + 1][curr->cursx + 1] == (curr->player.state == true ? 'x' : 'o')
	  && curr->board[curr->cursy + 2][curr->cursx + 2] == (curr->player.state == true ? 'x' : 'o')
	  && curr->board[curr->cursy + 3][curr->cursx + 3] == (curr->player.state == true ? 'o' : 'x'))
	{
	  curr->board[curr->cursy + 1][curr->cursx + 1] = '-';
	  curr->board[curr->cursy + 2][curr->cursx + 2] = '-';
	  if (curr->player.state == true)
	    curr->player.player1_capture += 2;
	  else
	    curr->player.player2_capture += 2;
	}
    }
  if (curr->cursy > 2 && curr->cursx > 2)
    {
      if (curr->board[curr->cursy - 1][curr->cursx - 1] == (curr->player.state == true ? 'x' : 'o')
	  && curr->board[curr->cursy - 2][curr->cursx - 2] == (curr->player.state == true ? 'x' : 'o')
	  && curr->board[curr->cursy - 3][curr->cursx - 3] == (curr->player.state == true ? 'o' : 'x'))
	{
	  curr->board[curr->cursy - 1][curr->cursx - 1] = '-';
	  curr->board[curr->cursy - 2][curr->cursx - 2] = '-';
	  if (curr->player.state == true)
	    curr->player.player1_capture += 2;
	  else
	    curr->player.player2_capture += 2;
	}
    }
  if (curr->cursy + 2 < curr->h && curr->cursx > 2)
    {
      if (curr->board[curr->cursy + 1][curr->cursx - 1] == (curr->player.state == true ? 'x' : 'o')
	  && curr->board[curr->cursy + 2][curr->cursx - 2] == (curr->player.state == true ? 'x' : 'o')
	  && curr->board[curr->cursy + 3][curr->cursx - 3] == (curr->player.state == true ? 'o' : 'x'))
	{
	  curr->board[curr->cursy + 1][curr->cursx - 1] = '-';
	  curr->board[curr->cursy + 2][curr->cursx - 2] = '-';
	  if (curr->player.state == true)
	    curr->player.player1_capture += 2;
	  else
	    curr->player.player2_capture += 2;
	}
    }
  if (curr->cursy > 2 && curr->cursx + 2 < curr->l)
    {
      if (curr->board[curr->cursy - 1][curr->cursx + 1] == (curr->player.state == true ? 'x' : 'o')
	  && curr->board[curr->cursy - 2][curr->cursx + 2] == (curr->player.state == true ? 'x' : 'o')
	  && curr->board[curr->cursy - 3][curr->cursx + 3] == (curr->player.state == true ? 'o' : 'x'))
	{
	  curr->board[curr->cursy - 1][curr->cursx + 1] = '-';
	  curr->board[curr->cursy - 2][curr->cursx + 2] = '-';
	  if (curr->player.state == true)
	    curr->player.player1_capture += 2;
	  else
	    curr->player.player2_capture += 2;
	}
    }
}

void		check_arbitrary(t_game *curr)
{
  rule_of_two(curr);
}

int		authorize_rule_of_two(t_game *curr)
{
  int		ret = 1;

  if (curr->cursx + 2 < curr->h && curr->cursx > 1)
    if (curr->board[curr->cursy][curr->cursx + 1] == (curr->player.state == true ? 'o' : 'x')
	&& curr->board[curr->cursy][curr->cursx + 2] == (curr->player.state == true? 'x' : 'o')
	&& curr->board[curr->cursy][curr->cursx - 1] == (curr->player.state == true ? 'x' : 'o'))
      ret = RULE_OF_TWO;
  if (curr->cursx + 1 < curr->h && curr->cursx > 2)
    if (curr->board[curr->cursy][curr->cursx - 1] == (curr->player.state == true ? 'o' : 'x')
	&& curr->board[curr->cursy][curr->cursx - 2] == (curr->player.state == true? 'x' : 'o')
	&& curr->board[curr->cursy][curr->cursx + 1] == (curr->player.state == true ? 'x' : 'o'))
      ret = RULE_OF_TWO;
  if (curr->cursy + 2 < curr->l && curr->cursy > 1)
    if (curr->board[curr->cursy + 1][curr->cursx] == (curr->player.state == true ? 'o' : 'x')
	&& curr->board[curr->cursy + 2][curr->cursx] == (curr->player.state == true? 'x' : 'o')
	&& curr->board[curr->cursy - 1][curr->cursx] == (curr->player.state == true ? 'x' : 'o'))
      ret = RULE_OF_TWO;
  if (curr->cursy + 1 < curr->l && curr->cursy > 2)
    if (curr->board[curr->cursy - 1][curr->cursx] == (curr->player.state == true ? 'o' : 'x')
	&& curr->board[curr->cursy - 2][curr->cursx] == (curr->player.state == true? 'x' : 'o')
	&& curr->board[curr->cursy + 1][curr->cursx] == (curr->player.state == true ? 'x' : 'o'))
      ret = RULE_OF_TWO;
  if (curr->cursy + 2 < curr->h && curr->cursx + 2 < curr->l && curr->cursy > 1 && curr->cursx > 1)
    if (curr->board[curr->cursy - 1][curr->cursx - 1] == (curr->player.state == true ? 'x' : 'o')
	&& curr->board[curr->cursy + 1][curr->cursx + 1] == (curr->player.state == true ? 'o' : 'x')
	&& curr->board[curr->cursy + 2][curr->cursx + 2] == (curr->player.state == true ? 'x' : 'o'))
      ret = RULE_OF_TWO;
  if (curr->cursy > 2 && curr->cursx + 2 < curr->l && curr->cursy + 1 < curr->h && curr->cursx > 1)
    if (curr->board[curr->cursy - 1][curr->cursx - 1] == (curr->player.state == true ? 'x' : 'o')
	&& curr->board[curr->cursy + 1][curr->cursx + 1] == (curr->player.state == true ? 'o' : 'x')
	&& curr->board[curr->cursy + 2][curr->cursx + 2] == (curr->player.state == true ? 'x' : 'o'))
      ret = RULE_OF_TWO;
  if (curr->cursy + 1 < curr->h && curr->cursx + 1 < curr->l && curr->cursy > 2 && curr->cursx > 2)
    if (curr->board[curr->cursy + 1][curr->cursx + 1] == (curr->player.state == true ? 'x' : 'o')
	&& curr->board[curr->cursy - 1][curr->cursx - 1] == (curr->player.state == true ? 'o' : 'x')
	&& curr->board[curr->cursy - 2][curr->cursx - 2] == (curr->player.state == true ? 'x' : 'o'))
      ret = RULE_OF_TWO;
  if (curr->cursy > 1 && curr->cursx + 1 < curr->l && curr->cursy + 2 < curr->h && curr->cursx > 2)
    if (curr->board[curr->cursy - 1][curr->cursx + 1] == (curr->player.state == true ? 'x' : 'o')
	&& curr->board[curr->cursy + 1][curr->cursx - 1] == (curr->player.state == true ? 'o' : 'x')
	&& curr->board[curr->cursy + 2][curr->cursx - 2] == (curr->player.state == true ? 'x' : 'o'))
      ret = RULE_OF_TWO;
  return (ret);
}

int		authorize_rule_of_three(t_game *curr)
{
  int		ret = 1;

  if (curr->cursx > 2 && curr->cursx + 2 < curr->l)
    {
      if (curr->board[curr->cursy][curr->cursx - 1] == (curr->player.state == true ? 'o' : 'x')
	  && curr->board[curr->cursy][curr->cursx - 2] == (curr->player.state == true ? 'o' : 'x')
	  && curr->board[curr->cursy][curr->cursx + 1] != (curr->player.state == true ? 'x' : 'o')
	  && ((curr->cursy > 2
	       && curr->board[curr->cursy - 1][curr->cursx + 1] == (curr->player.state == true ? 'o' : 'x')
	       && curr->board[curr->cursy - 2][curr->cursx + 2] == (curr->player.state == true ? 'o' : 'x'))
	      || (curr->cursy + 2 < curr->h
		  && curr->board[curr->cursy + 1][curr->cursx + 1] == (curr->player.state == true ? 'o' : 'x')
		  && curr->board[curr->cursy + 2][curr->cursx + 2] == (curr->player.state == true ? 'o' : 'x'))))
	ret = RULE_OF_THREE;
      if (curr->board[curr->cursy][curr->cursx + 1] == (curr->player.state == true ? 'o' : 'x')
	  && curr->board[curr->cursy][curr->cursx + 2] == (curr->player.state == true ? 'o' : 'x')
	  && curr->board[curr->cursy][curr->cursx - 1] != (curr->player.state == true ? 'x' : 'o')
	  && ((curr->cursy > 2
	       && curr->board[curr->cursy - 1][curr->cursx - 1] == (curr->player.state == true ? 'o' : 'x')
	       && curr->board[curr->cursy - 2][curr->cursx - 2] == (curr->player.state == true ? 'o' : 'x'))
	      || (curr->cursy + 2 < curr->h
		  && curr->board[curr->cursy + 1][curr->cursx - 1] == (curr->player.state == true ? 'o' : 'x')
		  && curr->board[curr->cursy + 2][curr->cursx - 2] == (curr->player.state == true ? 'o' : 'x'))))
	ret = RULE_OF_THREE;
    }
  if (curr->cursy > 2 && curr->cursy + 2 < curr->h)
    {
      if (curr->board[curr->cursy - 1][curr->cursx] == (curr->player.state == true ? 'o' : 'x')
	  && curr->board[curr->cursy - 2][curr->cursx] == (curr->player.state == true ? 'o' : 'x')
	  && curr->board[curr->cursy + 1][curr->cursx] != (curr->player.state == true ? 'x' : 'o')
	  && ((curr->cursx > 2
	       && curr->board[curr->cursy + 1][curr->cursx - 1] == (curr->player.state == true ? 'o' : 'x')
	       && curr->board[curr->cursy + 2][curr->cursx - 2] == (curr->player.state == true ? 'o' : 'x'))
	      || (curr->cursx + 2 < curr->l
		  && curr->board[curr->cursy + 1][curr->cursx + 1] == (curr->player.state == true ? 'o' : 'x')
		  && curr->board[curr->cursy + 2][curr->cursx + 2] == (curr->player.state == true ? 'o' : 'x'))))
	ret = RULE_OF_THREE;
      if (curr->board[curr->cursy + 1][curr->cursx] == (curr->player.state == true ? 'o' : 'x')
	  && curr->board[curr->cursy + 2][curr->cursx] == (curr->player.state == true ? 'o' : 'x')
	  && curr->board[curr->cursy - 1][curr->cursx] != (curr->player.state == true ? 'x' : 'o')
	  && ((curr->cursx > 2
	       && curr->board[curr->cursy - 1][curr->cursx - 1] == (curr->player.state == true ? 'o' : 'x')
	       && curr->board[curr->cursy - 2][curr->cursx - 2] == (curr->player.state == true ? 'o' : 'x'))
	      || (curr->cursy + 2 < curr->h
		  && curr->board[curr->cursy - 1][curr->cursx + 1] == (curr->player.state == true ? 'o' : 'x')
		  && curr->board[curr->cursy - 2][curr->cursx + 2] == (curr->player.state == true ? 'o' : 'x'))))
	ret = RULE_OF_THREE;
    }
  return (ret);
}

int		authorize_arbitrary(t_game *curr)
{
  int		ret;

  ret = authorize_rule_of_two(curr);
  if (ret == 1)
    ret = authorize_rule_of_three(curr);
  return (ret);
}

int		score_arbitrary(t_game *curr)
{
  unsigned int	posy = curr->cursy;
  unsigned int	posx = curr->cursx;
  unsigned int	res = 0;

  if ((curr->player.state == true ? curr->player.player1_capture : curr->player.player2_capture) == 10)
    return (WIN_GAME);
  while (posx > 0 && curr->board[posy][posx] == (curr->player.state == true ? 'o' : 'x'))
    posx -= 1;
  if (posx > 0 && posx < curr->l)
    posx += 1;
  while (posx < curr->l && curr->board[posy][posx] == (curr->player.state == true ? 'o' : 'x'))
    {
      res += 1;
      posx += 1;
    }
  if (res == 5)
    return (WIN_GAME);
  posy = curr->cursy;
  posx = curr->cursx;
  res = 0;
  while (posy > 0 && curr->board[posy][posx] == (curr->player.state == true ? 'o' : 'x'))
    posy -= 1;
  if (posy > 0 && posy < curr->h)
    posy += 1;
  while (posy < curr->h && curr->board[posy][posx] == (curr->player.state == true ? 'o' : 'x'))
    {
      res += 1;
      posy += 1;
    }
  if (res == 5)
    return (WIN_GAME);
  posy = curr->cursy;
  posx = curr->cursx;
  res = 0;
  while (posy > 0 && posx > 0 && curr->board[posy][posx] == (curr->player.state == true ? 'o' : 'x'))
    {
      posy -= 1;
      posx -= 1;
    }
  if (posy > 0 && posx > 0 && posy < curr->h && posx < curr->l)
    {
      posy += 1;
      posx += 1;
    }
  while (posy < curr->h && posx < curr->h && curr->board[posy][posx] == (curr->player.state == true ? 'o' : 'x'))
    {
      res += 1;
      posy += 1;
      posx += 1;
    }
  if (res == 5)
    return (WIN_GAME);
  posy = curr->cursy;
  posx = curr->cursx;
  res = 0;
  while (posy < curr->h && posx > 0 && curr->board[posy][posx] == (curr->player.state == true ? 'o' : 'x'))
    {
      posy += 1;
      posx -= 1;
    }
  if (posy > 0 && posx > 0 && posx < curr->l)
    {
      posy -= 1;
      posx += 1;
    }
  while (posy > 0 && posx < curr->l && posy < curr->h && curr->board[posy][posx] == (curr->player.state == true ? 'o' : 'x'))
    {
      res += 1;
      posy -= 1;
      posx += 1;
    }
  if (posy == 0 && curr->board[posy][posx] == (curr->player.state == true ? 'o' : 'x'))
    res += 1;
  if (res == 5)
    return (WIN_GAME);
  return (0);
}

int		player_cmds(t_game *curr, WINDOW *win)
{
  char		ch[4];
  int		ch_sum;
  int		ret;
  int		ret2 = 1;

  reset_key(ch);
  while (read(0, ch, 4))
    {
      ch_sum = ch[0] + ch[1] + ch[2] + ch[3];
      if (ch_sum == SPACE_KEY && curr->board[curr->cursy][curr->cursx] == '-' && (ret2 = authorize_arbitrary(curr) > 0))
	{
	  if (curr->options.vs_ia == false)
	    {
	      (curr->board[curr->cursy][curr->cursx] = (curr->player.state == true ? 'o' : 'x'));
	      curr->player.player1_tokens = (curr->player.state == true ? curr->player.player1_tokens - 1 : curr->player.player1_tokens);
	      curr->player.player2_tokens = (curr->player.state == false ? curr->player.player2_tokens - 1 : curr->player.player2_tokens);
	    }
	  else
	    {
	      curr->board[curr->cursy][curr->cursx] = 'o';
	      curr->player.player1_tokens -= 1;
	    }
	  check_arbitrary(curr);
	  if (score_arbitrary(curr) == WIN_GAME)
	    {
	      game_results(win, (curr->player.state == true ? 1 : 2));
	      curr->state = 0;
	      ret = display_menu(curr, win);
	      if (ret == NEW_GAME)
		{
		  reset_player_tokens(curr);
		  reset_board(curr);
		  curr->player.state = (curr->player.first == true ? true : false);
		  curr->cursy = 0;
		  curr->cursx = 0;
		}
	      else if (ret == END_GAME)
		return (END_GAME);
	    }
	  ret = check_tokens(curr);
	  if (ret == DRAW_GAME)
	    {
	      game_results(win, 0);
	      curr->state = 0;
	      ret = display_menu(curr, win);
	      if (ret == NEW_GAME)
		{
		  reset_player_tokens(curr);
		  reset_board(curr);
		  curr->player.state = (curr->player.first == true ? true : false);
		  curr->cursy = 0;
		  curr->cursx = 0;
		}
	      else if (ret == END_GAME)
		return (END_GAME);
	    }
	  else
	    curr->player.state = (curr->player.state == true ? false : true);
	  wclear(win);
	  display_board(curr, win);
	  wattron(win, COLOR_PAIR(curr->player.state == true ? 3 : 4));
	  wprintw(win, "Player %d's turn\n", (curr->player.state == true ? 1 : 2));
	  wprintw(win, "Tokens left: %d\n", (curr->player.state == true ? curr->player.player1_tokens : curr->player.player2_tokens));
	  wprintw(win, "Tokens own: %d\n", (curr->player.state == true ? curr->player.player1_capture : curr->player.player2_capture));
	  wattroff(win, COLOR_PAIR(curr->player.state == true ? 3 : 4));
	  wattroff(win, COLOR_PAIR(curr->player.state == true ? 3 : 4));
	  wrefresh(win);
	  return (0);
	}
      else
	{
	  if (ch_sum == ARROW_UP_KEY)
	    curr->cursy = (curr->cursy == 0 ? curr->h - 1 : curr->cursy - 1);
	  else if (ch_sum == ARROW_DOWN_KEY)
	    curr->cursy = (curr->cursy == curr->h - 1 ? 0 : curr->cursy + 1);
	  else if (ch_sum == ARROW_RIGHT_KEY)
	    curr->cursx = (curr->cursx == curr->l - 1 ? 0 : curr->cursx + 1);
	  else if (ch_sum == ARROW_LEFT_KEY)
	    curr->cursx = (curr->cursx == 0 ? curr->l - 1 : curr->cursx - 1);
	  else if (ch_sum == ESC_KEY)
	    {
	      ret = display_menu(curr, win);
	      wresize(win, curr->h + 5, curr->l + 1);
	      if (ret == NEW_GAME)
		{
		  reset_player_tokens(curr);
		  reset_board(curr);
		  curr->player.state = (curr->player.first == true ? true : false);
		  curr->cursy = 0;
		  curr->cursx = 0;
		}
	      else if (ret == END_GAME)
		return (END_GAME);
	    }
	  wclear(win);
	  display_board(curr, win);
	  if (ret2 == 1)
	    {
	      wattron(win, COLOR_PAIR(curr->player.state == true ? 3 : 4));
	      wprintw(win, "Player %d's turn\n", (curr->player.state == true ? 1 : 2));
	      wprintw(win, "Tokens left: %d\n", (curr->player.state == true ? curr->player.player1_tokens : curr->player.player2_tokens));
	      wprintw(win, "Tokens own: %d\n", (curr->player.state == true ? curr->player.player1_capture : curr->player.player2_capture));
	      wattroff(win, COLOR_PAIR(curr->player.state == true ? 3 : 4));
	    }
	  else
	    {
	      wattron(win, COLOR_PAIR(curr->player.state == true ? 3 : 4));
	      wprintw(win, "Bad move\n(%s)", ret2 == RULE_OF_TWO ? "rule of two" : "rule of three");
	      wattroff(win, COLOR_PAIR(curr->player.state == true ? 3 : 4));
	    }
	  ret2 = 1;
	  wrefresh(win);
	}
      reset_key(ch);
    }
  return (0);
}

void		ia_cmds(t_game *curr, WINDOW *win)
{
  wclear(win);
  wprintw(win, "IA is playing.");
  wrefresh(win);
  sleep(2);
  wclear(win);
  display_board(curr, win);
  wrefresh(win);
  curr->player.state = true;
}

int		end_game(WINDOW *win)
{
  wresize(win, MENU_H, MENU_L);
  wclear(win);
  wprintw(win, "%sThank you for playing Gomoku.\n%sSee you soon.", TABS, TABS);
  wrefresh(win);
  wgetch(win);
  return (0);
}

int		manage_game(t_game *curr)
{
  WINDOW	*win;
  int		ret;

  win = newwin(MENU_H, MENU_L, 1, 1);
  refresh();
  ret = display_menu(curr, win);
  if (ret == END_GAME)
    return (end_game(win));
  wresize(win, curr->h + 5, curr->l + 1);
  display_board(curr, win);
  wattron(win, COLOR_PAIR(curr->player.state == true ? 3 : 4));
  wprintw(win, "Player %d's turn\n", (curr->player.state == true ? 1 : 2));
  wprintw(win, "Tokens left: %d\n", (curr->player.state == true ? curr->player.player1_tokens : curr->player.player2_tokens));
  wprintw(win, "Tokens own: %d", (curr->player.state == true ? curr->player.player1_capture : curr->player.player2_capture));
  wattroff(win, COLOR_PAIR(curr->player.state == true ? 3 : 4));
  wrefresh(win);
  while (1)
    {
      if (curr->options.vs_ia == false || (curr->options.vs_ia == true && curr->player.state == true))
	{
	  ret = player_cmds(curr, win);
	  if (ret == END_GAME)
	    return (end_game(win));
	}
      else if (curr->options.vs_ia == true && curr->player.state == false)
	ia_cmds(curr, win);
      else
	return (MY_ERROR(-EINVAL, "Something went wrong during the game, exiting now."));
    }
  return (0);
}

int		main(int ac, char **av)
{
  int		ret;
  t_game	curr;
  t_opt		opt;

  get_title(&curr);
  init_game(&curr);
  init_opt(&opt);
  if ((get_opt(ac, av, &curr, &opt)) != -1)
    {
      initscr();
      curs_set(0);
      start_color();
      init_pair(1, COLOR_WHITE, COLOR_GREEN);
      init_pair(2, COLOR_WHITE, COLOR_RED);
      init_pair(3, COLOR_BLUE, COLOR_BLACK);
      init_pair(4, COLOR_RED, COLOR_BLACK);
      if ((ret = fill_board(&curr)) < 0)
	return (MY_ERROR(ret, "Board malloc failed"));
      manage_game(&curr);
      end_board(&curr);
    }
  return (0);
}
