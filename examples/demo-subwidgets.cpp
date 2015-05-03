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

#include "StandaloneWindow.hpp"
#include "widgets/ExampleColorWidget.hpp"
#include "widgets/ExampleRectanglesWidget.hpp"
#include "widgets/ExampleShapesWidget.hpp"
#include "widgets/ExampleTextWidget.hpp"

// ------------------------------------------------------
// use namespace

using DGL::Size;
using DGL::StandaloneWindow;
using DGL::Widget;
using DGL::Window;

// ------------------------------------------------------
// SubWidgets

class SubWidgets : public Widget
{
public:
    SubWidgets(Window& parent)
        : Widget(parent),
          wColor(this),
          wRects(this),
          wShapes(this),
          wText(this)
    {
    }

protected:
    void onDisplay() override
    {
    }

    void onResize(const ResizeEvent& e) override
    {
        const uint w = e.size.getWidth()/2;
        const uint h = e.size.getHeight()/2;

        wColor.setAbsolutePos(0, 0);
        wColor.setSize(w, h);

        wRects.setAbsolutePos(w, 0);
        wRects.setSize(w, h);

        wShapes.setAbsolutePos(0, h);
        wShapes.setSize(w, h);

        wText.setAbsolutePos(w, h);
        wText.setSize(w, h);
    }

private:
    ExampleColorWidget wColor;
    ExampleRectanglesWidget wRects;
    ExampleShapesWidget wShapes;
    ExampleTextWidget wText;
};

// ------------------------------------------------------
// main entry point

int main()
{
    StandaloneWindow swin;
    SubWidgets swid(swin);

    swin.setSize(600, 600);
    swin.setTitle("SubWidgets");
    swin.exec();

    return 0;
}

// ------------------------------------------------------
