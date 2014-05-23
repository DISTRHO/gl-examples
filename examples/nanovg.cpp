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

#define NANOVG_GL2_IMPLEMENTATION
#include "nanovg_src/nanovg_gl.h"
#include "nanovg_res/demo.h"
#include "nanovg_res/perf.h"

#include <sys/time.h>
#include <time.h>

// ------------------------------------------------------
// get time

#ifdef DISTRHO_OS_WINDOWS
#else
struct TimePOSIX {
    bool monotonic;
    double resolution;
    uint64_t base;

    TimePOSIX()
        : monotonic(false),
          resolution(1e-6),
          base(0)
    {
#if defined(CLOCK_MONOTONIC)
        struct timespec ts;

        if (::clock_gettime(CLOCK_MONOTONIC, &ts) == 0)
        {
            monotonic = true;
            resolution = 1e-9;
        }
#endif

        base = getRawTime();
    }

    uint64_t getRawTime()
    {
#if defined(CLOCK_MONOTONIC)
        if (monotonic)
        {
            struct timespec ts;

            ::clock_gettime(CLOCK_MONOTONIC, &ts);
            return (uint64_t) ts.tv_sec * (uint64_t) 1000000000 + (uint64_t) ts.tv_nsec;
        }
        else
#endif
        {
            struct timeval tv;

            ::gettimeofday(&tv, NULL);
            return (uint64_t) tv.tv_sec * (uint64_t) 1000000 + (uint64_t) tv.tv_usec;
        }
    }

    double getTime()
    {
        return (double)(getRawTime() - base) * resolution;
    }
};

static TimePOSIX gTime;
#endif

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

double prevt = 0;

class NanoVGExampleWidget : public Widget,
                            public IdleCallback
{
public:
    NanoVGExampleWidget(Window& parent)
        : Widget(parent),
          fContext(nullptr)
    {
        parent.addIdleCallback(this);
//             init = false;

            initGraph(&fPerf, GRAPH_RENDER_FPS, "Frame Time");

            fContext = nvgCreateGL2(512, 512, NVG_ANTIALIAS);
            DISTRHO_SAFE_ASSERT_RETURN(fContext != nullptr,);

            loadDemoData(fContext, &fData);

            prevt = gTime.getTime();
    }

    ~NanoVGExampleWidget() override
    {
        if (fContext == nullptr)
            return;

        freeDemoData(fContext, &fData);
        nvgDeleteGL2(fContext);
    }

protected:
    void idleCallback() override
    {
        repaint();
    }

    void onDisplay() override
    {
        const int winWidth  = getWidth();
        const int winHeight = getHeight();

        double t, dt;

        t = gTime.getTime();
        dt = t - prevt;
        prevt = t;
        updateGraph(&fPerf, dt);

        if (premult)
            glClearColor(0,0,0,0);
        else
            glClearColor(0.3f, 0.3f, 0.32f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

        nvgBeginFrame(fContext, winWidth, winHeight, 1.0f, premult ? NVG_PREMULTIPLIED_ALPHA : NVG_STRAIGHT_ALPHA);

        renderDemo(fContext, mx, my, winWidth, winHeight, t, blowup, &fData);
        renderGraph(fContext, 5, 5, &fPerf);

        nvgEndFrame(fContext);

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
    PerfGraph   fPerf;
};

// ------------------------------------------------------
// main entry point

int main()
{
    StandaloneWindow swin;
    NanoVGExampleWidget widget(swin);

    swin.setSize(1000, 600);
    swin.setTitle("NanoVG");
    swin.exec();

    return 0;
}

// ------------------------------------------------------

extern "C" {
#include "nanovg_res/demo.c"
#include "nanovg_res/perf.c"
}

// ------------------------------------------------------
