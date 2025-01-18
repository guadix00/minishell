#include "minishell.h"

// int process_heredoc(t_token *heredoc_token)
// {
//     int redir[2];
//     int heredoc;
//     int status;
//     char *line;

//     status = 0;
//     if (pipe(redir) == -1)
//     {
//         perror("pipe");
//         return -1;
//     }

//     heredoc = fork();
//     if (heredoc == -1)
//     {
//         perror("fork");
//         close(redir[0]);
//         close(redir[1]);
//         return -1;
//     }

//     if (heredoc == 0) 
//     {
//         close(redir[0]);
//         while (1)
//         {
//             line = readline("> ");
//             if (!line || strcmp(heredoc_token->next->value, line) == 0)
//             {
//                 free(line);
//                 break;
//             }
//             write(redir[1], line, ft_strlen(line));
//             write(redir[1], "\n", 1);
//             free(line);
//         }
//         close(redir[1]);
//         exit(0);
//     }

//     // Parent process
//     close(redir[1]);
//     if (waitpid(heredoc, &status, 0) == -1)
//     {
//         perror("waitpid");
//         close(redir[0]);
//         return -1;
//     }

//     status = WEXITSTATUS(status);
//     if (status != 0)
//     {
//         close(redir[0]);
//         return -1;
//     }
//     return redir[0]; 
// }


int process_heredoc(t_token *heredoc_token)
{
    int redir[2];
    int heredoc;
    int status;
    char *line;

    status = 0;
    if (pipe(redir) == -1)
    {
        perror("pipe");
        return -1;
    }

    heredoc = fork();
    if (heredoc == -1)
    {
        perror("fork");
        close(redir[0]);
        close(redir[1]);
        return -1;
    }

    if (heredoc == 0) // Child process
    {
        here_signals();
        close(redir[0]); // Close the read end of the pipe in the child process
        while (1)
        {
            line = readline("> ");
            if (!line || strcmp(heredoc_token->next->value, line) == 0)
            {
                free(line);
                break;
            }
            write(redir[1], line, strlen(line));
            write(redir[1], "\n", 1);
            free(line);
        }
        close(redir[1]); // Close the write end of the pipe in the child process
        exit(0);
    }

    // Parent process
    close(redir[1]); // Close the write end of the pipe in the parent process
    if (waitpid(heredoc, &status, 0) == -1)
    {
        perror("waitpid");
        close(redir[0]);
        return -1;
    }

    status = WEXITSTATUS(status);
    if (status != 0)
    {
        close(redir[0]);
        return -1;
    }

    return redir[0]; // Return the read end of the pipe
}
