#include "map.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include "bottle.hpp"

bool form_to::operator==(form_to &a){
	return form==a.form && to==a.to;
}
bool form_to::operator!=(form_to &a){
	return form!=a.form || to!=a.to;
}

bool bt_sort(bottle* a,bottle* b){
    return a->get_w()<b->get_w();
}
MAP::MAP(uint num,uint size){
	list = new std::vector<bottle>();
	path = new std::vector<form_to>();
	for(int i=0;i<num;i++){
		list->push_back( bottle(size) );
	}
	this->size=size;
}
MAP::MAP(const MAP &bot){
	size=bot.size;
	list = new std::vector<bottle>();
	path = new std::vector<form_to>();
	*(list)=*(bot.list);
	*(path)=*(bot.path);
}
MAP::MAP(MAP &&bot){
	size=bot.size;
	list = new std::vector<bottle>();
	path = new std::vector<form_to>();
	*(list)=*(bot.list);
	*(path)=*(bot.path);
}

MAP& MAP::operator=(const MAP &bot){
	if(this != &bot) {
		size=bot.size;
		list = new std::vector<bottle>();
		path = new std::vector<form_to>();
		*(list)=*(bot.list);
		*(path)=*(bot.path);
	}
	return *this;
}
MAP::~MAP(){
	delete list;
	delete path;
}
void MAP::show_bottle(){
	int t = list->size()/2;
	int b = list->size()/2;
	if(t+b != list->size()) t++;

	for(int i=0;i<t;i++){
		std::cout<<"\t"<<i;
	}std::cout<<std::endl;
	for(int lv=size-1;lv>=0;lv--){
		for(int i=0;i<t;i++)
			std::cout<<"\t|"<<(*list)[i].contents[lv]<<"|";
		std::cout<<std::endl;
	}
	for(int i=0;i<t;i++)
		std::cout<<"\t|-|";
	std::cout<<std::endl<<std::endl;

	for(int i=t;i<b+t;i++)
		std::cout<<"\t"<<i;
	std::cout<<std::endl;
	for(int lv=size-1;lv>=0;lv--){
		for(int i=t;i<b+t;i++)
			std::cout<<"\t|"<<(*list)[i].contents[lv]<<"|";
		std::cout<<std::endl;
	}
	for(int i=t;i<b+t;i++)
		std::cout<<"\t|-|";
	std::cout<<std::endl;
}
int MAP::get_colorsize(){
	int count[26];
	for(int i=0;i<26;i++) count[i]=0;
	
	for(std::vector<bottle>::iterator it=list->begin();it!=list->end();it++){
		for(int i=0;i<size;i++)
		if( (it->contents)[i]!=' '){
			count[(it->contents)[i]-'A']++;
		}
	}
	int num=0;
	for(int i=0;i<26;i++){
		if(count[i]==size) num++;
		else if(count[i]!=0) return 0;
	}
	return num;
}
void MAP::reset(){
	for(std::vector<bottle>::iterator it=list->begin();it!=list->end();it++)
		for(int i=0;i<size;i++)
			(it->contents)[i]=' ';
}
bool MAP::setcolor(int id,int loc,char type){
	if(id>=list->size()) return false;
	if(loc>=size) return false;
	if( (type<'A' || type >'Z') && type!=' ' ) return false;
	std::vector<bottle>::iterator it=list->begin()+id;
	(it->contents)[loc]=type;
	return true;
}
bool MAP::operator==(const MAP &map){
	std::vector<bottle*> a;
	for(std::vector<bottle>::iterator it=this->list->begin();it!=this->list->end();it++){
		a.push_back(&(*it));
	}
	std::vector<bottle*> b;
	for(std::vector<bottle>::iterator it=map.list->begin();it!=map.list->end();it++){
		b.push_back(&(*it));
	}
	if(a.size()!=b.size()) return false;
	std::sort(a.begin(),a.end(),bt_sort);
	std::sort(b.begin(),b.end(),bt_sort);
	for(int i=0;i<a.size();i++){
		if(a[i]->get_w()!=b[i]->get_w()) return false;
	}
	return true;
}
bool MAP::isOK(){
	for(std::vector<bottle>::iterator it=this->list->begin();it!=this->list->end();it++){
		if(!(it->is_empty() || it->is_finish())) return false;
	}
	return true;
}
int MAP::get_path_size(){
	return path->size();
}
void MAP::down(){
	for(std::vector<bottle>::iterator it=this->list->begin();it!=this->list->end();it++){
		it->sort();
	}
}
void MAP::showpath(){
	for(int i=0;i<path->size();i++){
		std::cout<<"step "<<i+1<<" : "<<path->at(i).form<<" to "<< path->at(i).to<<std::endl;
	}
}
bool MAP::ckdead(int n){
	if(path->size() >= n*2){
		int begin=path->size()-(n*2);
		if(path->at(begin+0)!=path->at(begin+n)) return false;
		for(int i=0;i<n;i++){
			form_to A=path->at(begin+i);
			form_to B=path->at(begin+i+1);
			if(A.form != B.to) return false;
		}
		return true;
	}else{
		return false;
	}
}
bool MAP::is_dead(){
	bool t3=ckdead(3);
	bool t7=ckdead(7);
	bool t10=ckdead(10);
	return t3||t7 || t10;
}
