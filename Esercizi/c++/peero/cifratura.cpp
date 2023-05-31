#include <iostream>
#include <string>
#include <iomanip>
#include <openssl/aes.h>

using namespace std;

// Funzione per cifrare un messaggio con AES-256
void encryptAES(string plaintext, string key, string iv) {
    // Converti la chiave e l'IV da stringhe a array di byte
    unsigned char aes_key[AES_BLOCK_SIZE * 8];
    unsigned char aes_iv[AES_BLOCK_SIZE];
    memcpy(aes_key, key.c_str(), key.size());
    memcpy(aes_iv, iv.c_str(), iv.size());

    // Crea il contesto di cifratura
    AES_KEY aes;
    AES_set_encrypt_key(aes_key, 256, &aes);

    // Aggiungi padding al messaggio per raggiungere una lunghezza multipla di 16 byte
    int plaintext_len = plaintext.size();
    int padded_len = plaintext_len + (AES_BLOCK_SIZE - plaintext_len % AES_BLOCK_SIZE);
    unsigned char padded_plaintext[padded_len];
    memcpy(padded_plaintext, plaintext.c_str(), plaintext_len);
    memset(padded_plaintext + plaintext_len, AES_BLOCK_SIZE - plaintext_len % AES_BLOCK_SIZE, AES_BLOCK_SIZE - plaintext_len % AES_BLOCK_SIZE);

    // Cifra il messaggio
    unsigned char ciphertext[padded_len];
    AES_cbc_encrypt(padded_plaintext, ciphertext, padded_len, &aes, aes_iv, AES_ENCRYPT);

    // Stampa il messaggio cifrato in esadecimale
    cout << "Ciphertext: ";
    for (int i = 0; i < padded_len; i++) {
        cout << hex << setfill('0') << setw(2) << (int) ciphertext[i];
    }
    cout << endl;
}

// Funzione per decifrare un messaggio con AES-256
void decryptAES(string ciphertext, string key, string iv) {
    // Converti la chiave e l'IV da stringhe a array di byte
    unsigned char aes_key[AES_BLOCK_SIZE * 8];
    unsigned char aes_iv[AES_BLOCK_SIZE];
    memcpy(aes_key, key.c_str(), key.size());
    memcpy(aes_iv, iv.c_str(), iv.size());

    // Crea il contesto di decifratura
    AES_KEY aes;
    AES_set_decrypt_key(aes_key, 256, &aes);

    // Converti il messaggio cifrato da esadecimale ad array di byte
    int ciphertext_len = ciphertext.size();
    unsigned char ciphertext_bytes[ciphertext_len / 2];
    for (int i = 0; i < ciphertext_len; i += 2) {
        ciphertext_bytes[i / 2] = strtoul(ciphertext.substr(i, 2).c_str(), nullptr, 16);
    }

    // Decifra il messaggio
    unsigned char plaintext[ciphertext_len / 2];
    AES_cbc_encrypt(ciphertext_bytes, plaintext, ciphertext_len / 2, &aes, aes_iv, AES_DECRYPT);

    // Rimuovi il padding dal messaggio
    int padding = plaintext[ciphertext_len / 2 - 1];
    int plaintext_len = ciphertext_len / 2 - padding;
    unsigned char unpadded_plaintext[plaintext_len];
    memcpy(unpadded_plaintext, plaintext, plaintext_len);

    // Stampa il messaggio decifrato
