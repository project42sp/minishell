# include "../../includes/minishell.h"

void	ft_close(int fd1, int fd2, int fd3, int fd4)
{
	if (fd1 > -1)
		close(fd1);
	if (fd2 > -1)
		close(fd2);
	if (fd3 > -1)
		close(fd3);
	if (fd4 > -1)
		close(fd4);
}

t_fd	*fd_create(int old_fd)
{
	t_fd	*fd;

	fd = ft_calloc(1, sizeof(t_fd));
	if (!fd)
		return (NULL);
	fd->fd[0] = -1;
	fd->fd[1] = -1;
	fd->oldfd = old_fd;
	fd->last = 0;
	return (fd);
}
