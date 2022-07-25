#ifndef HOVER_DELEGATE_H
#define HOVER_DELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>

/*
 * Creates hover in table
 */

class hover_delegate : public QStyledItemDelegate
{
public:
    hover_delegate(QObject *parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // HOVER_DELEGATE_H
