#include	"gomoku.h"

int		capture_two(t_game *curr)
{
  if (curr->cursx + 2 < curr->l)
    {
      if (curr->goban[curr->cursy][curr->cursx + 1].cont == (curr->player.state == true ? IA_SPOT : PLAYER_SPOT)
	  && curr->goban[curr->cursy][curr->cursx + 2].cont == (curr->player.state == true ? IA_SPOT : PLAYER_SPOT)
	  && curr->goban[curr->cursy][curr->cursx + 3].cont == (curr->player.state == true ? PLAYER_SPOT : IA_SPOT))
	{
	  curr->goban[curr->cursy][curr->cursx + 1].cont = EMPTY_SPOT;
	  curr->goban[curr->cursy][curr->cursx + 2].cont = EMPTY_SPOT;
	  if (curr->player.state == true)
	    curr->player.player1_capture += 2;
	  else
	    curr->player.player2_capture += 2;
	}
    }
  if (curr->cursx > 2)
    {
      if (curr->goban[curr->cursy][curr->cursx - 1].cont == (curr->player.state == true ? IA_SPOT : PLAYER_SPOT)
	  && curr->goban[curr->cursy][curr->cursx - 2].cont == (curr->player.state == true ? IA_SPOT : PLAYER_SPOT)
	  && curr->goban[curr->cursy][curr->cursx - 3].cont == (curr->player.state == true ? PLAYER_SPOT : IA_SPOT))
	{
	  curr->goban[curr->cursy][curr->cursx - 1].cont = EMPTY_SPOT;
	  curr->goban[curr->cursy][curr->cursx - 2].cont = EMPTY_SPOT;
	  if (curr->player.state == true)
	    curr->player.player1_capture += 2;
	  else
	    curr->player.player2_capture += 2;
	}
    }
  if (curr->cursy + 2 < curr->h)
    {
      if (curr->goban[curr->cursy + 1][curr->cursx].cont == (curr->player.state == true ? IA_SPOT : PLAYER_SPOT)
	  && curr->goban[curr->cursy + 2][curr->cursx].cont == (curr->player.state == true ? IA_SPOT : PLAYER_SPOT)
	  && curr->goban[curr->cursy + 3][curr->cursx].cont == (curr->player.state == true ? PLAYER_SPOT : IA_SPOT))
	{
	  curr->goban[curr->cursy + 1][curr->cursx].cont = EMPTY_SPOT;
	  curr->goban[curr->cursy + 2][curr->cursx].cont = EMPTY_SPOT;
	  if (curr->player.state == true)
	    curr->player.player1_capture += 2;
	  else
	    curr->player.player2_capture += 2;
	}
    }
  if (curr->cursy > 2)
    {
      if (curr->goban[curr->cursy - 1][curr->cursx].cont == (curr->player.state == true ? IA_SPOT : PLAYER_SPOT)
	  && curr->goban[curr->cursy - 2][curr->cursx].cont == (curr->player.state == true ? IA_SPOT : PLAYER_SPOT)
	  && curr->goban[curr->cursy - 3][curr->cursx].cont == (curr->player.state == true ? PLAYER_SPOT : IA_SPOT))
	{
	  curr->goban[curr->cursy - 1][curr->cursx].cont = EMPTY_SPOT;
	  curr->goban[curr->cursy - 2][curr->cursx].cont = EMPTY_SPOT;
	  if (curr->player.state == true)
	    curr->player.player1_capture += 2;
	  else
	    curr->player.player2_capture += 2;
	}
    }
  if (curr->cursy + 2 < curr->h && curr->cursx + 2 < curr->l)
    {
      if (curr->goban[curr->cursy + 1][curr->cursx + 1].cont == (curr->player.state == true ? IA_SPOT : PLAYER_SPOT)
	  && curr->goban[curr->cursy + 2][curr->cursx + 2].cont == (curr->player.state == true ? IA_SPOT : PLAYER_SPOT)
	  && curr->goban[curr->cursy + 3][curr->cursx + 3].cont == (curr->player.state == true ? PLAYER_SPOT : IA_SPOT))
	{
	  curr->goban[curr->cursy + 1][curr->cursx + 1].cont = EMPTY_SPOT;
	  curr->goban[curr->cursy + 2][curr->cursx + 2].cont = EMPTY_SPOT;
	  if (curr->player.state == true)
	    curr->player.player1_capture += 2;
	  else
	    curr->player.player2_capture += 2;
	}
    }
  if (curr->cursy > 2 && curr->cursx > 2)
    {
      if (curr->goban[curr->cursy - 1][curr->cursx - 1].cont == (curr->player.state == true ? IA_SPOT : PLAYER_SPOT)
	  && curr->goban[curr->cursy - 2][curr->cursx - 2].cont == (curr->player.state == true ? IA_SPOT : PLAYER_SPOT)
	  && curr->goban[curr->cursy - 3][curr->cursx - 3].cont == (curr->player.state == true ? PLAYER_SPOT : IA_SPOT))
	{
	  curr->goban[curr->cursy - 1][curr->cursx - 1].cont = EMPTY_SPOT;
	  curr->goban[curr->cursy - 2][curr->cursx - 2].cont = EMPTY_SPOT;
	  if (curr->player.state == true)
	    curr->player.player1_capture += 2;
	  else
	    curr->player.player2_capture += 2;
	}
    }
  if (curr->cursy + 2 < curr->h && curr->cursx > 2)
    {
      if (curr->goban[curr->cursy + 1][curr->cursx - 1].cont == (curr->player.state == true ? IA_SPOT : PLAYER_SPOT)
	  && curr->goban[curr->cursy + 2][curr->cursx - 2].cont == (curr->player.state == true ? IA_SPOT : PLAYER_SPOT)
	  && curr->goban[curr->cursy + 3][curr->cursx - 3].cont == (curr->player.state == true ? PLAYER_SPOT : IA_SPOT))
	{
	  curr->goban[curr->cursy + 1][curr->cursx - 1].cont = EMPTY_SPOT;
	  curr->goban[curr->cursy + 2][curr->cursx - 2].cont = EMPTY_SPOT;
	  if (curr->player.state == true)
	    curr->player.player1_capture += 2;
	  else
	    curr->player.player2_capture += 2;
	}
    }
  if (curr->cursy > 2 && curr->cursx + 2 < curr->l)
    {
      if (curr->goban[curr->cursy - 1][curr->cursx + 1].cont == (curr->player.state == true ? IA_SPOT : PLAYER_SPOT)
	  && curr->goban[curr->cursy - 2][curr->cursx + 2].cont == (curr->player.state == true ? IA_SPOT : PLAYER_SPOT)
	  && curr->goban[curr->cursy - 3][curr->cursx + 3].cont == (curr->player.state == true ? PLAYER_SPOT : IA_SPOT))
	{
	  curr->goban[curr->cursy - 1][curr->cursx + 1].cont = EMPTY_SPOT;
	  curr->goban[curr->cursy - 2][curr->cursx + 2].cont = EMPTY_SPOT;
	  if (curr->player.state == true)
	    curr->player.player1_capture += 2;
	  else
	    curr->player.player2_capture += 2;
	}
    }
  return (0);
}
