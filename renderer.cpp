/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include "renderer.h"

#include <QtQuick/qquickwindow.h>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLContext>
#include <QtCore/QRunnable>

OpenGLWindow::OpenGLWindow()
    : m_t(0)
    , m_renderer(nullptr)
{
    //this->setVisible(true);
    connect(this, &QQuickItem::windowChanged, this, &OpenGLWindow::handleWindowChanged);
}

void OpenGLWindow::setT(qreal t)
{
    if (t == m_t)
        return;
    m_t = t;
    emit tChanged();
    if (window())
        window()->update();
}

void OpenGLWindow::setInputPos(const QVector2D &inputPos)
{
    /*if(m_renderer != nullptr){
        m_renderer->m_viewportPosition = m_renderer->m_viewportPosition + m_renderer->mouseTranslate(glm::vec3(inputPos.x(), inputPos.y(), 0.0));
        m_renderer->updateView();
        this->update();
    }*/
}

void OpenGLWindow::handleWindowChanged(QQuickWindow *win)
{
    if (win) {
        connect(win, &QQuickWindow::beforeSynchronizing, this, &OpenGLWindow::sync, Qt::DirectConnection);
        connect(win, &QQuickWindow::sceneGraphInvalidated, this, &OpenGLWindow::cleanup, Qt::DirectConnection);
        connect(win, &QQuickWindow::widthChanged, this, &OpenGLWindow::resize, Qt::DirectConnection);
        connect(win, &QQuickWindow::heightChanged, this, &OpenGLWindow::resize, Qt::DirectConnection);

        // Ensure we start with cleared to black. The squircle's blend mode relies on this.
        win->setColor(Qt::white);
    }
}

void OpenGLWindow::cleanup()
{
    delete m_renderer;
    m_renderer = nullptr;
}

void OpenGLWindow::releaseResources()
{
    window()->scheduleRenderJob(new CleanupJob(m_renderer), QQuickWindow::BeforeSynchronizingStage);
    m_renderer = nullptr;
}

void OpenGLWindow::dragMoveEvent(QDragMoveEvent *event)
{
    if(m_renderer != nullptr){
        m_renderer->m_viewportPosition = m_renderer->m_viewportPosition + m_renderer->mouseTranslate(glm::vec3(event->pos().x(), event->pos().y(), 0.0));
        m_renderer->updateView();
        this->update();
    }
}

void OpenGLWindow::resize(){
    if(m_renderer != nullptr){
        m_renderer->updateView();
    }
}

Renderer::~Renderer()
{
    delete m_program;
}

void OpenGLWindow::sync()
{
    if (!m_renderer) {
        m_renderer = new Renderer();
        connect(window(), &QQuickWindow::beforeRendering, m_renderer, &Renderer::init, Qt::DirectConnection);
        connect(window(), &QQuickWindow::beforeRenderPassRecording, m_renderer, &Renderer::paint, Qt::DirectConnection);
    }
    m_renderer->setViewportSize(window()->size() * window()->devicePixelRatio());
    m_renderer->setT(m_t);
    m_renderer->setWindow(window());
}

void Renderer::init()
{
    if (!m_program) {
        QSGRendererInterface *rif = m_window->rendererInterface();
        Q_ASSERT(rif->graphicsApi() == QSGRendererInterface::OpenGL || rif->graphicsApi() == QSGRendererInterface::OpenGLRhi);

        initializeOpenGLFunctions();
        m_program = new QOpenGLShaderProgram();
        m_program->addCacheableShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shader.vsh");
        m_program->addCacheableShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shader.fsh");

        m_program->bindAttributeLocation("vertex", 0);
        m_program->link();
        updateView();
    }
}

void Renderer::paint()
{
    // Play nice with the RHI. Not strictly needed when the scenegraph uses
    // OpenGL directly.
    updateView();
    m_window->beginExternalCommands();

    m_program->bind();

    m_program->enableAttributeArray(0);

    glm::vec2 vert[]{
        glm::vec2(-0.2, 0.2),
        glm::vec2(0.2, 0.2),
        glm::vec2(0.2, -0.2),
        glm::vec2(-0.2, -0.2)
    };

    // This example relies on (deprecated) client-side pointers for the vertex
    // input. Therefore, we have to make sure no vertex buffer is bound.
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    m_program->setAttributeArray(0, GL_FLOAT, vert, 2);
    m_program->setUniformValue("ViewProjectionMatrix", QMatrix4x4(glm::value_ptr(m_vp)));
    m_program->setUniformValue("ModelMatrix", QMatrix4x4(glm::value_ptr(m_modelMatrix)));

    glViewport(0, 0, m_viewportSize.width(), m_viewportSize.height());

    glDisable(GL_DEPTH_TEST);   //This function makes qml widgets overlap the viewport


    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    m_program->disableAttributeArray(0);
    m_program->release();

    // Not strictly needed for this example, but generally useful for when
    // mixing with raw OpenGL.
    m_window->resetOpenGLState();

    m_window->endExternalCommands();
}

void Renderer::updateView(){
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(m_viewportPosition.x, -m_viewportPosition.y, -m_viewportPosition.z));
    m_modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3( 0.0f, 0.0f, 1.0f));
    if(m_viewportSize.width()<m_viewportSize.height()){
        m_projectionMatrix =  glm::ortho((float)-m_viewportSize.width()/(float)m_viewportSize.height()/m_viewportZoom, (float)m_viewportSize.width()/(float)m_viewportSize.height()/m_viewportZoom, -1.0f/m_viewportZoom, 1.0f/m_viewportZoom);
    }else{
        m_projectionMatrix =  glm::ortho(-1.0f/m_viewportZoom, 1.0f/m_viewportZoom, (float)-m_viewportSize.height()/(float)m_viewportSize.width()/m_viewportZoom, (float)m_viewportSize.height()/(float)m_viewportSize.width()/m_viewportZoom);
    }
    m_vp = m_projectionMatrix * view;
}

glm::vec3 Renderer::mouseTranslate(glm::vec3 pos){
    return glm::unProject(pos, m_modelMatrix, m_projectionMatrix, glm::vec4(0.0f, 0.0f, m_viewportSize.width(), m_viewportSize.height()));
}
