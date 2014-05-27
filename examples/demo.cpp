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

#include "ImageButton.hpp"
#include "StandaloneWindow.hpp"
#include "widgets/ExampleColorWidget.hpp"
#include "widgets/ExampleImagesWidget.hpp"
#include "widgets/ExampleRectanglesWidget.hpp"
#include "widgets/ExampleShapesWidget.hpp"
#include "widgets/ExampleTextWidget.hpp"
#include "widgets/NanoPerfWidget.hpp"

// ------------------------------------------------------
// Images

#include "demo_res/DemoArtwork.cpp"
#include "images_res/CatPics.cpp"

// ------------------------------------------------------
// use namespace

using DGL::App;
using DGL::ImageButton;
using DGL::Line;
using DGL::Size;

// ------------------------------------------------------
// Left side tab-like widget

class LeftSideWidget : public Widget
{
public:
    static const int kPageCount = 5;

    class Callback
    {
    public:
        virtual ~Callback() {}
        virtual void curPageChanged(int curPage) = 0;
    };

    LeftSideWidget(Window& parent, Callback* const cb)
        : Widget(parent),
          callback(cb),
          curPage(0),
          curHover(-1)
    {
        using namespace DemoArtwork;
        img1.loadFromMemory(ico1Data, ico1Width, ico1Height, GL_BGR);
        img2.loadFromMemory(ico2Data, ico2Width, ico2Height, GL_BGR);
        img3.loadFromMemory(ico3Data, ico3Width, ico2Height, GL_BGR);
        img4.loadFromMemory(ico4Data, ico4Width, ico4Height, GL_BGR);
        img5.loadFromMemory(ico5Data, ico5Width, ico5Height, GL_BGR);
    }

protected:
    void onDisplay() override
    {
        const int iconSize = bgIcon.getWidth();

        glColor3f(0.027f, 0.027f, 0.027f);
        Rectangle<int>(0, 0, getSize()).draw();

        bgIcon.setY(curPage*iconSize + curPage*3);

        glColor3f(0.129f, 0.129f, 0.129f);
        bgIcon.draw();

        glColor3f(0.184f, 0.184f, 0.184f);
        bgIcon.drawOutline();

        if (curHover != curPage && curHover != -1)
        {
            Rectangle<int> rHover(1, curHover*iconSize + curHover*3, iconSize-2, iconSize-2);

            glColor3f(0.071f, 0.071f, 0.071f);
            rHover.draw();

            glColor3f(0.102f, 0.102f, 0.102f);
            rHover.drawOutline();
        }

        glLineWidth(2.0f);
        glColor3f(0.184f, 0.184f, 0.184f);
        lineSep.draw();

        // reset color
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

        const int pad = iconSize/2 - DemoArtwork::ico1Width/2;

        img1.drawAt(pad, pad);
        img2.drawAt(pad, pad + 3 + iconSize);
        img3.drawAt(pad, pad + 6 + iconSize*2);
        img4.drawAt(pad, pad + 9 + iconSize*3);
        img5.drawAt(pad, pad + 12 + iconSize*4);
    }

    bool onMouse(const MouseEvent& ev) override
    {
        if (ev.button != 1 || ! ev.press)
            return false;
        if (! contains(ev.pos))
            return false;

        const int iconSize = bgIcon.getWidth();

        for (int i=0; i<kPageCount; ++i)
        {
            bgIcon.setY(i*iconSize + i*3);

            if (bgIcon.contains(ev.pos))
            {
                curPage = i;
                callback->curPageChanged(i);
                repaint();
                break;
            }
        }

        return true;
    }

    bool onMotion(const MotionEvent& ev) override
    {
        if (contains(ev.pos))
        {
            const int iconSize = bgIcon.getWidth();

            for (int i=0; i<kPageCount; ++i)
            {
                bgIcon.setY(i*iconSize + i*3);

                if (bgIcon.contains(ev.pos))
                {
                    if (curHover == i)
                        return true;

                    curHover = i;
                    repaint();
                    return true;
                }
            }

            if (curHover == -1)
                return true;

            curHover = -1;
            repaint();
            return true;
        }
        else
        {
            if (curHover == -1)
                return false;

            curHover = -1;
            repaint();
            return true;
        }
    }

    void onResize(const ResizeEvent& ev) override
    {
        const int width  = ev.size.getWidth();
        const int height = ev.size.getHeight();

        bgIcon.setWidth(width-4);
        bgIcon.setHeight(width-4);

        lineSep.setStartPos(width, 0);
        lineSep.setEndPos(width, height);
    }

private:
    Callback* const callback;
    int curPage, curHover;
    Rectangle<int> bgIcon;
    Line<int> lineSep;
    Image img1, img2, img3, img4, img5;
};

#if 0
// ------------------------------------------------------
// Resize handle

