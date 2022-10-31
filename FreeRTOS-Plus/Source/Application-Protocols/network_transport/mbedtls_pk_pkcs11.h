/*
 * FreeRTOS V202112.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

#ifndef MBEDTLS_PK_PKCS11_H
#define MBEDTLS_PK_PKCS11_H

#include <string.h>
#include "mbedtls/pk.h"
#include "core_pkcs11_config.h"
#include "core_pkcs11.h"

mbedtls_pk_info_t mbedtls_pkcs11_pk_ecdsa;
mbedtls_pk_info_t mbedtls_pkcs11_pk_rsa;

/*-----------------------------------------------------------*/

CK_RV xPKCS11_initMbedtlsPkContext( mbedtls_pk_context * pxMbedtlsPkCtx,
                                    CK_SESSION_HANDLE xSessionHandle,
                                    CK_OBJECT_HANDLE xPkHandle );

int lPKCS11PkMbedtlsCloseSessionAndFree( mbedtls_pk_context * pxMbedtlsPkCtx );

int lPKCS11RandomCallback( void * pvCtx,
                           unsigned char * pucOutput,
                           size_t uxLen );

#endif /* MBEDTLS_PK_PKCS11_H */
