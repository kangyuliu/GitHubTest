#include <iostream>
#include <vector>
#include <string>
#include <map>
#include < unordered_map >
#include <assert.h>
using namespace std;

struct Point{
	int x;
	int y;
};

class Maze{
public:
	Maze(string &str);
	vector<vector<char> > getRender(string &str);
private:
	pair<Point, Point> getPair(string & str);
private:
	unsigned int rows;	//行
	unsigned int cols;	//列
	vector<vector<char> > render;	//渲染

};

Maze::Maze(string &str)
{
	size_t found;
	found = str.find(" ");
	assert(found !=	string::npos);
	string tmp = str.substr(0,found);
	rows = 2*atoi(tmp.c_str())+1;
	tmp = str.substr(found+1, str.size()-found-1);
	cols = 2*atoi(tmp.c_str())+1;

	for(int row=0; row < rows; row++)
		render.push_back(vector<char>(cols,'W'));

}

vector<vector<char> > Maze::getRender(string &str)
{
	if(str.empty())
		return render;

	int size = str.size();
	size_t found = 0;
	
	while(found < size){
		size_t flag = found;
		found = str.find(";",found);
		string tmp;

		
		//assert(found !=	string::npos);
		if(found !=	string::npos){
			tmp = str.substr(flag,found-flag);
		}
		else{
			tmp = str.substr(flag,size-1);
		}
		
		pair<Point, Point> p = getPair(tmp);
		if(p.first.x == p.second.x){
			render[2*p.first.x+1][2*p.first.y+1] = 'R';
			render[2*p.second.x+1][2*p.second.y] = 'R';
			render[2*p.second.x+1][2*p.second.y+1] = 'R';
		}
		if(p.first.y == p.second.y){
			render[2*p.first.x+1][2*p.first.y+1] = 'R';
			render[2*p.second.x][2*p.second.y+1] = 'R';
			render[2*p.second.x+1][2*p.second.y+1] = 'R';
		}
		if(found != string::npos)
			found = found+1;
		else 
			found =size;
	}

	return render;

}

pair<Point, Point> Maze::getPair(string & str)
{
	//检查输入字符的合法性
	for(size_t i=0; i< str.size(); i++){
		if(str[i] == '0' || str[i] =='1' || str[i] =='2' || str[i] =='3'
			 || str[i] == '4' || str[i] == '5' || str[i] == '6' || str[i] == '7'
			 || str[i] == '8' || str[i] == '9' || str[i] == ' '
			 || str[i] == ',' || str[i] == ';')
			 continue;
		else {
			cout << "Invalid number format.\n";
			exit(0);
		}

	}

	Point p1, p2;
	size_t  found = str.find(" ");
	assert(found != string::npos);
	string tmp1 = str.substr(0,found);
	string tmp2 = str.substr(found+1,str.size()-found-1);

	found = tmp1.find(",");
	assert(found != string::npos);
	string tmpX = tmp1.substr(0,found);
	string tmpY = tmp1.substr(found+1,tmp1.size()-found-1);

	p1.x = atoi(tmpX.c_str());
	if(p1.x < 0 || p1.x > rows){
		cout << "Number out of range.\n";
		exit(0);
	}
	p1.y = atoi(tmpY.c_str());
	if(p1.y < 0 || p1.y > cols){
		cout << "Number out of range.\n";
		exit(0);
	}


	found = tmp2.find(",");
	assert(found != string::npos);
	tmpX = tmp2.substr(0,found);
	tmpY = tmp2.substr(found+1,tmp2.size()-found-1);
	
	p1.x = atoi(tmpX.c_str());
	if(p1.x < 0 || p1.x > rows){
		cout << "Number out of range.\n";
		exit(0);
	}
	p1.y = atoi(tmpY.c_str());
	if(p1.y < 0 || p1.y > cols){
		cout << "Number out of range.\n";
		exit(0);
	}

	pair<Point,Point> p = make_pair(p1,p2);
	return p;
}



int main(){
	//测试用例
	
	string str1;
	string str2;
	char ch;
	while((ch=getchar()) != '\n'){
		str1.push_back(ch);
	}
	while((ch=getchar()) != '\n'){
		str2.push_back(ch);
	}
	Maze maze(str1);
	vector<vector<char> > render = maze.getRender(str2);
	for(size_t i =0; i < render.size();i++){
		for(size_t j=0; j < render[i].size();j++){
			cout << "[" << render[i][j] << "]" << " ";
		}
		cout << endl;
	}

	return 0;
}

