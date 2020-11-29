#include "bottle.hpp"
#include <iostream>
#include <vector>

bottle::bottle(const bottle &bot){
	SIZE=bot.SIZE;
	contents=new char[SIZE];
	for(int i=SIZE-1;i>=0;i--)
		contents[i]=bot.contents[i];
}
bottle::bottle(bottle &&bot){
	SIZE=bot.SIZE;
	contents=new char[SIZE];
	for(int i=SIZE-1;i>=0;i--)
		contents[i]=bot.contents[i];
}

bottle& bottle::operator=(const bottle &bot){
	if(this != &bot) {
		SIZE=bot.SIZE;
		delete contents;
		contents=new char[SIZE];
		for(int i=SIZE-1;i>=0;i--)
			contents[i]=bot.contents[i];
	}
	return *this;
}
bottle::bottle(uint size){
	SIZE=size;
	contents=new char[size];
	for(int i = size - 1 ; i>=0 ; i--){
		contents[i]=' ';
	}
}
bottle::~bottle(){
	delete [] contents;
}
char bottle::get_top_color(){
	for(int i=SIZE-1;i>=0;i--){
		if(contents[i]!=' ')
			return contents[i];
	}
	return ' ';
}
bool bottle::is_finish(){
	char a=contents[0];
	if(a==' ') return false;
	for(int i=1;i<SIZE;i++){
		if(contents[i]!=a){
			return false;
		}
	}
	return true;
}
bool bottle::is_onecolor(){
	char a=contents[0];
	if(a==' ') return true;
	for(int i=1;i<SIZE;i++){
		if(contents[i]!=a && contents[i]!=' '){
			return false;
		}
	}
	return true;
}
bool bottle::is_full(){
	return contents[SIZE-1]!=' ';
}
bool bottle::is_empty(){
	return contents[0]==' ';
}
int bottle::operator<<(bottle &bot){//倒入
	
	
	if(bot.is_finish()) return 0;
	if(bot.get_top_color()!=this->get_top_color() && (!this->is_empty()) ) return 0;
	if(this->is_full()) return 0;
	if(bot.is_empty()) return 0;
	if(bot.is_onecolor() && this->is_empty()) return 0;//無意義動作過濾
	int indexa=0;
	for(int i=0;i<SIZE;i++){
		if(contents[i]==' '){
			indexa=i;
			break;
		}
	}
	int indexb=0;
	for(int i=0;i<SIZE;i++){
		if(bot.contents[i]!=' ')
			indexb=i;
	}
	contents[indexa]=bot.contents[indexb];
	bot.contents[indexb]=' ';
	int m = (*this)<<bot;
	return m+1;
}
bool bottle::operator>>(bottle &bot){//強制倒入1格
	
	if(bot.is_full()) return false;
	if(this->is_empty() ) return false;
	int indexa=0;
	for(int i=0;i<SIZE;i++){
		if(contents[i]!=' ')
			indexa=i;
	}
	int indexb=0;
	for(int i=0;i<SIZE;i++){
		if(bot.contents[i]==' '){
			indexb=i;
			break;
		}
	}
	bot.contents[indexb]=contents[indexa];
	contents[indexa]=' ';
	return true;
}
void bottle::sort(){
	std::vector<int> index;
	for(int i=0;i<SIZE;i++)
		if(contents[i]!=' ') index.push_back(i);
	int i=0;
	for(;i<index.size();i++){
		contents[i]=contents[index[i]];
	}
	for(;i<SIZE;i++){
		contents[i]=' ';
	}
}
unsigned long bottle::get_w(){
	unsigned long w=0;
	unsigned long p=1;
	for(int i=0;i<SIZE;i++){
		unsigned long a=0;
		if(contents[i]>='A' && contents[i]<='Z'){
			a=(contents[i]-'A'+1);
		}
		w+=a*p;
		p=p*27;
	}
	return w;
	
}
