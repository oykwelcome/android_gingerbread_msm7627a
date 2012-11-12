/**
 * @file
 * Class for encapsulating message encryption and decryption operations.
 */

/******************************************************************************
 * Copyright 2010-2011, Qualcomm Innovation Center, Inc.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 ******************************************************************************/
#ifndef _ALLJOYN_CRYPTO_H
#define _ALLJOYN_CRYPTO_H

#ifndef __cplusplus
#error Only include AllJoynCrypto.h in C++ code.
#endif

#include <qcc/platform.h>
#include <qcc/KeyBlob.h>

#include <alljoyn/Message.h>

#include <Status.h>


namespace ajn {

/**
 * Class for encapsulating AllJoyn message encryption and decryption operations.
 */
class Crypto {

  public:

    /**
     * Encrypt a marshaled message inplace using the key blob provided and the encryption algorithm
     * and key stored in the key blob.
     *
     * @param keyBlob         The key blob containing the key for the encryption operation.
     * @param msg             The message data to be encrypted. The data buffer must be large enough to handle
     *                        the expansion specified in the ExpansionBytes member variable.
     * @param hdrLen          The length of the header part of the message that will not be encrypted.
     * @param bodyLen[in/out] On input the size of the plaintext body, on output the size of the
     *                        encrypted body.
     * @param nonce           A nonce.
     *
     * @return - ER_OK if the data was succesfully encrypted.
     *         - ER_BUS_KEYBLOB_OP_INVALID if the key blob cannot be used for encryption.
     *         - Other errors if the arguments are invalid.
     */
    static QStatus Encrypt(const qcc::KeyBlob& keyBlob, uint8_t* msg, size_t hdrLen, size_t& bodyLen, const qcc::KeyBlob& nonce);

    /**
     * Decrypt and authenticate marshaled message inplace using the key blob provided and the
     * decryption algorithm and key stored in the key blob.
     *
     * @param keyBlob         The key blob containing the key for the decryption operation.
     * @param msg             The message data to be decrypted.
     * @param hdrLen          The length of the non-encrypted header part of the message.
     * @param bodyLen[in/out] On input the size of the crypttext body, on output the size of the
     *                        decrypted body.
     * @param nonce           A nonce.
     *
     * @return - ER_OK if the data was succesfully decrypted.
     *         - ER_BUS_KEYBLOB_OP_INVALID if the key blob cannot be used for decryption.
     *         - Other errors if the arguments are invalid.
     */
    static QStatus Decrypt(const qcc::KeyBlob& keyBlob, uint8_t* msg, size_t hdrLen, size_t& bodyLen, const qcc::KeyBlob& nonce);

    /**
     * Compute a SHA1 hash over the header fields and return the result in a key blob.
     *
     * @param hdrFields   The header fields to compute a hash from.
     * @param keyBlob     The key blob to return the hash.
     *
     * @return ER_OK if the hash was succesfully computed.
     */
    static QStatus HashHeaderFields(const HeaderFields& hdrFields, qcc::KeyBlob& keyBlob);

    /**
     * The number of bytes that encryption adds to the length of the message.
     */
    static const size_t ExpansionBytes;

    /**
     * Size of the nonce used for message encryption.
     */
    static const size_t NonceBytes;

};


}

#endif