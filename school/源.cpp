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
//// ����ö��
//enum fx { ��, ����, ��, ����, ��, ����, ��, ���� };
//
//// ȫ�ֱ���
//int num; // �ص�����
//vector<vector<tuple<int, int, fx>>> xx; // �ڽӱ� (�ھӽڵ�, ����, ����)
//vector<int> dao; // �洢����㵽ÿ���ص����̾���
//vector<int> pre_d; // ǰ���ڵ�����
//vector<fx> pre_f; // ǰ����������
//int s; // ���
//
//// ������������ƽ̨��
//void clearScreen() {
//#ifdef _WIN32
//    system("cls");
//#else
//    system("clear");
//#endif
//}
////����ǰ������;�������
//void nwe() {
//    // ���þ����ǰ������
//    fill(dao.begin(), dao.end(), INT_MAX);
//    fill(pre_d.begin(), pre_d.end(), -1);
//    fill(pre_f.begin(), pre_f.end(), ��);
//
//}
//// ��ȡ�����ַ���
//string getDirectionString(fx direction) {
//    switch (direction) {
//    case ��: return "��";
//    case ����: return "����";
//    case ��: return "��";
//    case ����: return "����";
//    case ��: return "��";
//    case ����: return "����";
//    case ��: return "��";
//    case ����: return "����";
//    default: return "δ֪����";
//    }
//}
//
//// ��ȡת����Ϣ
//string getTurn(fx a, fx b) {
//    if (a == b) return "ֱ��";
//    int diff = (b - a + 8) % 8; // ���㷽���ֵ
//    if (diff == 1 || diff == 2) return "��ת";
//    if (diff == 6 || diff == 7) return "��ת";
//    return "��ͷ";
//}
//// ��ӡ����ָ��
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
//            turn = "����";
//        }
//        else {
//            fx fangxiang_ed = pre_f[now_dian];
//            turn = getTurn(fangxiang_ed, fangxiang_jiang);
//        }
//        cout << "(" << turn << "����" << getDirectionString(fangxiang_jiang) << "������" << km << "�ף����ص㡾 " << next_dian << " ��)" << endl;
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
//        int current_dist = yy.top().first;  // ��ǰ����
//        int current_node = yy.top().second; // ��ǰ�ڵ�
//        yy.pop();
//
//        // �����ǰ���������֪��̾��룬����
//        if (current_dist > dao[current_node]) continue;
//
//        for (const auto& edge : a[current_node]) {
//            int neighbor = get<0>(edge);  // �ھӽڵ�
//            int weight = get<1>(edge);    // �ߵ�Ȩ��
//            fx direction = get<2>(edge); // �ߵķ���
//
//            // ����ھӽڵ��ڲ��������б��У�����
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
//    cout << "-��ӭʹ��У԰����ϵͳ-" << endl;
//    cout << "������ͼ�еص�������";
//    cin >> num;
//    xx.resize(num + 1);
//    dao.resize(num + 1, INT_MAX);
//    pre_d.resize(num + 1);
//    pre_f.resize(num + 1);
//
//    cout << "����������Ĵ��š��������ͷ���(0=��,1=����,2=��,3=����,4=��,5=����,6=��,7=������ok��������)" << endl << "-----------------" << endl;
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
//                cout << "����ֵ������ 0-7 ֮�䣬���������룡" << endl;
//                continue;
//            }
//        }
//        catch (const invalid_argument& e) {
//            cout << "�����ʽ�������������룡" << endl;
//            continue;
//        }
//        catch (const out_of_range& e) {
//            cout << "�������ֳ�����Χ�����������룡" << endl;
//            continue;
//        }
//        xx[A].push_back({ B, C, static_cast<fx>(D) });
//        xx[B].push_back({ A, C, static_cast<fx>((D + 4) % 8) }); // �����
//    }
//
//    clearScreen();
//    cout << "ok,bro,��ʼ�׶��Ѿ�����~" << endl;
////--------------------------------------------------------------------------
//    cout << "��ѡ��Ҫʵ�ֹ���:" << endl << "��1���鿴��ǰ���ص㵽���еص�����·������" << endl << "��2���鿴��������֮��Ŀɹ滮·��" << endl;
//    int gn_xz;
//    cin >> gn_xz;
//    switch (gn_xz) {
//    case 1:
//        cout << "�����������ĸ��ص㣺" << endl;
//        cin >> s;
//        // �������Ƿ�Ϸ�
//        if (s < 1 || s > num) {
//            cout << "��������Ч��" << endl;
//            return 0;
//        }
//
//        // ���� Dijkstra �㷨
//        dijkstra(xx, s, dao, pre_d, pre_f, { 2 });
//
//        clearScreen();
//        for (int i = 1; i <= num; ++i) {
//            if (dao[i] == INT_MAX) {
//                cout << "�ص� " << i << ": ���ɴ�" << endl;
//            }
//            else {
//                cout << "����㡾 " << s << " �����ص㡾 " << i << " �� �ĵ���ָ�" << endl;
//                daohang(s, i, pre_d, pre_f);
//                cout << "����Ŀ�ĵأ��ܾ���Ϊ " << dao[i] << " ��" << endl << endl;
//            }
//        }
//        break;
//    case 2:
//        int e,dao_se=0;
//        cout << "�����������ĸ��ص㣺" << endl;
//        cin >> s;
//        // �������Ƿ�Ϸ�
//        if (s < 1 || s > num) {
//            cout << "��������Ч��" << endl;
//            return 0;
//        }
//        vector<int>xq;
//        vector<int>bxq;
//        string s1;
//        int s2;
//        cout<< "��������Ҫȥ�ĸ��ص㣺" << endl;
//        cin >> e;
//        cout << "������Ҫ�����ĵ�ĵ�(ok����)";
//        while (1) {
//            cin >> s1;
//            if (s1 == "ok")break;
//            try {
//                s2 =stoi(s1);
//                if (s2 < 1 || s2 > num) {
//                    cout << "����ֵ������ 1-"<<num<< "֮�䣬���������룡" << endl;
//                    continue;
//                }
//            }
//            catch (const invalid_argument& e) {
//                cout << "�����ʽ�������������룡" << endl;
//                continue;
//            }
//            catch (const out_of_range& e) {
//                cout << "�������ֳ�����Χ�����������룡" << endl;
//                continue;
//            }
//            xq.push_back(s2);
//        }
//        cout << "�����벻Ҫ�����ĵ�ĵ�(ok����)";
//        while (1) {
//            cin >> s1;
//            if (s1 == "ok")break;
//            try {
//                s2 = stoi(s1);
//                if (s2 < 1 || s2 > num) {
//                    cout << "����ֵ������ 1-" << num << "֮�䣬���������룡" << endl;
//                    continue;
//                }
//            }
//            catch (const invalid_argument& e) {
//                cout << "�����ʽ�������������룡" << endl;
//                continue;
//            }
//            catch (const out_of_range& e) {
//                cout << "�������ֳ�����Χ�����������룡" << endl;
//                continue;
//            }
//            bxq.push_back(s2);
//        }
//
//
//        // ���� Dijkstra_s �㷨
//        dijkstra_s(xx, s, e,dao_se, pre_d, pre_f, xq,bxq);
//        break;
//    }
//
//    return 0;
//}
///*�����������ԣ�
//
//��1��--��100m��-----��2��
//  |��               / |
//  | ��             / ��77m��
//  |��400m��     (400) |
//��90m��   ��     /    ��4��----��88m��-----��6��
//  |          �� /                           |��2m��
//��5��-��3m��--��3��------��399m��----------��7��
//
//
//-��ӭʹ��У԰����ϵͳ-
//������ͼ�еص�������7
//����������Ĵ��š��������ͷ���(0=��,1=����,2=��,3=����,4=��,5=����,6=��,7=������ok��������)
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