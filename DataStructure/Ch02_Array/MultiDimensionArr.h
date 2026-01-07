#include<iostream>
using namespace std;

class MultiDimensionArr{
public:
    //차원수, 차원의 범위를 입력으로 받는 생성자
    MultiDimensionArr(int dimension,int* indexStart,int* indexFinish);
    
    //배열 지정(원소)
    float& GetElement(int* indexes);
    //다른 배열을 이용한 배열 초기화
    MultiDimensionArr(const MultiDimensionArr& MDArr);
    
    //배열 범위 및 크기 동적 변경
    void ResizeDimension(int newDimension,int* indextStart,int* indexFinish);
    //배열 크기 판단할 수 있는 방법 제공.
    int GetArrSize()const;
    int GetDimensizeSize(int dimension) const;
    //파일을 통한 배열 입출력
    friend ostream& operator<<(ostream& os,const MultiDimensionArr& MDArr);
    friend istream& operator>>(istream& is,MultiDimensionArr& MDArr);
private:
    //1차원 배열
    float* arr;
    //차원 크기
    int dimensionSize;
    //각 차원별 시작(인덱스)
    int* indexStart;
    //각 차원별 끝(인덱스)
    int* indexFinish;

    //범위 점검(차원별?)
    bool IsRightIndexAt(int index,int dimension);
};