#ifndef		_TRACE_H_
# define	_TRACE_H_

# include	<stdio.h>
# include	<stdarg.h>
# include	<errno.h>

# define	RESET_COLOR	"\e[0m"
# define	MAKE_GREEN	"\e[1;32m"
# define	MAKE_RED	"\e[1;31m"
# define	MAKE_YELLOW	"\e[1;33m"

# define	MERR		("ERROR")
# define	MWARN		("WARNING")
# define	MTRACE		("TRACE")

int		my_trace(int, char *, char *, ...);

# define	MY_ERROR(_rc, _format, ...)	my_trace(_rc, MERR,	\
							 #_format,	\
							 ## __VA_ARGS__)
# define	MY_WARN(_format, ...)		my_trace(0, MWARN,	\
							 #_format,	\
							 ## __VA_ARGS__)
# define	MY_TRACE(_format, ...)		my_trace(0, MTRACE,	\
							 #_format,	\
							 ## __VA_ARGS__)

#endif		/* _TRACE_H_ */
