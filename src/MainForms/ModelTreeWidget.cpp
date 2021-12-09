#include "ModelTreeWidget.h"
#include "ui_ModelTreeWidget.h"
#include "QTreeWidgetItem"
#include <QAction>
#include "qdebug.h"
ModelTreeWidget::ModelTreeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModelTreeWidget)
{
    ui->setupUi(this);
    ui->treeWidget->setHeaderHidden(true);
    pOpenClose = new QMenu(ui->treeWidget);
    showAction = new QAction(QString::fromLocal8Bit("展开全部"),pOpenClose);
    closeAction = new QAction(QString::fromLocal8Bit("折叠全部"),pOpenClose);
    ui->treeWidget->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->treeWidget->addAction(showAction);
    ui->treeWidget->addAction(closeAction);
    connect(showAction,SIGNAL(triggered()),this,SLOT(showAction_triggered()));
    connect(closeAction,SIGNAL(triggered()),this,SLOT(closeAction_triggered()));
}

ModelTreeWidget::~ModelTreeWidget()
{
    delete ui;
}

void ModelTreeWidget::addModelObject(ModelBase *object)
{
    QString fileName = object->FileName();
    QTreeWidgetItem* fileItem = new QTreeWidgetItem;
    fileItem->setText(0, fileName.toUtf8());
    ui->treeWidget->addTopLevelItem(fileItem);

    std::vector<ModelBase::TASK_DATA>& taskDatas = object->getTaskDatas();
    QTreeWidgetItem* taskItem = new QTreeWidgetItem;
    taskItem->setText(0, "Task");
    fileItem->addChild(taskItem);
    for(int i = 0; i < taskDatas.size(); i++)
    {
        ModelBase::TASK_DATA data = taskDatas[i];
        QTreeWidgetItem* item = new QTreeWidgetItem;
        QString itemName = data.key + "=" + data.value;

        item->setText(0, itemName);
        taskItem->addChild(item);
    }

    std::vector<ModelBase::TASK_DATA>& systemDatas = object->getSystemDatas();
    QTreeWidgetItem* systemItem = new QTreeWidgetItem;
    systemItem->setText(0, "System");
    fileItem->addChild(systemItem);
    for(int i = 0; i < systemDatas.size(); i++)
    {
        ModelBase::TASK_DATA data = systemDatas[i];
        QTreeWidgetItem* item = new QTreeWidgetItem;
        QString itemName = data.key + "=" + data.value;
        item->setText(0, itemName);
        systemItem->addChild(item);
    }

    std::vector<ModelBase::TASK_DATA>& conditionsDatas = object->getConditionsDatas();
    QTreeWidgetItem* conditionsItem = new QTreeWidgetItem;
    conditionsItem->setText(0, "Conditions");
    fileItem->addChild(conditionsItem);
    for(int i = 0; i < conditionsDatas.size(); i++)
    {
        ModelBase::TASK_DATA data = conditionsDatas[i];
        QTreeWidgetItem* item = new QTreeWidgetItem;
        QString itemName = data.key + "=" + data.value;
        item->setText(0, itemName);
        conditionsItem->addChild(item);
    }
}

void ModelTreeWidget::closeItem()
{
    ui->treeWidget->collapseAll();
}

void ModelTreeWidget::showItem(int index)
{
    QTreeWidgetItem* item = ui->treeWidget->topLevelItem(index);
    for(int i = 0; i < item->childCount(); i++)
    {
        QTreeWidgetItem* itemChild = item->child(i);
        ui->treeWidget->expandItem(itemChild);
    }
    ui->treeWidget->expandItem(item);
}

void ModelTreeWidget::showAction_triggered()
{
    ui->treeWidget->expandAll();
}

void ModelTreeWidget::closeAction_triggered()
{
    ui->treeWidget->collapseAll();
}
