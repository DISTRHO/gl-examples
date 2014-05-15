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

#ifndef EXAMPLE_SHAPES_WIDGET_HPP_INCLUDED
#define EXAMPLE_SHAPES_WIDGET_HPP_INCLUDED

// ------------------------------------------------------
// DGL Stuff

#include "Widget.hpp"
#include "Window.hpp"

// ------------------------------------------------------
// use namespace

using DGL::Circle;
using DGL::Triangle;
using DGL::Rectangle;
using DGL::Widget;
using DGL::Window;

// ------------------------------------------------------
// our widget

class ExampleShapesWidget : public Widget
{
public:
    ExampleShapesWidget(Window& parent)
        : Widget(parent)
    {
        setSize(300, 300);
    }

protected:
    void onDisplay() override
    {
#if 0
        glEnable(GL_MULTISAMPLE);
        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_SRC_ALPHA);
        glEnable(GL_ONE_MINUS_SRC_ALPHA);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
#endif

        glLineWidth(1.0f);
        glColor3f(0.302f, 0.337f, 0.361f);
        bg.draw();

        glColor3f(0.235f, 0.271f, 0.294f);
        rect.draw();

        glColor3f(0.176f, 0.212f, 0.235f);
        rect.drawOutline();

        glColor3f(0.302f*2, 0.337f*2, 0.361f*2);
        tri.draw();

        glLineWidth(3.0f);
        glColor3f(0.302f/2.0f, 0.337f/2.0f, 0.361f/2.0f);
        tri.drawOutline();

        glColor3f(0.235f, 0.271f, 0.294f);
        cir.draw();

        glLineWidth(2.0f);
        glColor3f(0.176f/4, 0.212f/4, 0.235f/4);
        cir.drawOutline();
    }

    void onReshape(int, int) override
    {
        const int cx = getX();
        const int cy = getY();
        const int width  = getWidth();
        const int height = getHeight();

        // background
        bg = getArea();

        // rectangle
        rect = Rectangle<int>(cx+20, cy+10, width-40, height-20);

        // center triangle
        tri = Triangle<int>(cx+width*0.5, cy+height*0.1, cx+width*0.1, cy+height*0.9, cx+width*0.9, cy+height*0.9);

        // circle
        cir = Circle<int>(cx+width/2, cy+height*2/3, height/6, 300);
    }

private:
    Rectangle<int> bg;
    Rectangle<int> rect;
    Triangle<int> tri;
    Circle<int> cir;
};

// ------------------------------------------------------

#endif // EXAMPLE_SHAPES_WIDGET_HPP_INCLUDED
