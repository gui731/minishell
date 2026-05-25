#include "../../includes/minishell.h"

t_token *new_token(char *value, t_token_type type)
{
    t_token *token;

    token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);

    token->value = value;
    token->type = type;
    token->next = NULL;
    return (token);
}

void add_token(t_token **list, t_token *new)
{
    t_token *tmp;

    if (!*list)
    {
        *list = new;
        return;
    }
    tmp = *list;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}
