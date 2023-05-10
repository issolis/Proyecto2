#ifndef NODEBACK_H
#define NODEBACK_H


class nodeBack
{
public:
    nodeBack(int x, int y);
    int x;
    int y;
    nodeBack* next;
    int id;
    nodeBack(int id);

};

#endif // NODEBACK_H
