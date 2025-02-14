/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:49:59 by yustinov          #+#    #+#             */
/*   Updated: 2025/02/12 16:58:20 by yustinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
    char *line;

    while (1)
    {
        line = readline("test$ ");
        if (!line)
            break;
        if (*line)
            add_history(line);
        printf("You typed: %s\n", line);
        free(line);
    }
    rl_clear_history();
    return (0);
}
