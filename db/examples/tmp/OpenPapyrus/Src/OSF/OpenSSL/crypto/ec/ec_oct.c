/*
 * Copyright 2011-2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

/* ====================================================================
 * Copyright 2002 Sun Microsystems, Inc. ALL RIGHTS RESERVED.
 * Binary polynomial ECC support in OpenSSL originally developed by
 * SUN MICROSYSTEMS, INC., and contributed to the OpenSSL project.
 */
#include "internal/cryptlib.h"
#pragma hdrstop
//#include <openssl/opensslv.h>
#include "ec_lcl.h"

int EC_POINT_set_compressed_coordinates_GFp(const EC_GROUP * group, EC_POINT * point, const BIGNUM * x, int y_bit, BN_CTX * ctx)
{
	if(group->meth->point_set_compressed_coordinates == 0 && !(group->meth->flags & EC_FLAGS_DEFAULT_OCT)) {
		ECerr(EC_F_EC_POINT_SET_COMPRESSED_COORDINATES_GFP, ERR_R_SHOULD_NOT_HAVE_BEEN_CALLED);
		return 0;
	}
	if(group->meth != point->meth) {
		ECerr(EC_F_EC_POINT_SET_COMPRESSED_COORDINATES_GFP, EC_R_INCOMPATIBLE_OBJECTS);
		return 0;
	}
	if(group->meth->flags & EC_FLAGS_DEFAULT_OCT) {
		if(group->meth->field_type == NID_X9_62_prime_field)
			return ec_GFp_simple_set_compressed_coordinates(group, point, x, y_bit, ctx);
		else
#ifdef OPENSSL_NO_EC2M
		{
			ECerr(EC_F_EC_POINT_SET_COMPRESSED_COORDINATES_GFP, EC_R_GF2M_NOT_SUPPORTED);
			return 0;
		}
#else
			return ec_GF2m_simple_set_compressed_coordinates(group, point, x, y_bit, ctx);
#endif
	}
	return group->meth->point_set_compressed_coordinates(group, point, x, y_bit, ctx);
}

int EC_POINT_set_affine_coordinates(const EC_GROUP *group, EC_POINT *point, const BIGNUM *x, const BIGNUM *y, BN_CTX *ctx) // @sobolev @v10.6.3
{
	if(group->meth->point_set_affine_coordinates == NULL) {
		ECerr(EC_F_EC_POINT_SET_AFFINE_COORDINATES, ERR_R_SHOULD_NOT_HAVE_BEEN_CALLED);
		return 0;
	}
	if(!ec_point_is_compat(point, group)) {
		ECerr(EC_F_EC_POINT_SET_AFFINE_COORDINATES, EC_R_INCOMPATIBLE_OBJECTS);
		return 0;
	}
	if(!group->meth->point_set_affine_coordinates(group, point, x, y, ctx))
		return 0;
	if(EC_POINT_is_on_curve(group, point, ctx) <= 0) {
		ECerr(EC_F_EC_POINT_SET_AFFINE_COORDINATES, EC_R_POINT_IS_NOT_ON_CURVE);
		return 0;
	}
	return 1;
}

#ifndef OPENSSL_NO_EC2M
int EC_POINT_set_compressed_coordinates_GF2m(const EC_GROUP * group, EC_POINT * point, const BIGNUM * x, int y_bit, BN_CTX * ctx)
{
	if(group->meth->point_set_compressed_coordinates == 0 && !(group->meth->flags & EC_FLAGS_DEFAULT_OCT)) {
		ECerr(EC_F_EC_POINT_SET_COMPRESSED_COORDINATES_GF2M, ERR_R_SHOULD_NOT_HAVE_BEEN_CALLED);
		return 0;
	}
	if(group->meth != point->meth) {
		ECerr(EC_F_EC_POINT_SET_COMPRESSED_COORDINATES_GF2M, EC_R_INCOMPATIBLE_OBJECTS);
		return 0;
	}
	if(group->meth->flags & EC_FLAGS_DEFAULT_OCT) {
		if(group->meth->field_type == NID_X9_62_prime_field)
			return ec_GFp_simple_set_compressed_coordinates(group, point, x, y_bit, ctx);
		else
			return ec_GF2m_simple_set_compressed_coordinates(group, point, x, y_bit, ctx);
	}
	return group->meth->point_set_compressed_coordinates(group, point, x, y_bit, ctx);
}
#endif

