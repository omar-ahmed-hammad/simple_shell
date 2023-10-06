#include "shell.h"

/**
 * get_input - get line minus the newline
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
 * execute_command - Handle the built-in
 * setenv,unsetenv, and cd commands
 * @cmd: user entered commands
 *
 * Wait: for the child process to finish
 */

void execute_command(char *cmd)
{
	char **args = custom_tokenize(cmd);

	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		perror("fork");
		return;
	}

	if (child_pid == 0)
	{
		execvp(args[0], args);
		perror("execvp");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
	}
}
/**
 * main - entry point to the program
 *
 * Return:  0.
 */

int main(void)
{
	char *input, *token;
	char *delimiter = ";";

	while (1)
	{
		printf("$ ");
		input = get_input();

		if (input == NULL)
		{
			printf("\n");
			exit(EXIT_SUCCESS);
		}

		token = strtok(input, delimiter);

		while (token != NULL)
		{
			execute_command(token);
			token = strtok(NULL, delimiter);
		}

		free(input);
	}

	return (0);
}
