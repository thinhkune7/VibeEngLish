#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QTextStream>
#include<QStringList>
#include<QFile>
#include<QDebug>
#include<QMessageBox>
#include<QCoreApplication>
#include <QDirIterator>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("VibeEnglish");
    ui->stackedWidget->setCurrentIndex(0);
    docdulieutufile();
    docfilehocphan();
    tailennuthocphan();
    stylesheetxoahocphan=ui->btn_xoa_hoc_phan->styleSheet();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: docdulieutufile(){
    QString duongDan = QCoreApplication::applicationDirPath() + "/dictionary.txt";
    QFile file (duongDan);
    if (file.open(QIODevice::ReadOnly|QIODevice::Text)){
        v.clear();
        QTextStream in(&file);
        while (!in.atEnd()){
            QString line=in.readLine();
            QStringList tumoi=line.split(": ");
            if(tumoi.size()==2)
                v.push_back({tumoi[0].toStdString(),tumoi[1].toStdString()});
        }
        file.close();
        qDebug()<<"Đã tải thành công "<<v.size()<<" từ vựng từ file dữ liệu người dùng vào ứng dụng";
    }
    else {
        QFile filegoc (":/dictionary_root.txt");
        if (!filegoc.open(QIODevice::ReadOnly|QIODevice::Text)){
            qDebug()<<"Không tải được từ vựng";
            return;
        }
        else{
            v.clear();
            QTextStream in(&filegoc);
            while (!in.atEnd()){
                QString line=in.readLine();
                QStringList tumoi=line.split(": ");
                if(tumoi.size()==2)
                    v.push_back({tumoi[0].toStdString(),tumoi[1].toStdString()});
            }
            filegoc.close();
            qDebug()<<"Đã tải thành công "<<v.size()<<" từ vựng từ file dữ liệu gốc vào ứng dụng";
        }
    }
}




//Tra cứu từ điển
int MainWindow::binarySearch(const vector<Tuvung> &v, string target)
{
    QString qtarget=QString::fromStdString(target);
    int right=v.size()-1;
    int left=0;
    while (left<=right){
        int mid=left+(right-left)/2;
        QString tukhop=QString::fromStdString(v[mid].tienganh);
        int ketquasosanh=tukhop.compare(qtarget,Qt::CaseInsensitive);
        if (ketquasosanh==0)
            return mid;
        else if (ketquasosanh<0){
            left=mid+1;
        }
        else right=mid-1;
    }
    return -1;
}

void MainWindow::searchWord(const vector<Tuvung> &v, string target)
{
    int index=binarySearch(v,target);
    if (index!=-1){
        QString nghia= QString::fromStdString(v[index].tiengviet);
        ui->lbl_ket_qua->setText(nghia);
    }
    else {
        ui->lbl_ket_qua->setText("Từ không tồn tại trong từ điển");
    }
}


//Thêm từ vựng
int MainWindow::indexToInsert(const vector<Tuvung> &v, string word)
{
    int check=binarySearch(v,word);
    if (check !=-1)
        return -1;
    int right=v.size()-1;
    int left=0;
    while (left<=right){
        int mid=left+(right-left)/2;
        if (v[mid].tienganh<word)
            left=mid+1;
        else right=mid-1;
    }
    return left;
}
bool MainWindow::addWord(vector<Tuvung> &v, const Tuvung &wordandmean)
{
    int index=indexToInsert(v,wordandmean.tienganh);
    if(index==-1){
        return false;
    }
    v.insert(v.begin()+index,wordandmean);
    return true;
}


//Xoá từ vựng
bool MainWindow::deleteWord(vector<Tuvung> &v, const Tuvung &wordandmean)
{
    int index=binarySearch(v,wordandmean.tienganh);
    if (index==-1)
        return false;
    v.erase(v.begin()+index);
    return true;
}



void MainWindow::on_btn_tra_tu_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->text_nhap_tu->clear();
    ui->lbl_ket_qua->clear();
}


void MainWindow::on_btn_quan_ly_tu_dien_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);

}


void MainWindow::on_btn_them_tu_vung_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->text_nhap_tu_tieng_anh_them->clear();
    ui->text_nhap_tu_tieng_viet_them->clear();
    ui->lbl_ket_qua_them->clear();
}


