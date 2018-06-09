/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_c.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robert0 <fripponsupersonique@42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 22:00:59 by robert0           #+#    #+#             */
/*   Updated: 2018/06/09 23:20:59 by robert0          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<string.h>
#include	"libft.h"

static size_t	ft_get_nb_words(const char *s, char c_sep)
{
	size_t	ret;
	int		bool_in_word;

	ret = 0;
	bool_in_word = 0;
	
	while (*s != '\0')
	{
		if ((bool_in_word == 0) && (*s != c_sep))
		{
			bool_in_word = 1;
			ret++;
		}

		else if ((bool_in_word == 1) && (*s == c_sep))
			bool_in_word = 0;

		s++;
	}

	return (ret);
}

static size_t	ft_get_len_word(char const *s, char c_sep)
{
	size_t	ret;

	ret = 0;
	while ((*s != c_sep) && (*s != '\0'))
	{
		ret++;
		s++;
	}

	return (ret);
}

static char	**ft_strsplit_c0(const char *s)
{
	char **ret;

	ret = (char **)(ft_memalloc(2 * sizeof (char *)));
	ret[0] = ft_strdup(s);
	ret[1] = NULL;

	return (ret);
}

static char	**ft_strsplit_cother(size_t nb_words, char **ret, const char *s, char c)
{
	size_t	count;
	size_t	temp_size;
	int		bool_malloc_err;

	count = 0;
	temp_size = 0;
	bool_malloc_err = 0;
	while ((nb_words != 0) && (bool_malloc_err == 0))
	{
		while ((*s == c) && (*s != '\0'))
			s++;

		temp_size = ft_get_len_word(s, c);
		ret[count] = ft_strsub((char *)(s), 0, temp_size);
		if (ret[count] == NULL)
		{
			bool_malloc_err = 1;
			ft_memdel((void**)(&ret));
		}

		s = s + temp_size;
		count++;
		nb_words--;
	}

	ret[count] = NULL;
	return (ret);
}

char	**ft_strsplit_c(char const *s, char c)
{
	size_t	nb_words;
	char	**ret;

	ret = NULL;
	if (s != NULL)
	{
		if (c == '\0')
			ret = ft_strsplit_c0(s);

		else
		{
			nb_words = ft_get_nb_words(s, c);
			ret = (char**)(ft_memalloc((nb_words + 1) * sizeof (char *)));
			if (ret != NULL)
				ret = ft_strsplit_cother(nb_words, ret, s, c);
		}
	}

	return (ret);
}
