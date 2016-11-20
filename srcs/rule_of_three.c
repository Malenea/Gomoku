#include	"gomoku.h"

int		authorize_check_h(t_game *curr)
{
  if (curr->cursy > 1
      && curr->goban[curr->cursy - 1][curr->cursx].cont == (curr->player.state == true ? 'o' : 'x')
      && curr->goban[curr->cursy - 2][curr->cursx].cont == (curr->player.state == true ? 'o' : 'x'))
    {
      if (curr->cursy > 2 && curr->goban[curr->cursy - 3][curr->cursx].cont == (curr->player.state == true ? 'x' : 'o'))
	return (0);
      if (curr->cursy < curr->h && curr->goban[curr->cursy + 1][curr->cursx].cont == (curr->player.state == true ? 'x' : 'o'))
	return (0);
      return (1);
    }
  else if (curr->cursy < curr->h - 1
	   && curr->goban[curr->cursy + 1][curr->cursx].cont == (curr->player.state == true ? 'o' : 'x')
	   && curr->goban[curr->cursy + 2][curr->cursx].cont == (curr->player.state == true ? 'o' : 'x'))
    {
      if (curr->cursy < curr->h - 2 && curr->goban[curr->cursy + 3][curr->cursx].cont == (curr->player.state == true ? 'x' : 'o'))
	return (0);
      if (curr->cursy > 0 && curr->goban[curr->cursy - 1][curr->cursx].cont == (curr->player.state == true ? 'x' : 'o'))
	return (0);
      return (1);
    }
  else if (curr->cursy > 0 && curr->cursy < curr->h
	   && curr->goban[curr->cursy - 1][curr->cursx].cont == (curr->player.state == true ? 'o' : 'x')
	   && curr->goban[curr->cursy + 1][curr->cursx].cont == (curr->player.state == true ? 'o' : 'x'))
    {
      if (curr->cursy < curr->h - 1 && curr->goban[curr->cursy + 2][curr->cursx].cont == (curr->player.state == true ? 'x' : 'o'))
	return (0);
      if (curr->cursy > 1 && curr->goban[curr->cursy - 2][curr->cursx].cont == (curr->player.state == true ? 'x' : 'o'))
	return (0);
      return (1);
    }
  return (0);
}

int		authorize_check_l(t_game *curr)
{
  if (curr->cursx > 1
      && curr->goban[curr->cursy][curr->cursx - 1].cont == (curr->player.state == true ? 'o' : 'x')
      && curr->goban[curr->cursy][curr->cursx - 2].cont == (curr->player.state == true ? 'o' : 'x'))
    {
      if (curr->cursx > 2 && curr->goban[curr->cursy][curr->cursx - 3].cont == (curr->player.state == true ? 'x' : 'o'))
	return (0);
      if (curr->cursx < curr->l && curr->goban[curr->cursy][curr->cursx + 1].cont == (curr->player.state == true ? 'x' : 'o'))
	return (0);
      return (1);
    }
  else if (curr->cursx < curr->l - 1
	   && curr->goban[curr->cursy][curr->cursx + 1].cont == (curr->player.state == true ? 'o' : 'x')
	   && curr->goban[curr->cursy][curr->cursx + 2].cont == (curr->player.state == true ? 'o' : 'x'))
    {
      if (curr->cursx < curr->l - 2 && curr->goban[curr->cursy][curr->cursx + 3].cont == (curr->player.state == true ? 'x' : 'o'))
	return (0);
      if (curr->cursx > 0 && curr->goban[curr->cursy][curr->cursx - 1].cont == (curr->player.state == true ? 'x' : 'o'))
	return (0);
      return (1);
    }
  else if (curr->cursx > 0 && curr->cursx < curr->l
	   && curr->goban[curr->cursy][curr->cursx - 1].cont == (curr->player.state == true ? 'o' : 'x')
	   && curr->goban[curr->cursy][curr->cursx + 1].cont == (curr->player.state == true ? 'o' : 'x'))
    {
      if (curr->cursx < curr->l - 1 && curr->goban[curr->cursy][curr->cursx + 2].cont == (curr->player.state == true ? 'x' : 'o'))
	return (0);
      if (curr->cursx > 1 && curr->goban[curr->cursy][curr->cursx - 2].cont == (curr->player.state == true ? 'x' : 'o'))
	return (0);
      return (1);
    }
  return (0);
}

