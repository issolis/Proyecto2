#include "widget.h"
#include <QDebug>
#include <QRandomGenerator>
#include <listid.h>
#include <QTcpSocket>
#include <QLabel>

int posXL1 [54]={-120,-100,-80 ,-60 , -40,-20 ,0   ,-60 ,-60,-60,-60,-120,-100,-80 ,-60 , -40,-20 ,0,40,40,40,40,40,40,60,80,100,120,120,120,120,120,120,-40,-40,-40,-40,-40,-20,0,-20,0,40,40,40,40,40,60,80,60,80,60,80};
int posYL1 [54]={-120,-120,-120,-120,-120,-120,-120,-100,-80,-60,-40,-20 ,-20 ,-20 ,-20 ,-20 ,-20 ,-20,-120,-100,-80,-60,-40,-20,-100,-80,-100,-120,-100,-80,-60,-40,-20,20,40,60,80,100, 20,20,100,100,20,40,60,80,100,20,20,60,60,100,100};

int posxE1=0;
int posYE1=0;
int blocks=53;

QVariant level=1;
QVariant dirY=1;
QVariant dirX=1;
QVariant dirZ=1;
QVariant lifes=3;
QVariant totalPoints=0;


QVariant counter=0;
bool came=true;
bool came1=true;
bool controler=true;
listID IDList;
listID IDList1;
bool tryToFixTheBug=false;
bool keyUnlocked=false;



widget::widget(QWidget *parent)
    : QWidget(parent)
{
    listMatL1.buildMatrix(14,22);
    scene = new QGraphicsScene(this);
    scene->setSceneRect(-220,-140, 440, 280);
    QBrush brush(Qt::gray);
    scene->setBackgroundBrush(brush);
    view = new QGraphicsView(this);
    view->setScene(scene);
    view->setFixedSize(442, 282);
    L1 = scene->addWidget(b_LevelI);

    QPixmap myPixmap(":g1.png");
    enemy1 = new QGraphicsPixmapItem(myPixmap);
    enemy2 = new QGraphicsPixmapItem(myPixmap);

    QPixmap myPixma (":pac.png");
    pacman= new QGraphicsPixmapItem(myPixma);
    points.insert(277);


    QObject::connect(b_LevelI, &QPushButton::clicked, [&]{
        bL1_Clicked();
    });

}
void widget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W) {
        direcction=3;
    }
    if (event->key() == Qt::Key_S) {
        direcction=4;
    }
    if (event->key() == Qt::Key_D) {
        direcction=1;
    }
    if (event->key() == Qt::Key_A) {
        direcction=2;
    }
    if (event->key() == Qt::Key_Alt) {
        if(keyUnlocked)
            keyUnlocked=false;
        else
            keyUnlocked=true;
    }

}

void widget::bL1_Clicked(){
    b_LevelI->hide();
    b_LevelI->setEnabled(false);


    list.insert(53);

    int i=0;
    blockNode *aux=list.head;
    while(aux!=nullptr){
        scene->addItem(aux->item);
        QBrush redBrush(Qt::blue);
        QPen pen(Qt::blue);
        aux->item->setBrush(redBrush);
        aux->item->setPen(pen);
        aux->item->setPos(posXL1[i], posYL1[i]);
        listMatL1.findNode (((220+posXL1[i])/20+(140+posYL1[i])/20*22)+1)->closed=true;
        aux=aux->next;
        i++;
    }

    scene->addItem(enemy1);
    //scene->addItem(enemy2);
    scene->addItem(pacman);
    pacman->setPos(-120,0);
    colocatePoints();
   // MoveFirstEnemy();
    //MoveSecondEnemy();
    movePlayer();
    checkPoints();
    checkCollision();
    label();
    //server();

}

void widget:: defineRouteFirstEnemy(){
    pathFindingList *list=new pathFindingList;
    list->buildMatrix(14,22);
    list->makeItTrue();

    int i=0;
    while(i!=blocks){
        list->findNode (((220+posXL1[i])/20+(140+posYL1[i])/20*22)+1)->closed=true;
        i++;
    }
    int conversionPos=((220+enemy1->pos().x())/20+(140+enemy1->pos().y())/20*22)+1;
    int x=((220+pacman->pos().x())/20+(140+pacman->pos().y())/20*22)+1;
    list->findRoute(conversionPos, x);

    pathFindingNode *auxEnd;
    auxEnd= list->end;

    if(auxEnd!=nullptr){
        while (auxEnd!=nullptr) {
            IDList.insert(auxEnd->id);
            auxEnd=auxEnd->parent;
        }
    }
    list->freeEveryThing();
    free(list );
    came=false;

}

