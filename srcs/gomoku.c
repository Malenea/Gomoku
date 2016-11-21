#include	"gomoku.h"

int		game_loop(t_game *curr, WINDOW *win)
{
  int		ret;

  wresize(win, curr->h + 6, curr->l + 1);
  print_goban(curr, win);
  print_infos(curr, win);
  wrefresh(win);
  curr->state = 1;
  while (1)
    {
      if (curr->options.vs_ia == false
	  || (curr->options.vs_ia == true && curr->player.state == true))
	{
	  ret = player_cmds(curr, win);
	  if (ret == END_GAME)
	    return (end_game(curr, win));
	}
      else if (curr->options.vs_ia == true && curr->player.state == false)
	{
	  ia_cmds(curr, win);
	}
      else
	return (MY_ERROR(-EINVAL, "Something went wrong during the game, exiting now."));
    }
  return (0);
}

int		main(int ac, char **av)
{
  WINDOW	*win;
  t_game	curr;
  int		ret = 0;

  init_game(&curr);
  ret = init_goban(&curr);
  if (ret < 0)
    return (-ENOMEM);
  init_ncurses(win);
  win = newwin(MENU_H, MENU_L, 1, 1);
  refresh();

  ret = prompt_menu(&curr, win);
  if (ret == END_GAME)
    return (end_game(&curr, win));
  game_loop(&curr, win);
  return (0);
}
