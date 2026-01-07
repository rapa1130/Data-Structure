#include<iostream>
using namespace std;

const int DEFAULT_SIZE = 10;
const float DEFAULT_VALUE = 0.0f;

class GeneralArray{
    public:
        float& operator[](int index);
        float operator[](int index) const;
        int GetSize() const;
        GeneralArray(int size = DEFAULT_SIZE, float initialzeValue = DEFAULT_VALUE);
        GeneralArray(const GeneralArray& ga);
        GeneralArray& operator=(const GeneralArray& right);
        friend ostream& operator<<(ostream& os,const GeneralArray& a);
        friend istream& operator>>(istream& is,GeneralArray& a);
        ~GeneralArray();
        
    private:
        float* arr;
        int size;
};


