#ifndef MAP_HPP
#define MAP_HPP
#include <iostream>
#include <vector>
#include "bottle.hpp"
struct form_to{
    int form;
    int to;
    bool operator==(form_to&);
    bool operator!=(form_to&);
};
bool bt_sort(bottle*,bottle*);
class MAP{
    public:
        MAP(uint num,uint size);
        MAP(const MAP&);
        MAP(MAP&&);
        MAP& operator=(const MAP&);
        ~MAP();
        void show_bottle();
        int get_colorsize();
        void reset();
        bool setcolor(int,int,char);
        bool operator==(const MAP&);
        bool isOK();
        int get_path_size();
        void down();
        void showpath();
		bool ckdead(int);
        bool is_dead();
    //private:
        int size;
        std::vector<form_to> *path;
        std::vector<bottle> *list;
};
#endif