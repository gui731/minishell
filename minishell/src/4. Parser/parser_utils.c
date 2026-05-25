#include "../../includes/minishell.h"

t_cmd *new_cmd(void)
{
    t_cmd *cmd = malloc(sizeof(t_cmd));

    if (!cmd)
        return (NULL);
    cmd->argv = NULL;
    cmd->infile = NULL;
    cmd->infile_fd = -1;
    cmd->outfile = NULL;
    cmd->append = 0;
    cmd->heredoc_delim = NULL;
    cmd->heredoc_fd = -1;
    cmd->heredoc_expand = 0;
    cmd->heredoc_input = NULL;
    cmd->full_path = NULL;
    cmd->next = NULL;
    return (cmd);
}

void add_cmd(t_cmd **list, t_cmd *new)
{
    t_cmd *tmp;

    if (!*list)
    {
        *list = new;
        return ;
    }
    tmp = *list;
    while (tmp->next)
        tmp=tmp->next;
    tmp->next = new;

}

void add_arg(t_cmd *cmd, char *value)
{
    int i = 0;
    char **new;

    while (cmd->argv && cmd->argv[i])
        i++;
    new = malloc(sizeof(char*)*(i + 2));
    if (!new)
        return ; 
    i = 0;
    while (cmd->argv && cmd->argv[i])
    {
        new[i]=cmd->argv[i];
        i++;
    }
    new[i++]=ft_strdup(value);
    new[i] = NULL;

    free(cmd->argv);
    cmd->argv = new;

}