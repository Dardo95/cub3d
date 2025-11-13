#include "../../includes/cub3d.h"

static int	validate_texture_and_extract(void *mlx, t_texture *tex)
{
	if (tex->width > TEX_SIZE || tex->height > TEX_SIZE)
	{
		mlx_destroy_image(mlx, tex->img_ptr);
		tex->img_ptr = NULL;
		return (err("Texture too large"));
	}
	tex->data = mlx_get_data_addr(tex->img_ptr,
			&tex->bpp, &tex->line_len, &tex->endian);
	if (!tex->data)
	{
		mlx_destroy_image(mlx, tex->img_ptr);
		tex->img_ptr = NULL;
		return (err("Failed to get texture data"));
	}
	return (1);
}

int	load_texture(void *mlx, t_texture *tex, const char *path)
{
	if (!path || !*path)
		return (err("Missing texture path"));
	if (!can_open_readonly(path))
		return (err("Cannot open texture file"));
	tex->img_ptr = mlx_xpm_file_to_image(mlx, (char *)path,
			&tex->width, &tex->height);
	if (!tex->img_ptr)
		return (err("Failed to load texture"));
	return (validate_texture_and_extract(mlx, tex));
}

char	*join_texture_path(const char *dir, const char *path)
{
	char	*tmp;
	char	*joined;
	size_t	len;

	if (!dir || !path)
		return (NULL);
	if (*path == '/')
		return (NULL);
	if (!*dir)
		return (ft_strdup(path));
	len = ft_strlen(dir);
	if (dir[len - 1] == '/')
		return (ft_strjoin(dir, path));
	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	joined = ft_strjoin(tmp, path);
	free(tmp);
	return (joined);
}
