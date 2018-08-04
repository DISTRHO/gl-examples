/*
 * DISTRHO Plugin Framework (DPF)
 * Copyright (C) 2012-2015 Filipe Coelho <falktx@falktx.com>
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
// Single Widget Window

static int gWindowCount = 0;

template<class WIG>
class SingleWidgetWindow : public Window
{
public:
    SingleWidgetWindow(Application& app)
        : Window(app),
          fWidget(*this)
    {
        const String title = "demo-multi-" + String(++gWindowCount);

        setSize(fWidget.getSize());
        setTitle(title);
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

        if (--gWindowCount == 0)
            getApp().quit();
    }

private:
    WIG fWidget;
};

// ------------------------------------------------------
// main entry point

int main()
{
    Application app;
    SingleWidgetWindow<ExampleColorWidget> wColor(app);
    SingleWidgetWindow<ExampleImagesWidget> wImages(app);
    SingleWidgetWindow<ExampleRectanglesWidget> wRects(app);
    SingleWidgetWindow<ExampleShapesWidget> wShapes(app);
    SingleWidgetWindow<ExampleTextWidget> wText(app);

    app.exec();

    return 0;
}

// ------------------------------------------------------
