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
// Our Demo Window

class LeftSizeWidget : public Widget
{
public:
    class Callback
    {
    public:
        virtual ~Callback() {}
        virtual void curPageChanged(int curPage) = 0;
    };

    LeftSizeWidget(Window& parent, Callback* const cb)
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
    }

protected:
    void onDisplay() override
    {
        const int cx = getX();
        const int cy = getY();
        const int iconSize = getWidth();

        glColor3f(0.027f, 0.027f, 0.027f);
        bg.draw();

        bgIcon.setY(cy + curPage*iconSize + curPage + 1);

        glColor3f(0.129f, 0.129f, 0.129f);
        bgIcon.draw();

        glColor3f(0.184f, 0.184f, 0.184f);
        bgIcon.drawOutline();

        if (curHover != curPage && curHover != -1)
        {
            Rectangle<int> rHover(cx + 1, cy + curHover*iconSize + curHover + 1, iconSize-2, iconSize-2);

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

        img1.drawAt(cx + pad, cy + pad);
        img2.drawAt(cx + pad, cy + pad + 1 + iconSize);
        img3.drawAt(cx + pad, cy + pad + 2 + iconSize*2);
        img4.drawAt(cx + pad, cy + pad + 3 + iconSize*3);
    }

    bool onMouse(int button, bool press, int x, int y) override
    {
        if (button != 1 || ! press)
            return false;
        if (! bg.contains(x, y))
            return false;

        const int iconSize = getWidth();

        for (int i=0; i<4; ++i)
        {
            bgIcon.setY(i*iconSize + i + 1);

            if (bgIcon.contains(x, y))
            {
                curPage = i;
                callback->curPageChanged(i);
                repaint();
                break;
            }
        }

        return true;
    }

    bool onMotion(int x, int y) override
    {
        if (getArea().contains(x, y))
        {
            const int iconSize = getWidth();

            for (int i=0; i<4; ++i)
            {
                bgIcon.setY(i*iconSize + i + 1);

                if (bgIcon.contains(x, y))
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

    void onReshape(int, int) override
    {
        const int cx = getX();
        const int iconSize = getWidth();

        bg = getArea();

        bgIcon.setX(cx+1);
        bgIcon.setWidth(iconSize-2);
        bgIcon.setHeight(iconSize-2);

        lineSep.setStartPos(iconSize+4, getY());
        lineSep.setEndPos(iconSize+4, getHeight());
    }

private:
    Callback* const callback;
    int curPage, curHover;
    Rectangle<int> bg, bgIcon;
    Line<int> lineSep;
    Image img1, img2, img3, img4;
};

// ------------------------------------------------------
// Our Demo Window

class DemoWindow : public Window,
                   public LeftSizeWidget::Callback
{
public:
    DemoWindow(App& app)
        : Window(app),
          wColor(*this),
          wImages(*this),
          wRects(*this),
          wShapes(*this),
          wLeft(*this, this),
          curWidget(nullptr)
    {
        wColor.hide();
        wImages.hide();
        wRects.hide();
        wShapes.hide();

        wColor.setPos(80, 2);
        wImages.setPos(80, 2);
        wRects.setPos(80, 2);
        wShapes.setPos(80, 2);
        wLeft.setPos(2, 2);

        setSize(600, 500);
        setTitle("DGL Demo");

        curPageChanged(0);
    }

    void onReshape(int width, int height) override
    {
        Size<int> size(width-80, height);
        wColor.setSize(size);
        wImages.setSize(size);
        wRects.setSize(size);
        wShapes.setSize(size);

        wLeft.setSize(73, height);

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
        }

        if (curWidget != nullptr)
            curWidget->show();
    }

private:
    ExampleColorWidget wColor;
    ExampleImagesWidget wImages;
    ExampleRectanglesWidget wRects;
    ExampleShapesWidget wShapes;
    LeftSizeWidget wLeft;

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
