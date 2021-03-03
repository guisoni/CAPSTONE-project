#ifndef Core_H
#define Core_H

#include <iostream>
class Core{
    public: 
     static Core *GetCore(){
        if(core_ == nullptr){
            core_= new Core(); 
            std::cout<<"Core Started\n"; 
            return core_;
        }
        return core_;
    }        
    static void FreeCore(){
        std::cout<<"Core Deleted\n";
        delete core_;
    }
    
    private:
    Core(){};
    
    static Core *core_; 
};
#endif

Core* Core::core_=nullptr;
int main(){
    Core::GetCore();
    Core::FreeCore();
}

