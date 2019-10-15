#include "libft.h"

void	ft_printtab(char **tab)
{
	char **ptr = tab;

	while (*ptr) {
		ft_putendl(*ptr);
		ptr++;
	}
}
