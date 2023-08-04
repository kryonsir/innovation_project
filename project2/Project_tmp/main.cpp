/*
#include <openssl/evp.h>
#include <openssl/sm3.h>

#include "openssl/evp.h"
#include "openssl/sm3.h"
*/

#include <iostream>
#include <sstream>
#include <iomanip>
#include<stdint.h>

//#include "C:\k\no_app\innovation_lecture\all_project\innovation_project\sm3_self\project3\sm3_self.h"
//#pragma comment (lib,"C:\k\no_app\innovation_lecture\all_project\innovation_project\sm3_self\x64\Debug\sm3_self.lib")
#include "sm3_self.h"
#include<time.h>
#include<unordered_map>
#include<ctime>

#define bits 0x0000000000000ffffff



using namespace std;


void pr(uint8_t* msg)
{
	for (size_t i = 0; i < 32; ++i) {
		printf("%02x ", msg[i]);
	}
	cout << endl;
}

void randomstr(char* str, size_t length) {
	srand(static_cast<unsigned int>(time(nullptr)));

	const char charset[] = "bcdefghijklmnopqrstuvwxyz0123456789";

	for (size_t i = 0; i < length - 1; i++) {
		int index = rand() % (sizeof(charset) - 1);
		str[i] = charset[index];
	}
	str[length - 1] = '\0';  // Ìí¼Ó×Ö·û´®ÖÕÖ¹·û
}


void randstr(char* str, size_t len)
{
	srand(static_cast<unsigned int>(time(nullptr)));
	for (size_t i = 0; i < len - 1; i++)
	{
		str[i] = rand() % 256;

	}
	str[len - 1] = '0';
}
/*
int main()
{
	int i = 0;
	uint8_t message[32] = { 0 };
	clock_t start, end;
	start = clock();

	while (i < 100000)
	{
		sm3_hash(message, 32, message);
		i++;
	}
	end = clock();
	cout << (double)(end - start) / CLOCKS_PER_SEC;
	return 0;
}
*/


int main()
{

	uint8_t message[32] = "xflfCRB0WRwcRGtTfIZswlXL7oyjJVJ" ;
	//uint8_t message[32] = "";
	//randstr((char*)message, 8);
	//randomstr((char*)message, 14);
	pr(message);
	uint8_t a[32] = { 0 };
	uint8_t b[32] = { 0 };
	sm3_hash(message, strlen((char*)message), a);
	sm3_hash(message, strlen((char*)message), b);
	unsigned char head[32];
	memcpy(head, a, 32);
	int i = 0;
	unsigned long long* aa = (unsigned long long*)a;
	unsigned long long* bb = (unsigned long long*)b;
	clock_t start, end;
	start = clock();
	unsigned long long x = *aa & bits;
	unsigned long long y = *bb & bits;
	while (1)
	{
		sm3_hash(a, 32, a);
		sm3_hash(b, 32, b);
		sm3_hash(b, 32, b);
		
		x = *aa & bits;
		y = *bb & bits;

		if (x == y)
		{
			cout << i << endl;
			pr(a);
			pr(b);
			break;
		}

		i++;


	}

	sm3_hash(message,strlen((char*)message),a);
	unsigned char ta[32];
	unsigned char tb[32];


	int j = 0;
	while (1)
	{
		memcpy(ta, a, 32);
		memcpy(tb, b, 32);

		sm3_hash(a, 32, a);
		sm3_hash(b, 32, b);
		x = *aa & bits;
		y = *bb & bits;

		if (x == y)
		{
			cout << j << endl;
			cout << "preimage1:\t";
			pr(ta);
			cout << "preimage2:\t";
			pr(tb);
			cout << "image:\n";
			pr(a);
			pr(b);
			break;
		}

		j++;

	}

	sm3_hash(ta, 32, ta);
	pr(ta);
	sm3_hash(tb, 32, tb);
	pr(tb);


	end = clock();
	cout << "run time:" << (double)(end - start) / CLOCKS_PER_SEC << endl;


	return 0;
}




/*
78 66 6c 66 43 52 42 30 57 52 77 63 52 47 74 54 66 49 5a 73 77 6c 58 4c 37 6f 79 6a 4a 56 4a 00
2377729
7e 48 ca ce f5 de 75 a1 0e 83 e2 ac 45 47 b3 67 3b ee 3f b5 b8 e3 0b df 68 c2 6b a2 f9 a2 99 a6
7e 48 ca 2b a6 6a 11 83 cc 49 8d 0f 23 87 4b 97 ad 51 77 69 cb 2a bf 36 4f 08 e2 76 21 f4 85 58
19894471
preimage1:      d6 d6 8a da 9b c8 94 3f 8d 45 5c f8 0e 64 1e 00 08 f3 66 d6 d5 2e 23 75 b9 cb 89 7a ed c4 8e a7
preimage2:      36 88 70 9d bb 3f e3 53 9c 85 83 98 3f 53 19 16 54 12 23 ef 2c ca df 55 ba 11 d5 e2 93 15 cf 5f
image:
3d a4 a8 60 49 4f b5 7d 36 3e b2 80 d1 a4 46 cf ce 51 64 29 2d ef 01 5f 10 81 a5 b3 3b b4 2b 76
3d a4 a8 4c 9c 71 ca e8 f6 28 f0 be ba cc e7 a9 40 5b 6a b0 64 89 08 67 28 75 70 37 c7 77 0b 92
3d a4 a8 60 49 4f b5 7d 36 3e b2 80 d1 a4 46 cf ce 51 64 29 2d ef 01 5f 10 81 a5 b3 3b b4 2b 76
3d a4 a8 4c 9c 71 ca e8 f6 28 f0 be ba cc e7 a9 40 5b 6a b0 64 89 08 67 28 75 70 37 c7 77 0b 92
run time:21.893



*/
