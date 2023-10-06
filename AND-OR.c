#include "shell.h"

/**
 * get_input - a funtion pointer to a funtion
 * implementation
 *
 * Return: 0 always
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
 * setenv, unsetenv, and cd commands
 * @cmd: user entered commands
 *
 * Return: -1
 */
int execute_command(char *cmd)
{
	char **args = custom_tokenize(cmd);

	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		perror("fork");
		return (-1);
	}

	if (child_pid == 0)
	{
		execvp(args[0], args);
		perror("execvp");
		exit(EXIT_FAILURE);
	}
	else
	{
		int status;

		waitpid(child_pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (-1);
	}
}

/**
 * main - entry point to the program calls other
 * funtions in it.
 *
 * Return: 0 always
 */

int main(void)
{
	char *input, *token;
	char *delimiters = ";&|";
	int prev_result = 0;

	while (1)
	{
		printf("$ ");
		input = get_input();

		if (input == NULL)
		{
			printf("\n");
			exit(EXIT_SUCCESS);
		}

		token = strtok(input, delimiters);

		while (token != NULL)
		{
			int result = execute_command(token);

			if (strcmp(token, "&&") == 0)
				prev_result = (result == 0) ? 1 : 0;
			else if (strcmp(token, "||") == 0)
				prev_result = (result == 0) ? 0 : 1;
			else
				prev_result = result;

			token = strtok(NULL, delimiters);
		}
		free(input);
	}

	return (0);
}
