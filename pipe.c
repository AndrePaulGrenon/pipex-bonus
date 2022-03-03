/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrenon <agrenon@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 14:54:03 by agrenon           #+#    #+#             */
/*   Updated: 2022/03/03 17:55:21 by agrenon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_pipe.h"

void	ft_free_argvec(char **argvec, char *cmd)
{
	if (argvec)
	{
		if (argvec[0])
		{
			free(argvec[0]);
			cmd = NULL;
		}
		if (argvec[1])
			free(argvec[1]);
		free (argvec);
	}
	if (cmd)
		free (cmd);
	return ;
}

void	ft_err_message(char **argvec, char *cmd)
{	
	ft_print_cmd("Pas assez d'arguements\n");
	ft_print_cmd(" ou fichier invalide !\n");
	ft_print_cmd("\n- UTILISEZ: ./pipex input_text.txt ");
	ft_print_cmd("CMD CMD output_text.txt\n");
	ft_print_cmd("\n- VERIFIER : input_text.txt est valide\n");
	ft_print_cmd("             CMD est existante\n\n");
	ft_free_argvec(argvec, cmd);
	if (!cmd)
		perror("open");
	exit(0);
	return ;
}

void	ft_no_cmd(char *argv, char **argvec)
{
	ft_print_cmd("\nERREUR: COMMANDE -> ");
	ft_print_cmd(argv);
	ft_print_cmd(" <- NON TROUVÉE\n");
	ft_print_cmd("\n Veuillez entrer une commande valide\n\n");
	ft_free_argvec(argvec, NULL);
	exit(0);
	return ;
}

int	main(int argc, char **argv, char **env)
{
	char	*cmd;
	char	**argvec;
	int		i;
	int		files[2];

	if (argc <= 4)
		ft_err_message(NULL, NULL);
	i = 2 + ft_here_doc(argv);
	while (i < argc - 1)
	{
		pipe(files);
		argvec = malloc(sizeof(size_t) * 3);
		cmd = ft_command(argv, argvec, env, i);
		if (i == argc - 2)
		{	
			if (open(argv[argc -1], O_RDWR | O_CREAT | O_TRUNC, 0777) == -1)
				ft_err_message(argvec, cmd);
			ft_execute_me(argvec, env, cmd, 0);
			break ;
		}
		ft_execute_me(argvec, env, cmd, i);
		i++;
	}
	return (0);
}
