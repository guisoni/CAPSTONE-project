#ifndef Core_H
#define Core_H

class Core
    public: 
     static Core *GetCore(){
        if(core_ == nullptr){
            core_= new Core();  
            return core_;
        }
        return core_;
    }
    static Print(){
        std::cout<<"Core Started\n";
    }
    private:
    Core(){};
    ~Core(){delete core_;}
    static Core *core_; 
}
#endif

Core* Core::core_ = nullptr;
int main(){
    Core::StartCore();

}

