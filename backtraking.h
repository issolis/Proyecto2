#ifndef BACKTRAKING_H
#define BACKTRAKING_H
#include <iostream>
#include <vector>
#include <climits>
#include "listback.h"
#include <QString>


const int N = 10;

class backTraking
{
public:
    backTraking(int arr[N][N]);
    void backtrack(int x, int y, int distance, int end_x, int end_y,listBack path);


    int shortestPathLength;


    listBack shortestPath;
    listBack id_list;


    nodeBack *a;
    listBack findShortestPath(int start_x, int start_y, int end_x, int end_y);




private:
    const int MAX_SIZE = 10;
    int grid[N][N];




};

#endif // BACKTRAKING_H
