#include "shell.h"

/**
 * get_input - get line minus the newline
 *
 * Return: bytes readd
 */

char *get_input(void)
{
	static char buffer[BUFFSIZE];
	ssize_t position = 0;
	ssize_t bytes_read = 0;

	if (position >= bytes_read)
	{
		bytes_read = read(STDIN_FILENO, buffer, BUFFSIZE);
		if (bytes_read <= 0)
			return (NULL);
		position = 0;
	}

	while (position < bytes_read)
	{
		if (buffer[position] == '\n')
		{
			buffer[position] = '\0';
			char *input = strdup(buffer);

			position++;
			return (input);
		}
		position++;
	}

	return (NULL);
}

/**
 * main - entry point to the program
 *
 * Return:  0.
 */

int main(void)
{
	char *cmd;
	char **args;

	while (1)
	{
		printf("$ ");
		cmd = get_input();

		if (cmd == NULL)
		{
			printf("\n");
			exit(EXIT_SUCCESS);
		}
		args = custom_tokenize(cmd);
		if (strcmp(args[0], "cd") == 0)
		{
			char *new_dir = args[1];

			if (new_dir == NULL || strcmp(new_dir, "~") == 0)
				new_dir = getenv("HOME");

			if (chdir(new_dir) != 0)
			{
				perror("cd");
			}
			else
			{
				char cwd[BUFFSIZE];

				if (getcwd(cwd, sizeof(cwd)) != NULL)
					setenv("PWD", cwd, 1);
				else
					perror("getcwd");
			}
			continue;
			}
	}
	return (0);
}
