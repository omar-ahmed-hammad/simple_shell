#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
int opt_chars_read(void);
int elseif_op(void);
int elseif_op(void);
void forkChild(void);
void remove_newline(char *, ssize_t);
void handle_eof_error(char *strg);
void handle_eof_or_error(void);
void handleKid_pid(const char *cmd);
void handle_error(char *strg[]);

#endif
