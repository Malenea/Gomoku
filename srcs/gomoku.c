#include	<sys/types.h>
#include	<sys/stat.h>
#include	<fcntl.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<unistd.h>
#include	<stdbool.h>
#include	<errno.h>
#include	<getopt.h>
#include	<ncurses.h>
#include	"gomoku.h"

void		end_board(t_game *curr)
{
  int		posh;
  int		pos = 0;

  if (curr->is_title)
    {
      while (curr->title[pos])
	{
	  free(curr->title[pos]);
	  pos += 1;
	}
      free(curr->title);
    }
  for (posh = 0; curr->board[posh]; posh++)
    if (curr->board[posh])
      free(curr->board[posh]);
  if (curr->board)
    free(curr->board);
  curs_set(1);
  endwin();
}

void		init_game(t_game *curr)
{
  curr->pstate = true;
  curr->h = 0;
  curr->l = 0;
  curr->cursy = 0;
  curr->cursx = 0;
  curr->options.vs_ia = true;
}

int		fill_board(t_game *curr)
{
  int		posh;
  int		posl;

  posh = 0;
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
  while (posh < curr->h)
    {
      if (posh == curr->cursy)
	{
	  posl = 0;
	  while (posl < curr->l)
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
  char		**title;
  unsigned int	h = 0;

  curr->title = malloc(sizeof(char *) * TITLE_H);
  curr->title[TITLE_H] = NULL;
  title_path = malloc(sizeof(char) * (strlen(path) + strlen(TITLE_PATH)));
  strcpy(title_path, path);
  strcat(title_path, TITLE_PATH);
  if ((fd = open(title_path, O_RDONLY)) < 0)
    {
      curr->is_title = false;
      return (-EBADF);
    }
  while (read(fd, buffer, TITLE_L))
    {
      buffer[TITLE_L] = 0;
      curr->title[h] = strdup(buffer);
      h += 1;
    }
  close(fd);
  if (title_path)
    free(title_path);
  curr->is_title = true;
  return (0);
}

void		display_title(t_game *curr, WINDOW *win)
{
  int		pos = 0;

  if (curr->is_title == true)
    {
      while (curr->title[pos])
	{
	  wprintw(win, "%s", curr->title[pos]);
	  pos += 1;
	}
    }
  wprintw(win, "\n\n");
}

void		print_menu(t_game *curr, WINDOW *win)
{
  if (curr->mstate == 0)
    {
      wprintw(win, "%s", TABS);
      wattron(win, COLOR_PAIR(1));
      wprintw(win, "New Game\n");
      wattroff(win, COLOR_PAIR(1));
    }
  else
    wprintw(win, "%sNew Game\n", TABS);
  if (curr->mstate == 1)
    {
      wprintw(win, "%s", TABS);
      wattron(win, COLOR_PAIR(1));
      wprintw(win, "Options\n");
      wattroff(win, COLOR_PAIR(1));
    }
  else
    wprintw(win, "%sOptions\n", TABS);
  if (curr->mstate == 2)
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

int		get_menu(t_game *curr, WINDOW *win)
{
  char		ch[4];
  int		ch_sum;

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
	  return ((curr->mstate == 0 ? NEW_GAME : (curr->mstate == 1 ? OPTIONS : END_GAME)));
	}
      else if (ch_sum == ARROW_UP_KEY)
	curr->mstate = (curr->mstate == 0 ? 2 : curr->mstate - 1);
      else if (ch_sum == ARROW_DOWN_KEY)
	curr->mstate = (curr->mstate == 2 ? 0 : curr->mstate + 1);
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

  curr->mstate = 0;
  ret = get_menu(curr, win);
  if (ret == NEW_GAME)
    return (NEW_GAME);
  else if (ret == OPTIONS)
    return (OPTIONS);
  else if (ret == END_GAME)
    return (END_GAME);
  return (0);
}

void		player_cmds(t_game *curr, WINDOW *win)
{
  char		ch[4];
  int		ch_sum;

  reset_key(ch);
  while (read(0, ch, 4))
    {
      ch_sum = ch[0] + ch[1] + ch[2] + ch[3];
      if (ch_sum == SPACE_KEY && curr->board[curr->cursy][curr->cursx] == '-')
	{
	  if (curr->options.vs_ia == false)
	    (curr->board[curr->cursy][curr->cursx] = (curr->pstate == true ? 'o' : 'x'));
	  else
	    curr->board[curr->cursy][curr->cursx] = 'o';
	  //CHECK_ARBITRARY
	  wclear(win);
	  display_board(curr, win);
	  wrefresh(win);
	  curr->pstate = (curr->pstate == true ? false : true);
	  return ;
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
	  wclear(win);
	  display_board(curr, win);
	  wrefresh(win);
	}
      reset_key(ch);
    }
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
  curr->pstate = true;
}

int		manage_game(t_game *curr)
{
  WINDOW	*win;
  int		ret;

  win = newwin(MENU_H, MENU_L, 1, 1);
  refresh();
  ret = display_menu(curr, win);
  if (ret == END_GAME)
    {
      wclear(win);
      wprintw(win, "%sThank you for playing Gomoku.\n%sSee you soon.", TABS, TABS);
      wrefresh(win);
      wgetch(win);
      return (0);
    }
  wresize(win, curr->h * 2, curr->l);
  display_board(curr, win);
  wrefresh(win);
  while (1)
    {
      if (curr->options.vs_ia == false || (curr->options.vs_ia == true && curr->pstate == true))
	player_cmds(curr, win);
      else if (curr->options.vs_ia == true && curr->pstate == false)
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
      if ((ret = fill_board(&curr)) < 0)
	return (MY_ERROR(ret, "Board malloc failed"));
      //
      manage_game(&curr);
      end_board(&curr);
      //
    }
  return (0);
}
