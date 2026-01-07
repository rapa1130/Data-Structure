#pragma once
#include<iostream>
#include<vector>
#include"../3.2_Stack/Stack.h"

#define MAX_ROW 12
#define MAX_COL 15
#define DIR_NUM 8

using namespace std;

typedef pair<int,int> Coordinate;
enum MAP_TYPE{VOID,WALL};

int dx[DIR_NUM]={-1,0,1,1,1,0,-1,-1};
int dy[DIR_NUM]={-1,-1,-1,0,1,1,1,0};

class Maze{
public:
    Maze();
    Stack<Coordinate> FindRoute(const Coordinate& start,const Coordinate& dest) const;
    void PrintMaze() const;
    void PrintMazeRoute(const Coordinate& start,const Coordinate& dest,const Stack<Coordinate>& route)const{
        int toPrint[MAX_ROW][MAX_COL];

        for(int i=1;i<MAX_ROW+1;i++){
            for(int j=1;j<MAX_COL+1;j++){
                toPrint[i-1][j-1]=space[i][j];
            }
        }
        Stack<Coordinate> temp = route;
        while(!temp.isEmpty()){
            Coordinate top= temp.Top();
            toPrint[top.second][top.first]= 2;
            temp.Pop();
        }

        for(int i=0;i<MAX_ROW;i++){
            for(int j=0;j<MAX_COL;j++){
                cout<<toPrint[i][j]<<" ";
            }
            cout<<endl;
        }
    }
private:
    int** space;
    int _space[12][15]={
        {0,1,0,0,0,1,1,0,0,0,1,1,1,1,1},
        {1,0,0,0,1,1,0,1,1,1,0,0,1,1,1},
        {0,1,1,0,0,0,0,1,1,1,1,0,0,1,1},
        {1,1,0,1,1,1,1,0,1,1,0,1,1,0,0},
        {1,1,0,1,0,0,1,0,1,1,1,1,1,1,1},
        {0,0,1,1,0,1,1,1,0,1,0,0,1,0,1},
        {0,0,1,1,0,1,1,1,0,1,0,0,1,0,1},
        {0,1,1,1,1,0,0,1,1,1,1,1,1,1,1},
        {0,0,1,1,0,1,1,0,1,1,1,1,1,0,1},
        {1,1,0,0,0,1,1,0,1,1,0,0,0,0,0},
        {0,0,1,1,1,1,1,0,0,0,1,1,1,1,0},
        {0,1,0,0,1,1,1,1,1,0,1,1,1,1,0}
    };
};


template<typename T>
T** Alloc2D(int row,int col){
    T** ret=new T*[row];
    for(int i=0;i<row;i++){
        ret[i]=new T[col];
    }
    return ret;
}

Maze::Maze()
{
    int newRow=MAX_ROW+2;
    int newCol=MAX_COL+2;
    space=Alloc2D<int>(newRow,newCol);
    for(int i=0;i<MAX_ROW+2;i++){
        space[i][0] = space[i][newCol-1] = MAP_TYPE::WALL;
    }
    for(int i=0;i<MAX_COL+2;i++){
        space[0][i] = space[newRow - 1][i] = MAP_TYPE::WALL;
    }

    for(int i=0;i<MAX_ROW;i++){
        for(int j=0;j<MAX_COL;j++){
            space[i+1][j+1]=_space[i][j];
        }
    }
}



Stack<Coordinate> Maze::FindRoute(const Coordinate& start,const Coordinate& dest) const
{
    int coverdRowSize = MAX_ROW+2;
    int coverdColSize = MAX_COL+2;
    bool** close = Alloc2D<bool>(coverdRowSize,coverdColSize);
    bool** open = Alloc2D<bool>(coverdRowSize,coverdColSize);
    Coordinate** parent=Alloc2D<Coordinate>(coverdRowSize,coverdColSize);
    Stack<Coordinate> toGo;
    Stack<Coordinate> route;
    Stack<Coordinate> bestRoute;
    int bestRouteSize=INT32_MAX;
    toGo.Push(Coordinate(start.first,start.second));
    open[start.second][start.first] = true;
    parent[start.second][start.first] = start;

    while(!toGo.isEmpty()){
        const Coordinate top = toGo.Top();
        if(top==dest){
            route.Pop();
            toGo.Pop();
            close[top.second][top.first]=false;
            open[top.second][top.first]=false;
            if(route.GetSize()<bestRouteSize){
                bestRoute=route;
                bestRouteSize=route.GetSize();
            }
            continue;
        }
        
        toGo.Pop();
        if(close[top.second][top.first]){
            continue;
        }
        route.Push(top);
        close[top.second][top.first]=true;
        
        
        bool canMove=false;
        for(int i=0;i<DIR_NUM;i++){
            int nextX = top.first + dx[i];
            int nextY = top.second + dy[i];
            if(space[nextY][nextX]==MAP_TYPE::WALL){
                continue;
            }
            if(open[nextY][nextX]){
                continue;
            }
            if(close[nextY][nextX]){
                continue;
            }
            canMove=true;
            open[nextY][nextX]=true;
            toGo.Push(Coordinate(nextX,nextY));
            parent[nextY][nextX]=top;
        }

        if(!canMove && !toGo.isEmpty()){
            Coordinate target = parent[toGo.Top().second][toGo.Top().first];
            
            while(!route.isEmpty()){
                if(target==route.Top()) break;
                route.Pop();
            }
        }
    }
    return bestRoute;
}


void Maze::PrintMaze() const
{
    for(int i=1;i<MAX_ROW+1;i++){
        for(int j=1;j<MAX_COL+1;j++){
            cout<<space[i][j]<<" ";
        }
        cout<<endl;
    }

}

