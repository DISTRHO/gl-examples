/*
 * DISTRHO Plugin Framework (DPF)
 * Copyright (C) 2012-2014 Filipe Coelho <falktx@falktx.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any purpose with
 * or without fee is hereby granted, provided that the above copyright notice and this
 * permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD
 * TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN
 * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
 * IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

// ------------------------------------------------------
// DGL Stuff

#include "App.hpp"
#include "Window.hpp"
#include "widgets/ExampleRectanglesWidget.hpp"

// ------------------------------------------------------
// Qt Stuff

#include <QtGui/QApplication>
#include <QtGui/QIcon>
#include <QtGui/QResizeEvent>

#if DISTRHO_OS_LINUX
# include <QtGui/QX11EmbedContainer>
typedef QX11EmbedContainer QWidgetContainer;
#elif DISTRHO_OS_MAC
# include <QtGui/QMacCocoaViewContainer>
typedef QMacCocoaViewContainer QWidgetContainer;
#else
# define DISTRHO_NEEDS_WINDOW_SIZE
# include <QtGui/QWidget>
typedef QWidget QWidgetContainer;
#endif

// ------------------------------------------------------
// use namespace

using DGL::App;
using DGL::Window;

// ------------------------------------------------------
// Qt widget

template<class DGLWidget>
class DGLtoQtWidget : public QWidgetContainer
{
public:
    DGLtoQtWidget(QWidget* const qParent = nullptr)
#if DISTRHO_OS_MAC
        : QWidgetContainer(nullptr, qParent),
          glApp(),
          glWindow(glApp, 0),
#else
        : QWidgetContainer(qParent),
          glApp(),
          glWindow(glApp, winId()),
#endif
          glWidget(glWindow),
          qTimerId(startTimer(30))
    {
#if DISTRHO_OS_MAC
          //NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
          //[pool release];
          setCocoaView((void*)glWindow.getWindowId());
#endif
    }

    ~DGLtoQtWidget() override
    {
        killTimer(qTimerId);
        glWindow.close();
    }

protected:
    void resizeEvent(QResizeEvent* const event) override
    {
        const QSize& size(event->size());

        glWidget.setSize(size.width(), size.height());

#ifdef DISTRHO_NEEDS_WINDOW_SIZE
        // only needed if not handled by qt
        glWindow.setSize(size.width(), size.height());
#endif

        QWidgetContainer::resizeEvent(event);
    }

    void timerEvent(QTimerEvent* const event) override
    {
        if (event->timerId() == qTimerId)
            glApp.idle();

        QWidgetContainer::timerEvent(event);
    }

private:
    App glApp;
    Window glWindow;
    DGLWidget glWidget;

    const int qTimerId;
};

#ifdef DISTRHO_NEEDS_WINDOW_SIZE
# undef DISTRHO_NEEDS_WINDOW_SIZE
#endif

// ------------------------------------------------------
// main entry point

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon::fromTheme("firefox"));

    DGLtoQtWidget<ExampleRectanglesWidget> widget;
    widget.setWindowIcon(QIcon::fromTheme("firefox"));
    widget.resize(300, 300);
    widget.show();

    return app.exec();
}

// ------------------------------------------------------
