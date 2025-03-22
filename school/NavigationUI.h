#ifndef 导航界面_H
#define 导航界面_H

class 导航系统;

class 导航界面 {
public:
    void 运行();

private:
    void 初始化地图(导航系统& 导航);
    void 查找最短路径(导航系统& 导航);
    void 查找必经点路径(导航系统& 导航);
};

#endif // 导航界面_H