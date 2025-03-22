#include "NavigationUI.h"
#include "NavigationSystem.h"
#include "Utils.h"
#include <iostream>
#include <string>
#include <sstream>  // ��� sstream ͷ�ļ�

using namespace std;

void ��������::����() {
    try {
        int �ص�����;
        cout << "������ͼ�еص�������";
        cin >> �ص�����;
        if (�ص����� <= 0) throw invalid_argument("�ص���������Ϊ��������");

        ����ϵͳ ����(�ص�����);
        ��ʼ����ͼ(����);

        ����();
        cout << "��ͼ��ʼ����ɣ�" << endl;
        while (1) {
            int ѡ��;
            cout << "��ѡ���ܣ�\n��1���������·��\n��2�����Ҵ��ؾ����·��\n��3���˳�����\n";
            cin >> ѡ��;

            switch (ѡ��) {
            case 1:
                �������·��(����);
                break;
            case 2:
                ���ұؾ���·��(����);
                break;
            case 3:
                cout << "�пճ���~";
                return;
            default:
                cout << "��Чѡ��" << endl;
                break;
            }
            cout << "���������~" << endl;
            cin.ignore(); // ����֮ǰ�Ļ��з�
            cin.get();    // �ȴ��û��������
            ����();       // ����
        }
    }
    catch (const exception& e) {
        cerr << "����: " << e.what() << endl;
    }
}

void ��������::��ʼ����ͼ(����ϵͳ& ����) {
    cout << "�������·��Ϣ����ʽ����� �յ� ���� ���򣩣����� ok ������" << endl;
    cout << "����ο�ͼ��" << endl;
    std::cout << "          ��(0)    " << std::endl;
    std::cout << "          |    " << std::endl;
    std::cout << "          |    " << std::endl;
    std::cout << "��(6) ----+---- ��(2)" << std::endl;
    std::cout << "          |    " << std::endl;
    std::cout << "          |    " << std::endl;
    std::cout << "          ��(4)    " << std::endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ������뻺����

    string ��;
    while (getline(cin, ��)) {
        if (�� == "ok") break;

        istringstream ������(��);
        string ���, �յ�, ����, ����ֵ;
        if (!(������ >> ��� >> �յ� >> ���� >> ����ֵ)) {
            cout << "�����ʽ�������������룡" << endl;
            continue;
        }

        try {
            int ����� = stoi(���);
            int �յ��� = stoi(�յ�);
            int ����ֵ = stoi(����);
            int ������ = stoi(����ֵ);

            if (!����.�ص���Ч(�����) || !����.�ص���Ч(�յ���)) {
                cout << "�ص���ű����� 1 �� " << ����.��ȡ�ص�����() << " ֮�䣡" << endl;
                continue;
            }
            if (����ֵ < 0) {
                cout << "���벻��Ϊ������" << endl;
                continue;
            }
            if (������ < 0 || ������ > 7) {
                cout << "����ֵ������ 0 �� 7 ֮�䣡" << endl;
                continue;
            }

            ����.��ӵ�·(�����, �յ���, ����ֵ, static_cast<����ö��>(������));
        }
        catch (...) {
            cout << "�����ʽ�������������룡" << endl;
        }
    }
}

void ��������::�������·��(����ϵͳ& ����) {
    int ���, �յ�;
    cout << "�����������յ㣺";
    cin >> ��� >> �յ�;

    if (!����.�ص���Ч(���) || !����.�ص���Ч(�յ�)) {
        cout << "�ص������Ч��" << endl;
        return;
    }

    ����.�������·��(���);
    ����.��ӡ����(�յ�);
}

void ��������::���ұؾ���·��(����ϵͳ& ����) {
    int ���, �յ�;
    cout << "�����������յ㣺";
    cin >> ��� >> �յ�;

    if (!����.�ص���Ч(���) || !����.�ص���Ч(�յ�)) {
        cout << "�ص������Ч��" << endl;
        return;
    }

    vector<int> �ؾ���, ���õ�;
    string ����;
    int �ص�;

    cout << "������ؾ��㣨ok��������";
    while (cin >> ���� && ���� != "ok") {
        try {
            �ص� = stoi(����);
            if (!����.�ص���Ч(�ص�)) {
                cout << "�ص���ű����� 1 �� " << ����.��ȡ�ص�����() << " ֮�䣡" << endl;
                continue;
            }
            �ؾ���.push_back(�ص�);
        }
        catch (...) {
            cout << "������Ч�����������룡" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    cout << "��������õ㣨ok��������";
    while (cin >> ���� && ���� != "ok") {
        try {
            �ص� = stoi(����);
            if (!����.�ص���Ч(�ص�)) {
                cout << "�ص���ű����� 1 �� " << ����.��ȡ�ص�����() << " ֮�䣡" << endl;
                continue;
            }
            ���õ�.push_back(�ص�);
        }
        catch (...) {
            cout << "������Ч�����������룡" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    ����.����ؾ���·��(���, �յ�, �ؾ���, ���õ�);
}