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

#ifndef EXAMPLE_RECTANGLES_WIDGET_HPP_INCLUDED
#define EXAMPLE_RECTANGLES_WIDGET_HPP_INCLUDED

// ------------------------------------------------------
// DGL Stuff

#include "Widget.hpp"
#include "Window.hpp"

// ------------------------------------------------------
// use namespace

using DGL::Rectangle;
using DGL::Widget;
using DGL::Window;

// ------------------------------------------------------
// our widget

class ExampleRectanglesWidget : public Widget
{
public:
    ExampleRectanglesWidget(Window& parent)
        : Widget(parent)
    {
        for (int i=0; i<9; ++i)
            fClicked[i] = false;
    }

protected:
    void onDisplay() override
    {
        const int cx = getX();
        const int cy = getY();
        const int width  = getWidth();
        const int height = getHeight();

        Rectangle<int> r;

        r.setWidth(width/3 - 6);
        r.setHeight(height/3 - 6);

        // draw a 3x3 grid
        for (int i=0; i<3; ++i)
        {
            r.setX(cx + 3 + i*width/3);

            // 1st
            r.setY(cy + 3);

            if (fClicked[0+i])
                glColor3f(0.8f, 0.5f, 0.3f);
            else
                glColor3f(0.3f, 0.5f, 0.8f);

            r.draw();

            // 2nd
            r.setY(cy + 3 + height/3);

            if (fClicked[3+i])
                glColor3f(0.8f, 0.5f, 0.3f);
            else
                glColor3f(0.3f, 0.5f, 0.8f);

            r.draw();

            // 3rd
            r.setY(cy + 3 + height*2/3);

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
        //setSize(width, height);
        Widget::onReshape(width, height);
    }

    bool onMouse(int button, bool press, int x, int y) override
    {
        if (button != 1 || ! press)
            return false;

        const int cx = getX();
        const int cy = getY();
        const int width  = getWidth();
        const int height = getHeight();

        Rectangle<int> r;

        r.setWidth(width/3 - 6);
        r.setHeight(height/3 - 6);

        // draw a 3x3 grid
        for (int i=0; i<3; ++i)
        {
            r.setX(cx + 3 + i*width/3);

            // 1st
            r.setY(cy + 3);

            if (r.contains(x, y))
            {
                fClicked[0+i] = !fClicked[0+i];
                repaint();
                break;
            }

            // 2nd
            r.setY(cy + 3 + height/3);

            if (r.contains(x, y))
            {
                fClicked[3+i] = !fClicked[3+i];
                repaint();
                break;
            }

            // 3rd
            r.setY(cy + 3 + height*2/3);

            if (r.contains(x, y))
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

#endif // EXAMPLE_RECTANGLES_WIDGET_HPP_INCLUDED
