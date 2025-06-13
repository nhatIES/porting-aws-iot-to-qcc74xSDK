/*
 * FreeRTOS PKCS #11 PAL for QCC74x SDK
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file core_pkcs11_pal.c
 * @brief PKCS11 Platform Abstraction Layer for QCC74x SDK.
 */

/* FreeRTOS includes */
#include <FreeRTOS.h>
#include <task.h>
#include "semphr.h"

/* PKCS#11 Interface includes */
#include "iot_crypto.h"
#include "core_pkcs11.h"
#include "core_pkcs11_pal.h"
#include "core_pkcs11_config.h"

/* C runtime includes */
#include <stdio.h>
#include <string.h>

/* QCC74x SDK logging */
#define LIBRARY_LOG_NAME "PKCS11_PAL"
#define LIBRARY_LOG_LEVEL LOG_INFO
#include "logging_stack.h"

/* File name definitions for key storage */
#define pkcs11palFILE_NAME_CLIENT_CERTIFICATE    "P11_Cert"
#define pkcs11palFILE_NAME_KEY                   "P11_Key"
#define pkcs11palFILE_CODE_SIGN_PUBLIC_KEY       "P11_CSK"
#define pkcs11palFILE_JITP_CERTIFICATE           "P11_JITP"
#define pkcs11palFILE_NAME_CLAIM_CERTIFICATE     "P11_Claim_Cert"
#define pkcs11palFILE_NAME_CLAIM_KEY             "P11_Claim_Key"

enum eObjectHandles
{
    eInvalidHandle = 0, /* According to PKCS #11 spec, 0 is never a valid object handle. */
    eAwsDevicePrivateKey = 1,
    eAwsDevicePublicKey,
    eAwsDeviceCertificate,
    eAwsCodeSigningKey,
    eAwsJITPCertificate,
    eAwsClaimCertificate,
    eAwsClaimPrivateKey
};

static StaticSemaphore_t pkcs_pal_lock_buffer;
static SemaphoreHandle_t pkcs_pal_lock;

/*-----------------------------------------------------------*/

static void __attribute__((constructor)) pkcs_pal_lock_init (void)
{
    pkcs_pal_lock = xSemaphoreCreateMutexStatic(&pkcs_pal_lock_buffer);
}

static void initialize_storage_partition()
{
    static bool storage_inited = false;

    xSemaphoreTake(pkcs_pal_lock, portMAX_DELAY);
    if (storage_inited == true) {
        xSemaphoreGive(pkcs_pal_lock);
        return;
    }

    LOG_I("[PKCS11_PAL] Initializing QCC74x storage partition (stub)");
    
    // TODO: Initialize QCC74x flash/storage subsystem
    // This might involve initializing flash sectors, wear leveling, etc.
    
    storage_inited = true;
    xSemaphoreGive(pkcs_pal_lock);
}

