#include "sm3_self.h"
using namespace std;
void randomstr(char* str, size_t length) {
    srand(static_cast<unsigned int>(time(nullptr)));

    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

    for (size_t i = 0; i < length - 1; i++) {
        int index = rand() % (sizeof(charset) - 1);
        str[i] = charset[index];
    }
    str[length - 1] = '\0';  // 添加字符串终止符
}
void pr(uint8_t* msg)
{
    for (size_t i = 0; i < 32; ++i) {
        printf("%02x ", msg[i]);
    }
    printf("\n");
}
int main() {
    const uint8_t message[32] = { 0 };
    randomstr((char*)message, 32);
    //const uint8_t message[] = "hello,world!hello,world!hello,world!hello,world!hello,world!hello,world!hello,world!你好八路军和红军都是中国共产党领导下的武装力量，在中国革命战争时期发挥了重要作用。八路军是中国抗日战争时期中国共产党领导下的一支正规军队，其正式名称为“中国人民抗日游击队暨八路军总部”。八路军主要活动在中国抗日战争期间的敌后地区，采取游击战和游击战略，实施袭击、破坏和游击战争，对抗日本侵略军进行有效的抵抗。八路军是中国抗日战争中的重要力量之一，为中国人民的抗战事业做出了巨大贡。红军则是指中国共产党领导下的工农红军，也被称为中国工农红军或中国工农红军总部。红军的形成可以追溯到1927年中国共产党领导的南昌起义。红军在中国革命战争时期起到了重要的作用，注重农村包围城市的斗争，积极开展游击战争，并最终在长征中获得了更大的发展和壮大。红军的斗争精神和战略战术对中国革命事业产生了深远影响。值得注意的是，根据中国的法律法规，关于历史事件和组织的讨论属于合法范围，但请注意不要涉及敏感政治话";
    uint8_t hash[32];
    int len = strlen((char*)message);
    clock_t start, end;
    start = clock();
    //100000 times evaluate:
    int i = 0;
    while (i < 100000)
    {
        randomstr((char*)message, 32);
        sm3_hash(message, strlen((char*)message), hash);
        i++;
    }
    end = clock();
    printf("evaluate 100000 times hash expends %f s \n", (double)(end - start)/CLOCKS_PER_SEC);
    // 打印哈希值
    return 0;
}
