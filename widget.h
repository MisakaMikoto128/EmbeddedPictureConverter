#ifndef WIDGET_H
#define WIDGET_H
#include <QPoint>
#include <QDropEvent>
#include <QMimeData>
#include <QWidget>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
using namespace cv;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_btnConvYUY2_clicked();

private:
    Ui::Widget *ui;
    QString current_image_path;
    void yuy2Convert(const QString & image_path);
protected:
    void dragEnterEvent(QDragEnterEvent *event);//拖拽进入
    void dropEvent(QDropEvent *event);//释放拖拽的文件
};

#endif // WIDGET_H
