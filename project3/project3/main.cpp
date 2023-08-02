#include "sm3_self.h"

int main() {
    const uint8_t message[] = "hello,world!hello,world!hello,world!hello,world!hello,world!hello,world!hello,world!��ð�·���ͺ�������й��������쵼�µ���װ���������й�����ս��ʱ�ڷ�������Ҫ���á���·�����й�����ս��ʱ���й��������쵼�µ�һ֧������ӣ�����ʽ����Ϊ���й��������λ����߰�·���ܲ�������·����Ҫ����й�����ս���ڼ�ĵк��������ȡ�λ�ս���λ�ս�ԣ�ʵʩϮ�����ƻ����λ�ս�����Կ��ձ����Ծ�������Ч�ĵֿ�����·�����й�����ս���е���Ҫ����֮һ��Ϊ�й�����Ŀ�ս��ҵ�����˾޴󹱡��������ָ�й��������쵼�µĹ�ũ�����Ҳ����Ϊ�й���ũ������й���ũ����ܲ���������γɿ���׷�ݵ�1927���й��������쵼���ϲ����塣������й�����ս��ʱ��������Ҫ�����ã�ע��ũ���Χ���еĶ�����������չ�λ�ս�����������ڳ����л���˸���ķ�չ��׳�󡣺���Ķ��������ս��ս�����й�������ҵ��������ԶӰ�졣ֵ��ע����ǣ������й��ķ��ɷ��棬������ʷ�¼�����֯���������ںϷ���Χ������ע�ⲻҪ�漰�������λ�";
    uint8_t hash[32];
    int len = strlen((char*)message);
    printf("len: %d\n", len);
    for (int i = 0; i < len; i++)
    {
        printf("%02x", message[i]);
    }
    printf("\n");
    clock_t start, end;
    start = clock();

    sm3_hash(message, strlen((char*)message), hash);
    end = clock();
    printf("evaluate hash expends %f time\n", (end - start)/CLOCKS_PER_SEC);
    // ��ӡ��ϣֵ
    for (size_t i = 0; i < 32; ++i) {
        printf("%02x ", hash[i]);
    }
    printf("\n");

    return 0;
}