void MainWindow::on_btn_xoa_tu_vung_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->text_nhap_tu_tieng_anh_xoa->clear();
    ui->lbl_ket_qua_xoa->clear();
}

//Xem từ điển
void MainWindow::on_btn_xem_tu_dien_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    ui->lw_show_tu_dien->clear();
    int n=v.size();
    for (int i=0;i<n;i++){
        QString tu=QString::fromStdString(v[i].tienganh);
        QString nghia=QString::fromStdString(v[i].tiengviet);
        ui->lw_show_tu_dien->addItem(tu +": "+nghia);
    }
}


void MainWindow::on_btn_back_tu_tra_tu_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_btn_back_tu_quan_ly_tu_dien_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_btn_back_tu_them_tu_vung_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_btn_back_tu_xoa_tu_vung_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_btn_back_tu_xem_tu_dien_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}



void MainWindow::on_btn_tim_kiem_clicked()
{
    QString tu=ui->text_nhap_tu->text();
    string tu_cpp=tu.toStdString();
    searchWord(v,tu_cpp);
}


void MainWindow::on_btn_them_clicked()
{
    Tuvung tumoi;
    tumoi.tienganh=ui->text_nhap_tu_tieng_anh_them->text().toStdString();
    tumoi.tiengviet=ui->text_nhap_tu_tieng_viet_them->text().toStdString();
    bool check=addWord(v,tumoi);
    if (!check){
        ui->lbl_ket_qua_them->setText("Từ vựng đã tồn tại trong từ điển, vui lòng nhập từ khác");
    }
    else ui->lbl_ket_qua_them->setText("Đã thêm từ vựng thành công");
    ui->text_nhap_tu_tieng_anh_them->clear();
    ui->text_nhap_tu_tieng_viet_them->clear();

}


void MainWindow::on_btn_them_2_clicked()
{
    Tuvung tucu;
    tucu.tienganh =ui->text_nhap_tu_tieng_anh_xoa->text().toStdString();
    bool check=deleteWord(v,tucu);
    if(!check){
        ui->lbl_ket_qua_xoa->setText("Từ vựng không tồn tại trong từ điển, vui lòng nhập từ khác");
    }
    else ui->lbl_ket_qua_xoa->setText("Đã xoá từ vựng thành công");
}


void MainWindow::on_btn_save_close_clicked()
{
    QString duongDan = QCoreApplication::applicationDirPath() + "/dictionary.txt";
    QFile file(duongDan);
    if (!file.open(QIODevice::WriteOnly|QIODevice::Text)){
        QMessageBox::warning(this, "Lỗi","Không thể tạo hoặc mở file để lưu, ứng dụng sẽ thoát");
        this->close();
    }
    QTextStream out(&file);
    int n=v.size();
    for (int i=0;i<n;i++){
        out<<QString::fromStdString(v[i].tienganh)<<": "<<QString::fromStdString(v[i].tiengviet)<<'\n';
    }
    file.close();
    luufilehocphan();
    QMessageBox::information(this, "Chúc mừng","Đã lưu thành công từ điển và học phần, ứng dụng sẽ thoát");
    this->close();
}


