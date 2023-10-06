#include "shell.h"

/**
 * opt_chars_read - run set check if end
 * of file isn't reached
 *
 * Return: 1 on success
 */

int opt_chars_read(void)
{
	char *cmd;

	/* checks if the end of file (EOF)*/
	if (feof(stdin))
	{
		printf("\n");
		free(cmd);
		exit(1);
	}
	else
	{
		perror("getline");
		exit(1);
	}
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

/**
 * get_path - handle env variable
 * @cmd: CLI iput or command
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
 * handle_error - handle NULL errors
 * @error_message: error message
 */

void handle_error(char *error_message)
{
	char cmd;

	perror(error_message);
	free(cmd);
	exit(EXIT_FAILURE);
}

/**
 * remove_newline - Remove the newline character
 * from the command
 * @cmd: user commands in terminal
 * @chars_read: reads charaters elements bu user.
 *
 * Return: 0
 */

void remove_newline(char *cmd, ssize_t chars_read)
{
	/* Remove the newline character from the command */
	if (cmd[chars_read - 1] == '\n')
		cmd[chars_read - 1] = '\0';
}

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
