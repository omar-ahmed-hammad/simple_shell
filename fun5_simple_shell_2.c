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
