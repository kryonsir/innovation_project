#include "sm3_self.h"

// 循环左移函数
uint32_t left_rotate(uint32_t x, uint32_t n) {
    return (x << n) | (x >> (32 - n));
}

// 布尔函数 FF
inline uint32_t FF(uint32_t j, uint32_t x, uint32_t y, uint32_t z) {
    uint32_t ret = 0;
    if (j >= 0 && j <= 15)
        ret = x ^ y ^ z;
    else if (j >= 16 && j <= 63)
        ret = (x & y) | (x & z) | (y & z);
    return ret;
}


// 布尔函数 GG
inline uint32_t GG(uint32_t j, uint32_t x, uint32_t y, uint32_t z) {
    uint32_t ret = 0;
    if (j >= 0 && j <= 15)
        ret = x ^ y ^ z;
    else if (j >= 16 && j <= 63)
        ret = (x & y) | ((~x) & z);
    return ret;
}

// P0函数
inline uint32_t P0(uint32_t x) {
    return x ^ left_rotate(x, 9) ^ left_rotate(x, 17);
}

// P1函数
inline uint32_t P1(uint32_t x) {
    return x ^ left_rotate(x, 15) ^ left_rotate(x, 23);
}





// SM3 哈希函数
void sm3_hash(const uint8_t* message, size_t message_len, uint8_t* hash) {
    // 初始化IV
    uint32_t IV[8] = {
        0x7380166f, 0x4914b2b9, 0x172442d7, 0xda8a0600,
        0xa96f30bc, 0x163138aa, 0xe38dee4d, 0xb0fb0e4e
    };

    // 初始化T
    uint32_t T[64];
    int i = 0;
    for (i = 0; i < 16; i++)
        T[i] = 0x79cc4519;
    for (i = 16; i < 64; i++)
        T[i] = 0x7a879d8a;


    // 对消息进行填充
    size_t new_len = (message_len + 1) / 64 * 64 + 64;
    uint8_t* padded_message = (uint8_t*)malloc(new_len);
    memcpy(padded_message, message, message_len);
    padded_message[message_len] = 0x80;
    memset(padded_message + message_len + 1, 0, new_len - message_len - 9);
    uint64_t bit_len = message_len * 8;
    uint64_t reversed_bit_len = 0;

    for (int i = 0; i < 8; i++) {
        reversed_bit_len |= ((bit_len >> (i * 8)) & 0xFF) << ((7 - i) * 8);
    }

    memcpy(padded_message + new_len - 8, &reversed_bit_len, 8);

    // 迭代压缩函数
    for (size_t i = 0; i < new_len / 64; ++i) {
        uint32_t W[68], W1[64];
        uint32_t A, B, C, D, E, F, G, H, SS1, SS2, TT1, TT2;

        // 消息扩展
        for (size_t j = 0; j < 16; ++j) {
            W[j] = ((uint32_t)padded_message[i * 64 + 4 * j] << 24)
                | ((uint32_t)padded_message[i * 64 + 4 * j + 1] << 16)
                | ((uint32_t)padded_message[i * 64 + 4 * j + 2] << 8)
                | (uint32_t)padded_message[i * 64 + 4 * j + 3];
        }

        for (size_t j = 16; j < 68; ++j) {
            W[j] = P1(W[j - 16] ^ W[j - 9] ^ left_rotate(W[j - 3], 15)) ^ left_rotate(W[j - 13], 7) ^ W[j - 6];
        }
        for (size_t j = 0; j < 64; ++j) {
            W1[j] = W[j] ^ W[j + 4];
        }

        // 压缩函数
        A = IV[0]; B = IV[1]; C = IV[2]; D = IV[3];
        E = IV[4]; F = IV[5]; G = IV[6]; H = IV[7];
        for (size_t j = 0; j < 64; ++j) {
            SS1 = left_rotate((left_rotate(A, 12) + E + left_rotate(T[j], j)), 7);
            SS2 = SS1 ^ left_rotate(A, 12);
            TT1 = FF(j, A, B, C) + D + SS2 + W1[j];
            TT2 = GG(j, E, F, G) + H + SS1 + W[j];
            D = C;
            C = left_rotate(B, 9);
            B = A;
            A = TT1;
            H = G;
            G = left_rotate(F, 19);
            F = E;
            E = P0(TT2);
        }
        IV[0] ^= A; IV[1] ^= B; IV[2] ^= C; IV[3] ^= D;
        IV[4] ^= E; IV[5] ^= F; IV[6] ^= G; IV[7] ^= H;
    }

    // 输出哈希值
    for (size_t i = 0; i < 8; ++i) {
        hash[i * 4 + 0] = (IV[i] >> 24) & 0xFF;
        hash[i * 4 + 1] = (IV[i] >> 16) & 0xFF;
        hash[i * 4 + 2] = (IV[i] >> 8) & 0xFF;
        hash[i * 4 + 3] = IV[i] & 0xFF;
    }

    free(padded_message);
}
