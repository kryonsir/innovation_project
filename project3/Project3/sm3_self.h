#pragma once
#include<stdio.h>>
#include<stdlib.h>
#include <stdint.h>
#include <string.h>
#include<time.h>
#include<iostream>
using namespace std;

uint32_t left_rotate(uint32_t x, uint32_t n);
inline uint32_t FF(uint32_t j, uint32_t x, uint32_t y, uint32_t z);
inline uint32_t GG(uint32_t j, uint32_t x, uint32_t y, uint32_t z);
inline uint32_t P0(uint32_t x);
inline uint32_t P1(uint32_t x);
void sm3_hash(const uint8_t* message, size_t message_len, uint8_t* hash,uint32_t IV[]);
void sm3_hash_ext(const uint8_t* message, size_t message_len, uint8_t* hash, uint32_t iv[], int len);
void pr_msg(uint8_t* msg);

