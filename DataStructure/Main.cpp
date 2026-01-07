#include <iostream>
#include "Ch02_Array/GeneralArray.h"
using namespace std;

int main(){
    GeneralArray arr;
    arr[3]= 8;
    cout<<arr;
    cout<<arr.GetSize()<<endl;
    return 0;
}