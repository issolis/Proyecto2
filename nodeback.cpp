#include "nodeback.h"

nodeBack::nodeBack(int x, int y)
{
    this->x = x;
    this->y = y;
    next = nullptr;

}
nodeBack::nodeBack(int id){
    this->id=id;
    next=nullptr;
}
