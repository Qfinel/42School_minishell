#include"../minishell.h"
#include<stdio.h>
#include"../libft/libft.h"

int main(void)
{
    char *str = " wc -l";
    char **arr = ft_split(str, ' ');
    char **arr2 = split_with_quotes(str);
    printf("Using ft_split:\n");
    printf("%s\n", arr[0]);
    printf("%s\n", arr[1]);
    printf("Using split_with_quotes:\n");
    printf("%s\n", arr2[0]);
    printf("%s\n", arr2[1]);
    return (0);
}