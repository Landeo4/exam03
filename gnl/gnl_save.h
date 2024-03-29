/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_save.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:24:15 by tpotilli          #+#    #+#             */
/*   Updated: 2024/03/06 12:57:37 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

char	*get_next_line(int fd);
char	*ft_first_backup(char *backup, int fd);
char	*ft_get_str(char *backup);
int		ft_find_newline(char *str);
char	*ft_next_line(char *backup);
char	*free_join(char *backup, char *buffer);
char	*ft_strchr(char *s, int c);
char	*ft_substr(char *s, int start, int len);
int		ft_strlen(char *str);
char	*cpyjoin(char const *s1, char const *s2, char *str);
char	*ft_strjoin(char *s1, char *s2);

#endif