int		authorize_check_d1(t_game *curr)
{
  if (curr->cursy > 1 && curr->cursx > 1
      && curr->goban[curr->cursy - 1][curr->cursx - 1].cont == (curr->player.state == true ? 'o' : 'x')
      && curr->goban[curr->cursy - 2][curr->cursx - 2].cont == (curr->player.state == true ? 'o' : 'x'))
    {
      if (curr-> cursy > 2 && curr->cursx > 2 && curr->goban[curr->cursy - 3][curr->cursx - 3].cont == (curr->player.state == true ? 'x' : 'o'))
	return (0);
      if (curr->cursy < curr->h && curr->cursx < curr->l && curr->goban[curr->cursy + 1][curr->cursx + 1].cont == (curr->player.state == true ? 'x' : 'o'))
	return (0);
      return (1);
    }
  else if (curr->cursy < curr->h - 1 && curr->cursx < curr->l - 1
	   && curr->goban[curr->cursy + 1][curr->cursx + 1].cont == (curr->player.state == true ? 'o' : 'x')
	   && curr->goban[curr->cursy + 2][curr->cursx + 2].cont == (curr->player.state == true ? 'o' : 'x'))
    {
      if (curr->cursy < curr->h - 2 && curr->cursx < curr->l - 2 && curr->goban[curr->cursy + 3][curr->cursx + 3].cont == (curr->player.state == true ? 'x' : 'o'))
	return (0);
      if (curr->cursy > 0 && curr->cursx > 0 && curr->goban[curr->cursy - 1][curr->cursx - 1].cont == (curr->player.state == true ? 'x' : 'o'))
	return (0);
      return (1);
    }
  else if (curr->cursy > 0 && curr->cursx > 0 && curr->cursy < curr->h && curr->cursx < curr->l
	   && curr->goban[curr->cursy - 1][curr->cursx - 1].cont == (curr->player.state == true ? 'o' : 'x')
	   && curr->goban[curr->cursy + 1][curr->cursx + 1].cont == (curr->player.state == true ? 'o' : 'x'))
    {
      if (curr->cursy < curr->h - 1 && curr->cursx < curr->l - 1 && curr->goban[curr->cursy + 2][curr->cursx + 2].cont == (curr->player.state == true ? 'x' : 'o'))
	return (0);
      if (curr->cursy > 1 && curr->cursx > 1 && curr->goban[curr->cursy - 2][curr->cursx - 2].cont == (curr->player.state == true ? 'x' : 'o'))
	return (0);
      return (1);
    }
  return (0);
}

int		authorize_check_d2(t_game *curr)
{
  if (curr->cursy < curr->h - 1  && curr->cursx > 1
      && curr->goban[curr->cursy + 1][curr->cursx - 1].cont == (curr->player.state == true ? 'o' : 'x')
      && curr->goban[curr->cursy + 2][curr->cursx - 2].cont == (curr->player.state == true ? 'o' : 'x'))
    {
      if (curr->cursy < curr->h - 2 && curr->cursx > 2 && curr->goban[curr->cursy + 3][curr->cursx - 3].cont == (curr->player.state == true ? 'x' : 'o'))
	return (0);
      if (curr->cursy > 0 && curr->cursx < curr->l && curr->goban[curr->cursy - 1][curr->cursx + 1].cont == (curr->player.state == true ? 'x' : 'o'))
	return (0);
      return (1);
    }
    else if (curr->cursy > 1 && curr->cursx < curr->l - 1
	   && curr->goban[curr->cursy - 1][curr->cursx + 1].cont == (curr->player.state == true ? 'o' : 'x')
	   && curr->goban[curr->cursy - 2][curr->cursx + 2].cont == (curr->player.state == true ? 'o' : 'x'))
    {
      if (curr->cursy > 2 && curr->cursx < curr->l - 2 && curr->goban[curr->cursy - 3][curr->cursx + 3].cont == (curr->player.state == true ? 'x' : 'o'))
	return (0);
      if (curr->cursy < curr->h && curr->cursx > 0 && curr->goban[curr->cursy + 1][curr->cursx - 1].cont == (curr->player.state == true ? 'x' : 'o'))
	return (0);
      return (1);
    }
  else if (curr->cursy > 0 && curr->cursx > 0 && curr->cursy  < curr->h && curr->cursx < curr->l
	   && curr->goban[curr->cursy - 1][curr->cursx + 1].cont == (curr->player.state == true ? 'o' : 'x')
	   && curr->goban[curr->cursy + 1][curr->cursx - 1].cont == (curr->player.state == true ? 'o' : 'x'))
    {
      if (curr->cursy > 1 && curr->cursx < curr->l - 1 && curr->goban[curr->cursy - 2][curr->cursx + 2].cont == (curr->player.state == true ? 'x' : 'o'))
	return (0);
      if (curr->cursy < curr->h - 1 && curr->cursx > 1 && curr->goban[curr->cursy + 2][curr->cursx - 2].cont == (curr->player.state == true ? 'x' : 'o'))
	return (0);
      return (1);
    }
  return (0);
}

int		authorize_rule_of_three(t_game *curr)
{
  if ((authorize_check_h(curr) == 1 && authorize_check_l(curr) == 1)
      || (authorize_check_h(curr) == 1 && authorize_check_d1(curr) == 1)
      || (authorize_check_l(curr) == 1 && authorize_check_d1(curr) == 1)
      || (authorize_check_h(curr) == 1 && authorize_check_d2(curr) == 1)
      || (authorize_check_l(curr) == 1 && authorize_check_d2(curr) == 1)
      || (authorize_check_d1(curr) == 1 && authorize_check_d2(curr) == 1))
    return (RULE_OF_THREE);
  return (0);
}
