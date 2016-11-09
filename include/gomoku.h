#ifndef		_GOMOKU_H_
# define	_GOMOKU_H_

# include	"trace.h"

# define	DEFAULT_VALUE (15)
# define	MENU_H (150)
# define	MENU_L (150)
# define	TITLE_H (18)
# define	TITLE_L (117)

# define	TITLE_PATH ("/srcs/div/title")
# define	DEF_READ (117)
# define	TABS ("\t\t\t\t\t\t\t")

# define	NEW_GAME (0)
# define	OPTIONS (1)
# define	END_GAME (42)

# define	SPACE_KEY (32)
# define	ARROW_UP_KEY (183)
# define	ARROW_DOWN_KEY (184)
# define	ARROW_RIGHT_KEY (185)
# define	ARROW_LEFT_KEY (186)

# define	EMPTY_SPOT ('-')
# define	PLAYER_SPOT ('o')
# define	IA_SPOT ('x')

typedef struct	s_opt
{
  bool		is_verbose;
}		t_opt;

typedef struct	s_gopt
{
  bool		vs_ia;
}		t_gopt;

typedef struct	s_game
{
  bool		is_title;
  char		**title;
  unsigned int	mstate;
  bool		pstate;
  unsigned int	h;
  unsigned int	l;
  unsigned int	cursy;
  unsigned int	cursx;
  char		**board;
  t_gopt	options;
}		t_game;

#endif		/* _GOMOKU_H_ */
