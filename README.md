# 校园导航系统

## 项目简介
这是一个基于 Dijkstra 算法的校园导航系统，支持以下功能：
1. **查找最短路径**：输入起点和终点，系统会计算并显示最短路径。
2. **查找带必经点的路径**：输入起点、终点和必经点，系统会计算经过所有必经点的最短路径。
3. **避让点设置**：可以设置避让点，系统会避开这些地点计算路径。

## 功能特点
- **支持方向导航**：路径中会显示每一步的转向和方向。
- **跨平台清屏**：支持 Windows 和 Linux 系统的清屏功能。
- **输入校验**：对用户输入进行严格校验，防止无效输入导致程序崩溃。

## 代码结构
```
CampusNavigation/
├── include/
│   ├── NavigationSystem.h  // 导航系统核心类
│   ├── Utils.h              // 工具函数（清屏、方向转换等）
│   └── NavigationUI.h       // 用户界面类
├── src/
│   ├── NavigationSystem.cpp // 导航系统实现
│   ├── Utils.cpp            // 工具函数实现
│   ├── NavigationUI.cpp     // 用户界面实现
│   └── main.cpp             // 程序入口
└── README.md                // 项目说明文档
```

## 使用方法

### 1. 编译项目
确保已安装 CMake 和 C++ 编译器（如 g++ 或 MSVC），然后执行以下命令：
```bash
mkdir build
cd build
cmake ..
make
```

### 2. 运行程序
编译完成后，运行生成的可执行文件：
```bash
./CampusNavigation
```

### 3. 输入示例
#### 输入地点和道路信息
```
请输入图中地点数量：4
请输入道路信息（格式：起点 终点 距离 方向），输入 ok 结束：
1 2 100 2
1 3 200 3
2 4 150 4
3 4 50 5
ok
```

#### 查找最短路径
```
请选择功能：
【1】查找最短路径
【2】查找带必经点的路径
【3】退出程序
1
请输入起点和终点：1 4
```

#### 查找带必经点的路径
```
请选择功能：
【1】查找最短路径
【2】查找带必经点的路径
【3】退出程序
2
请输入起点和终点：1 4
请输入必经点（ok结束）：2 3
ok
请输入避让点（ok结束）：ok
```

### 4. 输出示例
#### 最短路径
```
从起点【1】到地点【4】的导航：
(出发，向东方向走100米到达【2】)
(右转，向南方向走150米到达【4】)
总距离: 250米
```

#### 带必经点的路径
```
从起点【1】经过必经点到终点【4】的导航：
(出发，向东方向走100米到达【2】)
(右转，向南方向走150米到达【4】)
全程导航总距离: 250米
```

## 代码示例
### 核心算法（Dijkstra）
```cpp
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
```

### 用户界面
```cpp
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
                cout << "有空常来~" << endl;
                return;
            default:
                cout << "无效选择！" << endl;
                break;
        }
    } catch (const exception& e) {
        cerr << "错误: " << e.what() << endl;
    }
}
```

## 后续计划
- 支持图形化界面（如 Qt 或 OpenGL）。
- 添加更多地图数据（如教学楼、食堂、宿舍等）。
- 优化算法性能，支持大规模地图。
- 对字典树的使用，对这个dfs回溯剪枝的分类筛选功能的完善，适当补充更完备的算法。
---

## 贡献者
- [徐志春]

## 许可证
本项目采用 MIT 许可证，详情请参阅 [LICENSE](LICENSE)。

---
