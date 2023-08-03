#include "sm3_self.h"
#include<iostream>
using namespace std;
void pr(uint8_t* msg)
{
    for (size_t i = 0; i < 32; ++i) {
        printf("%02x ", msg[i]);
    }
    printf("\n");
}

void pr_msg(uint8_t* msg)
{
    for (size_t i = 0; i < 128; ++i) {
        printf("%02x ", msg[i]);
    }
    printf("\n");
}

#define T(iv,i) iv[4 * i] << 24 | iv[4 * i + 1] << 16 | iv[4 * i + 2] << 8 | iv[4 * i + 3]

void padding(uint8_t message[],uint8_t* padded_message)
{
    // 对消息进行填充
    size_t message_len = strlen((char*)message);
    size_t new_len = (message_len + 1) / 64 * 64 + 64;
    padded_message = (uint8_t*)malloc(new_len);
    memcpy(padded_message, message, message_len);
    padded_message[message_len] = 0x80;
    memset(padded_message + message_len + 1, 0, new_len - message_len - 9);
    uint64_t bit_len = message_len * 8;
    uint64_t reversed_bit_len = 0;

    for (int i = 0; i < 8; i++) {
        reversed_bit_len |= ((bit_len >> (i * 8)) & 0xFF) << ((7 - i) * 8);
    }

    memcpy(padded_message + new_len - 8, &reversed_bit_len, 8);

}

int main()
{
    // 初始化IV
uint32_t IV[8] = {
    0x7380166f, 0x4914b2b9, 0x172442d7, 0xda8a0600,
    0xa96f30bc, 0x163138aa, 0xe38dee4d, 0xb0fb0e4e
};

	uint8_t secret[] = "secret";
    pr(secret);
    uint8_t msg[1024];

    // 对消息进行填充
    size_t message_len = strlen((char*)secret);
    size_t new_len = (message_len + 1) / 64 * 64 + 64;
    memcpy(msg, secret, message_len);
    msg[message_len] = 0x80;
    memset(msg + message_len + 1, 0, new_len - message_len - 9);
    uint64_t bit_len = message_len * 8;
    uint64_t reversed_bit_len = 0;

    for (int i = 0; i < 8; i++) {
        reversed_bit_len |= ((bit_len >> (i * 8)) & 0xFF) << ((7 - i) * 8);
    }

    memcpy(msg + new_len - 8, &reversed_bit_len, 8);

    pr_msg(msg);


	uint8_t result[32];
    cout << "hello\n";
    sm3_hash(msg, 6, result,IV);
    pr(result);
    uint8_t message[32] = "message";
    memcpy(msg + 64, message, 7);
    uint32_t ivv[8];
    for (int i = 0; i < 8; i++)
    {
        ivv[i] = T(result, i);
    }
    sm3_hash_ext(message, 7, result, ivv,1);
    cout << "使用secret的hash值作为iv，计算message的hash值\n";
    pr(result);
    cout << "直接计算secret+padding+message的hash值\n";
    sm3_hash(msg, 71, result, IV);
    pr(result);


    uint8_t iv[32] = "nihao,nihao,nizhendehao,nihao,,";
    pr(iv);

    for (size_t i = 0; i < 8; i++)
    {
        printf("%x ", ivv[i]);

    }
    printf("\n");





}