void MainWindow::on_btn_them_tu_flashcard_clicked()
{
    QHBoxLayout*khungNgang=new QHBoxLayout();
    QLineEdit *oTiengAnh=new QLineEdit (this);
    oTiengAnh->setStyleSheet(
        "QLineEdit {"
            "background-color: #FFFFFF;" /* Nền trắng sáng */
        "color: #1F2937;"            /* CHỮ MÀU ĐEN ĐẬM - Đảm bảo luôn nhìn thấy chữ */
        "border: 1px solid #D1D5DB;" /* Viền xám nhạt */
            "border-radius: 8px;"        /* Bo góc mềm mại */
        "padding: 8px 12px;"         /* Khoảng cách từ chữ tới viền vừa đủ */
            "font-size: 14px;"
            "font-family: Arial, sans-serif;"
        "}"

        "QLineEdit:focus {"
            "border: 2px solid #3B82F6;" /* Khi click vào gõ, viền sáng màu xanh dương */
                "background-color: #FFFFFF;"
        "}"
    );
    oTiengAnh->setPlaceholderText("Nhập từ tiếng Anh");
    QLineEdit *oTiengViet=new QLineEdit(this);
    oTiengViet->setStyleSheet(
        "QLineEdit {"
        "background-color: #FFFFFF;" /* Nền trắng sáng */
        "color: #1F2937;"            /* CHỮ MÀU ĐEN ĐẬM - Đảm bảo luôn nhìn thấy chữ */
        "border: 1px solid #D1D5DB;" /* Viền xám nhạt */
        "border-radius: 8px;"        /* Bo góc mềm mại */
        "padding: 8px 12px;"         /* Khoảng cách từ chữ tới viền vừa đủ */
        "font-size: 14px;"
        "font-family: Arial, sans-serif;"
        "}"

        "QLineEdit:focus {"
        "border: 2px solid #3B82F6;" /* Khi click vào gõ, viền sáng màu xanh dương */
        "background-color: #FFFFFF;"
        "}"
        );
    oTiengViet->setPlaceholderText("Nhập nghĩa tiếng Việt");
    tumoi.push_back({oTiengAnh,oTiengViet});
    QPushButton *nutXoa=new QPushButton(this);
    nutXoa->setText("XOÁ");
    nutXoa->setFixedSize(75,25);
    nutXoa->setStyleSheet(
        "background-color: #3B82F6;"
        "color: white;"
        "border-radius: 8px;"
        "font-weight: bold;"
        );
    khungNgang->addWidget(oTiengAnh);
    khungNgang->addWidget(oTiengViet);
    khungNgang->addWidget(nutXoa);
    ui->layout_danh_sach_tu->addLayout(khungNgang);
    connect(nutXoa,&QPushButton::clicked,this, [=](){
        for (int j=0;j<tumoi.size();j++){
            if(tumoi[j].oTiengAnh==oTiengAnh){
                tumoi.erase(tumoi.begin()+j);
                break;
            }
        }
        ui->layout_danh_sach_tu->removeItem(khungNgang);
        oTiengAnh->deleteLater();
        oTiengViet->deleteLater();
        nutXoa->deleteLater();
        khungNgang->deleteLater();

    });
}


