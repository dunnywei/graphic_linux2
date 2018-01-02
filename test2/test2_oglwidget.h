#ifndef TEST2_OGLWIDGET_H
#define TEST2_OGLWIDGET_H

#include<GL/glew.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include <QWidget>
#include <QOpenGLWidget>


class test2_oglwidget:public QOpenGLWidget
{
public:
    test2_oglwidget(QWidget *parent = 0);
    ~test2_oglwidget();
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

};

#endif // TEST2_OGLWIDGET_H
