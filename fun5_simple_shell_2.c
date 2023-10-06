#include "shell.h"

/**
 * hanndle_env_cmd - handle the built-in env command
 * in file 5.simple....c
 */

void hanndle_env_cmd(void)
{
	char **env = environ;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
	continue;
}

/**
 * handle_error - function that handle NULL errors
 * @error_message: print error message
 *
 * Return: error message
 */

void handle_error(char *error_message)
{
	char cmd;

	perror(error_message);
	free(cmd);
	exit(EXIT_FAILURE);
}
/**
 * get_path - function that handle env variable.
 * @cmd: CLI iput or command
 *
 * Return: 0.
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