void MainWindow::on_btn_luu_flashcard_clicked()
{
    int n=tumoi.size();
    vector<Tuvung>hocphan;
    for (int i=0;i<n;i++){
        string tu=tumoi[i].oTiengAnh->text().toStdString();
        string nghia=tumoi[i].oTiengViet->text().toStdString();
        hocphan.push_back({tu,nghia});
    }
    if (ischinhsua){
        danhsachhocphan[thutuhocphanchinhsua]=hocphan;
        tenhocphan[thutuhocphanchinhsua]=ui->text_ten_hoc_phan->text().toStdString();
        nuthocphan[thutuhocphanchinhsua]->setText(ui->text_ten_hoc_phan->text());
        ischinhsua=false;
    }
    else{
    danhsachhocphan.push_back(hocphan);
    tenhocphan.push_back(ui->text_ten_hoc_phan->text().toStdString());
    int thutuhocphan=danhsachhocphan.size()-1;
    QPushButton *btnMoi=new QPushButton(this);
    btnMoi->setStyleSheet(
        "QPushButton {"
        "background-color: #10B981;" /* Màu xanh ngọc lục bảo tươi sáng */
        "color: #FFFFFF;"            /* Chữ màu trắng */
        "border: none;"              /* Không dùng viền */
        "border-radius: 8px;"        /* Bo góc mềm mại */
        "padding: 12px 24px;"        /* Nút to, không gian bấm rộng rãi */
        "font-size: 15px;"
        "font-weight: bold;"
        "font-family:  Arial, sans-serif;"
        "}"

        "QPushButton:hover {"
        "background-color: #059669; /* Đậm hơn một chút khi đưa chuột vào */"
        "}"

        "QPushButton:pressed {"
        "background-color: #047857;" /* Đậm nhất khi người dùng click xuống */
        "}"

        );
    nuthocphan.push_back(btnMoi);
    btnMoi->setText(QString::fromStdString(tenhocphan[thutuhocphan]));
    connect(btnMoi,&QPushButton::clicked,this, [=](){
        ui->stackedWidget->setCurrentIndex(8);
        ui->lw_du_lieu_hoc_phan->clear();
        for (int i=0;i<danhsachhocphan[thutuhocphan].size();i++){
            ui->lw_du_lieu_hoc_phan->addItem(QString::fromStdString(danhsachhocphan[thutuhocphan][i].tienganh)+": "+QString::fromStdString((danhsachhocphan[thutuhocphan][i].tiengviet)));
        }
        hocphantemp=danhsachhocphan[thutuhocphan];
        thutuhocphanchinhsua=thutuhocphan;

    });
    QPushButton *btnXoaHP=new QPushButton(this);
    btnXoaHP->setText("X");
    btnXoaHP->setFixedSize(40, 40);
    btnXoaHP->setStyleSheet(
        "background-color: #EF4444; color: white; "
        "font-weight: bold; border-radius: 8px;"
        );
    btnXoaHP ->hide();
    nutxoahocphan.push_back(btnXoaHP);
    QHBoxLayout *hangNgang=new QHBoxLayout();
    hangNgang->addWidget(btnMoi);
    hangNgang->addWidget(btnXoaHP);
    ui->layout_danh_sach_hoc_phan->addLayout(hangNgang);
    connect(btnXoaHP,&QPushButton::clicked,this,[=](){
        for (int j=0;j<nuthocphan.size();j++){
            if (nuthocphan[j]==btnMoi){
                nuthocphan.erase(nuthocphan.begin()+j);
                danhsachhocphan.erase(danhsachhocphan.begin()+j);
                tenhocphan.erase(tenhocphan.begin()+j);
                nutxoahocphan.erase(nutxoahocphan.begin()+j);
                break;
            }
        }
        ui->layout_danh_sach_hoc_phan->removeItem(hangNgang);
        btnXoaHP->deleteLater();
        btnMoi->deleteLater();
        hangNgang->deleteLater();
    });
    }
    QLayoutItem *monDo=ui->layout_danh_sach_tu->takeAt(0);
    while (monDo!=nullptr){
        if (monDo->layout()!=nullptr){
            QLayoutItem*monDoNho=monDo->layout()->takeAt(0);
            while (monDoNho!=nullptr){
            if(monDoNho->widget()!=nullptr){
                delete monDoNho->widget();
            }
            delete monDoNho;
            monDoNho=monDo->layout()->takeAt(0);
            }
            delete monDo->layout();
        }
        monDo=ui->layout_danh_sach_tu->takeAt(0);
    }
    // QLayoutItem *child;
    // // Liên tục lấy phần tử đầu tiên ra cho đến khi Layout rỗng
    // while ((child = ui->layout_danh_sach_tu->takeAt(0)) != nullptr) {
    //     if (child->widget()) {
    //         delete child->widget(); // Nếu nó là cái Nút hoặc Ô chữ -> Xóa
    //     }
    //     else if (child->layout()) {
    //         QLayoutItem *subChild;
    //         // Nếu nó là một Layout ngang -> Dọn sạch bên trong nó trước
    //         while ((subChild = child->layout()->takeAt(0)) != nullptr) {
    //             if (subChild->widget()) delete subChild->widget();
    //             delete subChild;
    //         }
    //         delete child->layout(); // Xóa Layout ngang
    //     }
    //     delete child; // Tiêu hủy cái "sổ đỏ" (Quan trọng nhất để chống rác bộ nhớ)
    // }
    tumoi.clear();
    ui->text_ten_hoc_phan->clear();
    ui->stackedWidget->setCurrentIndex(6);
}


void MainWindow::on_btn_flashcard_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}


void MainWindow::on_btn_tao_hoc_phan_clicked()
{
    ui->text_ten_hoc_phan->clear();
    ui->stackedWidget->setCurrentIndex(7);
}