void widget:: defineRouteSecondEnemy(){
    pathFindingList *list=new pathFindingList;
    list->buildMatrix(14,22);
    list->makeItTrue();

    int i=0;
    while(i!=blocks){
        list->findNode (((220+posXL1[i])/20+(140+posYL1[i])/20*22)+1)->closed=true;
        i++;
    }
    int conversionPos=((220+enemy2->pos().x())/20+(140+enemy2->pos().y())/20*22)+1;
    int x=((220+pacman->pos().x())/20+(140+pacman->pos().y())/20*22)+1;
    list->findRoute(conversionPos, x);

    pathFindingNode *auxEnd;
    auxEnd= list->end;

    if(auxEnd!=nullptr){
        while (auxEnd!=nullptr) {
            IDList1.insert(auxEnd->id);
            auxEnd=auxEnd->parent;
        }
    }
    list->freeEveryThing();
    free(list );
    came1=false;
}

void widget::MoveFirstEnemy(){
    int x; int y;
    QTimer *timer = new QTimer();

    QObject::connect(timer, &QTimer::timeout, [&]() {
        if(came){
            defineRouteFirstEnemy();
        }
        else{
            if(IDList.numberElements!=0){
                x=adapPosX(IDList.head->id);
                y=adapPosY(IDList.head->id);

                IDList.deleteFirst();
                if(IDList.head==nullptr){
                    came=true;
                    controler=true;
                }

                enemy1->setPos(x, y);
            }
            else{
                came=true;
            }
        }
    });
    timer->start(220);

}

void widget::MoveSecondEnemy(){
    int x; int y;
    QTimer *timer = new QTimer();

    QObject::connect(timer, &QTimer::timeout, [&]() {
        if(came1){
            defineRouteSecondEnemy();
        }
        else{
            if(IDList.numberElements!=0){
                x=adapPosX(IDList1.head->id);
                y=adapPosY(IDList1.head->id);

                IDList1.deleteFirst();
                if(IDList1.head==nullptr){
                    came1=true;
                }
                enemy2->setPos(x, y);
            }else{
                came1=true;
            }
        }
    } );
    timer->start(10);
}

int widget::randNumber(){
    int i=0; bool again=false;
    while(true){
        again=false;
        int rand=QRandomGenerator::global()->bounded(1, 301);
        while(i!=53){
            if((220+posXL1[i])/20+(140+posYL1[i])/20*22+1==rand){
                again=true;
                break;
            } i++;
        }

        if(!again)
            return rand;
    }

}

int widget::adapPosX(int id){
    int posX=-220+(id-1)%22*20;
    return posX;
}

int widget::adapPosY(int id){
    return -140+(id-1)/22*20;
}

void widget::movePlayer(){
    QTimer *timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, [&]() {
        if(!keyUnlocked){
            int conversionPos;
            if(direcction==1){
                conversionPos=((240+pacman->pos().x())/20+(140+pacman->pos().y())/20*22)+1;
                if (!noPutIt(1, conversionPos))
                    pacman->setPos(pacman->pos().x()+20, pacman->pos().y());
                if(pacman->pos().x()>200){
                    pacman->setPos(-220, pacman->pos().y());
                }
            }
            if(direcction==2){
                conversionPos=((200+pacman->pos().x())/20+(140+pacman->pos().y())/20*22)+1;
                if (!noPutIt(1, conversionPos))
                    pacman->setPos(pacman->pos().x()-20, pacman->pos().y());
                if(pacman->pos().x()<-220){
                    pacman->setPos(200, pacman->pos().y());
                }
            }
            if(direcction==3){
                conversionPos=((220+pacman->pos().x())/20+(120+pacman->pos().y())/20*22)+1;
                if (!noPutIt(1, conversionPos))
                    pacman->setPos(pacman->pos().x(), pacman->pos().y()-20);
                if(pacman->pos().y()<-140){
                    pacman->setPos( pacman->pos().x(),120);
                }

            }
            if(direcction==4){
                conversionPos=((220+pacman->pos().x())/20+(160+pacman->pos().y())/20*22)+1;
                if (!noPutIt(1, conversionPos))
                    pacman->setPos(pacman->pos().x(), pacman->pos().y()+20);
                if(pacman->pos().y()>120){
                    pacman->setPos(pacman->pos().x(),-140);
                }
            }
        }
    }
    );
    timer->start(250);
}

