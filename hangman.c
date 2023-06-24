/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hangman.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awalter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 13:03:30 by awalter           #+#    #+#             */
/*   Updated: 2023/06/24 13:03:31 by awalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hangman.h"

void	to_lower(char *str)
{
	for (int i = 0; str[i]; i++)
		if ('A' <= str[i] && str[i] <= 'Z')
			str[i] += 32;
}

int	check_guess(char *to_find, char *guess, char *guessed, char *discovered)
{
	int	i = -1;
	int	changed = 0;

	to_lower(guess);
	if (strlen(guess) == 1)
	{
		printf("\033[0;33mThis is not a guess\033[0m\n");
		return (1);
	}
	if (strlen(guess) == 2)
	{
		while (guessed[++i])
		{
			if (guess[0] == guessed[i])
			{
				printf("\033[0;33m%c was already guessed\033[0m\n", guess[0]);
				return (1);
			}
		}
		guessed[i] = guess[0];
		for (int i = 0; to_find[i]; i++)
		{
			if (to_find[i] == guess[0])
			{
				changed = 1;
				discovered[i] = guess[0];
			}
		}
		if (changed == 1)
			return (1);
		return (0);
	}
	if (strcmp(to_find, guess) == 0)
	{
		free(guess);
		free(to_find);
		free(guessed);
		free(discovered);
		printf("\033[0;32mSUCCESS\033[0m\n");
		exit(0);
	}
	return (0);
}

void	hangman_loop(char *to_find)
{
	char	*guessed;
	char	*discovered;
	int		nb_lives = 8;
	char	buff;
	char	*guess;

	guessed = calloc(sizeof(char), 27);
	discovered = calloc(sizeof(char), (strlen(to_find)));
	if (!discovered)
	{
		printf("error during initialisation\n");
		exit(1);
	}
	memset(discovered, '-', strlen(to_find) - 1);
	while (nb_lives)
	{
		printf("%s\n", discovered);
		guess = calloc(sizeof(char), 50);
		write(1, "your guess: ", 12);
		while (1)
		{
			if (read(0, &buff, 1) == -1)
			{
				printf("error while reading input\n");
				exit(1);
			}
			if (strlen(guess) > 30)
			{
				printf("you're searching for a word to long\n");
				break;
			}
			strncat(guess, &buff, 1);
			if (buff == '\n')
				break;
		}
		if (strlen(guess) > 30)
			break;
		if (!check_guess(to_find, guess, guessed, discovered))
		{
			nb_lives--;
			if (nb_lives > 1)
				printf("\033[0;31mwrong guess ~~~~~~~~ %d lives left\033[0m\n", nb_lives);
			else
				printf("\033[0;31mwrong guess ~~~~~~~~ %d life left\033[0m\n", nb_lives);
		}
		free(guess);
	}
	printf("\033[0;31myou lost, the word to find was : %s\033[0m\n", to_find);
	free(to_find);
	free(guessed);
	free(discovered);
	exit(0);
}

int main(void)
{
	srand(time(NULL));
	int		r = rand() % NB_WORDS;
	int		fd;
	char	*word_to_find;

	fd = open("word_list", O_RDONLY);
	if (fd == -1)
		return (1);
	for (int i = 0; i < r; i++)
		free(get_next_line(fd));
	word_to_find = get_next_line(fd);
	close(fd);
	to_lower(word_to_find);
	hangman_loop(word_to_find);
	return (0);
}