void MainWindow::on_btn_back_tu_flashcard_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_btn_back_tu_them_flashcard_clicked()
{
    tumoi.clear();
    QLayoutItem *monDo=ui->layout_danh_sach_tu->takeAt(0);
    while (monDo!=nullptr){
        if (monDo->layout()!=nullptr){
            QLayoutItem*monDoNho=monDo->layout()->takeAt(0);
            while (monDoNho!=nullptr){
                if(monDoNho->widget()!=nullptr){
                    delete monDoNho->widget();
                }
                delete monDoNho;
                monDoNho=monDo->layout()->takeAt(0);
            }
            delete monDo->layout();
        }
        monDo=ui->layout_danh_sach_tu->takeAt(0);
    }
    ui->stackedWidget->setCurrentIndex(6);
}


void MainWindow::on_btn_back_tu_du_lieu_hoc_phan_clicked()
{
    ui->lw_du_lieu_hoc_phan->clear();
    ui->stackedWidget->setCurrentIndex(6);
}

bool isMatTiengAnh=true;
void MainWindow::on_btn_hoc_voi_flashcard_clicked()
{
    i=0;
    ui->stackedWidget->setCurrentIndex(9);
    ui->btn_tu_tieng_anh->setText(QString::fromStdString(hocphantemp[i].tienganh));
    ui->btn_tu_tieng_viet->setText(QString::fromStdString(hocphantemp[i].tiengviet));
    ui->stackedWidget_2->setCurrentIndex(0);
    isMatTiengAnh=true;
    ui->lbl_thu_tu_tu->setText(QString::number(i+1)+" / "+QString::number(hocphantemp.size()));
}


void MainWindow::on_btn_back_tu_quan_ly_tu_dien_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}

void MainWindow::on_btn_tu_tieng_anh_clicked()
{
    if(isMatTiengAnh){
        ui->stackedWidget_2->setCurrentIndex(1);
        isMatTiengAnh=false;
    }
    else {
        ui->stackedWidget_2->setCurrentIndex(0);
        isMatTiengAnh=true;
    }
}

void MainWindow::on_btn_tu_tieng_viet_clicked()
{
    if(isMatTiengAnh){
        ui->stackedWidget_2->setCurrentIndex(1);
        isMatTiengAnh=false;
    }
    else {
        ui->stackedWidget_2->setCurrentIndex(0);
        isMatTiengAnh=true;
    }
}



void MainWindow::on_btn_tu_tiep_theo_clicked()
{
    if(i+1<hocphantemp.size()){
        i++;
        ui->btn_tu_tieng_anh->setText(QString::fromStdString(hocphantemp[i].tienganh));
        ui->btn_tu_tieng_viet->setText(QString::fromStdString(hocphantemp[i].tiengviet));
        ui->stackedWidget_2->setCurrentIndex(0);
        ui->lbl_thu_tu_tu->setText(QString::number(i+1)+" / "+QString::number(hocphantemp.size()));
    }
}


void MainWindow::on_btn_tu_truoc_do_clicked()
{
    if(i-1>=0){
        i--;
        ui->btn_tu_tieng_anh->setText(QString::fromStdString(hocphantemp[i].tienganh));
        ui->btn_tu_tieng_viet->setText(QString::fromStdString(hocphantemp[i].tiengviet));
        ui->stackedWidget_2->setCurrentIndex(0);
        ui->lbl_thu_tu_tu->setText(QString::number(i+1)+" / "+QString::number(hocphantemp.size()));
    }
}

void MainWindow::luufilehocphan()
{
    QString duongDan = QCoreApplication::applicationDirPath() + "/danhsachhocphan.txt";
    QFile file(duongDan);
    if (!file.open(QIODevice::WriteOnly|QIODevice::Text)){
        qDebug()<<"Lỗi không mở được file";
        return;
    }
    QTextStream out(&file);
    int n=danhsachhocphan.size();
    for (int i=0;i<n;i++){
        out<<"#"<<QString::fromStdString(tenhocphan[i])<<'\n';
        for (int j=0;j<danhsachhocphan[i].size();j++){
            QString tu=QString::fromStdString(danhsachhocphan[i][j].tienganh);
            QString nghia=QString::fromStdString(danhsachhocphan[i][j].tiengviet);
            out<<tu<<": "<<nghia<<'\n';
        }
    }
    file.close();
    qDebug()<<"Lưu file học phần thành công";
}

