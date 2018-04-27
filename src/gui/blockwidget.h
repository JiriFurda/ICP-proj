#ifndef BLOCKWIDGET_H
#define BLOCKWIDGET_H

#include <QWidget>

#include <QtWidgets>

namespace Ui {
class BlockWidget;
}

class BlockWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BlockWidget(QWidget *parent = 0);
    ~BlockWidget();

private:
    Ui::BlockWidget *ui;

private slots:
    void showContextMenu(const QPoint &pos);
};

#endif // BLOCKWIDGET_H
