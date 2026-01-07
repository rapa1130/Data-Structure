#include"MultiDimensionArr.h"

MultiDimensionArr::MultiDimensionArr(int dimension, int *indexStart, int *indexFinish)
    :dimensionSize(dimension)
{
    this->indexStart=new int[dimension];
    this->indexFinish=new int[dimension];
    copy(indexStart,indexStart+dimension,this->indexStart);
    copy(indexFinish,indexFinish+dimension,this->indexFinish);
    arr=new float[GetArrSize()];
}

float& MultiDimensionArr::GetElement(int *indexes)
{
    int nowIndex=0;
    int nowDimensionSize=1;
    for(int dimension=dimensionSize-1;dimension>=0;dimension--){
        if(!IsRightIndexAt(indexes[dimension],dimension)){
            throw -1;
        }
        nowIndex += (indexes[dimension]-indexStart[dimension]) * nowDimensionSize;
        nowDimensionSize*=GetDimensizeSize(dimension);
    }
    return arr[nowIndex];
}

MultiDimensionArr::MultiDimensionArr(const MultiDimensionArr &MDArr)
    :dimensionSize(MDArr.dimensionSize)
{
    copy(MDArr.arr,MDArr.arr+MDArr.dimensionSize,arr);
    copy(MDArr.indexStart,MDArr.indexStart+MDArr.dimensionSize,indexStart);
    copy(MDArr.indexFinish,MDArr.indexFinish+MDArr.dimensionSize,indexFinish);
}

void MultiDimensionArr::ResizeDimension(int newDimension,int* indexStart,int* indexFinish)
{
    dimensionSize=newDimension;
    copy(indexStart,indexStart+newDimension,this->indexStart);
    copy(indexFinish,indexFinish+newDimension,this->indexFinish);
    int newArrSize=GetArrSize();
    float* temp=new float[newArrSize];
    copy(arr,arr+newArrSize,temp);
}


int MultiDimensionArr::GetArrSize() const
{
    int nowDimension=dimensionSize-1;
    int nowSize=1;
    for(;nowDimension>=0;nowDimension--){
        nowSize*=GetDimensizeSize(nowDimension);
    }
    return nowSize;
}

int MultiDimensionArr::GetDimensizeSize(int dimension) const
{
    return indexFinish[dimension]- indexStart[dimension]+1;
}

bool MultiDimensionArr::IsRightIndexAt(int index, int dimension)
{
    return indexStart[dimension]<=index && indexFinish[dimension]>=index;
}

ostream &operator<<(ostream &os, const MultiDimensionArr &MDArr)
{
    for(int index=0;index<MDArr.GetArrSize();index++){
        os<<MDArr.arr[index]<<" ";
    }

    return os;
}

istream &operator>>(istream &is, MultiDimensionArr &MDArr)
{
    for(int index=0;index<MDArr.GetArrSize();index++){
        is>>MDArr.arr[index];
    }

    return is;
}


/*
#include"Ch2/MultiDimensionArr.h"
#include<fstream>
using namespace std;
int main(){
	int* indexStart=new int[2];
	int* indexFinish=new int[2];
	indexStart[0]=indexStart[1]=-1;
	indexFinish[0]=indexFinish[1]=1;
	MultiDimensionArr arr(2,indexStart,indexFinish);

	int* indexes=new int[2];
	indexes[0]=-1;
	indexes[1]=-1;
	arr.GetElement(indexes)=1;

	indexes[0]=-1;
	indexes[1]=0;
	arr.GetElement(indexes)=2;

	indexes[0]=0;
	indexes[1]=-1;
	arr.GetElement(indexes)=3;

	indexes[0]=0;
	indexes[1]=0;
	arr.GetElement(indexes)=4;
	
	//파일 출력
	
	ofstream ofs;
	ofs.open("MultiArr.txt");
	ofs<<arr;
	

	//파일 입력
	
	ifstream ifs;
	ifs.open("MultiArr.txt");
	ifs>>arr;
	cout<<arr;
	
}*/