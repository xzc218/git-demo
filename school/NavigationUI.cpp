#include "NavigationUI.h"
#include "NavigationSystem.h"
#include "Utils.h"
#include <iostream>
#include <string>
#include <sstream>  // 添加 sstream 头文件

using namespace std;

void 导航界面::运行() {
    try {
        int 地点数量;
        cout << "请输入图中地点数量：";
        cin >> 地点数量;
        if (地点数量 <= 0) throw invalid_argument("地点数量必须为正整数！");

        导航系统 导航(地点数量);
        初始化地图(导航);

        清屏();
        cout << "地图初始化完成！" << endl;
        while (1) {
            int 选择;
            cout << "请选择功能：\n【1】查找最短路径\n【2】查找带必经点的路径\n【3】退出程序\n";
            cin >> 选择;

            switch (选择) {
            case 1:
                查找最短路径(导航);
                break;
            case 2:
                查找必经点路径(导航);
                break;
            case 3:
                cout << "有空常来~";
                return;
            default:
                cout << "无效选择！" << endl;
                break;
            }
            cout << "任意键继续~" << endl;
            cin.ignore(); // 忽略之前的换行符
            cin.get();    // 等待用户按任意键
            清屏();       // 清屏
        }
    }
    catch (const exception& e) {
        cerr << "错误: " << e.what() << endl;
    }
}

void 导航界面::初始化地图(导航系统& 导航) {
    cout << "请输入道路信息（格式：起点 终点 距离 方向），输入 ok 结束：" << endl;
    cout << "方向参考图：" << endl;
    std::cout << "          北(0)    " << std::endl;
    std::cout << "          |    " << std::endl;
    std::cout << "          |    " << std::endl;
    std::cout << "西(6) ----+---- 东(2)" << std::endl;
    std::cout << "          |    " << std::endl;
    std::cout << "          |    " << std::endl;
    std::cout << "          南(4)    " << std::endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清除输入缓冲区

    string 行;
    while (getline(cin, 行)) {
        if (行 == "ok") break;

        istringstream 输入流(行);
        string 起点, 终点, 距离, 方向值;
        if (!(输入流 >> 起点 >> 终点 >> 距离 >> 方向值)) {
            cout << "输入格式错误，请重新输入！" << endl;
            continue;
        }

        try {
            int 起点编号 = stoi(起点);
            int 终点编号 = stoi(终点);
            int 距离值 = stoi(距离);
            int 方向编号 = stoi(方向值);

            if (!导航.地点有效(起点编号) || !导航.地点有效(终点编号)) {
                cout << "地点代号必须在 1 到 " << 导航.获取地点总数() << " 之间！" << endl;
                continue;
            }
            if (距离值 < 0) {
                cout << "距离不能为负数！" << endl;
                continue;
            }
            if (方向编号 < 0 || 方向编号 > 7) {
                cout << "方向值必须在 0 到 7 之间！" << endl;
                continue;
            }

            导航.添加道路(起点编号, 终点编号, 距离值, static_cast<方向枚举>(方向编号));
        }
        catch (...) {
            cout << "输入格式错误，请重新输入！" << endl;
        }
    }
}

void 导航界面::查找最短路径(导航系统& 导航) {
    int 起点, 终点;
    cout << "请输入起点和终点：";
    cin >> 起点 >> 终点;

    if (!导航.地点有效(起点) || !导航.地点有效(终点)) {
        cout << "地点代号无效！" << endl;
        return;
    }

    导航.计算最短路径(起点);
    导航.打印导航(终点);
}

void 导航界面::查找必经点路径(导航系统& 导航) {
    int 起点, 终点;
    cout << "请输入起点和终点：";
    cin >> 起点 >> 终点;

    if (!导航.地点有效(起点) || !导航.地点有效(终点)) {
        cout << "地点代号无效！" << endl;
        return;
    }

    vector<int> 必经点, 避让点;
    string 输入;
    int 地点;

    cout << "请输入必经点（ok结束）：";
    while (cin >> 输入 && 输入 != "ok") {
        try {
            地点 = stoi(输入);
            if (!导航.地点有效(地点)) {
                cout << "地点代号必须在 1 到 " << 导航.获取地点总数() << " 之间！" << endl;
                continue;
            }
            必经点.push_back(地点);
        }
        catch (...) {
            cout << "输入无效，请重新输入！" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    cout << "请输入避让点（ok结束）：";
    while (cin >> 输入 && 输入 != "ok") {
        try {
            地点 = stoi(输入);
            if (!导航.地点有效(地点)) {
                cout << "地点代号必须在 1 到 " << 导航.获取地点总数() << " 之间！" << endl;
                continue;
            }
            避让点.push_back(地点);
        }
        catch (...) {
            cout << "输入无效，请重新输入！" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    导航.计算必经点路径(起点, 终点, 必经点, 避让点);
}