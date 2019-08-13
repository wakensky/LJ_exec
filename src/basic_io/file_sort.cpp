#include<iostream>
#include<fstream>
#include<algorithm>
#include<string>
#include<random>
#include<vector>

using namespace std;

//生成一个含有100000个int64_t的文件
void create(string& filename){
	ofstream outfile;
	//写文件
	outfile.open(filename,ios::out);
	//判断文件是否成功打开，若失败则返回
	if(!outfile.good()){
		cout << "文件打开错误" << endl;
		return;
	}
	//使用random_engine代替rand()
	default_random_engine random;
	//范围1~5000
	uniform_int_distribution<unsigned> range(1,5000);
	int64_t a = 0;
	//数据规模
	for(int i = 0; i < 1000000; i++){
		a = range(random);
		outfile << a << "\n";
	}
	outfile.close();
}

//创建十个文件
void create_ten_file(){
	string filenumber = "0123456789";
	for(int i = 0; i < filenumber.size(); i++){
		string name = (string)("file") + filenumber[i] + ".txt";
		create(name);
	}
}

//简单排序思路
void sort_ten_file(){
	vector<int64_t> data;
	string filenumber = "0123456789";
	int64_t line;
	//对十个文件进行读取
	for(int i = 0; i < filenumber.size(); i++){
		string name = (string)("file") + filenumber[i] + ".txt";
		ifstream infile;
		infile.open(name,ios::in);
		//判断文件是否成功打开
		if(!infile.good())	return;
		//读取每个文件中的数据到data
		while(infile >> line){
			data.push_back(line);
		}
		infile.close();
		cout << "read finish" << endl;
	}
	//均读取完毕后对数据进行排序
	sort(data.begin(), data.end());
	//将排序后的数组写入新的文件
	string outfile_name = "sorted_file.txt";
	ofstream out;
	//写入新的文件
	out.open(outfile_name, ios::out);
	for(int i = 0; i < data.size(); i++){
		out << data[i] << "\n";
	}
	out.close();
}

int main(){
	create_ten_file();
	sort_ten_file();
	return 0;
}
