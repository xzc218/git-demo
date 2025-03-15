#include<iostream>
#include<vector>
#include<string>
using namespace std;
//1
int num;
vector<vector<pair<int, int> >>xx;
vector<int>jl;
int s;
//2
int i, j;
//3
void dijkstra(vector<vector<pair<int, int> >>&a,int start,vector<int>&jl) {
	
}
int main() {
	
	cout << "-欢迎使用校园导航系统-" << endl;
	cout << "请输入图中地点数量：";
	cin >> num;
	xx.resize(num + 1, vector<pair<int, int>>(num + 1));
	jl.resize(num + 1, INT_MAX);
	cout << "请输入两点的代号和两点距离(ok结束输入)" << endl << "-----------------"<<endl;
	while (1) {
		string a, b, c;
		int A, B, C;
		cin >> a;
		if (a == "OK"||a=="ok") {
			cout << "-----------------";
			break;
		}
		cin>> b >> c;
		try {
			A = stoi(a);
			B = stoi(b);
			C = stoi(c);
		}
		catch (const std::invalid_argument& e) {
			std::cerr << "无效的字符串，无法转换: " << e.what() << std::endl;
		}
		catch (const std::out_of_range& e) {
			std::cerr << "转换结果超出范围: " << e.what() << std::endl;
		}
		xx[A].push_back({ B,C });
	}
	cin >> s;
	dijkstra(xx, s, jl);
	for (i = 1; i <= num; ++i) {
		cout << jl[i] << endl;
	}
	return 0;
}
