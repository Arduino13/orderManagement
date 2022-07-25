#include "hover_delegate.h"
#include <QDebug>

hover_delegate::hover_delegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

void hover_delegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    int width_pen = 2;

    QPen pen(QColor(51, 153, 255));
    QRect rect = option.rect;

    int width=rect.topRight().x()-rect.topLeft().x();
    int height=rect.bottomLeft().y()-rect.topLeft().y();

    pen.setWidth(width_pen);
    painter->setPen(pen);
    painter->drawRect(rect.topLeft().x(),rect.topLeft().y(),width,height);
    painter->fillRect(rect.topLeft().x(),rect.topLeft().y(),width+1,height-(width_pen-2),QColor(215, 215, 215));

	//returns control back to child 
    QStyledItemDelegate::paint(painter,option,index);
}
