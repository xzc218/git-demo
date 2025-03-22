#include "Utils.h"
#include <cstdlib>
#include <iostream>

using namespace std;

void 清屏() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

string 获取方向字符串(int 方向值) {
    switch (方向值) {
    case 0: return "北";
    case 1: return "东北";
    case 2: return "东";
    case 3: return "东南";
    case 4: return "南";
    case 5: return "西南";
    case 6: return "西";
    case 7: return "西北";
    default: return "未知方向";
    }
}

string 获取转向(int 起点方向, int 终点方向) {
    if (起点方向 == 终点方向) return "直走";
    int 差值 = (终点方向 - 起点方向 + 8) % 8;
    if (差值 == 1 || 差值 == 2) return "右转";
    if (差值 == 6 || 差值 == 7) return "左转";
    return "掉头";
}