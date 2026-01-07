#ifndef STACK_H
#define STACK_H
#include<iostream>
using namespace std;

template<typename T>
class Stack{
public:
    Stack(int capacity=10);
    Stack(const Stack& stack)
        :Stack(stack.capacity)
    {
        this->size=stack.size;
        
        for(int i=0;i<size;i++){
            arr[i]=stack.arr[i];
        }
    }
    Stack& operator=(const Stack& stack){
        this->capacity=stack.capacity;
        this->size=stack.size;
        this->arr=new T[stack.capacity];
        for(int i=0;i<size;i++){
            arr[i]=stack.arr[i];
        }
        return *this;
    }
    bool isEmpty()const;
    T& Top();
    T Top() const;
    void Push(const T& item);
    void Pop();
    //스택 출력
    //friend ostream& operator<<(ostream& os,const Stack& stack);
    friend ostream& operator<<(ostream& os,const Stack& stack){
         for(int i=0;i<stack.size;i++){
            os<<stack.arr[i]<<" ";
        }
        os<<endl;
        return os;
    }
    int GetSize() const{
        return size;
    }
    //스택 반 나누기
    Stack& SplitHalf();
    //스택 두개 합치기
    Stack& MergeStack(const Stack& stack)const;
private:
    T* arr;
    int capacity;
    int size;
};

template<typename T>
ostream& operator<<(ostream& os,const Stack<T>& stack){
        for(int i=0;i<stack.size;i++){
        os<<stack.arr[i]<<" ";
    }
    os<<endl;
    return os;
}

template <typename T>
inline Stack<T>::Stack(int capacity)
    : capacity(capacity), size(0)
{
    if(capacity<1) throw "capacity is more than 1";
    arr=new T[capacity];
}

template <typename T>
bool Stack<T>::isEmpty() const
{
    return size==0;
}

template <typename T>
T Stack<T>::Top() const
{
    if(isEmpty()){
        throw "Stack is Empty";
    }
    return arr[size-1];
}

template <typename T>
T& Stack<T>::Top()
{
    if(isEmpty()){
        throw "Stack is Empty";
    }
    return arr[size-1];
}

template <typename T>
void Stack<T>::Push(const T &item)
{
    if(capacity==size){
        capacity*=2;
        T* temp=new T[capacity];
        copy(arr,arr+size,temp);
        delete[] arr;
        arr=temp;
    }
    arr[size]=item;
    size++;
}

template <typename T>
void Stack<T>::Pop()
{
    if(isEmpty()){
        throw "Stack is Empty";
    }
    size--;
}

template <typename T>
Stack<T> &Stack<T>::SplitHalf()
{
    if(isEmpty()){
        throw "stack is empty!";
    }
    int half=size/2;
    Stack<T>* ret=new Stack<T>();
    for(int i=half;i<size;i++){
        ret->Push(arr[i]);
    }
    cout<<"half:"<<half<<" size:"<<size<<endl;
    int intitalSize=size;
    for(int i=half;i<intitalSize;i++){
        cout<<"Pop"<<endl;
        Pop();
    }
    
    return *ret;
}

template <typename T>
Stack<T> &Stack<T>::MergeStack(const Stack &stack) const
{
    Stack<T>* ret=new Stack<T>(size + stack.size);
    
    for(int index=0;index<size;index++){
        ret->Push(arr[index]);
    }
    for(int index=0;index<stack.size;index++){
        ret->Push(stack.arr[index]);
    }
    return *ret;
}

/*template<typename T>
ostream& operator<<(ostream& os,const Stack<T>& stack){
    for(int i=0;i<stack.size;i++){
        os<<stack.arr[i]<<" ";
    }
    os<<endl;
}
*/
#endif