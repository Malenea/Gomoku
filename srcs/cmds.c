#include	"gomoku.h"

int		player_cmds(t_game *curr, WINDOW *win)
{
  char		ch[4];
  int		ch_sum;
  int		ret;
  int		ret2 = 1;

  wclear(win);
  print_goban(curr, win);
  print_infos(curr, win);
  wrefresh(win);
  reset_key(ch);
  while (read(0, ch, 4))
    {
      ch_sum = ch[0] + ch[1] + ch[2] + ch[3];
      if (ch_sum == SPACE_KEY && curr->goban[curr->cursy][curr->cursx].cont == EMPTY_SPOT && (ret2 = arbitrary(AUTHORITY, curr) == 0))
	{
	  if (curr->options.vs_ia == false)
	    {
	      (curr->goban[curr->cursy][curr->cursx].cont = (curr->player.state == true ? PLAYER_SPOT : IA_SPOT));
	      curr->player.player1_tokens = (curr->player.state == true ? curr->player.player1_tokens - 1 : curr->player.player1_tokens);
	      curr->player.player2_tokens = (curr->player.state == false ? curr->player.player2_tokens - 1 : curr->player.player2_tokens);
	    }
	  else
	    {
	      curr->goban[curr->cursy][curr->cursx].cont = PLAYER_SPOT;
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

int		ia_cmds(t_game *curr, WINDOW *win)
{
  int		ret;
  int		ret2 = 1;

  if ((goban_reader(curr)) == 0)
    {
      curr->player.state = true;// <- FIXME
      return (0);
    }
  if ((ret2 = arbitrary(AUTHORITY, curr)) == 0)
    {
      curr->goban[curr->cursy][curr->cursx].cont = IA_SPOT;
      curr->player.player2_tokens -= 1;
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
	{
	  wclear(win);
	  print_goban(curr, win);
	  wrefresh(win);
	}
    }
  //
  curr->player.state = true;
  return (0);
}
