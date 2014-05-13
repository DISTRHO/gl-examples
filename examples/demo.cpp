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
#include "Widget.hpp"

// ------------------------------------------------------
// use namespace

using namespace DGL;

// ------------------------------------------------------
// our widget

class DummyWidget : public Widget
{
public:
    DummyWidget(Window& win)
        : Widget(win)
    {
    }

protected:
    void onDisplay() override
    {
        glColor3f(0.302f, 0.337f, 0.361f);
        bgFull.draw();

        glColor3f(0.235f, 0.271f, 0.294f);
        bgSmall.draw();

        glColor3f(0.176f, 0.212f, 0.235f);
        bgSmall.drawOutline();

        glColor3f(0.302f*2, 0.337f*2, 0.361f*2);
        tri.draw();
    }

    void onReshape(int width, int height)
    {
        // full bg
        bgFull = DGL::Rectangle<int>(0, 0, width, height);

        // small bg
        bgSmall = DGL::Rectangle<int>(20, 10, width-40, height-20);

        // center triangle
        tri = Triangle<int>(width*0.5, height*0.1, width*0.1, height*0.9, width*0.9, height*0.9);

        // make widget same size as window
        setSize(width, height);

        // default reshape implementation
        Widget::onReshape(width, height);
    }

private:
    Rectangle<int> bgFull, bgSmall;
    Triangle<int> tri;
};

// ------------------------------------------------------
// Our Demo Window

class DemoWindow : public Window
{
public:
    DemoWindow(App& app)
        : Window(app),
          w1(*this)
    {
        setSize(300, 300);
        setTitle("DGL Demo");
    }

private:
    DummyWidget w1;
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
