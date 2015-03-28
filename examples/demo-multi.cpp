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
// Single Widget Window

static int gWindowCount = 0;

template<class WIG>
class SingleWidgetWindow : public Window
{
public:
    SingleWidgetWindow(App& app)
        : Window(app),
          fWidget(*this),
          fIsMain(true)
    {
        setSize(fWidget.getSize());
        setTitle("demo-multi");
        show();
    }

    SingleWidgetWindow(App& app, Window& parent)
        : Window(app, parent),
          fWidget(*this),
          fIsMain(false)
    {
        setResizable(false);
        setSize(fWidget.getSize());
        setTitle(d_string("transient #") + d_string(++gWindowCount));
        show();
    }

protected:
    void onReshape(uint width, uint height) override
    {
        fWidget.setSize(width, height);
        Window::onReshape(width, height);
    }

    void onClose() override
    {
        Window::onClose();

        if (fIsMain)
            getApp().quit();
    }

private:
    WIG fWidget;
    bool fIsMain;
};

// ------------------------------------------------------
// main entry point

int main()
{
    App app;
    SingleWidgetWindow<ExampleColorWidget> wColor(app);
    SingleWidgetWindow<ExampleImagesWidget> wImages(app, wColor);
    SingleWidgetWindow<ExampleRectanglesWidget> wRects(app, wColor);
    SingleWidgetWindow<ExampleShapesWidget> wShapes(app, wColor);
    SingleWidgetWindow<ExampleTextWidget> wText(app, wColor);

    app.exec();

    return 0;
}

// ------------------------------------------------------
