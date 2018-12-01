#include <iostream>
#include <map>
using namespace std;

class solution{
   public:
   typedef void (solution::*Fun)(string str);//function pointer
   typedef std::function<void ()> Task;
   unordered_map<string,int> um;
   unordered_map<string,Fun> um_callback; 
   solution(){
       um[""] = 0;
   }
   bool createFile(string path,int id){
       if(um.find(path) != um.end())
           return false;
       int found = path.find_last_of('/');
       string lPath = path.substr(0,found);
       if(um.find(lPath) == um.end()){
           return false;
       }
       um[path] = id;
       watch(path);
       
       if(lPath != ""){
           while(lPath != ""){
               (this->*(um_callback[lPath]))(lPath);
               found = lPath.find_last_of('/');
               lPath = lPath.substr(0,found);
           }   
       }
       return true;
   }
   int getFile(string path){
       if(um.find(path) != um.end())
           return um[path];
       return -1;
   }

   void printPath(string str){
       std::cout<<"watch:"<<str<<std::endl;     
   }
    
   void watch(string path){
       if(um.find(path) == um.end())
           return;
       um_callback[path] = &solution::printPath;
       return;
   }
   
};

int main() {
    string path1 = "/a";
    string path2 = "/a/b";
    string path3 = "/c/b";
    string path4 = "/a/b/c";
    solution s;
    bool res = s.createFile(path1,1);
    std::cout << "createFile1\n" << res << endl;
    res = s.createFile(path2,2);
    std::cout << "createFile2\n" << res << endl;
    res = s.createFile(path3,3);
    std::cout << "createFile3\n" << res << endl;
    res = s.createFile(path4,4);
    std::cout << "createFile4\n" << res << endl;
    int id = s.getFile(path2);
    std::cout << "getFile 2\n" << id << endl;
}
