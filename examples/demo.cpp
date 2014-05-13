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
        l1.setStartPos(5, 5);
        l2.setStartPos(5, 5+50);
        l3.setStartPos(5, 5+100);

        l1.setEndPos(300-5, 5);
        l2.setEndPos(300-5, 5+50);
        l3.setEndPos(300-5, 5+100);
    }

protected:
    void onDisplay() override
    {
        glColor3f(0.3f, 0.5f, 0.8f);
        l1.draw();

        glColor3f(0.5f, 0.8f, 0.3f);
        l2.draw();

        glColor3f(0.8f, 0.3f, 0.5f);
        l3.draw();
    }

    Line<int> l1, l2, l3;
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
