#include "get_next_line.h"

int main()
{
	char *tmp;
	int i = 0;
	int fd;

	fd = open("t2", O_RDONLY);
	while (42)
	{
		tmp = get_next_line(fd);
		printf("voici donc ce que je recup %s .\n", tmp);
		if (tmp == NULL)
		{
			free(tmp);
			break;
		}
		free(tmp);
		i++;
	}
}
