//#include <iostream>
//#include <vector>
//#include <string>
//#include <queue>
//#include <cstdlib>
//#include <tuple>
//#include <climits> // for INT_MAX
//#include<algorithm>
//using namespace std;
//
//// 方向枚举
//enum fx { 北, 东北, 东, 东南, 南, 西南, 西, 西北 };
//
//// 全局变量
//int num; // 地点数量
//vector<vector<tuple<int, int, fx>>> xx; // 邻接表 (邻居节点, 距离, 方向)
//vector<int> dao; // 存储从起点到每个地点的最短距离
//vector<int> pre_d; // 前驱节点数组
//vector<fx> pre_f; // 前驱方向数组
//int s; // 起点
//
//// 清屏函数（跨平台）
//void clearScreen() {
//#ifdef _WIN32
//    system("cls");
//#else
//    system("clear");
//#endif
//}
////重置前驱数组和距离数组
//void nwe() {
//    // 重置距离和前驱数组
//    fill(dao.begin(), dao.end(), INT_MAX);
//    fill(pre_d.begin(), pre_d.end(), -1);
//    fill(pre_f.begin(), pre_f.end(), 北);
//
//}
//// 获取方向字符串
//string getDirectionString(fx direction) {
//    switch (direction) {
//    case 北: return "北";
//    case 东北: return "东北";
//    case 东: return "东";
//    case 东南: return "东南";
//    case 南: return "南";
//    case 西南: return "西南";
//    case 西: return "西";
//    case 西北: return "西北";
//    default: return "未知方向";
//    }
//}
//
//// 获取转向信息
//string getTurn(fx a, fx b) {
//    if (a == b) return "直走";
//    int diff = (b - a + 8) % 8; // 计算方向差值
//    if (diff == 1 || diff == 2) return "右转";
//    if (diff == 6 || diff == 7) return "左转";
//    return "掉头";
//}
//// 打印导航指令
//void daohang(int s, int e, vector<int>& pre_d, vector<fx>& pre_f) {
//    vector<int> path;
//    int dian = e;
//    while (dian != s) {
//        path.push_back( dian);
//        dian = pre_d[dian];
//    }
//    path.push_back(s);
//
//    for (int i = path.size() - 1; i > 0; --i) {
//        int now_dian = path[i];
//        int next_dian = path[i - 1];
//        fx fangxiang_jiang = pre_f[next_dian];
//        int km = dao[next_dian] - dao[now_dian];
//        string turn;
//        if (now_dian == s) {
//            turn = "出发";
//        }
//        else {
//            fx fangxiang_ed = pre_f[now_dian];
//            turn = getTurn(fangxiang_ed, fangxiang_jiang);
//        }
//        cout << "(" << turn << "，向" << getDirectionString(fangxiang_jiang) << "方向走" << km << "米，到地点【 " << next_dian << " 】)" << endl;
//    }
//}
//void dijkstra(vector<vector<tuple<int, int, fx>>>& a, int start, 
//    vector<int>& dao, vector<int>& pre_d, vector<fx>& pre_f, 
//    const vector<int>& avoidNodes) {
//    dao[start] = 0;
//    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> yy;
//    yy.push({ 0, start });
//
//    while (!yy.empty()) {
//        int current_dist = yy.top().first;  // 当前距离
//        int current_node = yy.top().second; // 当前节点
//        yy.pop();
//
//        // 如果当前距离大于已知最短距离，跳过
//        if (current_dist > dao[current_node]) continue;
//
//        for (const auto& edge : a[current_node]) {
//            int neighbor = get<0>(edge);  // 邻居节点
//            int weight = get<1>(edge);    // 边的权重
//            fx direction = get<2>(edge); // 边的方向
//
//            // 如果邻居节点在不经过的列表中，跳过
//            if (find(avoidNodes.begin(), avoidNodes.end(), neighbor) != avoidNodes.end()) {
//                continue;
//            }
//
//            if (dao[current_node] + weight < dao[neighbor]) {
//                dao[neighbor] = dao[current_node] + weight;
//                pre_d[neighbor] = current_node;
//                pre_f[neighbor] = direction;
//                yy.push({ dao[neighbor], neighbor });
//            }
//        }
//    }
//}
//int main() {
//    cout << "-欢迎使用校园导航系统-" << endl;
//    cout << "请输入图中地点数量：";
//    cin >> num;
//    xx.resize(num + 1);
//    dao.resize(num + 1, INT_MAX);
//    pre_d.resize(num + 1);
//    pre_f.resize(num + 1);
//
//    cout << "请输入两点的代号、两点距离和方向(0=北,1=东北,2=东,3=东南,4=南,5=西南,6=西,7=西北，ok结束输入)" << endl << "-----------------" << endl;
//    while (true) {
//        string a, b, c, d;
//        int A, B, C, D;
//        cin >> a;
//        if (a == "OK" || a == "ok") {
//            cout << "-----------------" << endl;
//            break;
//        }
//        cin >> b >> c >> d;
//        try {
//            A = stoi(a);
//            B = stoi(b);
//            C = stoi(c);
//            D = stoi(d);
//            if (D < 0 || D > 7) {
//                cout << "方向值必须在 0-7 之间，请重新输入！" << endl;
//                continue;
//            }
//        }
//        catch (const invalid_argument& e) {
//            cout << "输入格式错误，请重新输入！" << endl;
//            continue;
//        }
//        catch (const out_of_range& e) {
//            cout << "输入数字超出范围，请重新输入！" << endl;
//            continue;
//        }
//        xx[A].push_back({ B, C, static_cast<fx>(D) });
//        xx[B].push_back({ A, C, static_cast<fx>((D + 4) % 8) }); // 反向边
//    }
//
//    clearScreen();
//    cout << "ok,bro,初始阶段已经结束~" << endl;
////--------------------------------------------------------------------------
//    cout << "请选择要实现功能:" << endl << "【1】查看当前到地点到所有地点的最短路径距离" << endl << "【2】查看具体两点之间的可规划路径" << endl;
//    int gn_xz;
//    cin >> gn_xz;
//    switch (gn_xz) {
//    case 1:
//        cout << "请输入您在哪个地点：" << endl;
//        cin >> s;
//        // 检查起点是否合法
//        if (s < 1 || s > num) {
//            cout << "起点代号无效！" << endl;
//            return 0;
//        }
//
//        // 调用 Dijkstra 算法
//        dijkstra(xx, s, dao, pre_d, pre_f, { 2 });
//
//        clearScreen();
//        for (int i = 1; i <= num; ++i) {
//            if (dao[i] == INT_MAX) {
//                cout << "地点 " << i << ": 不可达" << endl;
//            }
//            else {
//                cout << "从起点【 " << s << " 】到地点【 " << i << " 】 的导航指令：" << endl;
//                daohang(s, i, pre_d, pre_f);
//                cout << "到达目的地，总距离为 " << dao[i] << " 米" << endl << endl;
//            }
//        }
//        break;
//    case 2:
//        int e,dao_se=0;
//        cout << "请输入您在哪个地点：" << endl;
//        cin >> s;
//        // 检查起点是否合法
//        if (s < 1 || s > num) {
//            cout << "起点代号无效！" << endl;
//            return 0;
//        }
//        vector<int>xq;
//        vector<int>bxq;
//        string s1;
//        int s2;
//        cout<< "请输入您要去哪个地点：" << endl;
//        cin >> e;
//        cout << "请输入要经过的点的点(ok结束)";
//        while (1) {
//            cin >> s1;
//            if (s1 == "ok")break;
//            try {
//                s2 =stoi(s1);
//                if (s2 < 1 || s2 > num) {
//                    cout << "方向值必须在 1-"<<num<< "之间，请重新输入！" << endl;
//                    continue;
//                }
//            }
//            catch (const invalid_argument& e) {
//                cout << "输入格式错误，请重新输入！" << endl;
//                continue;
//            }
//            catch (const out_of_range& e) {
//                cout << "输入数字超出范围，请重新输入！" << endl;
//                continue;
//            }
//            xq.push_back(s2);
//        }
//        cout << "请输入不要经过的点的点(ok结束)";
//        while (1) {
//            cin >> s1;
//            if (s1 == "ok")break;
//            try {
//                s2 = stoi(s1);
//                if (s2 < 1 || s2 > num) {
//                    cout << "方向值必须在 1-" << num << "之间，请重新输入！" << endl;
//                    continue;
//                }
//            }
//            catch (const invalid_argument& e) {
//                cout << "输入格式错误，请重新输入！" << endl;
//                continue;
//            }
//            catch (const out_of_range& e) {
//                cout << "输入数字超出范围，请重新输入！" << endl;
//                continue;
//            }
//            bxq.push_back(s2);
//        }
//
//
//        // 调用 Dijkstra_s 算法
//        dijkstra_s(xx, s, e,dao_se, pre_d, pre_f, xq,bxq);
//        break;
//    }
//
//    return 0;
//}
///*输入样例测试：
//
//【1】--（100m）-----【2】
//  |、               / |
//  | 、             / （77m）
//  |（400m）     (400) |
//（90m）   、     /    【4】----（88m）-----【6】
//  |          、 /                           |（2m）
//【5】-（3m）--【3】------（399m）----------【7】
//
//
//-欢迎使用校园导航系统-
//请输入图中地点数量：7
//请输入两点的代号、两点距离和方向(0=北,1=东北,2=东,3=东南,4=南,5=西南,6=西,7=西北，ok结束输入)
//-----------------
//1 2 100 2
//1 3 400 3
//1 5 90 4
//5 3 3 3
//2 3 400 5
//2 4 77 4
//4 6 88 6
//3 7 399 3
//6 7 2 4
//
//
//
//
//
//
//1 2 222 2
//2 3 330 4
//1 3 111 3
//ok
//*/