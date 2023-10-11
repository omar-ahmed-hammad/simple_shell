#include "shell.h"

/**
 * get_input -> get line minus the newline
 *
 * Return: bytes read
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
 * Return: 0
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
		if (strcmp(args[0], "setenv") == 0)
		{
			if (args[1] != NULL && args[2] != NULL)
			{
				if (setenv(args[1], args[2], 1) != 0)
				{
					perror("setenv");
			}}
			else
			{
				fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
			}
			continue;
		}
		if (strcmp(args[0], "unsetenv") == 0)
		{
			if (args[1] != NULL)
			{
				if (unsetenv(args[1]) != 0)
				{
					perror("unsetenv");
			}}
			else
			{
				fprintf(stderr, "Usage: unsetenv VARIABLE\n");
			}
			continue;
	}}
	return (0);
}
