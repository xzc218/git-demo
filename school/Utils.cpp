#include "Utils.h"
#include <cstdlib>
#include <iostream>

using namespace std;

void ����() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

string ��ȡ�����ַ���(int ����ֵ) {
    switch (����ֵ) {
    case 0: return "��";
    case 1: return "����";
    case 2: return "��";
    case 3: return "����";
    case 4: return "��";
    case 5: return "����";
    case 6: return "��";
    case 7: return "����";
    default: return "δ֪����";
    }
}

string ��ȡת��(int ��㷽��, int �յ㷽��) {
    if (��㷽�� == �յ㷽��) return "ֱ��";
    int ��ֵ = (�յ㷽�� - ��㷽�� + 8) % 8;
    if (��ֵ == 1 || ��ֵ == 2) return "��ת";
    if (��ֵ == 6 || ��ֵ == 7) return "��ת";
    return "��ͷ";
}