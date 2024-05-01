#ifndef NEWS_H
#define NEWS_H

#include <QDialog>

namespace Ui {
class News;
}

class News : public QDialog
{
    Q_OBJECT

public:
    explicit News(const QPixmap& image, const QString& text, QWidget *parent = nullptr);
    ~News() override;

private slots:
    void on_pushButton_clicked();

private:
    Ui::News *ui;
};

#endif // NEWS_H
