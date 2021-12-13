#ifndef BOTTLE_HPP
#define BOTTLE_HPP
#include <iostream>
#include <vector>

class bottle{
    public:
        bottle(uint);
        bottle(const bottle&);
        bottle(bottle &&bot);
        bottle& operator=(const bottle&);
        ~bottle();
        char get_top_color();//取得瓶子最頂部的顏色
        bool is_finish();//瓶子是否裝滿且只有一種顏色
	bool is_onecolor();//瓶子是否只有一種顏色
        bool is_full();//瓶子是否為滿的
        bool is_empty();//瓶子是否為空的
        int operator<<(bottle&);
        bool operator>>(bottle&);
        void sort();//將瓶內空格全部往上
        unsigned long get_w();//取得瓶子特徵值
        char *contents;//0:buttom 3:top 
        uint SIZE;
};

#endif
