#ifndef ZCQUERYDUTINFO_H
#define ZCQUERYDUTINFO_H

#include <QWidget>

namespace Ui {
class ZcQueryDutinfo;
}

class ZcQueryDutinfo : public QWidget
{
    Q_OBJECT

public:
    explicit ZcQueryDutinfo(QWidget *parent = 0);
    ~ZcQueryDutinfo();

private:
    Ui::ZcQueryDutinfo *ui;
};

#endif // ZCQUERYDUTINFO_H
