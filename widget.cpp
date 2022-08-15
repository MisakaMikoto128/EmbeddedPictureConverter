#include "widget.h"
#include "ui_widget.h"
#include <iostream>
#include <fstream>
#include <QTextStream>
#include <QMessageBox>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowTitle(tr("YUV数组数据生成器！"));
    this->setWindowIcon(QIcon(tr(":/icoming/img/feeder.png")));
    //设置可以接收拖拽文件
    this->setAcceptDrops(true);
}

Widget::~Widget()
{
    delete ui;
}

/**
 * @brief yuy2Data2StdString
 * @param yuy2_image
 * @param width : The number of horizontal pixels,eg. width = 2,than Y U | Y V 4bytes are distributed horizontally.
 * @param height : the  number of rows.
 * @param rstr
 */
void yuy2Data2StdString(uint8_t* yuy2_image,int width,int height,std::string& rstr){
    std::stringstream result;
    int offset = 0;
    result << "{"<< std::endl;
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            offset = (y*width+x)*2;
            result << uint16_t((yuy2_image+offset)[1] << 8 | (yuy2_image+offset)[0]) << ",";
        }
        result << std::endl;
    }
    result << "};"<< std::endl;
    rstr = result.str();
}

/**
 * @brief yuvData2yuy2
 * @param yuv_image
 * @param width : The number of YUV data horizontal pixels,eg. width = 2,than Y U V | Y U V 6bytes are distributed horizontally.
 * @param height
 * @param yuy2_image
 */
void yuvData2yuy2(uint8_t* yuv_image,int width,int height,uint8_t* yuy2_image){
    int offset2 = 0;
    int offset1 = 0;
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            offset2 = (y*width+x)*3;
            offset1 = (y*width+x)*2;
            (yuy2_image+offset1)[0] = (yuv_image+offset2)[0];
            if(x%2 == 0){
                (yuy2_image+offset1)[1] = (yuv_image+offset2)[1];
            }else{
                (yuy2_image+offset1)[1] = (yuv_image+offset2)[2];
            }
        }
    }
}


void Widget::on_btnConvYUY2_clicked()
{
    yuy2Convert(current_image_path);
}

void Widget::yuy2Convert(const QString &image_path)
{
    if(image_path.isEmpty()){
        QMessageBox::warning(this,
                               QString::fromLocal8Bit("Application error!"),
                               QString::fromLocal8Bit("Need a file!"),
                               QMessageBox::Close);
        return;
    }
    Mat image = imread(image_path.toStdString());
    Mat cv_yuv;
    cvtColor(image, cv_yuv, cv::COLOR_BGR2YUV);
    int width = image.cols;
    int height = image.rows;
    uchar* originalImage = (uchar*)cv_yuv.data;
    uchar* yuy2_image = new uchar[width*height*2];
    yuvData2yuy2(originalImage,width,height,yuy2_image);
    std::string result_str;
    yuy2Data2StdString(yuy2_image,width,height,result_str);
    ui->textEditOut->setPlainText(QString::fromStdString(result_str));
    delete[] yuy2_image;
}



void Widget::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

void Widget::dropEvent(QDropEvent *event)
{
    current_image_path = event->mimeData()->urls().first().toString().mid(sizeof("file:///") - 1);
    yuy2Convert(current_image_path);
}

