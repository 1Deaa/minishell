/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:15:24 by drahwanj          #+#    #+#             */
/*   Updated: 2025/04/16 16:15:25 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Allocate and zero a new pak node.
 */
// static t_pak    *new_pak(void)
// {
// 	t_pak	*pak;

// 	pak = (t_pak *)ft_calloc(1, sizeof(t_pak));
// 	if (!pak)
// 		return (NULL);
// 	pak->infile  = STDIN_FILENO;
// 	pak->outfile = STDOUT_FILENO;
// 	return (pak);
// }

// /*
//  * Append a string to a NULL‑terminated array, resizing with realloc.
//  */
// static int append_arg(char ***argv, int *argc, const char *value)
// {
// 	char **tmp = realloc(*argv, sizeof(char*) * (*argc + 2));
// 	if (!tmp)
// 		return -1;
// 	tmp[*argc]     = strdup(value);
// 	tmp[*argc + 1] = NULL;
// 	*argv = tmp;
// 	(*argc)++;
// 	return 0;
// }


// t_pak *parse_tokens(t_token *tok_head)
// {
// 	t_token *tok = tok_head;
// 	t_pak   *head = NULL;
// 	t_pak   *cur  = NULL;
// 	char   **argv = NULL;
// 	int      argc = 0;

// 	/* start first pak */
// 	cur = new_pak();
// 	if (!cur)
// 		return NULL;
// 	head = cur;

// 	while (tok)
// 	{
// 		if (tok->type == TK_PIPE)
// 		{
// 			/* finalize this pak's argv */
// 			cur->full_cmd = argv;
// 			argv = NULL;
// 			argc = 0;

// 			/* create next pak */
// 			t_pak *next = new_pak();
// 			if (!next)
// 				break;
// 			cur->next = next;
// 			next->prev = cur;
// 			cur = next;
// 		}
// 		else if (tok->type == TK_REDIR_IN || tok->type == TK_HEREDOC)
// 		{
// 			/* next token must be the filename */
// 			tok = tok->next;
// 			if (!tok)
// 				break;
// 			/* for heredoc you’d handle the here‑doc buffer */
// 			cur->infile = open(tok->value,
// 							   tok->type == TK_HEREDOC
// 							   ? O_RDONLY  /* replace with your heredoc fd */
// 							   : O_RDONLY, 0);
// 			if (cur->infile < 0)
// 				perror("open infile");
// 		}
// 		else if (tok->type == TK_REDIR_OUT)
// 		{
// 			tok = tok->next;
// 			if (!tok)
// 				break;
// 			cur->outfile = open(tok->value,
// 								O_WRONLY | O_CREAT | O_TRUNC,
// 								0644);
// 			if (cur->outfile < 0)
// 				perror("open outfile");
// 		}
// 		else if (tok->type == TK_APPEND)
// 		{
// 			tok = tok->next;
// 			if (!tok)
// 				break;
// 			cur->outfile = open(tok->value,
// 								O_WRONLY | O_CREAT | O_APPEND,
// 								0644);
// 			if (cur->outfile < 0)
// 				perror("open append");
// 		}
// 		else /* word or quoted */
// 		{
// 			if (append_arg(&argv, &argc, tok->value) < 0)
// 				perror("append_arg");
// 		}
// 		tok = tok->next;
// 	}

// 	/* finish last pak */
// 	cur->full_cmd = argv;
// 	return head;
// }

void print_paks(t_pak *head)
{
	t_pak *cur = head;
	int   idx = 0;

	while (cur)
	{
		printf("=== Pak %d ===\n", idx);
		
		/* Print the full_cmd array */
		if (cur->full_cmd && cur->full_cmd[0])
		{
			printf(" full_cmd:");
			for (int i = 0; cur->full_cmd[i]; i++)
				printf(" \"%s\"", cur->full_cmd[i]);
			putchar('\n');
		}
		else
		{
			printf(" full_cmd: (none)\n");
		}

		/* full_path */
		if (cur->full_path)
			printf(" full_path: %s\n", cur->full_path);
		else
			printf(" full_path: (null)\n");

		/* infile / outfile fds */
		printf(" infile fd : %d\n", cur->infile);
		printf(" outfile fd: %d\n", cur->outfile);

		/* linkage (optional) */
		printf(" prev pak  : %p\n", (void*)cur->prev);
		printf(" next pak  : %p\n", (void*)cur->next);

		putchar('\n');
		cur = cur->next;
		idx++;
	}
}
