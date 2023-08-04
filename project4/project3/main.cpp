#include "sm3_self.h"
using namespace std;
void randomstr(char* str, size_t length) {
    srand(static_cast<unsigned int>(time(nullptr)));

    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

    for (size_t i = 0; i < length - 1; i++) {
        int index = rand() % (sizeof(charset) - 1);
        str[i] = charset[index];
    }
    str[length - 1] = '\0';  // ����ַ�����ֹ��
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
    //const uint8_t message[] = "hello,world!hello,world!hello,world!hello,world!hello,world!hello,world!hello,world!��ð�·���ͺ�������й��������쵼�µ���װ���������й�����ս��ʱ�ڷ�������Ҫ���á���·�����й�����ս��ʱ���й��������쵼�µ�һ֧������ӣ�����ʽ����Ϊ���й��������λ����߰�·���ܲ�������·����Ҫ����й�����ս���ڼ�ĵк��������ȡ�λ�ս���λ�ս�ԣ�ʵʩϮ�����ƻ����λ�ս�����Կ��ձ����Ծ�������Ч�ĵֿ�����·�����й�����ս���е���Ҫ����֮һ��Ϊ�й�����Ŀ�ս��ҵ�����˾޴󹱡��������ָ�й��������쵼�µĹ�ũ�����Ҳ����Ϊ�й���ũ������й���ũ����ܲ���������γɿ���׷�ݵ�1927���й��������쵼���ϲ����塣������й�����ս��ʱ��������Ҫ�����ã�ע��ũ���Χ���еĶ�����������չ�λ�ս�����������ڳ����л���˸���ķ�չ��׳�󡣺���Ķ��������ս��ս�����й�������ҵ��������ԶӰ�졣ֵ��ע����ǣ������й��ķ��ɷ��棬������ʷ�¼�����֯���������ںϷ���Χ������ע�ⲻҪ�漰�������λ�";
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
    // ��ӡ��ϣֵ
    return 0;
}
