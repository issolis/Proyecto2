#include "listid.h"
#include <iostream>
#include <QString>
#include <QDebug>


listID::listID()
{

}
void listID::insert(int id){
    nodeID *newNode= new nodeID (id);


    if (head==nullptr){
        head=newNode;
    }else{
        nodeID *aux=head;
        head=newNode;
        head->next=aux;
    }
    numberElements++;
}

void listID::show(){
    nodeID *aux=head;
    QString string="";
    while(aux!=nullptr){
        string= string+" "+QString::number(aux->id);
        aux=aux->next;
    }
    qDebug()<<string;
}
void listID::deleteFirst(){
    if(head!=nullptr){
        if(numberElements==1)
            head=nullptr;
        else
            head=head->next;
        numberElements--;
    }
}
nodeID* listID:: findNode(int id){
    nodeID *aux=head;
    while(aux!=nullptr){
        if(aux->id==id)
            return aux;
        aux=aux->next;
    }
    nodeID *avoidError=new nodeID(-1);
    return avoidError;
}
