/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:51:43 by tpotilli          #+#    #+#             */
/*   Updated: 2024/03/05 18:53:44 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_exemple2.h"

char    *get_next_line(int fd);

int main()
{
	int fd = 0;
	int i = 0;

	while (i < 3)
	{
		fd = open("/home/theo/Desktop/gnl_du_c/test.txt", O_WRONLY);
		printf("%s", get_next_line(fd));
		i++;
	}
	close (fd);
	return (0);
}
