#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QLineEdit>
#include<QPushButton>
#include <QMainWindow>
using namespace std;
struct Tuvung{
    string tienganh;
    string tiengviet;
};

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_btn_tra_tu_clicked();

    void on_btn_quan_ly_tu_dien_clicked();

    void on_btn_them_tu_vung_clicked();

    void on_btn_xoa_tu_vung_clicked();

    void on_btn_xem_tu_dien_clicked();

    void on_btn_back_tu_tra_tu_clicked();

    void on_btn_back_tu_quan_ly_tu_dien_clicked();

    void on_btn_back_tu_them_tu_vung_clicked();

    void on_btn_back_tu_xoa_tu_vung_clicked();

    void on_btn_back_tu_xem_tu_dien_clicked();

    void on_btn_tim_kiem_clicked();

    void on_btn_them_clicked();

    void on_btn_them_2_clicked();

    void on_btn_save_close_clicked();

    void on_btn_them_tu_flashcard_clicked();

    void on_btn_luu_flashcard_clicked();

    void on_btn_flashcard_clicked();

    void on_btn_tao_hoc_phan_clicked();

    void on_btn_back_tu_flashcard_clicked();

    void on_btn_back_tu_them_flashcard_clicked();

    void on_btn_back_tu_du_lieu_hoc_phan_clicked();

    void on_btn_hoc_voi_flashcard_clicked();

    void on_btn_back_tu_quan_ly_tu_dien_2_clicked();

    void on_btn_tu_tieng_anh_clicked();

    void on_btn_tu_tieng_viet_clicked();

    void on_btn_tu_tiep_theo_clicked();

    void on_btn_tu_truoc_do_clicked();

    void on_btn_chinh_sua_hoc_phan_clicked();


    void on_btn_xoa_hoc_phan_clicked();

private:
    Ui::MainWindow *ui;
    vector<Tuvung>v;
    struct diaChiOTu{
        QLineEdit* oTiengAnh;
        QLineEdit* oTiengViet;
    };
    vector<diaChiOTu>tumoi;
    vector<vector<Tuvung>>danhsachhocphan;
    vector<Tuvung>hocphantemp;
    vector<string>tenhocphan;
    vector<QPushButton*>nuthocphan;
    vector<QPushButton*>nutxoahocphan;
    int thutuhocphanchinhsua;
    bool ischinhsua=false;
    int i=0;
    bool chedoxoahocphan=false;
    QString stylesheetxoahocphan;
    void docdulieutufile();
    void luufilehocphan();
    void docfilehocphan();
    void tailennuthocphan();
    int binarySearch(const vector<Tuvung>&v, string target);
    void searchWord(const vector<Tuvung>&v, string target);
    int indexToInsert(const vector<Tuvung>&v,string word);
    bool addWord(vector<Tuvung>&v, const Tuvung& wordandmean);
    bool deleteWord(vector<Tuvung>&v, const Tuvung&wordandmean);

};
#endif // MAINWINDOW_H
