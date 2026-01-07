#include"../4.3_TplChian/TemplateLL.h"

template<typename T>
class LinkedStack : public LinkedList<T>{
    public:
        LinkedStack() : LinkedList<T>() {}
        void Push(const T& data){
            this->PushFront(data);
        }
        void Pop(){
            this->PopFront();
        }
        T Top() const{
            return this->first->data;
        }
        bool IsEmpty() const{
            return this->first ==nullptr;
        }
};