/* Converts a label to its respective filename and handle. */
void prvLabelToFilenameHandle( uint8_t * pcLabel,
                               char ** pcFileName,
                               CK_OBJECT_HANDLE_PTR pHandle )
{
    if( pcLabel != NULL )
    {
        /* Translate from the PKCS#11 label to local storage file name. */
        if( 0 == memcmp( pcLabel,
                         pkcs11configLABEL_DEVICE_CERTIFICATE_FOR_TLS,
                         strlen( (char*)pkcs11configLABEL_DEVICE_CERTIFICATE_FOR_TLS ) ) )
        {
            *pcFileName = pkcs11palFILE_NAME_CLIENT_CERTIFICATE;
            *pHandle = eAwsDeviceCertificate;
        }
        else if( 0 == memcmp( pcLabel,
                              pkcs11configLABEL_DEVICE_PRIVATE_KEY_FOR_TLS,
                              strlen( (char*)pkcs11configLABEL_DEVICE_PRIVATE_KEY_FOR_TLS ) ) )
        {
            *pcFileName = pkcs11palFILE_NAME_KEY;
            *pHandle = eAwsDevicePrivateKey;
        }
        else if( 0 == memcmp( pcLabel,
                              pkcs11configLABEL_DEVICE_PUBLIC_KEY_FOR_TLS,
                              strlen( (char*)pkcs11configLABEL_DEVICE_PUBLIC_KEY_FOR_TLS ) ) )
        {
            *pcFileName = pkcs11palFILE_NAME_KEY;
            *pHandle = eAwsDevicePublicKey;
        }
        else if( 0 == memcmp( pcLabel,
                              pkcs11configLABEL_CODE_VERIFICATION_KEY,
                              strlen( (char*)pkcs11configLABEL_CODE_VERIFICATION_KEY ) ) )
        {
            *pcFileName = pkcs11palFILE_CODE_SIGN_PUBLIC_KEY;
            *pHandle = eAwsCodeSigningKey;
        }
        else if( 0 == memcmp( pcLabel,
                              pkcs11configLABEL_JITP_CERTIFICATE,
                              strlen( (char*)pkcs11configLABEL_JITP_CERTIFICATE ) ) )
        {
            *pcFileName = pkcs11palFILE_JITP_CERTIFICATE;
            *pHandle = eAwsJITPCertificate;
        }
        else if( 0 == memcmp( pcLabel,
                              pkcs11configLABEL_CLAIM_CERTIFICATE,
                              strlen( (char*)pkcs11configLABEL_CLAIM_CERTIFICATE ) ) )
        {
            *pcFileName = pkcs11palFILE_NAME_CLAIM_CERTIFICATE;
            *pHandle = eAwsClaimCertificate;
        }
        else if( 0 == memcmp( pcLabel,
                              pkcs11configLABEL_CLAIM_PRIVATE_KEY,
                              strlen( (char*)pkcs11configLABEL_CLAIM_PRIVATE_KEY ) ) )
        {
            *pcFileName = pkcs11palFILE_NAME_CLAIM_KEY;
            *pHandle = eAwsClaimPrivateKey;
        }
        else
        {
            *pcFileName = NULL;
            *pHandle = eInvalidHandle;
        }
    }
}

CK_RV PKCS11_PAL_Initialize( void )
{
    LOG_I("[PKCS11_PAL] Initializing PKCS11 PAL (stub)");
    
    // TODO: Initialize QCC74x crypto subsystem
    // This might involve enabling crypto peripherals, setting up secure elements, etc.
    CRYPTO_Init();
    
    return CKR_OK;
}

/**
 * @brief Writes a file to local storage.
 *
 * Port-specific file write for cryptographic information.
 *
 * @param[in] pxLabel       Label of the object to be saved.
 * @param[in] pucData       Data buffer to be written to file
 * @param[in] ulDataSize    Size (in bytes) of data to be saved.
 *
 * @return The file handle of the object that was stored.
 */
CK_OBJECT_HANDLE PKCS11_PAL_SaveObject( CK_ATTRIBUTE_PTR pxLabel,
                                        CK_BYTE_PTR pucData,
                                        CK_ULONG ulDataSize )
{
    initialize_storage_partition();

    CK_OBJECT_HANDLE xHandle = eInvalidHandle;
    char * pcFileName = NULL;

    /* Translate from the PKCS#11 label to local storage file name. */
    prvLabelToFilenameHandle( pxLabel->pValue,
                              &pcFileName,
                              &xHandle );

    LOG_D("[PKCS11_PAL] Writing file %s, %lu bytes (stub)", pcFileName ? pcFileName : "NULL", ulDataSize);

    if (pcFileName == NULL) {
        LOG_E("[PKCS11_PAL] Invalid file name for label");
        return eInvalidHandle;
    }

    // TODO: Implement actual file write to QCC74x flash/storage
    // This might involve:
    // - Writing to dedicated flash sectors
    // - Using wear leveling filesystem
    // - Encrypting sensitive data before storage
    
    LOG_I("[PKCS11_PAL] Object saved successfully (stub): %s", pcFileName);
    return xHandle;
}

