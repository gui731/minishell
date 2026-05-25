#include "../../includes/minishell.h"

void free_cmds(t_cmd *cmds)
{
    t_cmd *tmp;
    int i;

    while (cmds)
    {
        i = 0;
        while (cmds->argv && cmds->argv[i])
            free(cmds->argv[i++]);
        free(cmds->argv);
        free(cmds->infile);
        free(cmds->outfile);
        free(cmds->heredoc_delim);
        free(cmds->heredoc_input);
        free(cmds->full_path);
        if (cmds->heredoc_fd != -1)
            close(cmds->heredoc_fd);
        tmp = cmds;
        cmds = cmds->next;
        free(tmp);
    }
}


void free_tokens(t_token *tokens)
{
    t_token *tmp;

    while (tokens)
    {
        tmp = tokens->next;

        if (tokens->value)
            free(tokens->value);

        free(tokens);

        tokens = tmp;
    }
}
