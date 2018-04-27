#ifndef SCHEMEVIEW_H
#define SCHEMEVIEW_H

#include <QWidget>

#include <QtWidgets>

namespace Ui {
class SchemeView;
}

class SchemeView : public QWidget
{
    Q_OBJECT

public:
    explicit SchemeView(QWidget *parent = 0);
    ~SchemeView();

private:
    Ui::SchemeView *ui;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
};

#endif // SCHEMEVIEW_H
