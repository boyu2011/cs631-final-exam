#include <stdio.h>
#include <unistd.h>
int main(int argc, char **argv) {
	int pid;
	write(STDOUT_FILENO, "write1\n", 7);
	printf("write2\n");

	if ((pid = fork()) > 0) {
		sleep(2);
	} else if (pid == 0) {
		write(STDOUT_FILENO, "write3\n", 7);
	}

	printf("write4\n");
}

