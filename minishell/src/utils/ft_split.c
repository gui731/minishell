#include "../../includes/minishell.h"

int count_words(char *s, char c)
{
    int i = 0;
    int count = 0;

    while (s[i])
    {
        while (s[i] == c)
            i++;

        if (s[i])
            count++;

        while (s[i] && s[i] != c)
            i++;
    }

    return (count);
}

char    *word_dup(char *s, int start, int end)
{
    char    *word;
    int     i = 0;

    word = malloc(end - start + 1);
    if (!word)
        return (NULL);

    while (start < end)
        word[i++] = s[start++];

    word[i] = '\0';

    return (word);
}

char    **ft_split(char *s, char c)
{
    char    **result;
    int     i = 0;
    int     j = 0;
    int     start;

    result = malloc(sizeof(char *) * (count_words(s, c) + 1));
    if (!result)
        return (NULL);

    while (s[i])
    {
        while (s[i] == c)
            i++;

        start = i;

        while (s[i] && s[i] != c)
            i++;

        if (i > start)
            result[j++] = word_dup(s, start, i);
    }

    result[j] = NULL;

    return (result);
}

