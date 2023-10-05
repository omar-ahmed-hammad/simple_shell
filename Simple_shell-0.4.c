#include "shell.h"

/**
 * get_path -  the function that compute for
 * the path of file.
 * @cmd: user command entered
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

/**
 * handle_eof_or_error - handles the
 *
 * Return: 1 and exit.
 */

void handle_eof_or_error(void)
{
	char *cmd;

	if (feof(stdin))
	{
		printf("\n");   /* check if the end of file (EOF)*/
		free(cmd);
		exit(EXIT_FAILURE);
	}
	else
	{
		perror("getline");
		exit(1);
	}
}

/**
 * main - the entry of program
 *
 * Return: 0.
 */

int main(void)
{
	char *cmd = NULL;
	size_t buffsize = 0;
	ssize_t chars_read;

	while (1)
	{
		printf(":) ");
		chars_read = getline(&cmd, &buffsize, stdin);

		if (chars_read == -1)
			handle_eof_or_error();
		if (cmd[chars_read - 1] == '\n')	/* Remove newline char from cmd */
			cmd[chars_read - 1] = '\0';
		if (strcmp(cmd, "exit") == 0)	/* Handle the built-in exit command */
		{
			free(cmd);
			exit(EXIT_SUCCESS);
		}
		char *full_path = get_path(cmd);

		if (full_path == NULL)
		{
			printf("Command not found: %s\n", cmd);
			continue;
		}
		pid_t kid_pid = fork();

		if (kid_pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (kid_pid == 0)
		handleKid_pid(cmd);
		else /* Parent process */
			wait(NULL); /* Wait for the child process to finish */
		free(full_path);
	}
	free(cmd);
	return (0);
}

/**
 * handleKid_pid - handle conditional statement
 * for to fork() kid_child
 * @cmd: user inputed command
 *
 * Return: kid_pid on success.
 */

void handleKid_pid(const char *cmd)
{
		execve(cmd, (char *const[]){(char *const)cmd, NULL}, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
}
