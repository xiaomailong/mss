#ifndef DISPLAYCHOICEMODEL_H
#define DISPLAYCHOICEMODEL_H
#include <QAbstractTableModel>
#include <QMap>
#include <QList>

class PowerDisplayChoiceModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit PowerDisplayChoiceModel(QObject *parent = 0);
    ~PowerDisplayChoiceModel();
    bool setData( const QModelIndex &index, const QVariant &value, int role ) ;
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const ;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void setChoice(const QStringList &ListNames);
signals:
    void checkStatusChange(const QModelIndex &index,bool checked);
    void cleanAllChecked();
    void cleanAllCleaned();
public slots:

private:
    QMap<int, Qt::CheckState> check_state_map;

    QStringList tableList;
};

#endif // DISPLAYCHOICEMODEL_H
