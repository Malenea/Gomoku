#include	"gomoku.h"

int		check_cond_w5(t_game *curr, WINDOW *win)
{
  int		ret;
  int		ret2 = 0;

  if ((curr->player.state == true ? curr->player.p1_w5_cond : curr->player.p2_w5_cond) == true)
    {
      if (count_h(curr, (curr->player.state == true ? curr->player.player1_y_win : curr->player.player2_y_win),
		  (curr->player.state == true ? curr->player.player1_x_win : curr->player.player2_x_win),
		  (curr->player.state == true ? true : false)) == 1)
	{
	  game_results(win, (curr->player.state == true ? 1 : 2));
	  curr->state = 0;
	  ret = prompt_menu(curr, win);
	  if (ret == END_GAME)
	    return (END_GAME);
	}
      if (count_l(curr, (curr->player.state == true ? curr->player.player1_y_win : curr->player.player2_y_win),
		  (curr->player.state == true ? curr->player.player1_x_win : curr->player.player2_x_win),
		  (curr->player.state == true ? true : false)) == 1)
	{
	  game_results(win, (curr->player.state == true ? 1 : 2));
	  curr->state = 0;
	  ret = prompt_menu(curr, win);
	  if (ret == END_GAME)
	    return (END_GAME);
	}
      if (count_d1(curr, (curr->player.state == true ? curr->player.player1_y_win : curr->player.player2_y_win),
		  (curr->player.state == true ? curr->player.player1_x_win : curr->player.player2_x_win),
		  (curr->player.state == true ? true : false)) == 1)
	{
	  game_results(win, (curr->player.state == true ? 1 : 2));
	  curr->state = 0;
	  ret = prompt_menu(curr, win);
	  if (ret == END_GAME)
	    return (END_GAME);
	}
      if (count_d2(curr, (curr->player.state == true ? curr->player.player1_y_win : curr->player.player2_y_win),
		  (curr->player.state == true ? curr->player.player1_x_win : curr->player.player2_x_win),
		  (curr->player.state == true ? true : false)) == 1)
	{
	  game_results(win, (curr->player.state == true ? 1 : 2));
	  curr->state = 0;
	  ret = prompt_menu(curr, win);
	  if (ret == END_GAME)
	    return (END_GAME);
	}

      if (curr->player.state == true)
	{
	  curr->player.p1_w5_cond = false;
	  curr->player.player1_y_win = -1;
	  curr->player.player1_x_win = -1;
	}
      else
	{
	  curr->player.p2_w5_cond = false;
	  curr->player.player2_y_win = -1;
	  curr->player.player2_x_win = -1;
	}
    }
  return (0);
}

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
	  ret = check_cond_w5(curr, win);
	  if (ret == END_GAME)
	    return (end_game(curr, win));
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
