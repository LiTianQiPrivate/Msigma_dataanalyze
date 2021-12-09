#ifndef MODELTREEWIDGET_H
#define MODELTREEWIDGET_H

#include <QWidget>
#include "ModelBase.h"
#include <qmenu.h>
namespace Ui {
class ModelTreeWidget;
}

class ModelTreeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ModelTreeWidget(QWidget *parent = nullptr);
    ~ModelTreeWidget();
    void addModelObject(ModelBase* object);
    void closeItem(); // 合并item
    void showItem(int index); // 展开
    QMenu *pOpenClose;
    QAction *showAction;
    QAction *closeAction;
public slots:
    void showAction_triggered();
    void closeAction_triggered();
private:
    Ui::ModelTreeWidget *ui;
};

#endif // MODELTREEWIDGET_H