void MainWindow::docfilehocphan()
{
    QString duongDan = QCoreApplication::applicationDirPath() + "/danhsachhocphan.txt";
    QFile file(duongDan);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<"Lỗi không mở được file hoặc có thể là lần chạy ứng dụng đầu tiên";
        return;
    }
    QTextStream in(&file);
    vector<Tuvung>mothocphan;
    while (!in.atEnd()){
        QString line=in.readLine();
        if (line.startsWith("#")){
            QString tenhocphantemp=line.mid(1);
            tenhocphan.push_back(tenhocphantemp.toStdString());
            if(!mothocphan.empty()){
                danhsachhocphan.push_back(mothocphan);
                mothocphan.clear();
            }
        }
        else {
            QStringList parts=line.split(": ");
            if(parts.size()==2){
                Tuvung tumoi;
                tumoi.tienganh=parts[0].toStdString();
                tumoi.tiengviet=parts[1].toStdString();
                mothocphan.push_back(tumoi);
            }
        }
    }
    danhsachhocphan.push_back(mothocphan);
    qDebug()<<"Đọc file học phần thành công";
    file.close();
}

void MainWindow::tailennuthocphan()
{
    int n=tenhocphan.size();
    for (int i=0;i<n;i++){
        QPushButton*btnMoi=new QPushButton(this);
        btnMoi->setStyleSheet(
            "QPushButton {"
                "background-color: #10B981;" /* Màu xanh ngọc lục bảo tươi sáng */
                "color: #FFFFFF;"            /* Chữ màu trắng */
                "border: none;"              /* Không dùng viền */
                "border-radius: 8px;"        /* Bo góc mềm mại */
                "padding: 12px 24px;"        /* Nút to, không gian bấm rộng rãi */
                "font-size: 15px;"
                "font-weight: bold;"
                "font-family:  Arial, sans-serif;"
            "}"

            "QPushButton:hover {"
                "background-color: #059669; /* Đậm hơn một chút khi đưa chuột vào */"
            "}"

            "QPushButton:pressed {"
                "background-color: #047857;" /* Đậm nhất khi người dùng click xuống */
            "}"

        );
        nuthocphan.push_back(btnMoi);
        btnMoi->setText(QString::fromStdString(tenhocphan[i]));
        connect(btnMoi,&QPushButton::clicked,this, [=](){
            ui->stackedWidget->setCurrentIndex(8);
            ui->lw_du_lieu_hoc_phan->clear();
            for (int j=0;j<danhsachhocphan[i].size();j++){
                ui->lw_du_lieu_hoc_phan->addItem(QString::fromStdString(danhsachhocphan[i][j].tienganh)+": "+QString::fromStdString((danhsachhocphan[i][j].tiengviet)));
            }
            hocphantemp=danhsachhocphan[i];
            thutuhocphanchinhsua=i;

        });
        QPushButton *btnXoaHP=new QPushButton(this);
        btnXoaHP->setText("X");
        btnXoaHP->setFixedSize(40, 40);
        btnXoaHP->setStyleSheet(
            "background-color: #EF4444; color: white; "
            "font-weight: bold; border-radius: 8px;"
        );
        btnXoaHP ->hide();
        nutxoahocphan.push_back(btnXoaHP);
        QHBoxLayout *hangNgang=new QHBoxLayout();
        hangNgang->addWidget(btnMoi);
        hangNgang->addWidget(btnXoaHP);
        ui->layout_danh_sach_hoc_phan->addLayout(hangNgang);
        connect(btnXoaHP,&QPushButton::clicked,this,[=](){
            for (int j=0;j<nuthocphan.size();j++){
                if (nuthocphan[j]==btnMoi){
                    nuthocphan.erase(nuthocphan.begin()+j);
                    danhsachhocphan.erase(danhsachhocphan.begin()+j);
                    tenhocphan.erase(tenhocphan.begin()+j);
                    nutxoahocphan.erase(nutxoahocphan.begin()+j);
                    break;
                }
            }
            ui->layout_danh_sach_hoc_phan->removeItem(hangNgang);
            btnXoaHP->deleteLater();
            btnMoi->deleteLater();
            hangNgang->deleteLater();
        });

    }
    qDebug()<<"Số học phần: "<<n;
}


