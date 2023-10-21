#include "shell.h"
/**
 * clear_info - initializes information_s struct
 * @info: struct address
 */
void clear_info(in_formations *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}
/**
 * set_info - initializes information_s struct
 * @info: struct address
 * @av: argument vector
 */
void set_info(in_formations *info, char **av)
{
	int i = 0;

	info->prog_name = av[0];
	if (info->arg)
	{
		info->argv = into_two(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = duplicate_strings(info->arg);
				info->argv[1] = NULL;
			} 
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;
		/*change_alias(info);*/
		/*change_v(info);*/
	}
}
/**
 * free_info - frees information_s struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_info(in_formations *info, int all)
{
	free_vector(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->sep_buff)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		free_vector(info->environ);
		info->environ = NULL;
		b_free((void **)info->sep_buff);
		if (info->fd_read > 2)
			close(info->fd_read);
		put_char(NEG_ONE);
	}
}