/**
 * @brief Translates a PKCS #11 label into an object handle.
 *
 * Port-specific object handle retrieval.
 *
 * @param[in] pxLabel         Pointer to the label of the object
 *                           who's handle should be found.
 * @param[in] usLength       The length of the label, in bytes.
 *
 * @return The object handle if operation was successful.
 * Returns eInvalidHandle if unsuccessful.
 */
CK_OBJECT_HANDLE PKCS11_PAL_FindObject( CK_BYTE_PTR pxLabel,
                                        CK_ULONG usLength )
{
    CK_OBJECT_HANDLE xHandle = eInvalidHandle;
    char * pcFileName = NULL;
    initialize_storage_partition();

    /* Translate from the PKCS#11 label to local storage file name. */
    prvLabelToFilenameHandle( pxLabel,
                              &pcFileName,
                              &xHandle );

    if( pcFileName != NULL )
    {
        LOG_D("[PKCS11_PAL] Finding file %s (stub)", pcFileName);
        
        // TODO: Implement actual file search in QCC74x storage
        // For now, simulate file not found
        LOG_W("[PKCS11_PAL] File not found in storage (stub): %s", pcFileName);
        xHandle = eInvalidHandle;
    }

    return xHandle;
}

/*-----------------------------------------------------------*/

/**
 * @brief Gets the value of an object in storage, by handle.
 *
 * Port-specific file access for cryptographic information.
 *
 * This call dynamically allocates the buffer which object value
 * data is copied into.  PKCS11_PAL_GetObjectValueCleanup()
 * should be called after each use to free the dynamically allocated
 * buffer.
 *
 * @sa PKCS11_PAL_GetObjectValueCleanup
 *
 * @param[in] xHandle       The object handle.
 * @param[out] ppucData     Pointer to buffer for file data.
 * @param[out] pulDataSize  Size (in bytes) of data located in file.
 * @param[out] pIsPrivate   Boolean indicating if value is private (CK_TRUE)
 *                          or exportable (CK_FALSE)
 *
 * @return CKR_OK if operation was successful.  CKR_KEY_HANDLE_INVALID if
 * no such object handle was found, CKR_DEVICE_MEMORY if memory for
 * buffer could not be allocated, CKR_FUNCTION_FAILED for device driver
 * error.
 */
CK_RV PKCS11_PAL_GetObjectValue( CK_OBJECT_HANDLE xHandle,
                                      CK_BYTE_PTR * ppucData,
                                      CK_ULONG_PTR pulDataSize,
                                      CK_BBOOL * pIsPrivate )
{
    initialize_storage_partition();

    char * pcFileName = NULL;
    CK_RV ulReturn = CKR_OK;

    if( xHandle == eAwsDeviceCertificate )
    {
        pcFileName = pkcs11palFILE_NAME_CLIENT_CERTIFICATE;
        *pIsPrivate = CK_FALSE;
    }
    else if( xHandle == eAwsDevicePrivateKey )
    {
        pcFileName = pkcs11palFILE_NAME_KEY;
        *pIsPrivate = CK_TRUE;
    }
    else if( xHandle == eAwsDevicePublicKey )
    {
        /* Public and private key are stored together in same file. */
        pcFileName = pkcs11palFILE_NAME_KEY;
        *pIsPrivate = CK_FALSE;
    }
    else if( xHandle == eAwsCodeSigningKey )
    {
        pcFileName = pkcs11palFILE_CODE_SIGN_PUBLIC_KEY;
        *pIsPrivate = CK_FALSE;
    }
    else if( xHandle == eAwsJITPCertificate )
    {
        pcFileName = pkcs11palFILE_JITP_CERTIFICATE;
        *pIsPrivate = CK_FALSE;
    }
    else if( xHandle == eAwsClaimCertificate )
    {
        pcFileName = pkcs11palFILE_NAME_CLAIM_CERTIFICATE;
        *pIsPrivate = CK_FALSE;
    }
    else if( xHandle == eAwsClaimPrivateKey )
    {
        pcFileName = pkcs11palFILE_NAME_CLAIM_KEY;
        *pIsPrivate = CK_TRUE;
    }
    else
    {
        ulReturn = CKR_OBJECT_HANDLE_INVALID;
    }

    if (ulReturn == CKR_OK && pcFileName != NULL)
    {
        LOG_D("[PKCS11_PAL] Reading file %s (stub)", pcFileName);
        
        // TODO: Implement actual file read from QCC74x storage
        // For now, simulate file not found
        LOG_W("[PKCS11_PAL] Object not found in storage (stub): %s", pcFileName);
        ulReturn = CKR_OBJECT_HANDLE_INVALID;
    }

    return ulReturn;
}