void widget:: colocatePoints(){
    int i=0;
    int j=0;

    while(i!=330){
        bool flag=noPutIt(1,i);
        ;
        if(!flag){

            points.findNode(j)->item1->setPos(adapPosX(i),adapPosY(i));
            points.findNode(j)->item1->setZValue(-100);
            scene->addItem( points.findNode(j)->item1);
            j++;
        }
        i++;


    }
}

bool widget:: noPutIt(int level, int ID){
    int i=0;
    if(level==1){
        while(i!=blocks){
            if (adapPosX(ID)==posXL1[i] && adapPosY(ID)==posYL1[i]){

                return true;}
            i++;
        }

    }
    return false;
}

void widget:: checkPoints(){
    QTimer *timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, [&]() {
        int i=0;
        int j=0;

        while(i!=330-blocks){
            if(points.findNode(i)->item1->pos()==pacman->pos()){
                points.findNode(i)->item1->setPixmap(QPixmap (":bg.png"));
                if(pointsVisited.findNode(i)->id!=i)
                        totalPoints=totalPoints.toInt()+10;
                pointsVisited.insert(i);
            }
            i++;
        }
    }
    );
    timer->start(150);
}

void widget:: server(){
    QTimer *timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, [&]() {
        QString s=Server->socket->readAll();
        if(keyUnlocked){
            if(!s.isEmpty() ){


                int conversionPos;
                if(s=="\u0001"){
                    conversionPos=((240+pacman->pos().x())/20+(140+pacman->pos().y())/20*22)+1;
                    if (!noPutIt(1, conversionPos))
                        pacman->setPos(pacman->pos().x()+20, pacman->pos().y());
                    if(pacman->pos().x()>200){
                        pacman->setPos(-220, pacman->pos().y());
                    }
                }
                else if(s=="\u0002"){
                    conversionPos=((200+pacman->pos().x())/20+(140+pacman->pos().y())/20*22)+1;
                    if (!noPutIt(1, conversionPos))
                        pacman->setPos(pacman->pos().x()-20, pacman->pos().y());
                    if(pacman->pos().x()<-220){
                        pacman->setPos(200, pacman->pos().y());
                    }
                }
                else if(s=="\u0003"){
                    conversionPos=((220+pacman->pos().x())/20+(120+pacman->pos().y())/20*22)+1;
                    if (!noPutIt(1, conversionPos))
                        pacman->setPos(pacman->pos().x(), pacman->pos().y()-20);
                    if(pacman->pos().y()<-140){
                        pacman->setPos( pacman->pos().x(),120);
                    }

                }
                else if(s=="\u0004"){
                    conversionPos=((220+pacman->pos().x())/20+(160+pacman->pos().y())/20*22)+1;
                    if (!noPutIt(1, conversionPos))
                        pacman->setPos(pacman->pos().x(), pacman->pos().y()+20);
                    if(pacman->pos().y()>120){
                        pacman->setPos(pacman->pos().x(),-140);
                    }
                }
            }
        }
    });
    timer->start(250);
}

void widget:: checkCollision(){
    QTimer *timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, [&]() {
        if(pacman->pos()==enemy1->pos()){
            lifes=lifes.toInt()-1;
            int x=randNumber();
            pacman->setPos(adapPosX(x),adapPosY(x));
            if(lifes==0){
                QLabel *label = new QLabel("Perdiste", this);
                label->setAlignment(Qt::AlignCenter);
                label->setFixedSize(200, 50);
                label->show();
                label->move(220,140);
                label->setStyleSheet("background-color: red;");

                QTimer::singleShot(5000, [=]() {
                    close();
                });

            }
        }
    });
    timer->start(10);
}

void widget:: label(){
    QTimer *timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, [&]() {
        QLabel *label = new QLabel("Lifes:"+lifes.toString()+" Level:"+level.toString()+" Points:"+totalPoints.toString(), this);
        label->setFixedSize(180, 10);
        label->move(120,0);
        label->show();
        label->setStyleSheet("background-color: blue;");

    });
    timer->start(10);
}
