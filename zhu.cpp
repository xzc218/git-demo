#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cstdlib>
#include <tuple>
#include <climits> // for INT_MAX
using namespace std;

// 方向枚举
enum fx { 北, 东北, 东, 东南, 南, 西南, 西, 西北 };

// 全局变量
int num; // 地点数量
vector<vector<tuple<int, int, fx>>> xx; // 邻接表 (邻居节点, 距离, 方向)
vector<int> dao; // 存储从起点到每个地点的最短距离
vector<int> pre_d; // 前驱节点数组
vector<fx> pre_f; // 前驱方向数组
int s; // 起点

// 清屏函数（跨平台）
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// 获取方向字符串
string getDirectionString(fx direction) {
    switch (direction) {
    case 北: return "北";
    case 东北: return "东北";
    case 东: return "东";
    case 东南: return "东南";
    case 南: return "南";
    case 西南: return "西南";
    case 西: return "西";
    case 西北: return "西北";
    default: return "未知方向";
    }
}

// 获取转向信息
string getTurn(fx a, fx b) {
    if (a == b) return "直走";
    int diff = (b - a + 8) % 8; // 计算方向差值
    if (diff == 1 || diff == 2) return "右转";
    if (diff == 6 || diff == 7) return "左转";
    return "掉头";
}

// Dijkstra 算法实现
void dijkstra(vector<vector<tuple<int, int, fx>>>& a, int start, vector<int>& dao, vector<int>& pre_d, vector<fx>& pre_f) {
    dao[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> yy;
    yy.push({ 0, start });

    while (!yy.empty()) {
        int current_dist = yy.top().first;  // 当前距离
        int current_node = yy.top().second; // 当前节点
        yy.pop();

        // 如果当前距离大于已知最短距离，跳过
        if (current_dist > dao[current_node]) continue;

        for (const auto& edge : a[current_node]) {
            int neighbor = get<0>(edge);  // 邻居节点
            int weight = get<1>(edge);    // 边的权重
            fx direction = get<2>(edge); // 边的方向

            if (dao[current_node] + weight < dao[neighbor]) {
                dao[neighbor] = dao[current_node] + weight;
                pre_d[neighbor] = current_node;
                pre_f[neighbor] = direction;
                yy.push({ dao[neighbor], neighbor });
            }
        }
    }
}

// 打印导航指令
void daohang(int s, int e, vector<int>& pre_d, vector<fx>& pre_f) {
    vector<int> path;
    int current = e;
    while (current != s) {
        path.push_back(current);
        current = pre_d[current];
    }
    path.push_back(s);

    for (int i = path.size() - 1; i > 0; --i) {
        int current_node = path[i];
        int next_node = path[i - 1];
        fx f = pre_f[next_node];
        int jvli = dao[next_node] - dao[current_node];
        string turn;
        if (current_node == s) {
            turn = "出发";
        }
        else {
            fx prev_dir = pre_f[current_node];
            turn = getTurn(prev_dir, f);
        }
        cout << "("<<turn << "，向" << getDirectionString(f) << "方向走" << jvli << "米，到地点【 " << next_node << " 】)" << endl;
    }
}

int main() {
    cout << "-欢迎使用校园导航系统-" << endl;
    cout << "请输入图中地点数量：";
    cin >> num;
    xx.resize(num + 1);
    dao.resize(num + 1, INT_MAX);
    pre_d.resize(num + 1);
    pre_f.resize(num + 1);

    cout << "请输入两点的代号、两点距离和方向(0=北,1=东北,2=东,3=东南,4=南,5=西南,6=西,7=西北，ok结束输入)" << endl << "-----------------" << endl;
    while (true) {
        string a, b, c, d;
        int A, B, C, D;
        cin >> a;
        if (a == "OK" || a == "ok") {
            cout << "-----------------" << endl;
            break;
        }
        cin >> b >> c >> d;
        try {
            A = stoi(a);
            B = stoi(b);
            C = stoi(c);
            D = stoi(d);
            if (D < 0 || D > 7) {
                cout << "方向值必须在 0-7 之间，请重新输入！" << endl;
                continue;
            }
        }
        catch (const invalid_argument& e) {
            cout << "输入格式错误，请重新输入！" << endl;
            continue;
        }
        catch (const out_of_range& e) {
            cout << "输入数字超出范围，请重新输入！" << endl;
            continue;
        }
        xx[A].push_back({ B, C, static_cast<fx>(D) });
        xx[B].push_back({ A, C, static_cast<fx>((D + 4) % 8) }); // 反向边
    }

    clearScreen();
    cout << "ok,bro,初始阶段已经结束~" << endl;
    cout << "请输入您在哪个地点：" << endl;
    cin >> s;

    // 检查起点是否合法
    if (s < 1 || s > num) {
        cout << "起点代号无效！" << endl;
        return 0;
    }

    // 调用 Dijkstra 算法
    dijkstra(xx, s, dao, pre_d, pre_f);

    clearScreen();
    for (int i = 1; i <= num; ++i) {
        if (dao[i] == INT_MAX) {
            cout << "地点 " << i << ": 不可达" << endl;
        }
        else {
            cout << "从起点【 " << s << " 】到地点【 " << i << " 】 的导航指令：" << endl;
            daohang(s, i, pre_d, pre_f);
            cout << "到达目的地，总距离为 " << dao[i] << " 米" << endl<<endl;
        }
    }

    return 0;
}
