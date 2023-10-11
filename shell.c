#include "shell.h"

/**
 * runProgram - runs program
 * @pmt: command entered
 * @args: command arguments
 * @envp: env variables
 * @w_len: characters written
 * @pgNm: program name
 * Return: void
 */
void runProgram(char *pmt, char **args, char **envp, ssize_t w_len, char *pgNm)
{
	char *token = NULL;
	int n_tokens = 0;
	char delim[] = " ";
	int i = 0;

	pmt[w_len - 1] = '\0';

	if (strcmp(pmt, "env") == 0)
	{
		while (envp[i] != NULL)
		{
			printf("%s\n", envp[i]);
			i++;
		}
	}

	token = strtok(pmt, delim);
	while (token != NULL)
	{
		args[n_tokens] = token;
		n_tokens++;
		token = strtok(NULL, delim);
	}
	args[n_tokens] = NULL;
	if (n_tokens > 0)
	{
		handleExit(pmt, args);
		if (handleChangeDir(args) == 1)
			return;
		if (handleEnvs(args) == 1)
			return;
		execute(pgNm, args, envp);
	}
	n_tokens = 0;
}

/**
 * runNonInteractiveMode - runs if user is not typing in commands
 * @envp: environment variables
 * @progName: program name
 * Return: void
 */
void runNonInteractiveMode(char *progName, char **envp)
{
	static size_t MAXWORDS = 100;
	ssize_t chars_written = 0;
	char *prompt = NULL;
	size_t len = 0;
	char **args;

	args = malloc(sizeof(char *) * MAXWORDS);
	chars_written = _getline(&prompt, &len);

	runProgram(prompt, args, envp, chars_written, progName);

	free(args);
	free(prompt);
}

/**
 * runInteractiveMode - runs if user is typing in commands
 * @envp: environment variables
 * @progName: program name
 * Return: void
 */
void runInteractiveMode(char *progName, char **envp)
{
	static size_t MAXWORDS = 100;
	ssize_t chars_written = 0;
	char *prompt = NULL;
	size_t len = 0;
	char **args;

	args = malloc(sizeof(char *) * MAXWORDS);
	while (1)
	{
		_puts("#cisfun$ ");
		chars_written = _getline(&prompt, &len);
		if (chars_written == -1)
			break;
		runProgram(prompt, args, envp, chars_written, progName);
	}

	free(args);
	free(prompt);
}

/**
 * main - runs whole program
 * @ac: argument count
 * @av: argument vector
 * @env: environment variables
 *
 * Return: 0 if success
 */

int main(__attribute__((unused))int ac, char **av, char **env)
{

	if (isatty(STDIN_FILENO))
		runInteractiveMode(av[0], env);
	else
		runNonInteractiveMode(av[0], env);

	return (0);
}
