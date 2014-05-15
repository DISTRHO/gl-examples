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

#include "images_res/CatPics.cpp"

// ------------------------------------------------------
// use namespace

using DGL::App;
using DGL::ImageButton;
using DGL::Size;

// ------------------------------------------------------
// Our Demo Window

class LeftSizeWidget : public Widget
{
public:
    LeftSizeWidget(Window& parent)
        : Widget(parent)
    {
    }

protected:
    void onDisplay() override
    {
        glColor3f(0.302f/5, 0.337f/5, 0.361f/5);
        bg.draw();

        // reset color
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    }

    void onReshape(int, int) override
    {
        bg = getArea();
    }

private:
    Rectangle<int> bg;
};

// ------------------------------------------------------
// Our Demo Window

class DemoWindow : public Window
{
public:
    DemoWindow(App& app)
        : Window(app),
          wColor(*this),
          wImages(*this),
          wRects(*this),
          wShapes(*this),
          wLeft(*this),
          b1(*this, Image()),
          b2(*this, Image())
    {
        wColor.hide();
        wImages.hide();
        wRects.hide();
        wShapes.hide();

        wColor.setX(100);
        wImages.setX(100);
        wRects.setX(100);
        wShapes.setX(100);

        setSize(600, 500);
        setTitle("DGL Demo");
    }

    void onReshape(int width, int height) override
    {
        Size<int> size(width-100, height);
        wColor.setSize(size);
        wImages.setSize(size);
        wRects.setSize(size);
        wShapes.setSize(size);

        wLeft.setSize(100, height);

        Window::onReshape(width, height);
    }

private:
    ExampleColorWidget wColor;
    ExampleImagesWidget wImages;
    ExampleRectanglesWidget wRects;
    ExampleShapesWidget wShapes;
    LeftSizeWidget wLeft;

    ImageButton b1, b2;
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
