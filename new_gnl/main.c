#include "get_next_line.h"

int main()
{
	char *tmp;
	int i = 0;
	int fd;

	fd = open("t1", O_RDONLY);
	while (i < 3)
	{
		tmp = get_next_line(fd);
		printf("voici donc ce que je recup %s\n", tmp);
		free(tmp);
		i++;
	}
}
