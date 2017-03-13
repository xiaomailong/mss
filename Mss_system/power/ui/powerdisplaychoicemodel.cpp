#include "powerdisplaychoicemodel.h"
#define CHECK_BOX_COLUMN 0
#define File_PATH_COLUMN 1
#include<QDebug>
PowerDisplayChoiceModel::PowerDisplayChoiceModel(QObject *parent) : QAbstractTableModel(parent)
{

}


PowerDisplayChoiceModel::~PowerDisplayChoiceModel()
{

}

bool PowerDisplayChoiceModel::setData( const QModelIndex &index, const QVariant &value, int role )
{
        if(!index.isValid())
                return false;
           qDebug()<<"index.row ="<<index.row();
        if (role == Qt::CheckStateRole && index.column() == 0)
        {

                check_state_map[index.row()] = (value == Qt::Checked ? Qt::Checked : Qt::Unchecked);
                qDebug()<<"check_state_map[index.row()] ="<<check_state_map[index.row()];
                if(check_state_map[index.row()]==Qt::Unchecked) emit cleanAllChecked();
                if(check_state_map[index.row()]==Qt::Checked) emit cleanAllCleaned();
                emit checkStatusChange(index,check_state_map[index.row()]);
        }
        beginResetModel();
        endResetModel();


        return true;
}

//设定一下数据源
void PowerDisplayChoiceModel::setChoice(const QStringList &ListNames)
{
    tableList = ListNames;
}

QVariant PowerDisplayChoiceModel::data(const QModelIndex &index, int role) const
{
        if (!index.isValid())
                return QVariant();

        switch(role)
        {
        //case Qt::TextAlignmentRole:
        //              return Qt::AlignLeft | Qt::AlignVCenter;

        case Qt::DisplayRole:
            if(index.column() == 1)
             {
                 return tableList[index.row()];
             }
            return QVariant();

        case Qt::CheckStateRole:
             if(index.column() == 0)
              {
                   if (check_state_map.contains(index.row()))
                       return check_state_map[index.row()] == Qt::Checked ? Qt::Checked : Qt::Unchecked;

                    return Qt::Checked;
                }
        default:
                return QVariant();
        }

    return QVariant();
}

Qt::ItemFlags PowerDisplayChoiceModel::flags(const QModelIndex &index) const
{
        if (!index.isValid())
                return 0;

        if (index.column() == 0)
                return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;

        return  Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}


int PowerDisplayChoiceModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
       qDebug()<<"zwz parent.column() =" <<parent.column();
    return 4;
}

// 列数
int PowerDisplayChoiceModel::columnCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
       qDebug()<<"zwz parent.column() =" <<parent.column();
    return 2;
}


// 表头数据
QVariant PowerDisplayChoiceModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch (role)
    {
    case Qt::TextAlignmentRole:
        return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
    case Qt::DisplayRole:
    {
        if (orientation == Qt::Horizontal)
        {
            if (section == CHECK_BOX_COLUMN)
                return QStringLiteral("选择");

            if (section == File_PATH_COLUMN)
                return QStringLiteral("监测项目");
        }
    }
    default:
        return QVariant();
    }

    return QVariant();
}
