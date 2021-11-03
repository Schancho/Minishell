#include "minishell.h"

// void        garbage(t_garbage **garbage, void *address)
// {
//     t_garbage *new;

//     new = (t_garbage *)malloc(sizeof(t_garbage));
//     new->next = *(garbage);
//     new->garb = address;
//     *garbage = new;
// }
// void    test(t_garbage **garbag)
// {
//     t_command *st;
//     t_file *f;
//     char *str;

//     str = (char *)malloc(sizeof(char) * 100);
//     garbage(garbag, str);
//     //(*garbage)->garb = str;
//     st = (t_command*)malloc(sizeof(t_command));
//     garbage(garbag, st);
//     //(*garbage)->garb = st;
//     f = (t_file*)malloc(sizeof(t_file));
//     garbage(garbag, f);
//     //(*garbage)->garb = f;
// }
// int main()
// {
//     t_garbage *garbage;
//     test(&garbage);
//     printf("hello wworld\n");
//     system("leaks a.out");
// }
