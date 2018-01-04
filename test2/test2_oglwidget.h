#ifndef TEST2_OGLWIDGET_H
#define TEST2_OGLWIDGET_H

#include<QOpenGLWindow>
#include <QOpenGLFunctions>

class test2_oglwidget:public QOpenGLWindow,protected QOpenGLFunctions
{
   Q_OBJECT
public:

    test2_oglwidget();

    ~test2_oglwidget();


    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    void paintOverGL();
    void paintUnderGL();

    //void paintEvent(QPaintEvent *event);
    //void resizeEvent(QResizeEvent *event);
protected slots:
    void teardownGL();

private:
    void printContextInformation();


    

};

#endif // TEST2_OGLWIDGET_H
