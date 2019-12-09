#include "get_next_line.h"
int main(int argc, char **argv)
{
	if (argc == 9)
		return 0;
	int fd;
	int ret;
	int line;
	char *buff;
	line = 0;
	fd = open(argv[1], O_RDWR);
	while ((ret = get_next_line(fd, &buff)) > 0)
	{
		printf("[Return: %d] Line #%d: %s\n", ret, ++line, buff);
		//if (line == 6)
		//close (fd);
		free(buff);
	}
	printf("[Return: %d] Line #%d: %s\n", ret, ++line, buff);
	if (ret == -1)
		printf("-----------\nError\n\n");
	else if (ret == 0)									
		printf("-----------\nEnd of file\n\n");	
		close(fd);
	system("leaks a.out");	
	return (0);
													
}