int EC_POINT_get_affine_coordinates(const EC_GROUP *group, const EC_POINT *point, BIGNUM *x, BIGNUM *y, BN_CTX *ctx) // @sobolev @v10.6.3
{
    if(group->meth->point_get_affine_coordinates == NULL) {
        ECerr(EC_F_EC_POINT_GET_AFFINE_COORDINATES, ERR_R_SHOULD_NOT_HAVE_BEEN_CALLED);
        return 0;
    }
    if(!ec_point_is_compat(point, group)) {
        ECerr(EC_F_EC_POINT_GET_AFFINE_COORDINATES, EC_R_INCOMPATIBLE_OBJECTS);
        return 0;
    }
    if(EC_POINT_is_at_infinity(group, point)) {
        ECerr(EC_F_EC_POINT_GET_AFFINE_COORDINATES, EC_R_POINT_AT_INFINITY);
        return 0;
    }
    return group->meth->point_get_affine_coordinates(group, point, x, y, ctx);
}

size_t EC_POINT_point2oct(const EC_GROUP * group, const EC_POINT * point, point_conversion_form_t form, uchar * buf, size_t len, BN_CTX * ctx)
{
	if(group->meth->point2oct == 0 && !(group->meth->flags & EC_FLAGS_DEFAULT_OCT)) {
		ECerr(EC_F_EC_POINT_POINT2OCT, ERR_R_SHOULD_NOT_HAVE_BEEN_CALLED);
		return 0;
	}
	if(group->meth != point->meth) {
		ECerr(EC_F_EC_POINT_POINT2OCT, EC_R_INCOMPATIBLE_OBJECTS);
		return 0;
	}
	if(group->meth->flags & EC_FLAGS_DEFAULT_OCT) {
		if(group->meth->field_type == NID_X9_62_prime_field)
			return ec_GFp_simple_point2oct(group, point, form, buf, len, ctx);
		else
#ifdef OPENSSL_NO_EC2M
		{
			ECerr(EC_F_EC_POINT_POINT2OCT, EC_R_GF2M_NOT_SUPPORTED);
			return 0;
		}
#else
			return ec_GF2m_simple_point2oct(group, point,
			    form, buf, len, ctx);
#endif
	}

	return group->meth->point2oct(group, point, form, buf, len, ctx);
}

int EC_POINT_oct2point(const EC_GROUP * group, EC_POINT * point,
    const uchar * buf, size_t len, BN_CTX * ctx)
{
	if(group->meth->oct2point == 0
	    && !(group->meth->flags & EC_FLAGS_DEFAULT_OCT)) {
		ECerr(EC_F_EC_POINT_OCT2POINT, ERR_R_SHOULD_NOT_HAVE_BEEN_CALLED);
		return 0;
	}
	if(group->meth != point->meth) {
		ECerr(EC_F_EC_POINT_OCT2POINT, EC_R_INCOMPATIBLE_OBJECTS);
		return 0;
	}
	if(group->meth->flags & EC_FLAGS_DEFAULT_OCT) {
		if(group->meth->field_type == NID_X9_62_prime_field)
			return ec_GFp_simple_oct2point(group, point, buf, len, ctx);
		else
#ifdef OPENSSL_NO_EC2M
		{
			ECerr(EC_F_EC_POINT_OCT2POINT, EC_R_GF2M_NOT_SUPPORTED);
			return 0;
		}
#else
			return ec_GF2m_simple_oct2point(group, point, buf, len, ctx);
#endif
	}
	return group->meth->oct2point(group, point, buf, len, ctx);
}

size_t EC_POINT_point2buf(const EC_GROUP * group, const EC_POINT * point,
    point_conversion_form_t form,
    uchar ** pbuf, BN_CTX * ctx)
{
	size_t len;
	uchar * buf;
	len = EC_POINT_point2oct(group, point, form, NULL, 0, 0);
	if(len == 0)
		return 0;
	buf = (uchar *)OPENSSL_malloc(len);
	if(!buf)
		return 0;
	len = EC_POINT_point2oct(group, point, form, buf, len, ctx);
	if(len == 0) {
		OPENSSL_free(buf);
		return 0;
	}
	*pbuf = buf;
	return len;
}
