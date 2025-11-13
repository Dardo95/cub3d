#include "../../includes/cub3d.h"

int	err(const char *msg)
{
	write(2, "Error\n", 6);
	ft_error((char *)msg, FALSE);
	write(2, "\n", 1);
	return (0);
}
