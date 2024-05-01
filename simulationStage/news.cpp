#include "news.h"
#include "ui_news.h"

News::News(const QPixmap& image, const QString& text, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::News)
{
    ui->setupUi(this);

    setWindowTitle(QCoreApplication::applicationName() + ". News");
    ui->imageLbl->setPixmap(image);
    ui->textLbl->setText(text);

    setWindowModality(Qt::ApplicationModal);

    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::black);
    palette.setColor(QPalette::Text, Qt::black);
    ui->textLbl->setPalette(palette);

}

News::~News()
{
    delete ui;
}

void News::on_pushButton_clicked()
{
    close();
}

