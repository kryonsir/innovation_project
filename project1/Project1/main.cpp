#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<string>
#include "sm3.h"
#include<unordered_map>
#include<time.h>


using namespace std;

unsigned char md[SM3_DIGEST_LENGTH] = { 0 };
SM3_CTX SMC;
void gen_msg(const unsigned char* data)
{

    ossl_sm3_update(&SMC, data, strlen((const char*)data));
    ossl_sm3_final(md, &SMC);
}
int main()
{

    ossl_sm3_init(&SMC);
    unsigned long long  i = 0;
    unordered_map<std::string, unsigned long long>tempUmap;
    clock_t start, end;
    start = clock();
    while (i < 4294967295)
    {
        unsigned char message[8];
        memcpy(message, &i, 8);
        gen_msg(message);
        char temp[128];
        sprintf(temp, "%02x", *md);
        for (int i = 0; i < SM3_DIGEST_LENGTH; i++) {
            //printf("%02x", *(md + i));
            if (i == 0)continue;
            char tmp[40];
            sprintf(tmp, "%02x", *(md + i));
            sprintf(temp, "%s%s", temp, tmp);
        }
        if (i == 239028)cout << "碰撞前40bits：" << endl<< temp << "\t239028" << endl;
        if (i == 247089)cout << temp << "\t247089" << endl;

        if (i == 2779433)cout << "碰撞前48bits：" << endl << temp << "\t2779433" << endl;
        if (i == 15087606)cout << temp << "\t15087606" << endl;

        temp[12] = '\0';
        char value[8] = { 0 };
        auto it = tempUmap.find(temp);
        if (it != tempUmap.end()) {
            cout << it->second<< endl;
            cout << value << endl;
            break;
        }
        tempUmap.emplace(temp, i);
        i++;
    }
    end = clock();
    cout << "运行时间" << (double)(end - start) / CLOCKS_PER_SEC << endl;
    cout << "size:" << tempUmap.size() << endl;


}
/*
* 5:
* 45
* 461
* 
* 
239028
14757395258967641292
size:247089



d9 29 2b 7d 86 97 12 97 f7 30 b1 6c fc 65 19 3d d8 8a 75 1d e0 19 8a ba 9c f9 c1 72 22 70 50 e9
d9 29 2b 7d 86 54 c9 fa f5 f6 de a6 86 b6 4f 9b 75 3f 5f 28 d1 3c d2 93 b5 2f 3f 85 8d bd c2 82
7:
2779433
14757395258967641292
F1运行时间528.565
size:15087606


碰撞前40bits：
d9 29 2b 7d 86 97 12 97 f7 30 b1 6c fc 65 19 3d d8 8a 75 1d e0 19 8a ba 9c f9 c1 72 22 70 50 e9         239028
d9 29 2b 7d 86 54 c9 fa f5 f6 de a6 86 b6 4f 9b 75 3f 5f 28 d1 3c d2 93 b5 2f 3f 85 8d bd c2 82         247089
碰撞前48bits：
20 f0 62 04 bf 9d 85 60 1a 6c f9 43 c0 1f e1 00 5e d2 ce 8e d2 ea ad 82 b7 3f bf 9c 9d 10 b0 d9         2779433
20 f0 62 04 bf 9d 8b 5e 0f f7 b4 ca 03 4f fb c4 3a fd c1 24 05 86 2b 84 83 3e 48 59 85 d2 01 b0         15087606
2779433

运行时间441.338
size:15087606

*/                                                         