class ResizeHandle : public Widget
{
public:
    ResizeHandle(Window& parent)
        : Widget(parent),
          fMouseUnder(false),
          fLastX(0),
          fLastY(0)
    {
        fColor[0] = 1.0f;
        fColor[1] = 1.0f;
        fColor[2] = 1.0f;
        fColor[3] = 1.0f;

        setSize(16, 16);
    }

    void setColor(float color[4]) noexcept
    {
        std::memcpy(fColor, color, sizeof(float)*4);
    }

protected:
    void onDisplay() override
    {
        glColor4f(fColor[0], fColor[1], fColor[2], fColor[3]);

        fLine1.draw();
        fLine2.draw();
        fLine3.draw();

        // reset color
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    }

    void onReshape(int width, int height) override
    {
        fLine1.setStartPos(width/10, height*9/10);
        fLine1.setEndPos(width*9/10, width/10);

        fLine2.setStartPos(width*4/10, height*9/10);
        fLine2.setEndPos(width*9/10, height*4/10);

        fLine3.setStartPos(width*7/10, height*9/10);
        fLine3.setEndPos(width*9/10, height*7/10);
    }

    bool onMouse(int button, bool press, int x, int y) override
    {
        if (button != 1)
            return false;

        if (fMouseUnder)
        {
            if (! press)
                fMouseUnder = false;
            return true;
        }

        if (! contains(x, y))
            return false;
        if (! press)
            return false;

        fLastX = x+getAbsoluteX();
        fLastY = y+getAbsoluteY();
        fMouseUnder = true;
        return true;
    }

    bool onMotion(int x, int y) override
    {
        if (! fMouseUnder)
            return false;

        x += getAbsoluteX();
        y += getAbsoluteY();

        const int movedX = x - fLastX;
        const int movedY = y - fLastY;
        fLastX = x;
        fLastY = y;

        d_stdout("Moved %i, %i", movedX, movedY);

        Size<uint> size(getParentWindow().getSize());
        size += Size<uint>(movedX, movedY);

        getParentWindow().setSize(size);
        repaint();

        return true;
    }

    float fColor[4];
    bool  fMouseUnder;
    int   fLastX, fLastY;
    Line<float> fLine1, fLine2, fLine3;
};
#endif

// ------------------------------------------------------
// Our Demo Window

class DemoWindow : public Window,
                   public LeftSideWidget::Callback
{
public:
    DemoWindow(App& app)
        : Window(app),
          wColor(*this),
          wImages(*this),
          wRects(*this),
          wShapes(*this),
          wText(*this),
          wLeft(*this, this),
          //wRezHandle(*this),
          wPerf(*this, NanoPerfWidget::RENDER_FPS, "TESTING!!"),
          curWidget(nullptr)
    {
        wColor.hide();
        wImages.hide();
        wRects.hide();
        wShapes.hide();
        wText.hide();
        //wPerf.hide();

        wColor.setAbsoluteX(81);
        wImages.setAbsoluteX(81);
        wRects.setAbsoluteX(81);
        wShapes.setAbsoluteX(81);
        wText.setAbsoluteX(81);
        wLeft.setAbsolutePos(2, 2);
        wPerf.setAbsoluteY(5);

        setSize(600, 500);
        setTitle("DGL Demo");

        curPageChanged(0);
    }

    void onReshape(int width, int height) override
    {
        Size<int> size(width-81, height);
        wColor.setSize(size);
        wImages.setSize(size);
        wRects.setSize(size);
        wShapes.setSize(size);
        wText.setSize(size);

        wLeft.setSize(80-4, height-4);
        //wRezHandle.setAbsoluteX(width-wRezHandle.getWidth());
        //wRezHandle.setAbsoluteY(height-wRezHandle.getHeight());

        wPerf.setAbsoluteX(width-wPerf.getWidth()-5);

        Window::onReshape(width, height);
    }

protected:
    void curPageChanged(int curPage) override
    {
        if (curWidget != nullptr)
        {
            curWidget->hide();
            curWidget = nullptr;
        }

        switch (curPage)
        {
        case 0:
            curWidget = &wColor;
            break;
        case 1:
            curWidget = &wImages;
            break;
        case 2:
            curWidget = &wRects;
            break;
        case 3:
            curWidget = &wShapes;
            break;
        case 4:
            curWidget = &wText;
            break;
        }

        if (curWidget != nullptr)
            curWidget->show();
    }

private:
    ExampleColorWidget wColor;
    ExampleImagesWidget wImages;
    ExampleRectanglesWidget wRects;
    ExampleShapesWidget wShapes;
    ExampleTextWidget wText;
    LeftSideWidget wLeft;
    //ResizeHandle wRezHandle;
    NanoPerfWidget wPerf;

    Widget* curWidget;
};

// ------------------------------------------------------
// main entry point

int main()
{
    App app;
    DemoWindow win(app);

    win.show();
    app.exec();

    return 0;
}

// ------------------------------------------------------
