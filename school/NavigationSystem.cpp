#include "NavigationSystem.h"
#include "Utils.h"
#include <algorithm>
#include <queue>
#include <iostream>

using namespace std;

导航系统::导航系统(int 地点数量) : 地点总数(地点数量) {
    邻接表.resize(地点总数 + 1);
    距离.resize(地点总数 + 1, INT_MAX);
    前驱.resize(地点总数 + 1, -1);
    前驱方向.resize(地点总数 + 1, 北);
}

void 导航系统::添加道路(int 起点, int 终点, int 距离值, 方向枚举 方向值) {
    邻接表[起点].emplace_back(终点, 距离值, 方向值);
    邻接表[终点].emplace_back(起点, 距离值, static_cast<方向枚举>((方向值 + 4) % 8));
}

void 导航系统::计算最短路径(int 起点, const vector<int>& 避让地点) {
    fill(距离.begin(), 距离.end(), INT_MAX);
    fill(前驱.begin(), 前驱.end(), -1);
    fill(前驱方向.begin(), 前驱方向.end(), 北);

    距离[起点] = 0;
    当前起点 = 起点;

    using 节点对 = pair<int, int>;
    priority_queue<节点对, vector<节点对>, greater<>> 优先队列;
    优先队列.emplace(0, 起点);

    while (!优先队列.empty()) {
        int 当前距离, 当前节点;
        tie(当前距离, 当前节点) = 优先队列.top();
        优先队列.pop();

        if (当前距离 > 距离[当前节点]) continue;

        for (const auto& 边 : 邻接表[当前节点]) {
            int 邻居 = get<0>(边);
            int 权重 = get<1>(边);
            方向枚举 方向值 = get<2>(边);

            if (find(避让地点.begin(), 避让地点.end(), 邻居) != 避让地点.end()) continue;

            if (距离[当前节点] + 权重 < 距离[邻居]) {
                距离[邻居] = 距离[当前节点] + 权重;
                前驱[邻居] = 当前节点;
                前驱方向[邻居] = 方向值;
                优先队列.emplace(距离[邻居], 邻居);
            }
        }
    }
}

void 导航系统::计算必经点路径(int 起点, int 终点, const vector<int>& 必经点, const vector<int>& 避让地点) {
    int 距离_全程=0;
    if (必经点.empty()) {
        计算最短路径(起点, 避让地点);
        打印导航(终点);
        return;
    }
    计算最短路径(起点, 避让地点);
    打印导航(必经点[0]);
    if (距离[必经点[0]] == INT_MAX) {
        cout << "地点 " << 必经点[0] << " 不可达！" << endl;
        return;
    }
        cout << "到达第1个必经点" << endl;
        距离_全程 += 距离[必经点[0]];
    距离.resize(地点总数 + 1, INT_MAX);
    前驱.resize(地点总数 + 1, -1);
    前驱方向.resize(地点总数 + 1, 北);
    for (int i = 1; i < 必经点.size(); ++i) {
        计算最短路径(必经点[i-1], 避让地点);
            打印导航(必经点[i]);
            if (距离[必经点[i]] == INT_MAX) {
                cout << "地点 " << 必经点[i] << " 不可达！" << endl;
                return;
            }
            cout << "到达第i+1个必经点" << endl;
            距离_全程 += 距离[必经点[i]];
        距离.resize(地点总数 + 1, INT_MAX);
        前驱.resize(地点总数 + 1, -1);
        前驱方向.resize(地点总数 + 1, 北);
    }
    计算最短路径(必经点[必经点.size()-1], 避让地点);
        打印导航(终点);
        if (距离[终点] == INT_MAX) {
            cout << "地点 " << 终点 << " 不可达！" << endl;
            return;
        }
        距离_全程 += 距离[终点];
        cout << "到达第"<<必经点.size()+1<<"个必经点" << endl;
        cout << "全程导航总距离" << 距离_全程<<"米"<<endl;
}
void 导航系统::重构路径(int 终点, vector<int>& 路径, vector<方向枚举>& 方向列表) const {
    int 当前 = 终点;
    while (当前 != 当前起点 && 当前 != -1) {  // 添加 -1 检查，防止死循环
        路径.push_back(当前);
        方向列表.push_back(前驱方向[当前]);
        当前 = 前驱[当前];
    }
    if (当前 == 终点) {
        cout << "从起点【" << 当前 << "】到地点【" << 终点 << "】的导航：" << endl;
        cout << "你原地转个圈" << endl; return;
    }
    if (当前 == -1) {
        cout << "路径存在断裂，无法重构！" << endl;
        return;
    }
    路径.push_back(当前起点);
    reverse(路径.begin(), 路径.end());
    reverse(方向列表.begin(), 方向列表.end());
}

void 导航系统::打印导航(int 终点) const {
    if (距离[终点] == INT_MAX) {
        cout << "地点 " << 终点 << " 不可达！" << endl;
        return;
    }

    vector<int> 路径;
    vector<方向枚举> 方向列表;
    重构路径(终点, 路径, 方向列表);

    if (路径.empty()) {
        return;
    }

    cout << "从起点【" << 当前起点 << "】到地点【" << 终点 << "】的导航：" << endl;
    for (size_t i = 0; i < 路径.size() - 1; ++i) {
        int 起点 = 路径[i];
        int 终点 = 路径[i + 1];
        cout << "(";
        if (i == 0) {
            cout << "出发";
        }
        else
        cout << 获取转向(前驱方向[起点], 方向列表[i]);
         cout << "，向" << 获取方向字符串(方向列表[i])
            << "方向走" << 距离[终点] - 距离[起点]
            << "米到达【" << 终点 << "】)" << endl;
    }
    cout << "总距离: " << 距离[终点] << "米" << endl;
}
