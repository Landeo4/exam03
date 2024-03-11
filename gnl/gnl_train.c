/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_train.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:06:01 by tpotilli          #+#    #+#             */
/*   Updated: 2024/03/07 14:41:30 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl_train.h"

char *join_free(char *backup, char *tmp)
{
	char *new;

	int	i = 0;
	int	j = 0;
	while (backup[i])
		i++;
	while (tmp[j])
		j++;
	new = malloc(sizeof(char) * i + j + 1);
	i = 0;
	j = 0;
	while (backup[i])
	{
		new[i] = backup[i];
		i++;
	}
	while (tmp[j])
	{
		new[i] = tmp[j];
		i++;
		j++;
	}
	new[i] = '0'; //backslash 0
}

first_backup(char *backup, int fd)
{// donc la je dois recup BUFFERSIZE de mon backup
	char 	*tmp;
	int		check;
	int		i;

	while (!check)
	{
		if (i > 10)
			break;
		tmp = malloc(sizeof(char) * BUFFER_SIZE);
		check = read(fd, tmp, BUFFER_SIZE);
		if (check == -1)
		{
			free(tmp);
			return NULL;
		}
		tmp[check] = '0'; // ici ca doit etre un backslash 0
		backup = join_free(backup, tmp);
		free(tmp);
		i++;
	}
	return (backup);
}

char *ft_get_line(char *backup)
{
	
}

char *get_next_line(int fd)
{
	static char *backup;
	char *line;

	if (fd < 0 && !backup) // c'est cense etre des slash pas des et
		return (NULL);
	backup = first_backup(backup, fd);
	if (!backup)
		return (NULL);
	line = ft_get_line(backup);
	backup = get_new_backup();
}
// donc je dois:
// recuperer BUFFERSIZE de mon fd
// ensuite recup ma ligne si il y a un n
// ensuite recup prochain static