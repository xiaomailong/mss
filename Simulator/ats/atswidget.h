#ifndef ATSWIDGET_H
#define ATSWIDGET_H

#include <QWidget>

namespace Ui {
class AtsWidget;
}

class AtsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AtsWidget(QWidget *parent = 0);
    ~AtsWidget();
private slots:
    void on_tsr_sure_clicked();
    void onFinished();

    void on_tsr_opcmd_clicked();

    void on_tsr_power_clicked();

    void on_ats_ci_opcmd_clicked();

    void on_ats_vobc_cmd_clicked();

    void on_ats_vobc_heart_clicked();

    void on_ats_zc_time_clicked();

    void on_ats_ci_run_clicked();

    void on_ats_mss_button_clicked();

    void on_ats_ci_time_clicked();

private:
    Ui::AtsWidget *ui;
};

#endif // ATSWIDGET_H
