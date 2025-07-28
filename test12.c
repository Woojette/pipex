
#include "pipex.h"

int main()
{
    char **tab;

    tab = ft_split("", ' ');

    // tab =/= tab[0]
    if (!tab)
        printf("null");
    if (tab)
        printf("rentre");
    if (!tab[0])
        printf("tab[0]null");
    if (tab[0])
        printf("tab[1]null");
}