/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:51:43 by tpotilli          #+#    #+#             */
/*   Updated: 2024/03/07 13:56:15 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_exemple.h"
#include <stdio.h>
#include <fcntl.h>

int    main(void)
{
	int        fd1;
	int        run;
	char    	*str;

	fd1 = open("test.txt", O_RDWR);
	run = 0;
	while (run < 3)
	{
		str = get_next_line(fd1);
		if (str != NULL)
		{
			printf("main FD1 --> %s\n", str);
			free (str);
			str = NULL;
		}
		run++;
	}
	close(fd1);
	return (0);
}
