#include <iostream>
#include <string>
#include <vector>
#include <fstream>
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
                contents[i]=' ';
        }
        bottle(bottle &&bot){
            SIZE=bot.SIZE;
            contents=new char[SIZE];
            for(int i=SIZE-1;i>=0;i--)
                contents[i]=' ';
        }
        bottle(){
            SIZE=0;
            contents=NULL;
        }
        bottle& operator=(const bottle &bot){
            if(this != &bot) {
                SIZE=bot.SIZE;
                delete contents;
                contents=new char[SIZE];
                for(int i=SIZE-1;i>=0;i--)
                    contents[i]=' ';
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
            return 0;
        }

        bool operator<<(bottle &bot){
            return false;
        }
        char *contents;//0:buttom 3:top 
        uint SIZE;
};
struct form_to{
    char form;
    char to;
    bool operator==(form_to &a){
        form=a.form;
        to=a.to;
        return true;
    }
};
class MAP{
    public:
        int size;
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
        MAP(const MAP &bot){
            list = new vector<bottle>();
            path = new vector<form_to>();
            *(list)=*(bot.list);
            *(path)=*(bot.path);
        }
        MAP(MAP &&bot){
            list = new vector<bottle>();
            path = new vector<form_to>();
            *(list)=*(bot.list);
            *(path)=*(bot.path);
        }

        MAP& operator=(const MAP &bot){
            if(this != &bot) {
                list = new vector<bottle>();
                path = new vector<form_to>();
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

        
    private:
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
    pool.push_back(map);
    while(!pool.empty()){

        
    }
    cout<<"FAIL!！ 無法計算解答"<<endl;
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