#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	find_new_line(char *str)
{
	int i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char *join_free(char *backup, char *buf)
{
	int i = 0;
	int	j = 0;
	char *dest;
	int l1 = ft_strlen(backup);
	int l2 = ft_strlen(buf);

	dest = malloc(sizeof(char) * (l1 + l2 + 1));
	if (!dest)
		return (NULL);
	if (l1 > 0)
	{
		while (backup[i])
		{
			dest[i] = backup[i];
			i++;
		}
	}
	while (buf[j])
	{
		dest[i] = buf[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char *get_backup(char *backup, int fd)
{
	char	*buf;
	int		check;

	check = 1;
	// if (!backup)
	// {

	// }
	while (check != 0 && find_new_line(backup) == 0)
	{
		buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!buf)
			return (NULL);
		check = read(fd, buf, BUFFER_SIZE);
		if (!check)
		{
			free(buf);
			return (NULL);
		}
		buf[check] = '\0';
		backup = join_free(backup, buf);
		free(buf);
	}
	return (backup);
}

char *get_line(char *backup)
{
	char *nl;
	int i = 0;
	int token = 0;
	if (!backup)
		return (NULL);
	while (backup[i] && backup[i] != '\n')
		i++;
	if (backup[i] == '\n')
	{
		i++;
		token++;
	}
	nl = malloc(sizeof(char) * (i + 1));
	if (!nl)
		return (NULL);
	i = 0;
	while (backup[i] && backup[i] != '\n')
	{
		nl[i] = backup[i];
		i++;
	}
	if (token == 1)
	{
		nl[i] = backup[i];
		i++;
	}
	nl[i] = '\0';
	printf("dans get line %s\n", backup);
	return (nl);
}

char *next_line(char *backup)
{
	char *nv;
	int c = 0;
	int i = ft_strlen(backup);
	int j = find_new_line(backup);

	if (!backup || j == 0)
	{
		printf("pas de backup ou de new line\n");
		free(backup);
		return (NULL);
	}
	nv = malloc(sizeof(char) * (i - j));
	if (!nv)
	{
		printf("problem alloc\n");
		return (NULL);
	}
	i = 0;
	while (backup[i] != '\n')
		i++;
	i++;
	while (backup[i])
	{
		nv[c] = backup[i];
		i++;
		c++;
	}
	nv[c] = '\0';
	free(backup);
	return (nv);
}

char *get_next_line(int fd)
{
	static char *backup;
	char 		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	backup = get_backup(backup, fd);
	if (!backup)
	{
		printf("mon backup est null\n");
		return (NULL);
	}
	line = get_line(backup);
	backup = next_line(backup);
	return (line);
}

// donc je dois recup BUFFERSIZE de mon fd