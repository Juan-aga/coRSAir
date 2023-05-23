/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-aga <juan-aga@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:56:24 by juan-aga          #+#    #+#             */
/*   Updated: 2023/05/23 17:46:58 by juan-aga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corsair.h"

struct s_error_info	g_error_list[] = {
[ER_USAGE] = {ER_USAGE, "\nUsage:\n\t ./corsair key1 key2 message\n"},
[ER_FILE] = {ER_FILE, "Error opening file: "},
[ER_KEY] = {ER_KEY, "Error getting certificate or private key from file: "},
[ER_MEM] = {ER_MEM, "Failed to assign memory."},
[ER_READ] = {ER_READ, "Error reading file."}
};

static void	ft_print_certificate(int n, BIO *bio, RSA *rsa, RSA *private);
static void	ft_print_text(unsigned char *enc, unsigned char *dec);

void	ft_error(enum e_error_code er, const char *msg)
{
	printf("%s", g_error_list[er].message);
	if (msg)
		printf("%s", msg);
	printf("\n");
	exit(EXIT_FAILURE);
}

void	ft_decrypt_print(t_corsair *corsair)
{
	int				len;
	unsigned char	*enc;
	unsigned char	*dec;

	enc = calloc(sizeof(unsigned char), BUFFER);
	if (!enc)
		ft_error(ER_MEM, NULL);
	dec = calloc(sizeof(unsigned char), BUFFER);
	if (!dec)
	{
		free(enc);
		ft_error(ER_MEM, NULL);
	}
	len = read(corsair->file, enc, BUFFER);
	if (len <= 0)
	{
		free(enc);
		free(dec);
		ft_error(ER_READ, NULL);
	}
	RSA_private_decrypt(len, enc, dec, corsair->private, RSA_PKCS1_PADDING);
	ft_print_certificate(1, corsair->bioprint, corsair->rsa1, corsair->private);
	ft_print_certificate(2, corsair->bioprint, corsair->rsa2, corsair->private);
	ft_print_text(enc, dec);
	close(corsair->file);
}

static void	ft_print_certificate(int n, BIO *bio, RSA *rsa, RSA *private)
{
	printf("\n\tCertificate number: %i\n\n", n);
	RSA_print(bio, rsa, 0);
	RSA_print(bio, private, 0);
}

static void	ft_print_text(unsigned char *enc, unsigned char *dec)
{
	printf("\n\tEncrypted file:\n%s\n", enc);
	printf("\n\tDesencrypted file:\n%s\n", dec);
	free(enc);
	free(dec);
}
