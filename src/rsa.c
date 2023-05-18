/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-aga <juan-aga@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:58:18 by juan-aga          #+#    #+#             */
/*   Updated: 2023/05/16 18:45:52 by juan-aga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corsair.h"

RSA	*ft_get_rsa(const char *file)
{
	X509		*cert;
	EVP_PKEY	*pkey;
	RSA			*rsa;
	BIO			*bio;
	int			fd;

	bio = BIO_new(BIO_s_file());
	fd = BIO_read_filename(bio, file);
	if (!fd)
		ft_error(ER_FILE, file);
	cert = PEM_read_bio_X509(bio, NULL, 0, NULL);
	if (!cert)
		ft_error(ER_KEY, file);
	pkey = X509_get_pubkey(cert);
	if (!pkey)
		ft_error(ER_KEY, file);
	rsa = EVP_PKEY_get1_RSA(pkey);
	if (!rsa)
		ft_error(ER_KEY, file);
	X509_free(cert);
	EVP_PKEY_free(pkey);
	BIO_free(bio);
	return (rsa);
}

void	ft_calc(t_corsair *cor)
{
	cor->n1 = (BIGNUM *) RSA_get0_n(cor->rsa1);
	cor->n2 = (BIGNUM *) RSA_get0_n(cor->rsa2);
	cor->e = (BIGNUM *) RSA_get0_e(cor->rsa1);
	BN_gcd(cor->p, cor->n1, cor->n2, cor->ctx);
	BN_div(cor->q1, NULL, cor->n1, cor->p, cor->ctx);
	BN_div(cor->q2, NULL, cor->n2, cor->p, cor->ctx);
	BN_dec2bn(&cor->one, "1");
	BN_sub(cor->fi1, cor->q1, cor->one);
	BN_sub(cor->fi2, cor->p, cor->one);
	BN_mul(cor->totient, cor->fi1, cor->fi2, cor->ctx);
	BN_mod_inverse(cor->d, cor->e, cor->totient, cor->ctx);
	RSA_set0_key(cor->private, cor->n1, cor->e, cor->d);
	RSA_set0_factors(cor->rsa1, cor->p, cor->q1);
	RSA_set0_factors(cor->rsa2, cor->p, cor->q2);
}