void MainWindow::on_btn_chinh_sua_hoc_phan_clicked()
{
    ischinhsua=true;
    tumoi.clear();
    int n=hocphantemp.size();
    for (int i=0;i<n;i++){
        QHBoxLayout*khungNgang=new QHBoxLayout();
        QLineEdit *oTiengAnh=new QLineEdit (this);
        oTiengAnh->setStyleSheet(
            "QLineEdit {"
            "background-color: #FFFFFF;" /* Nền trắng sáng */
            "color: #1F2937;"            /* CHỮ MÀU ĐEN ĐẬM - Đảm bảo luôn nhìn thấy chữ */
            "border: 1px solid #D1D5DB;" /* Viền xám nhạt */
            "border-radius: 8px;"        /* Bo góc mềm mại */
            "padding: 8px 12px;"         /* Khoảng cách từ chữ tới viền vừa đủ */
            "font-size: 14px;"
            "font-family: Arial, sans-serif;"
            "}"

            "QLineEdit:focus {"
            "border: 2px solid #3B82F6;" /* Khi click vào gõ, viền sáng màu xanh dương */
            "background-color: #FFFFFF;"
            "}"
            );
        oTiengAnh->setText(QString::fromStdString(hocphantemp[i].tienganh));
        QLineEdit *oTiengViet=new QLineEdit(this);
        oTiengViet->setStyleSheet(
            "QLineEdit {"
            "background-color: #FFFFFF;" /* Nền trắng sáng */
            "color: #1F2937;"            /* CHỮ MÀU ĐEN ĐẬM - Đảm bảo luôn nhìn thấy chữ */
            "border: 1px solid #D1D5DB;" /* Viền xám nhạt */
            "border-radius: 8px;"        /* Bo góc mềm mại */
            "padding: 8px 12px;"         /* Khoảng cách từ chữ tới viền vừa đủ */
            "font-size: 14px;"
            "font-family: Arial, sans-serif;"
            "}"

            "QLineEdit:focus {"
            "border: 2px solid #3B82F6;" /* Khi click vào gõ, viền sáng màu xanh dương */
            "background-color: #FFFFFF;"
            "}"
            );
        oTiengViet->setText(QString::fromStdString(hocphantemp[i].tiengviet));
        tumoi.push_back({oTiengAnh,oTiengViet});
        QPushButton *nutXoa=new QPushButton(this);
        nutXoa->setText("XOÁ");
        nutXoa->setFixedSize(75,25);
        nutXoa->setStyleSheet(
            "background-color: #3B82F6;"
            "color: white;"
            "border-radius: 8px;"
            "font-weight: bold;"
        );
        khungNgang->addWidget(oTiengAnh);
        khungNgang->addWidget(oTiengViet);
        khungNgang->addWidget(nutXoa);
        ui->layout_danh_sach_tu->addLayout(khungNgang);
        connect(nutXoa,&QPushButton::clicked,this, [=](){
            for (int j=0;j<tumoi.size();j++){
                if(tumoi[j].oTiengAnh==oTiengAnh){
                    tumoi.erase(tumoi.begin()+j);
                    break;
                }
            }
            ui->layout_danh_sach_tu->removeItem(khungNgang);
            oTiengAnh->deleteLater();
            oTiengViet->deleteLater();
            nutXoa->deleteLater();
            khungNgang->deleteLater();

        });


    }
    ui->text_ten_hoc_phan->setText(QString::fromStdString(tenhocphan[thutuhocphanchinhsua]));
    ui->stackedWidget->setCurrentIndex(7);
}


void MainWindow::on_btn_xoa_hoc_phan_clicked()
{
    chedoxoahocphan=!chedoxoahocphan;
    for (int i=0;i<nutxoahocphan.size();i++){
        nutxoahocphan[i]->setVisible(chedoxoahocphan);
    }
    if (chedoxoahocphan){
        ui->btn_xoa_hoc_phan->setStyleSheet("background-color: #F87171; color: white; font-weight: bold;");
        ui->btn_xoa_hoc_phan->setText("XONG");
    }
    else{
        ui->btn_xoa_hoc_phan->setStyleSheet(stylesheetxoahocphan);
        ui->btn_xoa_hoc_phan->setText("Xóa Học Phần");
    }
}

