#include "shell.h"

/**
 * opt_chars_read - run set check if end
 * of the file isn't reached
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
 * remove_newline - Remove the newline
 * char from the command
 * @cmd: user commands in terminal
 * @chars_read: reads charaters elements bu user
 *
 * Return: 0
 */

void remove_newline(char *cmd, ssize_t chars_read)
{

	/* Remove the newline character from the command */
	if (cmd[chars_read - 1] == '\n')
		cmd[chars_read - 1] = '\0';
}

/**
 * handleKid_pid - handle conditional statement
 * for to fork() kid_child
 * @cmd: user input command
 *
 * Return: kid_pid on success.
 */

void handleKid_pid(const char *cmd)
{
	execve(cmd, (char *const[]){(char *const)cmd, NULL}, NULL);
	perror("execve");
	exit(EXIT_FAILURE);
}
