#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;
//typedef unsigned int uint;
void clear_screen();
void pause();
void splitstring(const std::string&, std::vector<std::string>&, const std::string&);
class bottle{
    public:
        bottle(const bottle &bot){
            SIZE=bot.SIZE;
            contents=new char[SIZE];
            for(int i=SIZE-1;i>=0;i--)
                contents[i]=bot.contents[i];
        }
        bottle(bottle &&bot){
            SIZE=bot.SIZE;
            contents=new char[SIZE];
            for(int i=SIZE-1;i>=0;i--)
                contents[i]=bot.contents[i];
        }
        /*bottle(){
            SIZE=0;
            contents=NULL;
        }*/
        bottle& operator=(const bottle &bot){
            if(this != &bot) {
                SIZE=bot.SIZE;
                delete contents;
                contents=new char[SIZE];
                for(int i=SIZE-1;i>=0;i--)
                    contents[i]=bot.contents[i];
            }
            return *this;
        }
        bottle(uint size){
            SIZE=size;
            contents=new char[size];
            for(int i = size - 1 ; i>=0 ; i--){
                contents[i]=' ';
            }
        }
        ~bottle(){
            delete [] contents;
        }
        char get_top_color(){
            for(int i=SIZE-1;i>=0;i--){
                if(contents[i]!=' ')
                    return contents[i];
            }
            return ' ';
        }
        bool is_finish(){
            char a=contents[0];
            if(a==' ') return false;
            for(int i=1;i<SIZE;i++){
                if(contents[i]!=a){
                    return false;
                }
            }
            return true;
        }
        bool is_full(){
            return contents[SIZE-1]!=' ';
        }
        bool is_empty(){
            return contents[0]==' ';
        }
        bool operator<<(bottle &bot){
            //cout<<bot.contents[0]<<","<<bot.contents[1]<<","<<bot.contents[2]<<","<<bot.contents[3]<<endl;
            //cout<<this->contents[0]<<","<<contents[1]<<","<<contents[2]<<","<<contents[3]<<endl;
            
            if(bot.is_finish()) return false;
            if(bot.get_top_color()!=this->get_top_color() && (!this->is_empty()) ) return false;
            if(this->is_full()) return false;
            if(bot.is_empty()) return false;

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

            (*this)<<bot;

            return true;
        }
        void sort(){
            vector<int> index;
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
        unsigned long get_w(){
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
        char *contents;//0:buttom 3:top 
        uint SIZE;
};
struct form_to{
    int form;
    int to;
    bool operator==(form_to &a){
        return form==a.form && to==a.to;
    }
    bool operator!=(form_to &a){
        return form!=a.form || to!=a.to;
    }

};
bool bt_sort(bottle* a,bottle* b){
    return a->get_w()<b->get_w();
}
class MAP{
    public:
        MAP(uint num,uint size){
            list = new vector<bottle>();
            path = new vector<form_to>();
            for(int i=0;i<num;i++){
                list->push_back( bottle(size) );
            }
            this->size=size;
            /*for(vector<bottle>::iterator it=list->begin();it!=list->end();it++){
                cout<< (void*)it->contents <<endl;
            }*/
        }
        void clone(const MAP &bot){
            for(int i=0;i<bot.list->size();i++){
                list->push_back(bot.list->at(i));
            }
            for(int i=0;i<bot.path->size();i++){
                path->push_back(bot.path->at(i));
            }
        }
        MAP(const MAP &bot){
            //cout<<"I"<<endl;
            size=bot.size;
            list = new vector<bottle>();
            path = new vector<form_to>();
            //clone(bot);
            *(list)=*(bot.list);
            *(path)=*(bot.path);
        }
        MAP(MAP &&bot){
            //cout<<"II"<<endl;
            size=bot.size;
            list = new vector<bottle>();
            path = new vector<form_to>();
            //clone(bot);
            *(list)=*(bot.list);
            *(path)=*(bot.path);
        }

        MAP& operator=(const MAP &bot){
            //cout<<"III"<<endl;
            if(this != &bot) {
                size=bot.size;
                list = new vector<bottle>();
                path = new vector<form_to>();
                //clone(bot);
                *(list)=*(bot.list);
                *(path)=*(bot.path);
            }
            return *this;
        }
        ~MAP(){
            delete list;
            delete path;
        }
        void show_bottle(){
            int t = list->size()/2;
            int b = list->size()/2;
            if(t+b != list->size()) t++;

            for(int i=0;i<t;i++){
                cout<<"\t"<<i;
            }cout<<endl;
            for(int lv=size-1;lv>=0;lv--){
                for(int i=0;i<t;i++)
                    cout<<"\t|"<<(*list)[i].contents[lv]<<"|";
                cout<<endl;
            }
            for(int i=0;i<t;i++)
                cout<<"\t|-|";
            cout<<endl<<endl;

            for(int i=t;i<b+t;i++)
                cout<<"\t"<<i;
            cout<<endl;
            for(int lv=size-1;lv>=0;lv--){
                for(int i=t;i<b+t;i++)
                    cout<<"\t|"<<(*list)[i].contents[lv]<<"|";
                cout<<endl;
            }
            for(int i=t;i<b+t;i++)
                cout<<"\t|-|";
            cout<<endl;
        }
        int get_colorsize(){
            int count[26];
            for(int i=0;i<26;i++) count[i]=0;
            
            for(vector<bottle>::iterator it=list->begin();it!=list->end();it++){
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
        void reset(){
            for(vector<bottle>::iterator it=list->begin();it!=list->end();it++)
                for(int i=0;i<size;i++)
                    (it->contents)[i]=' ';
        }
        bool setcolor(int id,int loc,char type){
            if(id>=list->size()) return false;
            if(loc>=size) return false;
            if( (type<'A' || type >'Z') && type!=' ' ) return false;
            vector<bottle>::iterator it=list->begin()+id;
            (it->contents)[loc]=type;
            return true;
        }
        bool operator==(const MAP &map){
            vector<bottle*> a;
            for(vector<bottle>::iterator it=this->list->begin();it!=this->list->end();it++){
                a.push_back(&(*it));
            }
            vector<bottle*> b;
            for(vector<bottle>::iterator it=map.list->begin();it!=map.list->end();it++){
                b.push_back(&(*it));
            }
            if(a.size()!=b.size()) return false;
            sort(a.begin(),a.end(),bt_sort);
            sort(b.begin(),b.end(),bt_sort);
            for(int i=0;i<a.size();i++){
                if(a[i]->get_w()!=b[i]->get_w()) return false;
            }
            /*cout<<"equal"<<endl;
            for(int i=0;i<a.size();i++){
                cout<< a[i]->get_w()<<","<<b[i]->get_w()<<endl;
            }*/
            return true;
        }
        vector<MAP>* get_next(){
            vector<MAP> *other=new vector<MAP>();
            int s=list->size();
            for(int i=0;i<s;i++){
                for(int j=0;j<s;j++){
                    if(i!=j){
                        //cout<<"call clone"<<endl;
                        MAP tmp=(*this);
                        //cout<<"cmp "<<j<<" to "<<i<<endl;
                        if(tmp.list->at(i) << tmp.list->at(j)){
                            if(tmp.path->size()!=0){
                                form_to step=tmp.path->at(tmp.path->size()-1);
                                //cout<<"add"<<endl;
                                if(step.form != i || step.to!=j){
                                    if(!(tmp==(*this))){
                                        tmp.path->push_back({j,i});
                                        other->push_back(tmp);
                                    }
                                }
                            }else{
                                if(!(tmp==(*this))){
                                    tmp.path->push_back({j,i});
                                    other->push_back(tmp);
                                }
                            }
                        }
                    }
                }
            }
            //cout<<"return"<<endl;
            return other;
        }
        bool isOK(){
            for(vector<bottle>::iterator it=this->list->begin();it!=this->list->end();it++){
                if(!(it->is_empty() || it->is_finish())) return false;
            }
            return true;
        }
        int get_path_size(){
            return path->size();
        }
        void down(){
            for(vector<bottle>::iterator it=this->list->begin();it!=this->list->end();it++){
                it->sort();
            }
        }
        void showpath(){
            for(int i=0;i<path->size();i++){
                cout<<"step "<<i+1<<" : "<<path->at(i).form<<" to "<< path->at(i).to<<endl;
            }
        }
        bool is_dead(){
            bool t6=true;
            bool t4=true;
            if(path->size() >= 6){
                int begin=path->size()-6;
                if(path->at(begin+0)!=path->at(begin+3)) t6=false;
                if(path->at(begin+1)!=path->at(begin+4)) t6=false;
                if(path->at(begin+2)!=path->at(begin+5)) t6=false;
            }else{
                t6=false;
            }
            if(path->size() >= 4){
                int begin=path->size()-4;
                if(path->at(begin+0)!=path->at(begin+2)) t4=false;
                if(path->at(begin+1)!=path->at(begin+3)) t4=false;
            }else{
                t4=false;
            }
            if(t4||t6) cout<<"is dead"<<endl;
            return t4||t6;
        }
    //private:
        int size;
        vector<form_to> *path;
        vector<bottle> *list;
};
int main(){
    unsigned int color,num,size;
    cout<< "輸入瓶子數量:";
    cin >> num;
    cout<< "輸入顏色數量:";
    cin >> color;
    if(color>26){
        cout<<"請輸入小於26的數值";
    }
    cout<< "輸入瓶子容量:";
    cin >> size;
    MAP map(num,size);
    //setmap
    string *name=new string[color];
    ifstream colorname("default_color.txt");
    if(!colorname){
        for(int i=0;i<color;i++){
            char c[2];c[0]='A'+i;c[1]='\0';
            name[i]=string(c);        
        }
    }else{
        for(int i=0;i<color;i++){
            colorname>>name[i];        
        }
        colorname.close();
    }
    int t = color/2;
    int b = color/2;
    if(t+b != color) t++;
    string log="";
    string cmd;
    getline(cin, cmd);
    while(1){
        clear_screen();
        map.show_bottle();
        for(int i=0;i<t;i++){
            char c[2];c[0]='A'+i;c[1]='\0';
            cout<<c<<": "<<name[i]<<"\t";
        }cout<<endl;
        for(int i=t;i<t+b;i++){
            char c[2];c[0]='A'+i;c[1]='\0';
            cout<<c<<": "<<name[i]<<"\t";
        }cout<<endl;
        cout<<"log:"<<log<<endl;
        cout<<"輸入操作：";
        getline(cin, cmd);
        vector<string> cmd_list;
        splitstring(cmd, cmd_list," ");
        if(cmd_list[0]=="start"||cmd_list[0]=="s"){
            if(map.get_colorsize()==color)
                break;
            else
                log="[start]錯誤！參數尚未設定完成！";
        }else if(cmd_list[0]=="exit"||cmd_list[0]=="e"){
            cout<<"Bey! Bey!"<<endl;
            exit(0);
        }else if(cmd_list[0]=="reset"||cmd_list[0]=="r"){
            map.reset();
            log="[reset] 設定完成！";
        }else if(cmd_list[0]=="setbottle"||cmd_list[0]=="sb"){
            if(cmd_list.size()<3){
                log = "[setbottle]參數量過少";
            }else{
                int id= atoi(cmd_list[1].c_str());
                if(id>=num || id<0){
                    log="[setbottle] bottle-id 超出範圍！";
                }else{
                    vector<char> type;
                    bool ok=true;
                    for(int i=2;i<cmd_list.size();i++){
                        string c=cmd_list[i];
                        if(c.size()!=1) ok=false;
                        char cc=c[0];
                        if(cc>='A' && cc< ('A'+color)){
                            type.push_back(cc);
                        }else{
                            ok=false;
                        }
                    }
                    if(!ok){
                        log="[setbottle]顏色標籤有誤！";
                    }else{
                        int loc=0;
                        for(;loc<type.size();loc++)
                            map.setcolor(id,loc,type[loc]);
                        for(;loc<size;loc++)
                            map.setcolor(id,loc,' ');
                        log="[setbottle] 設定完成！";
                    }
                }
            }
        }else if(cmd_list[0]=="setcolor"||cmd_list[0]=="sc"){
            if(cmd_list.size()!=4){
                log = "[setcolor]參數量錯誤";
            }else{
                int id= atoi(cmd_list[1].c_str());
                int loc= atoi(cmd_list[2].c_str());
                if(id>=num || id<0){
                    log="[setcolor] bottle-id 超出範圍！";
                }else if(loc>=size || loc<0){
                    log="[setcolor] loc 超出範圍！";
                }else{
                    string c=cmd_list[3];
                    if(c.size()!=1){
                        log="[setcolor] 顏色標籤有誤！";
                    }else{
                        char cc=c[0];
                        if(cc>='A' && cc< ('A'+color)){
                            map.setcolor(id,loc,cc);
                            log="[setcolor] 設定完成！";
                        }else{
                            log="[setcolor] 顏色標籤有誤！";
                        }
                    }
                }
            }
        }else if(cmd_list[0]=="renamecolor"||cmd_list[0]=="rn"){
            if(cmd_list.size()!=3){
                log = "[renamecolor]參數量錯誤";
            }else{
                string c=cmd_list[1];
                if(c.size()!=1){
                    log="[renamecolor] 顏色標籤有誤！";
                }else{
                    char cc=c[0];
                    if(cc>='A' && cc< ('A'+color)){
                        name[cc-'A']=cmd_list[2];
                        log="[renamecolor] 設定完成！";

                    }else{
                        log="[renamecolor] 顏色標籤有誤！";
                    }
                }
            }
        }else if(cmd_list[0]=="clear"||cmd_list[0]=="c"){
            if(cmd_list.size()!=2 && cmd_list.size()!=3){
                log = "[clear]參數量錯誤";
            }else{
                int id= atoi(cmd_list[1].c_str());
                if(id>=num || id<0){
                    log="[clear] bottle-id 超出範圍！";
                }else if(cmd_list.size()==2){
                    for(int loc=0;loc<size;loc++)
                        map.setcolor(id,loc,' ');
                    log="[clear] 設定完成！";
                }else{
                    int loc= atoi(cmd_list[2].c_str());
                    if(loc>=size || loc<0){
                        log="[clear] loc 超出範圍！";
                    }else{
                        map.setcolor(id,loc,' ');
                        log="[clear] 設定完成！";
                    }
                }
            }
        }else{
            log="查無命令！";
        }
    }
    cout<<"開始計算"<<endl;
    
    vector<MAP> pool;
    map.down();

    /*cout<<"TEST"<<endl;
    map.list->at(2) << map.list->at(1);
    cout<<"TEST END"<<endl;*/

    pool.push_back(map);
    int level=0;
    while(!pool.empty()){
        MAP X=pool[0];
        if(X.path->size()>level){
            level=X.path->size();
            cout<<level<<" "<<pool.size() <<endl;
        }
        pool.erase(pool.begin());//刪除頭
        vector<MAP>* other_path = X.get_next();
        /*if(other_path->size()==0)
            cout<<"dead path"<<endl;*/
        for(vector<MAP>::iterator it=other_path->begin();it!=other_path->end();it++){
            //cout<<" test"<<endl;
            if(it->isOK()){
                clear_screen();
                it->show_bottle();
                cout<<"找到路徑！！"<<endl;
                it->showpath();
                return 0;
            }
            //cout<<"find "<<pool.size()<<endl;
            vector<MAP>::iterator f = find(pool.begin(),pool.end(),*it);
            //cout<<"find end"<<endl;
            if(f == pool.end()){
                //cout<<"append"<<endl;
                if(! (it->is_dead()))
                    pool.push_back(*it);
            }/*else{
                if(f->path->size() > it->path->size()){
                    cout<<"swap"<<endl;
                    vector<form_to> *tmp=f->path;
                    f->path=it->path;
                    it->path=tmp;
                }
            }*/
            //cout<<"end "<<pool.size()<<endl;
        }

        //整理　刪除死迴圈





        //cout<<" test delete"<<endl;
        delete other_path;
        //cout<<" test delete"<<endl;
    }
    cout<<"FAIL！ 無法計算解答"<<endl;
    return 0;
}


void clear_screen(){
#if (defined(_WIN32) || defined(_WIN64)) 
    std::system("cls");
#else
    std::system ("clear");
#endif
}

void pause(){
#if (defined(_WIN32) || defined(_WIN64)) 
    std::system("pause");
#else
    std::system ("read -n 1 -p \"Press any key to continue...\" INP");
#endif
}
void splitstring(const std::string& s, std::vector<std::string>& v, const std::string& c){
	std::string::size_type pos1, pos2;
	pos2 = s.find_first_of(c);
	pos1 = 0;
	while (std::string::npos != pos2){
		if(pos2-pos1)
			v.push_back(s.substr(pos1, pos2 - pos1));
		pos1 = pos2 + 1;
		pos2 = s.find_first_of(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}