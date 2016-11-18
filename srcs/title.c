#include	"gomoku.h"

int		get_title(t_game *curr)
{
  char		*path = getenv("PWD");
  char		*title_path;
  int		fd;
  char		buffer[DEF_READ];
  unsigned int	h = 0;

  curr->menu.title = malloc(sizeof(char *) * TITLE_H);
  curr->menu.title[TITLE_H] = NULL;
  title_path = malloc(sizeof(char) * (strlen(path) + strlen(TITLE_PATH)));
  strcpy(title_path, path);
  strcat(title_path, TITLE_PATH);
  if ((fd = open(title_path, O_RDONLY)) < 0)
    {
      curr->menu.title_state = false;
      return (-EBADF);
    }
  while (read(fd, buffer, TITLE_L))
    {
      buffer[TITLE_L] = 0;
      curr->menu.title[h] = strdup(buffer);
      h += 1;
    }
  close(fd);
  if (title_path)
    free(title_path);
  curr->menu.title_state = true;
  return (0);
}

void		display_title(t_game *curr, WINDOW *win)
{
  int		pos = 0;

  if (curr->menu.title_state)
    for (pos = 0; curr->menu.title[pos]; pos++)
      wprintw(win, "%s", curr->menu.title[pos]);
  wprintw(win, "\n\n");
}
