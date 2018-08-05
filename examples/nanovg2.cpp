/*
 * DISTRHO Plugin Framework (DPF)
 * Copyright (C) 2012-2018 Filipe Coelho <falktx@falktx.com>
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

#include "NanoVG.hpp"
#include "widgets/NanoPerfWidget.hpp"

// ------------------------------------------------------
// NanoVG Example Widget

int blowup = 0;
int premult = 0;

int mx = 0;
int my = 0;

class NanoExampleWidget : public NanoWidget,
                          public IdleCallback
{
public:
    NanoExampleWidget(Window& parent)
        : NanoWidget(parent)
    {
        parent.addIdleCallback(this);

        for (int i = 0; i < 12; ++i)
        {
            char file[128];
            std::snprintf(file, 128, "./nanovg_res/images/image%d.jpg", i+1);
            fImages[i] = createImageFromFile(file, 0);

            if (! fImages[i].isValid())
            {
                d_stdout("Could not load %s.", file);
                return;
            }
        }

        fFontIcons  = createFontFromFile("icons", "./nanovg_res/entypo.ttf");
        fFontNormal = createFontFromFile("sans", "./nanovg_res/Roboto-Regular.ttf");
        fFontBold   = createFontFromFile("sans-bold", "./nanovg_res/Roboto-Bold.ttf");
    }

protected:
    void idleCallback() override
    {
        repaint();
    }

    void onNanoDisplay() override
    {
        const int width  = getWidth();
        //const int height = getHeight();
        const double t = gTime.getTime();

        if (premult)
            glClearColor(0, 0, 0, 0);
        else
            glClearColor(0.3f, 0.3f, 0.32f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

        drawEyes(width - 250, 50, 150, 100, mx, my, t);
    }

    bool onKeyboard(const KeyboardEvent& ev) override
    {
        if (! ev.press)
            return false;

        switch (ev.key)
        {
        case kCharEscape:
            getParentApp().quit();
            break;
        case ' ':
            blowup = !blowup;
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
    FontId fFontNormal, fFontBold, fFontIcons;
    NanoImage fImages[12];

    void drawEyes(float x, float y, float w, float h, float mx, float my, float t)
    {
        Paint gloss, bg;
        float ex = w *0.23f;
        float ey = h * 0.5f;
        float lx = x + ex;
        float ly = y + ey;
        float rx = x + w - ex;
        float ry = y + ey;
        float dx,dy,d;
        float br = (ex < ey ? ex : ey) * 0.5f;
        float blink = 1 - std::pow(std::sin(t*0.5f),200)*0.8f;

        bg = linearGradient(x,y+h*0.5f,x+w*0.1f,y+h, Color(0,0,0,32), Color(0,0,0,16));
        beginPath();
        ellipse(lx+3.0f,ly+16.0f, ex,ey);
        ellipse(rx+3.0f,ry+16.0f, ex,ey);
        fillPaint(bg);
        fill();

        bg = linearGradient(x,y+h*0.25f,x+w*0.1f,y+h, Color(220,220,220,255), Color(128,128,128,255));
        beginPath();
        ellipse(lx,ly, ex,ey);
        ellipse(rx,ry, ex,ey);
        fillPaint(bg);
        fill();

        dx = (mx - rx) / (ex * 10);
        dy = (my - ry) / (ey * 10);
        d = std::sqrt(dx*dx+dy*dy);
        if (d > 1.0f) {
                dx /= d; dy /= d;
        }
        dx *= ex*0.4f;
        dy *= ey*0.5f;
        beginPath();
        ellipse(lx+dx,ly+dy+ey*0.25f*(1-blink), br,br*blink);
        fillColor(32,32,32,255);
        fill();

        dx = (mx - rx) / (ex * 10);
        dy = (my - ry) / (ey * 10);
        d = std::sqrt(dx*dx+dy*dy);
        if (d > 1.0f) {
                dx /= d; dy /= d;
        }
        dx *= ex*0.4f;
        dy *= ey*0.5f;
        beginPath();
        ellipse(rx+dx,ry+dy+ey*0.25f*(1-blink), br,br*blink);
        fillColor(32,32,32,255);
        fill();

        gloss = radialGradient(lx-ex*0.25f,ly-ey*0.5f, ex*0.1f,ex*0.75f, Color(255,255,255,128), Color(255,255,255,0));
        beginPath();
        ellipse(lx,ly, ex,ey);
        fillPaint(gloss);
        fill();

        gloss = radialGradient(rx-ex*0.25f,ry-ey*0.5f, ex*0.1f,ex*0.75f, Color(255,255,255,128), Color(255,255,255,0));
        beginPath();
        ellipse(rx,ry, ex,ey);
        fillPaint(gloss);
        fill();
    }
};

// -----------------------------------------------------------------------
// We need a custom window for multiple widgets

class NanoExampleWindow : public Window
{
public:
    NanoExampleWindow(Application& app)
        : Window(app),
          fDemo(*this),
          fPerf(*this, NanoPerfWidget::RENDER_FPS, "Frame Time")
    {
        fPerf.setAbsolutePos(5, 5);

        setSize(1000, 600);
        setTitle("NanoVG");
    }

protected:
    void onReshape(uint width, uint height) override
    {
        fDemo.setSize(width, height);

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
    Application app;
    NanoExampleWindow win(app);

    win.show();
    app.exec();

    return 0;
}

// ------------------------------------------------------
