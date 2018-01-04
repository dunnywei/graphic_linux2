#include "test2_oglwidget.h"
#include <QDebug>
#include <QString>


test2_oglwidget::test2_oglwidget()
{

}

test2_oglwidget::~test2_oglwidget()
{

}

void test2_oglwidget::initializeGL()
{
    /*
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
     */

     // Initialize OpenGL Backend
    /*
     initializeOpenGLFunctions();
     connect(context(), SIGNAL(aboutToBeDestroyed()), this, SLOT(teardownGL()), Qt::DirectConnection);
     printContextInformation();

     // Set global information
     glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
     */

}

void test2_oglwidget::paintGL()
{
    /*
    QSize viewport_size = size();
    glViewport(0, 0, viewport_size.width(), viewport_size.height());

    glDrawArrays(GL_TRIANGLES, 0, 3);
    */
    //glClear(GL_COLOR_BUFFER_BIT);


}

void test2_oglwidget::resizeGL(int w, int h)
{
    /*
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)w/h, 0.01, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,5,0,0,0,0,1,0);
    */
   w=0;
   h=0;
}

void test2_oglwidget::printContextInformation()
{
/*
   QString glType;
   QString glVersion;
   QString glProfile;

  // Get Version Information
   glType = (context()->isOpenGLES()) ? "OpenGL ES" : "OpenGL";
   glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

  // Get Profile Information
   #define CASE(c) case QSurfaceFormat::c: glProfile = #c; break
   switch (format().profile())
   {
       CASE(NoProfile);
       CASE(CoreProfile);
       CASE(CompatibilityProfile);
    }
    #undef CASE

  // qPrintable() will print our QString w/o quotes around it.
    qDebug() << qPrintable(glType) << qPrintable(glVersion) << "(" << qPrintable(glProfile) << ")";

*/
}

void test2_oglwidget::paintOverGL()
{

}

void test2_oglwidget::paintUnderGL()
{

}


void test2_oglwidget::teardownGL()
{

}

void test2_oglwidget::paintEvent(QPaintEvent *event)
{

}

void test2_oglwidget::resizeEvent(QResizeEvent *event)
{

}



