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

#include "ntk/NtkApp.hpp"
#include "ntk/NtkWidget.hpp"
#include "ntk/NtkWindow.hpp"

#include <FL/Fl_Button.H>

// ------------------------------------------------------

#define DISTRHO_PLUGIN_TARGET_DSSI

#include "DistrhoPlugin.hpp"
#include "DistrhoUI.hpp"
//#include "DistrhoPluginMain.cpp"
#include "DistrhoUIMain.cpp"

START_NAMESPACE_DISTRHO

using DGL::NtkWindow;

// ------------------------------------------------------
// NTK UI Test

class NtkUiTest : public UI
{
public:
    NtkUiTest()
        : UI(),
          but1(10,10,140,25,"Button 1"),
          but2(10,40,140,25,"Button 2")
    {
        box(FL_BORDER_BOX);
        color(46);

        add(but1);
        add(but2);

        end();
    }

    ~NtkUiTest()
    {
    }

protected:
    uint d_getWidth() const noexcept override
    {
        return 300;
    }

    uint d_getHeight() const noexcept override
    {
        return 300;
    }

    void d_parameterChanged(uint32_t, float) override
    {
    }

private:
    Fl_Button but1, but2;
};

// ------------------------------------------------------

Plugin* createPlugin()
{
    return nullptr;
}

UI* createUI()
{
    return new NtkUiTest();
}

// ------------------------------------------------------

END_NAMESPACE_DISTRHO

// ------------------------------------------------------

int main2()
{
    USE_NAMESPACE_DISTRHO;
    USE_NAMESPACE_DGL;

    NtkApp app;
    NtkWindow window(app);

    window.setSize(300, 300);
    window.setTitle("NTK UI Test");
    window.show();
    app.exec();

    return 0;
}

// ------------------------------------------------------
