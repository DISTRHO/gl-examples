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

// ------------------------------------------------------
// NanoVG Stuff

#include "widgets/NanoPerfWidget.hpp"
#include "nanovg_res/demo.h"

// ------------------------------------------------------
// use namespace

using namespace DGL;

// ------------------------------------------------------
// NanoVG Example Widget

int blowup = 0;
int screenshot = 0;
int premult = 0;

int mx = 0;
int my = 0;

class NanoExampleWidget : public NanoWidget,
                          public IdleCallback
{
public:
    NanoExampleWidget(Window& parent)
        : NanoWidget(parent),
          fContext(getContext())
    {
        parent.addIdleCallback(this);

        loadDemoData(fContext, &fData);
    }

    ~NanoExampleWidget() override
    {
        if (fContext == nullptr)
            return;

        freeDemoData(fContext, &fData);
    }

protected:
    void idleCallback() override
    {
        repaint();
    }

    void onNanoDisplay() override
    {
        if (fContext == nullptr)
            return;

        const int winWidth  = getWidth();
        const int winHeight = getHeight();

        if (premult)
            glClearColor(0, 0, 0, 0);
        else
            glClearColor(0.3f, 0.3f, 0.32f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

        renderDemo(fContext, mx, my, winWidth, winHeight, gTime.getTime(), blowup, &fData);

        if (screenshot)
        {
            screenshot = 0;
            saveScreenShot(winWidth, winHeight, premult, "dump.png");
        }
    }

    bool onKeyboard(const KeyboardEvent& ev) override
    {
        if (! ev.press)
            return false;

        switch (ev.key)
        {
        case CHAR_ESCAPE:
            getParentApp().quit();
            break;
        case ' ':
            blowup = !blowup;
            break;
        case 's':
        case 'S':
            screenshot = 1;
            break;
        case 'p':
        case 'P':
            premult = !premult;
            break;
        }

        return true;
    }

    bool onMotion(const MotionEvent& ev) override
    {
        mx = ev.pos.getX();
        my = ev.pos.getY();

        return false;
    }

private:
    NVGcontext* fContext;
    DemoData    fData;

};

// -----------------------------------------------------------------------
// We need a custom window for multiple widgets

class NanoExampleWindow : public Window
{
public:
    NanoExampleWindow(App& app)
        : Window(app),
          fDemo(*this),
          fPerf(*this, NanoPerfWidget::RENDER_FPS, "Frame Time")
    {
        fPerf.setAbsolutePos(5, 5);
        //fPerf.hide();

        setSize(1000, 600);
        setTitle("NanoVG");
    }

protected:
    void onReshape(int width, int height)
    {
        fDemo.setSize(width, height);
        //fDemo.setAbsolutePos(10, height-fDemo.getHeight()-50);

        Window::onReshape(width, height);
    }

private:
    NanoExampleWidget fDemo;
    NanoPerfWidget    fPerf;
};

// ------------------------------------------------------
// main entry point

int main()
{
    App app;
    NanoExampleWindow win(app);

    win.show();
    app.exec();

    return 0;
}

// ------------------------------------------------------

extern "C" {
#include "nanovg_res/demo.c"
}

// ------------------------------------------------------
