#include "item.h"
#include "ui_item.h"

#include <QDebug>


Item::Item(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Item)
{
    ui->setupUi(this);
}

Item::~Item()
{
    delete ui;
}

void Item::setIdType(QString idType) { ui->idType->setText(idType); }
void Item::setNameType(QString nameType){ ui->nameType->setText(nameType); }
void Item::setState(QString state){ui->state->setText(state);}
void Item::setId(int id){ui->id->setNum(id);}
void Item::setName(QString name){ui->name->setText(name);}
