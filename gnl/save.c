/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:14:51 by tpotilli          #+#    #+#             */
/*   Updated: 2024/03/07 14:05:14 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl_save.h"
//gcc -Wall -Werror -Wextra save.c

char *ft_alloc()
{
	char *buf;
	
	buf = malloc(sizeof(char) * 1);
	buf[0] = '\0';
	return (buf);
}

char	*ft_first_backup(char *backup, int fd)
{ // donc dans cette fonction backup a toute la string, on doit donc se limite via un buffer a BUFFER_SIZE de cette string
	int		help;
	char	*buffer;

	help = 1;
	if (!backup)
		backup = ft_alloc();
	while (!ft_strchr(backup, '\n') && help != 0) // tant que != \n et read fonctionne
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		help = read(fd, buffer, BUFFER_SIZE);
		if (help == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[help] = '\0';
		backup = free_join(backup, buffer); // puis on ajoute a chaque boucle
		free(buffer); // backup et buffer
	}
	printf("donc la premiere fois %s\n", backup);
	return (backup); //pour au final recup 
}

char	*ft_get_str(char *backup)
{
	char	*new_line;

	if (!backup)
		return (NULL);
	if (ft_find_newline(backup) >= 0)
		new_line = ft_substr(backup, 0, ((ft_find_newline(backup) + 1))); // pas /n
	else
		new_line = ft_substr(backup, 0, ft_strlen(backup)); // si un \n
	return (new_line);
}

int	ft_find_newline(char *str)
{
	int	i;

	i = -1;
	if (!(str))
		return (-1);
	while (str[++i])
	{
		if (str[i] == '\n')
			return (i);
	}
	return (-1);
}

char	*ft_next_line(char *backup)
{
	int		i;
	char	*new;

	i = (ft_strlen(backup) - ft_find_newline(backup)); // i qui prend tout backup - la prochaine ligne
	if (!backup || ft_find_newline(backup) == -1)
	{
		free(backup);
		return (NULL);
	}
	else
		new = ft_substr(backup, (ft_find_newline(backup) + 1), i);
	free(backup);
	return (new); // on supr notre ancien backup et on recup le nouveau
}

char	*free_join(char *backup, char *buffer)
{
	char	*stash;

	stash = ft_strjoin(backup, buffer);
	free(backup);
	return (stash);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*cpyjoin(char const *s1, char const *s2, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		j++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int			lens;
	char		*str;

	if (!s1 || !s2)
		return (NULL);
	lens = ft_strlen(s1);
	str = malloc(sizeof(char) * lens + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	cpyjoin(s1, s2, str);
	return (str);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_substr(char *s, int start, int len)
{
	int		i;
	char	*str;

	if (!s || len < 0)
	{
		str = NULL;
		return (str);
	}
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	i = -1;
	while (++i < len && (start + i) < ft_strlen(s))
		str[i] = s[start + i];
	str[i] = '\0';
	return (str);
}

char	*ft_strdup(char *s)
{
	int		i;
	char	*str;
	int		len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	backup = ft_first_backup(backup, fd); // on recup tout notre buffer
	if (!backup)
		return (NULL);
	printf("dsasdasas %s  FINISIIIIIII", backup);
	str = ft_get_str(backup); // recup tout la ligne jusqu'au \n
	backup = ft_next_line(backup); // on prepare la prochaine ligne
	return (str);
}

// les etapes pour faire get_next_line:
// verif le fd et le BUFFER_SIZE
// recuperer la phr

// #include <stdio.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>

// char    *get_next_line(int fd);

// int main()
// {
// 	int fd;
// 	int i = 0;

// 	while (i < 3)
// 	{
// 		fd = open("test.txt", O_WRONLY);
// 		// printf("fd = %d\n", fd);
// 		printf("%s", get_next_line(fd));
// 		i++;
// 	}
// 	close (fd);
// 	return (0);
// }
