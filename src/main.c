/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-aga <juan-aga@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:42:15 by juan-aga          #+#    #+#             */
/*   Updated: 2023/05/16 20:02:03 by juan-aga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corsair.h"

static void	ft_check_args(int ac, char **av, t_corsair *corsair);
static void	ft_open_file(char *file, t_corsair *corsair);
static void	ft_init(t_corsair *corsair);
static void	ft_free(t_corsair *c);

int	main(int ac, char **av)
{
	struct s_corsair	corsair;

	ft_check_args(ac, av, &corsair);
	ft_init(&corsair);
	ft_calc(&corsair);
	ft_decrypt_print(&corsair);
	ft_free(&corsair);
	return (0);
}

static void	ft_check_args(int ac, char **av, t_corsair *corsair)
{
	if (ac != 4)
		ft_error(ER_USAGE, NULL);
	corsair->rsa1 = ft_get_rsa(av[1]);
	corsair->rsa2 = ft_get_rsa(av[2]);
	ft_open_file(av[3], corsair);
	printf("av 3 es: %s\n", av[3]);
}

static void	ft_open_file(char *file, t_corsair *corsair)
{
	corsair->file = open(file, O_RDONLY);
	if (corsair->file < 0)
		ft_error(ER_FILE, file);
}

static void	ft_init(t_corsair *c)
{
	c->ctx = BN_CTX_new();
	c->bioprint = BIO_new_fp(stdout, BIO_NOCLOSE);
	c->one = BN_new();
	c->q1 = BN_new();
	c->q2 = BN_new();
	c->p = BN_new();
	c->d = BN_new();
	c->totient = BN_new();
	c->fi1 = BN_new();
	c->fi2 = BN_new();
	c->private = RSA_new();
}

static void	ft_free(t_corsair *c)
{
	BN_CTX_free(c->ctx);
	BIO_free(c->bioprint);
	BN_free(c->one);
	BN_free(c->n1);
	BN_free(c->n2);
	BN_free(c->q1);
	BN_free(c->q2);
	BN_free(c->p);
	BN_free(c->d);
	BN_free(c->e);
	BN_free(c->totient);
	BN_free(c->fi1);
	BN_free(c->fi2);
}
