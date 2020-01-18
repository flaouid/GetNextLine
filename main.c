#include "get_next_line.h"

int main(int ac, char **av)
{
	(void)ac;

	int fd;
	int ret;
	int line;
	char *buff;

	line = 0;

		fd = open(av[1], O_RDONLY);
		while ((ret = get_next_line(fd, &buff)) > 0)
		{
			printf("[Return: %d] Line #%d: %s\n", ret, ++line, buff);
			free(buff);
		}

		printf("[Return: %d] Line #%d: %s\n", ret, ++line, buff);
		if (ret == -1)
			printf("-----------\nError\n");
		else if (ret == 0)
			printf("-----------\nEnd of file\n");
		close(fd);

	system("leaks a.out");
	return (0);
}
