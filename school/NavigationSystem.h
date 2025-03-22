#ifndef 导航系统_H
#define 导航系统_H

#include <vector>
#include <tuple>
#include <climits>

enum 方向枚举 { 北, 东北, 东, 东南, 南, 西南, 西, 西北 };

class 导航系统 {
public:
    explicit 导航系统(int 地点数量);
    void 添加道路(int 起点, int 终点, int 距离, 方向枚举 方向值);
    void 计算最短路径(int 起点, const std::vector<int>& 避让地点 = {});
    void 计算必经点路径(int 起点, int 终点, const std::vector<int>& 必经点, const std::vector<int>& 避让地点);
    void 打印导航(int 终点) const;

    bool 地点有效(int 地点) const { return 地点 > 0 && 地点 <= 地点总数; }
    int 获取地点总数() const { return 地点总数; }

private:
    int 地点总数;
    std::vector<std::vector<std::tuple<int, int, 方向枚举>>> 邻接表;
    std::vector<int> 距离;
    std::vector<int> 前驱;
    std::vector<方向枚举> 前驱方向;
    int 当前起点 = -1;

    void 重构路径(int 终点, std::vector<int>& 路径, std::vector<方向枚举>& 方向列表) const;
};

#endif // 导航系统_H