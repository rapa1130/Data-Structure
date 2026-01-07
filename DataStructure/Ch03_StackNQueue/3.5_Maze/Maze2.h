#pragma once
#include<iostream>
#include"../3.2_Stack/Stack.h"
#define SPACE_MAX_SIZE 11
#define DIR_NUM 8
using namespace std;

typedef pair<int,int> Coordinate;
struct Node{
    Node(){}
    Node(int x,int y,int dir):coor(Coordinate(x,y)),dir(dir){}
    Node(const Coordinate& coor,int dir):coor(coor),dir(dir){}

    Coordinate coor;
    int dir;
};

int space[SPACE_MAX_SIZE][SPACE_MAX_SIZE]={
   {1,1,1,1,1,1,1,1,1,1,1},
   {1,0,0,0,0,0,0,0,0,1,1},
   {1,1,1,1,1,1,1,1,1,0,1},
   {1,1,0,0,0,0,0,0,0,1,1},
   {1,0,1,1,1,1,1,1,1,1,1},
   {1,1,0,0,0,0,0,0,0,1,1},
   {1,1,1,1,1,1,1,1,1,0,1},
   {1,1,0,0,0,0,0,0,0,1,1},
   {1,0,1,1,1,1,1,1,1,1,1},
   {1,1,0,0,0,0,0,0,0,0,1},
   {1,1,1,1,1,1,1,1,1,1,1}
};

int dx[DIR_NUM]={-1,0,1,1,1,0,-1,-1};
int dy[DIR_NUM]={-1,-1,-1,0,1,1,1,0};

class Maze2{
public:
    void ComputeRoute(Stack<Node> route){
        int toPrint[SPACE_MAX_SIZE][SPACE_MAX_SIZE];
        for(int i=0;i<SPACE_MAX_SIZE;i++){
            for(int j=0;j<SPACE_MAX_SIZE;j++){
                toPrint[i][j]=space[i][j];
            }
        }
        while(!route.isEmpty()){
            const Coordinate& top= route.Top().coor;
            route.Pop();
            toPrint[top.second][top.first]=2;
        }
        /*for(int i=1;i<SPACE_MAX_SIZE-1;i++){
            for(int j=1;j<SPACE_MAX_SIZE-1;j++){
                cout<<toPrint[i][j]<<" ";
            }
            cout<<endl;
        }*/
       for(int i=0;i<SPACE_MAX_SIZE;i++){
            for(int j=0;j<SPACE_MAX_SIZE;j++){
                cout<<toPrint[i][j]<<" ";
            }
            cout<<endl;
        }
    }

    Stack<Node> FindRoute(const Coordinate& start,const Coordinate& end){
        Stack<Node> nowRoute;
        bool mark[SPACE_MAX_SIZE][SPACE_MAX_SIZE]={false};

        nowRoute.Push(Node(start,-1));
        mark[start.second][start.first]=true;

        while(!nowRoute.isEmpty()){
            const Node& top=nowRoute.Top();
            //std::cout<<top.coor.first<<","<<top.coor.second<<endl;
            
            nowRoute.Pop();
            if(top.coor==end){
                break;
            }
            int nextDir=top.dir;
            int nowX=top.coor.first;
            int nowY=top.coor.second;
            for(;nextDir<DIR_NUM;nextDir++){
                cout<<nowRoute;

                int nextX = nowX + dx[nextDir];
                int nextY = nowY + dy[nextDir];
                if(nextX<0 || nextX>=SPACE_MAX_SIZE || nextY<0 || nextY>=SPACE_MAX_SIZE){
                    continue;
                }
                if(space[nextY][nextX] || mark[nextY][nextX]){
                    continue;
                }
                nowRoute.Push(Node(Coordinate(nextX,nextY),nextDir + 1));
                mark[nextY][nextX]=true;
                nowX=nextX;
                nowY=nextY;
                nextDir=0;
                cout<<"A"<<endl;
            }
        }
        return nowRoute;
    }
};