/*-----------------------------------------------------------*/

/**
 * @brief Cleanup after PKCS11_PAL_GetObjectValue().
 *
 * @param[in] pucData       The buffer to free.
 *                          (*ppucData from PKCS11_PAL_GetObjectValue())
 * @param[in] ulDataSize    The length of the buffer to free.
 *                          (*pulDataSize from PKCS11_PAL_GetObjectValue())
 */
void PKCS11_PAL_GetObjectValueCleanup( CK_BYTE_PTR pucData,
                                       CK_ULONG ulDataSize )
{
    /* Unused parameters. */
    ( void ) ulDataSize;

    if( NULL != pucData )
    {
        vPortFree( pucData );
    }
}

/*-----------------------------------------------------------*/

/* Convert from object handle to label for deletion. */
void prvHandleToLabel( char ** pcLabel,
                       CK_OBJECT_HANDLE xHandle )
{
    if( xHandle == eAwsDeviceCertificate )
    {
        *pcLabel = ( char * ) pkcs11configLABEL_DEVICE_CERTIFICATE_FOR_TLS;
    }
    else if( xHandle == eAwsDevicePrivateKey )
    {
        *pcLabel = ( char * ) pkcs11configLABEL_DEVICE_PRIVATE_KEY_FOR_TLS;
    }
    else if( xHandle == eAwsDevicePublicKey )
    {
        *pcLabel = ( char * ) pkcs11configLABEL_DEVICE_PUBLIC_KEY_FOR_TLS;
    }
    else if( xHandle == eAwsCodeSigningKey )
    {
        *pcLabel = ( char * ) pkcs11configLABEL_CODE_VERIFICATION_KEY;
    }
    else if( xHandle == eAwsJITPCertificate )
    {
        *pcLabel = ( char * ) pkcs11configLABEL_JITP_CERTIFICATE;
    }
    else if( xHandle == eAwsClaimCertificate )
    {
        *pcLabel = ( char * ) pkcs11configLABEL_CLAIM_CERTIFICATE;
    }
    else if( xHandle == eAwsClaimPrivateKey )
    {
        *pcLabel = ( char * ) pkcs11configLABEL_CLAIM_PRIVATE_KEY;
    }
    else
    {
        *pcLabel = NULL;
    }
}

/**
 * @brief Delete an object from NVS.
 *
 * @param[in] xHandle       Handle of the object to delete.
 *
 * @return CKR_OK if successful, CKR_FUNCTION_FAILED if failed.
 */
CK_RV PKCS11_PAL_DestroyObject( CK_OBJECT_HANDLE xHandle )
{
    initialize_storage_partition();
    
    char * pcLabel = NULL;
    
    prvHandleToLabel( &pcLabel, xHandle );
    
    if( pcLabel != NULL )
    {
        LOG_I("[PKCS11_PAL] Destroying object: %s (stub)", pcLabel);
        
        // TODO: Implement actual file deletion from QCC74x storage
        // This might involve:
        // - Securely erasing flash sectors
        // - Updating filesystem metadata
        // - Invalidating cached entries
        
        LOG_I("[PKCS11_PAL] Object destroyed successfully (stub)");
        return CKR_OK;
    }
    else
    {
        LOG_E("[PKCS11_PAL] Invalid handle for destruction: %lu", xHandle);
        return CKR_OBJECT_HANDLE_INVALID;
    }
}
