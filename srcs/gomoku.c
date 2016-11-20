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
      == 0)
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
      if (ch_sum == SPACE_KEY && curr->goban[curr->cursy][curr->cursx].cont == '-' && (ret2 = arbitrary(AUTHORITY, curr) == 0))
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
	  arbitrary(CHECK, curr);
	  ret = arbitrary(SCORE, curr);
	  if (ret == WIN_GAME)
	    {
	      game_results(win, (curr->player.state == true ? 1 : 2));
	      curr->state = 0;
	      ret = prompt_menu(curr, win);
	      if (ret == END_GAME)
		return (END_GAME);
	    }
	  else if (ret == DRAW_GAME)
	    {
	      game_results(win, 0);
	      curr->state = 0;
	      ret = prompt_menu(curr, win);
	      if (ret == END_GAME)
		return (END_GAME);
	    }
	  else
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
	      ret = prompt_menu(curr, win);
	      if (ret == END_GAME)
		return (END_GAME);
	    }
	  wclear(win);
	  print_goban(curr, win);
	  if (ret2 == 1)
	    print_infos(curr, win);
	  else
	    {
	      wattron(win, COLOR_PAIR(curr->player.state == true ? 3 : 4));
	      wprintw(win, "Bad move\n(rule of three)");
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
  print_goban(curr, win);
  wrefresh(win);
  curr->player.state = true;
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
