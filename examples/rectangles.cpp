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

class RectanglesWidget : public Widget
{
public:
    RectanglesWidget(Window& parent)
        : Widget(parent)
    {
        for (int i=0; i<9; ++i)
            fClicked[i] = false;
    }

protected:
    void onDisplay() override
    {
        const int width  = getWidth();
        const int height = getHeight();

        Rectangle<int> r;

        r.setWidth(width/3 - 6);
        r.setHeight(height/3 - 6);

        // draw a 3x3 grid
        for (int i=0; i<3; ++i)
        {
            r.setX(3 + i*width/3);

            // 1st
            r.setY(3);

            if (fClicked[0+i])
                glColor3f(0.8f, 0.5f, 0.3f);
            else
                glColor3f(0.3f, 0.5f, 0.8f);

            r.draw();

            // 2nd
            r.setY(3 + height/3);

            if (fClicked[3+i])
                glColor3f(0.8f, 0.5f, 0.3f);
            else
                glColor3f(0.3f, 0.5f, 0.8f);

            r.draw();

            // 3rd
            r.setY(3 + height*2/3);

            if (fClicked[6+i])
                glColor3f(0.8f, 0.5f, 0.3f);
            else
                glColor3f(0.3f, 0.5f, 0.8f);

            r.draw();
        }
    }

    void onReshape(int width, int height) override
    {
        // make this widget same size as window
        setSize(width, height);
        Widget::onReshape(width, height);
    }

    bool onMouse(int button, bool press, int x, int y) override
    {
        if (button != 1 || ! press)
            return false;

        const Point<int> pos(x, y);

        const int width  = getWidth();
        const int height = getHeight();

        Rectangle<int> r;

        r.setWidth(width/3 - 6);
        r.setHeight(height/3 - 6);

        // draw a 3x3 grid
        for (int i=0; i<3; ++i)
        {
            r.setX(3 + i*width/3);
            r.setY(3);

            if (r.contains(pos))
            {
                fClicked[0+i] = !fClicked[0+i];
                repaint();
                break;
            }

            r.setY(3 + height/3);

            if (r.contains(pos))
            {
                fClicked[3+i] = !fClicked[3+i];
                repaint();
                break;
            }

            r.setY(3 + height*2/3);

            if (r.contains(pos))
            {
                fClicked[6+i] = !fClicked[6+i];
                repaint();
                break;
            }
        }

        return true;
    }

private:
    bool fClicked[9];
};

// ------------------------------------------------------
// main entry point

int main()
{
    App app;
    Window win(app);
    RectanglesWidget rects(win);

    win.setSize(300, 300);
    win.setTitle("Rectangles");
    win.show();
    app.exec();

    return 0;
}

// ------------------------------------------------------
