#ifndef FFMPEGVIDEOWIDGET_H
#define FFMPEGVIDEOWIDGET_H


#include <QObject>
#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QGLShaderProgram>
#include <QMutex>
#include <mutex>
#include "IVideoCall.h"
struct AVFrame;

class FFmpegVideoWidget : public QOpenGLWidget,protected QOpenGLFunctions,public IVideoCall
{
    Q_OBJECT
public:
    void Init(int nWidth,int nHeight) override;
    FFmpegVideoWidget(QWidget* parent = nullptr);
    ~FFmpegVideoWidget();
    virtual void Repaint(AVFrame* pFrame) override; //不管成功與否都釋放frame空間
    // QOpenGLWidget interface
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
private:

    void SameSizeView(AVFrame* pFrame);
    void AlignmentView(AVFrame* pFrame);
    //shader程序
    QGLShaderProgram m_program;
    //shader中yuv變數
    GLuint unis[3] = {0};
    GLuint texs[3] = {0};
    unsigned char *datas[3] = { 0 };
    int m_nWidth;
    int m_nHeight;
    std::mutex m_Mutex;
};




#endif // FFMPEGVIDEOWIDGET_H
