#ifndef ����ϵͳ_H
#define ����ϵͳ_H

#include <vector>
#include <tuple>
#include <climits>

enum ����ö�� { ��, ����, ��, ����, ��, ����, ��, ���� };

class ����ϵͳ {
public:
    explicit ����ϵͳ(int �ص�����);
    void ��ӵ�·(int ���, int �յ�, int ����, ����ö�� ����ֵ);
    void �������·��(int ���, const std::vector<int>& ���õص� = {});
    void ����ؾ���·��(int ���, int �յ�, const std::vector<int>& �ؾ���, const std::vector<int>& ���õص�);
    void ��ӡ����(int �յ�) const;

    bool �ص���Ч(int �ص�) const { return �ص� > 0 && �ص� <= �ص�����; }
    int ��ȡ�ص�����() const { return �ص�����; }

private:
    int �ص�����;
    std::vector<std::vector<std::tuple<int, int, ����ö��>>> �ڽӱ�;
    std::vector<int> ����;
    std::vector<int> ǰ��;
    std::vector<����ö��> ǰ������;
    int ��ǰ��� = -1;

    void �ع�·��(int �յ�, std::vector<int>& ·��, std::vector<����ö��>& �����б�) const;
};

#endif // ����ϵͳ_H