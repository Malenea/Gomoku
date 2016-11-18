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

int		authorize_rule_of_three(t_game *curr)
{
  int		ret = 1;

  if (curr->cursy >= 0 && curr->cursy <= curr->h)
    {
      if (((curr->cursy > 1
	    && curr->goban[curr->cursy - 1][curr->cursx].cont == (curr->player.state == true ? 'o' : 'x')
	    && curr->goban[curr->cursy - 2][curr->cursx].cont == (curr->player.state == true ? 'o' : 'x')
	    && ((curr->cursy < curr->h
		 && curr->goban[curr->cursy + 1][curr->cursx].cont != (curr->player.state == true ? 'x' : 'o'))
		|| (curr->cursy > 2
		    && curr->goban[curr->cursy - 3][curr->cursx].cont != (curr->player.state == true ? 'x' : 'o'))))

	   || (curr->cursy > 0 && curr->cursy < curr->h
	       && curr->goban[curr->cursy - 1][curr->cursx].cont == (curr->player.state == true ? 'o' : 'x')
	       && curr->goban[curr->cursy + 1][curr->cursx].cont == (curr->player.state == true ? 'o' : 'x')
	       && ((curr->cursy + 1 < curr->h
		    && curr->goban[curr->cursy + 1][curr->cursx].cont != (curr->player.state == true ? 'x' : 'o'))
		   || (curr->cursy > 1
		       && curr->goban[curr->cursy - 3][curr->cursx].cont != (curr->player.state == true ? 'x' : 'o'))))

	   (curr->cursy - 1 < curr->h
	    && curr->goban[curr->cursy + 1][curr->cursx].cont == (curr->player.state == true ? 'o' : 'x')
	    && curr->goban[curr->cursy + 2][curr->cursx].cont == (curr->player.state == true ? 'o' : 'x')
	    && ((curr->cursy + 2 < curr->h
		 && curr->goban[curr->cursy + 3][curr->cursx].cont != (curr->player.state == true ? 'x' : 'o'))
		|| (curr->cursy > 0
		    && curr->goban[curr->cursy - 1][curr->cursx].cont != (curr->player.state == true ? 'x' : 'o')))))
	  
	  && ((curr->cursx > 1
	       && curr->goban[curr->cursy][curr->cursx - 1].cont == (curr->player.state == true ? 'o' : 'x')
	       && curr->goban[curr->cursy][curr->cursx - 2].cont == (curr->player.state == true ? 'o' : 'x')
	       && ((curr->cursx < curr->l
		    && curr->goban[curr->cursy][curr->cursx + 1].cont != (curr->player.state == true ? 'x' : 'o'))
		   || (curr->cursx > 2
		       && curr->goban[curr->cursy][curr->cursx - 3].cont != (curr->player.state == true ? 'x' : 'o'))))
	    || (curr->cursx > 0 && curr->cursx < curr->l
	       && curr->goban[curr->cursy][curr->cursx - 1].cont == (curr->player.state == true ? 'o' : 'x')
	       && curr->goban[curr->cursy][curr->cursx + 1].cont == (curr->player.state == true ? 'o' : 'x')
	       && ((curr->cursx + 1 < curr->l
		    && curr->goban[curr->cursy][curr->cursx + 1].cont != (curr->player.state == true ? 'x' : 'o'))
		   || (curr->cursx > 1
		       && curr->goban[curr->cursy][curr->cursx - 3].cont != (curr->player.state == true ? 'x' : 'o'))))
	   (curr->cursx - 1 < curr->l
	    && curr->goban[curr->cursy][curr->cursx + 1].cont == (curr->player.state == true ? 'o' : 'x')
	    && curr->goban[curr->cursy][curr->cursx + 2].cont == (curr->player.state == true ? 'o' : 'x')
	    && ((curr->cursx + 2 < curr->l
		 && curr->goban[curr->cursy][curr->cursx + 3].cont != (curr->player.state == true ? 'x' : 'o'))
		|| (curr->cursx > 0
		    && curr->goban[curr->cursy][curr->cursx - 1].cont != (curr->player.state == true ? 'x' : 'o'))))))
	ret = RULE_OF_THREE;
    }
  return (ret);
}

int		arbitrary(arbitrary_type is, t_game *curr)
{
  int		ret = 0;

  if (is == AUTHORITY)
    {
      ret = 1;
      if (curr->rules.r3 == true)
	  ret = authorize_rule_of_three(curr);
      return (ret);
    }
  else if (is == CHECK)
    {
    }
  else
    {
    }
  return (ret);
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
      if (ch_sum == SPACE_KEY && curr->goban[curr->cursy][curr->cursx].cont == '-' && (ret2 = arbitrary(AUTHORITY, curr) > 0))
	{
	  if (curr->options.vs_ia == false)
	    {
	      (curr->goban[curr->cursy][curr->cursx].cont = (curr->player.state == true ? 'o' : 'x'));
	      curr->player.player1_tokens = (curr->player.state == true ? curr->player.player1_tokens - 1 : curr->player.player1_tokens);
	      curr->player.player2_tokens = (curr->player.state == false ? curr->player.player2_tokens - 1 : curr->player.player2_tokens);
	    }
	  else
	    {
	      curr->goban[curr->cursy][curr->cursx].cont = 'o';
	      curr->player.player1_tokens -= 1;
	    }
	  /*
	  check_arbitrary(curr);
	  if (score_arbitrary(curr) == WIN_GAME)
	    {
	      game_results(win, (curr->player.state == true ? 1 : 2));
	      curr->state = 0;
	      ret = display_menu(curr, win);
	      if (ret == NEW_GAME)
		{
new_game(curr);
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
new_game(curr);
		}
	      else if (ret == END_GAME)
		return (END_GAME);
	    }
	  else
	    */
	    curr->player.state = (curr->player.state == true ? false : true);
	  wclear(win);
	  print_goban(curr, win);
	  print_infos(curr, win);
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
	      ret = print_menu(curr, win);
	      if (ret == NEW_GAME)
		new_game(curr, win);
	      else if (ret == END_GAME)
		return (END_GAME);
	    }
	  wclear(win);
	  print_goban(curr, win);
	  //if (ret2 == 1)
	    print_infos(curr, win);
	    /*
	  else
	    {
	      wattron(win, COLOR_PAIR(curr->player.state == true ? 3 : 4));
	      wprintw(win, "Bad move\n(%s)", ret2 == RULE_OF_TWO ? "rule of two" : "rule of three");
	      wattroff(win, COLOR_PAIR(curr->player.state == true ? 3 : 4));
	    }
	  ret2 = 1;
	    */
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
  print_goban(curr, win);
  wrefresh(win);
  curr->player.state = true;
}

int		game_loop(t_game *curr, WINDOW *win)
{
  int		ret;

  wresize(win, curr->h + 5, curr->l + 1);
  print_goban(curr, win);
  print_infos(curr, win);
  wrefresh(win);
  wgetch(win);
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
  int		ret;

  init_game(&curr);
  ret = init_goban(&curr);
  if (ret < 0)
    return (-ENOMEM);
  init_ncurses(win);
  win = newwin(MENU_H, MENU_L, 1, 1);
  refresh();

  ret = print_menu(&curr, win);
  if (ret == END_GAME)
    return (end_game(&curr, win));
  game_loop(&curr, win);
  return (0);
}
