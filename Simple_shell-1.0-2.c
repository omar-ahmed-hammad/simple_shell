#include "shell.h"

/**
 * hanndle_env_cmd - handle the built-in env command
 * in file 5.simple....c
 */

void hanndle_env_cmd(void)
{
	char environ;

	char **env = environ;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
		continue;
	}
}

/**
 * main - entry point to the program
 *
 * Return:  0.
 */

int main(void)
{
	char *cmd = NULL;
	size_t chars_read, buffsize = 0;

	while (1)
	{
		printf("$ ");
		chars_read = getline(&cmd, &buffsize, stdin);

		if (chars_read == -1)
			opt_chars_read();
		remove_newline(char *cmd, ssize_t chars_read);
		if (strcmp(cmd, "exit") == 0)	 /* Handle exit command */
		{
			free(cmd);
			exit(EXIT_SUCCESS);
		}
		else if (strcmp(cmd, "env") == 0)	 /* Handle env command */
			hanndle_env_cmd();
		char *full_path = get_path(cmd);

		if (full_path == NULL)
		{
			printf("Command not found: %s\n", cmd);
			continue;
		}
		pid_t child_pid = fork();

		if (child_pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (child_pid == 0) /* Child process */
			handleKid_pid(const char *cmd);
		else /* Parent process */
			wait(NULL); /* Wait for the child process to finish */
		free(full_path);
	}
	free(cmd);
	return (0);
}
