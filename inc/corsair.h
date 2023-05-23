/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corsair.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-aga <juan-aga@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:36:55 by juan-aga          #+#    #+#             */
/*   Updated: 2023/05/22 11:52:09 by juan-aga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORSAIR_H
# define CORSAIR_H

# ifndef BUFFER
#  define BUFFER 1024
# endif

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "openssl/ssl.h"
# include "openssl/bn.h"
# include "openssl/bio.h"
# include "openssl/evp.h"
# include "openssl/pem.h"
# include "openssl/x509.h"
# include "openssl/rsa.h"

enum e_error_code {
	ER_USAGE,
	ER_FILE,
	ER_KEY,
	ER_MEM,
	ER_READ
};

struct s_error_info {
	enum e_error_code	code;
	const char			*message;
};

extern struct s_error_info	g_error_list[];

typedef struct s_corsair {
	RSA		*rsa1;
	BIGNUM	*n1;
	BIGNUM	*q1;
	RSA		*rsa2;
	BIGNUM	*n2;
	BIGNUM	*q2;
	int		file;
	BN_CTX	*ctx;
	RSA		*private;
	BIO		*bioprint;
	BIGNUM	*one;
	BIGNUM	*p;
	BIGNUM	*totient;
	BIGNUM	*fi1;
	BIGNUM	*fi2;
	BIGNUM	*e;
	BIGNUM	*d;
}	t_corsair;

RSA		*ft_get_rsa(const char *file);
void	ft_calc(t_corsair *corsair);
void	ft_decrypt_print(t_corsair *corsair);
void	ft_error(enum e_error_code er, const char *msg);

#endif
