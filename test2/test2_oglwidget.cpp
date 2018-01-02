#include "test2_oglwidget.h"

test2_oglwidget::test2_oglwidget(QWidget *parent):QOpenGLWidget(parent)
{

}

test2_oglwidget::~test2_oglwidget()
{

}

void test2_oglwidget::initializeGL()
{
    GLfloat verts[]=
    {
            +0.0f, +100.0f,
            -100.0f,-100.0f,
            +100.0f,-100.0f,
     };
     GLuint mybufferID;
     glGenBuffers(1, &mybufferID);
     glBindBuffer(GL_ARRAY_BUFFER, mybufferID);
     glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

     glEnableVertexAttribArray(0);//first attribute
     glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

}

void test2_oglwidget::paintGL()
{
    QSize viewport_size = size();
    glViewport(0, 0, viewport_size.width(), viewport_size.height());

    glDrawArrays(GL_TRIANGLES, 0, 3);

}

void test2_oglwidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)w/h, 0.01, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,5,0,0,0,0,1,0);

}



