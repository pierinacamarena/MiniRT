#include "init.h"

static char	*read_file(int fd)
{
	char	buf[BUFSIZE + 1];
	int		count;
	char	*file_contents;

	file_contents = NULL;
	count = read(fd, buf, BUFSIZE);
	buf[count] = '\0';
	while (count > 0)
	{
		file_contents = ft_strjoin(file_contents, buf);
		if (file_contents == NULL)
		{
			perror("ft_strjoin");
			return (NULL);
		}
		count = read(fd, buf, BUFSIZE);
		buf[count] = '\0';
	}
	if (count == -1)
	{
		perror("read");
		free(file_contents);
		return (NULL);
	}
	return (file_contents);
}

t_file	*init_file(const char *filename)
{
	t_file	*file;

	file = (t_file *)malloc(sizeof(t_file));
	if (file == NULL)
		return (NULL);
	file->filename = filename;
	file->fd = open(filename, O_RDONLY);
	if (file->fd == -1)
	{
		perror(filename);
		free(file);
		return (NULL);
	}
	file->file_contents = read_file(file->fd);
	if (file->file_contents == NULL)
	{
		close(file->fd);
		free(file);
		return (NULL);
	}
	return (file);
}

t_data	*init_data(const char *filename)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	bzero(data, sizeof(t_data)); //implement custom
	data->file = init_file(filename);
	if (data->file == NULL)
	{
		clean(data);
		return (NULL);
	}
	data->params = parse(data->file->file_contents);
	if (data->params == NULL)
	{
		clean(data);
		return (NULL);
	}
	data->mlx = start_mlx();
	if (data->mlx == NULL)
	{
		clean(data);
		return (NULL);
	}
	data->img = get_new_image(data->mlx);
	if (data->img == NULL)
	{
		clean(data);
		return (NULL);
	}
	return (data);
}
