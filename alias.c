#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define BUFFER_SIZE 1024
/**
 * struct Alias - parameter structurie
 * @name: alias name
 * @value: alias value
 * @next: next alias _
 */

typedef struct Alias
{
	char *name;
	char *value;
	struct Alias *next;
} Alias;

Alias(*alias_list = NULL);

/**
 * get_input - get line minus the newline
 *
 * Return: bytes read
 */

char *get_input(void)
{
	static char [BUFFSIZE];
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

Alias *find_alias(char *name)
{
	Alias *current = alias_list;

	while (current != NULL)
	{
		if (strcmp(current->name, name) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

/**
 * print_aliases - print alias string
 */

void print_aliases(void)
{
	Alias *current = alias_list;

	while (current != NULL)
	{
		printf("%s='%s'\n", current->name, current->value);
		current = current->next;
	}
}
/**
 * add_alias - add alias string
 * @name: alias name
 * @value: alias value
 */
void add_alias(char *name, char *value)
{
	Alias *alias = find_alias(name);

	if (alias != NULL)
	{
		free(alias->value);
		alias->value = strdup(value);
	}
	else
	{
		Alias *new_alias = (Alias *)malloc(sizeof(Alias));

		new_alias->name = strdup(name);
		new_alias->value = strdup(value);
		new_alias->next = alias_list;
		alias_list = new_alias;
	}
}
/**
 * main - Handle alias command
 *
 * Return: 0 for success, non-zero for failure
 */

int main(void)
{
	char *input, *token;
	char *delimiters = ";&| ";
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
			if (strcmp(token, "alias") == 0)
			{
			}
			else
			{
				int result = execute_command(token);

				if (strcmp(token, "&&") == 0)
					prev_result = (result == 0) ? 1 : 0;
				else if (strcmp(token, "||") == 0)
					prev_result = (result == 0) ? 0 : 1;
				else
					prev_result = result;
			}
			token = strtok(NULL, delimiters);
		}
		free(input);
	}
	return (0);
}
