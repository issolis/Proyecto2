#include "listback.h"
#include <iostream>
#include <QString>
#include <QDebug>
listBack::listBack()
{
    this->head = nullptr;
}
void listBack::add(int x, int y){
    nodeBack* newNode = new nodeBack(x, y);
    if (head == nullptr) {
        head= newNode;
    } else {
        nodeBack* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

}
void listBack::addId(int id){
    nodeBack* newNode = new nodeBack(id);
    if (head == nullptr) {
        head= newNode;
    } else {
        nodeBack* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}
void listBack::deleteNode(){
    if (head == nullptr) {
        return;
    }
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
        return;
    }
    nodeBack* temp = head;
    while (temp->next->next != nullptr) {
        temp = temp->next;
    }
    delete temp->next;
    temp->next = nullptr;
}
bool listBack::esvacia(){
    return head == nullptr;
}
void listBack::printPath(listBack path){
    if (path.head == nullptr) {
        std::cout << "Empty path\n";
        return;
    }
    nodeBack* curr = path.head;
    std::cout << "(" << curr->x << "," << curr->y << ")";
    curr = curr->next;
    while (curr != nullptr) {
        std::cout << " , (" << curr->x << "," << curr->y << ")";
        curr = curr->next;
    }
    std::cout << std::endl;
}
int listBack::length(){
    int len = 0;
    nodeBack* current = head;
    while (current != NULL) {
        len++;
        current = current->next;
    }
    return len;
}
void listBack::addToGlobalList(listBack path, listBack id_list){

    nodeBack* curr = path.head;
    while (curr != nullptr) {
        add(curr->x, curr->y);
        int id= 22*curr->x+curr->y+1;
        id_list.addId(id);

        curr = curr->next;
    }




}
bool listBack  ::hasDuplicates() {
    if (head == nullptr) {

        return false;
    }
    else {
        nodeBack* current = head;
        while (current != nullptr) {
            nodeBack* runner = current->next;
            while (runner != nullptr) {
                if (current->x == runner->x && current->y == runner->y) {

                    return true;
                }
                runner = runner->next;
            }
            current = current->next;
        }

        return false;
    }
}
void listBack::printId(){
    if (head == nullptr) {
        std::cout << "Empty path\n";
        return;
    }
    nodeBack* curr = head;
    std::cout << curr->id;
    curr = curr->next;
    while (curr != nullptr) {
        std::cout << " , " << curr->id;
        curr = curr->next;
    }
    std::cout << std::endl;
}

void listBack::addL(listBack path){
    nodeBack* curr = path.head;
    while (curr != nullptr) {

        int id= 22*curr->x+curr->y+1;
        addId(id);

        curr = curr->next;
    }

}
