#include "minishell.h"

void parent_signals(void)
{
    signal(SIGINT, output_signals);
    signal(SIGQUIT, SIG_IGN);
}

/*void child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}*/

void child_signals(void)
{
	signal(SIGINT, display_new_line);
	signal(SIGQUIT, display_new_line);
}

void here_signals(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_IGN);
}

void output_signals(int sig)
{
    (void)sig;
    rl_on_new_line();
    printf("\nminishell> ");
    rl_redisplay();
}

void display_new_line(int sig)
{
    (void)sig;
    printf("hijos\n");
    rl_on_new_line();
    rl_redisplay();
}