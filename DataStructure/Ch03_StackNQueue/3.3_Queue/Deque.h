#include<iostream>
using namespace std;

template<typename T>
class Deque{
public:
    Deque(int capacity=10)
        :capacity(capacity),front(0),rear(0)
    {
        arr=new T[capacity];
    }

    void Push_front(const T& item)
    {   
        if((rear+1)==front){
            T* temp = new T[capacity * 2];
            int start = (front + 1) % capacity;
            if(start < 2){
                copy(arr+start,arr+rear+1,temp);
            }else{
                copy(arr+start,arr+capacity,temp);
                copy(arr,arr+rear+1,temp+(capacity-start));
            }
            front = capacity * 2 - 1;
            rear = capacity - 2;
            capacity *= 2;
            delete[] arr;
            arr = temp;
        }
        arr[front]=item;
        front = (front-1 < 0) ? capacity-1 : front-1;
    }

    void Pop_front()
    {
        if(IsEmpty()) throw "Deque is Empty!";
        front = (front+1) % capacity;
    }

    void Push_back(const T& item)
    {
        if((rear+1)==front){
            T* temp=new T[capacity*2];
            int start = (front+1) % capacity;
            if(start<2){
                copy(arr+start,arr+rear+1,temp);
            }else{
                copy(arr+start,arr+capacity,temp);
                copy(arr,arr+rear+1,temp+(capacity-start));
            }
            front = 2 * capacity - 1;
            rear=capacity-2;
            capacity*=2;
            delete[] arr;
            arr=temp;
        }
        rear=(rear+1)%capacity;
        arr[rear]=item;
        
    }
    void Pop_back()
    {
        if(IsEmpty()) throw "Deque is Empty!";
        rear=(rear-1 < 0)? capacity - 1 : rear - 1;
    }
    T& Front() const
    {
        if(IsEmpty()) throw "Deque is Empty!";
        return arr[(front+1)%capacity];
    }
    T& Back() const
    {
        if(IsEmpty()) throw "Deque is Empty!";
        return arr[rear];
    }
    bool IsEmpty() const
    {
        return rear==front;
    }
    T& operator[](int index) const
    {
        if(IsEmpty()) throw "Deque is Empty!";
        return arr[index];
    }
    int GetCapacity() const
    {
        return capacity;
    }
    int GetSize() const
    {
        int ret = 0;
        //0인 케이스를 잘 살펴봐야함.
        if(front>rear){
            ret+=capacity-front -1;
            ret+=rear;
        }else{
            ret+=rear-front;
        }
        return ret;
    }
    void Print() const
    {
        int index=(front+1)%capacity;
        while(index!=((rear+1)%capacity)){
            cout<<arr[index]<<" ";
            index=(index+1)%capacity;
        }
        cout<<endl;
    }
private:
    T* arr;
    int capacity;
    int front;
    int rear;
};