#include "shell.h"

/**
 * get_path - function that handles env variable.
 * @cmd: user entered commands
 *
 * Return: 0
 */

char *get_path(char *cmd)
{
	char *path_env = getenv("PATH");

	if (path_env == NULL)
		return (NULL);
	char *path = strtok(path_env, ":");

	while (path != NULL)
	{
		char *full_path = malloc(strlen(path) + strlen(cmd) + 2);

		if (full_path == NULL)
		{
			printf("malloc");
			exit(EXIT_FAILURE);
		}
		sprintf(full_path, "%s/%s", path, cmd);

		if (access(full_path, X_OK) == 0)
			return (full_path);

		free(full_path);
		path = strtok(NULL, ":");
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

		/* Handle the built-in exit command with arguments */
		if (strcmp(args[0], "exit") == 0)
		{
			int exit_status = EXIT_SUCCESS;

			if (args[1] != NULL)
				exit_status = atoi(args[1]);
			free(cmd);
			exit(exit_status);
		}

		/* Rest of your shell logic using args */
		/* ... */
	}

	return (0);
}
