#include"GeneralArray.h"

using namespace std;

float& GeneralArray::operator[](int index){
    if(index < 0 || index >= size){
        throw "OutOfIndex";
    }
    return arr[index];
}

float GeneralArray::operator[](int index) const{
    if(index < 0 || index >= size){
        throw "OutOfIndex";
    }
    return arr[index];
}


int GeneralArray::GetSize() const{
    return size;
}

GeneralArray::GeneralArray(int size, float initialValue)
    :size(size)
{
    arr= new float[size];
    fill_n(arr,size,initialValue);
}

GeneralArray::GeneralArray(const GeneralArray& ga){
    arr = new float[ga.size];
    size = ga.size;
    copy(ga.arr,ga.arr+ga.size,arr);
}

GeneralArray& GeneralArray::operator=(const GeneralArray& right){
    delete[] arr;
    arr= new float[right.size];
    copy(right.arr,right.arr + right.size,this->arr);
    this->size = right.size;
    return *this;
}

ostream& operator<<(ostream& os,const GeneralArray& arr){
    for(int i=0;i<arr.size;i++){
        os<<arr[i]<<" ";
    }
    os<<endl;
    return os;
}

istream& operator>>(istream& is, GeneralArray& arr){
    is>>arr[arr.size];

    return is;
}

GeneralArray::~GeneralArray(){
    delete[] arr;
}