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

#include "NanoVG.hpp"
#include "Widget.hpp"
#include "StandaloneWindow.hpp"

#include "extra/ScopedPointer.hpp"

#include "src/nanovg/nanovg.h"
#include "src/oui-blendish/blendish.h"

// ------------------------------------------------------
// use namespace

USE_NAMESPACE_DISTRHO;
USE_NAMESPACE_DGL;

// ------------------------------------------------------
// Test

class BlenderOption : public NanoWidget
{
public:
    BlenderOption(NanoWidget* groupWidget)
        : NanoWidget(groupWidget),
          state(BND_DEFAULT),
          area(10, 10, 200, BND_WIDGET_HEIGHT) {}

protected:
    bool onMouse(const MouseEvent& e)
    {
        if (! e.press)
            return false;
        if (! area.contains(e.pos))
            return false;

        if (state == BND_ACTIVE)
            state = BND_HOVER;
        else
            state = BND_ACTIVE;

        repaint();
        return true;
    }

    bool onMotion(const MotionEvent& e)
    {
        if (! area.contains(e.pos))
        {
            if (state == BND_HOVER)
            {
                state = BND_DEFAULT;
                repaint();
                return true;
            }

            return false;
        }

        if (state == BND_DEFAULT)
        {
            state = BND_HOVER;
            repaint();
        }

        return true;
    }

    void onNanoDisplay() override
    {
        bndOptionButton(getContext(), 10, 10, 200, BND_WIDGET_HEIGHT, state, "checkbox whoohoo!");
    }

private:
    BNDwidgetState state;
    Rectangle<int> area;
};

class BlenderRadioBox : public NanoWidget
{
public:
    BlenderRadioBox(NanoWidget* groupWidget)
        : NanoWidget(groupWidget),
          state(BND_DEFAULT),
          area(10, 40, 200, BND_WIDGET_HEIGHT) {}

protected:
    bool onMouse(const MouseEvent& e)
    {
        if (! e.press)
            return false;
        if (! area.contains(e.pos))
            return false;

        if (state == BND_ACTIVE)
            state = BND_HOVER;
        else
            state = BND_ACTIVE;

        repaint();
        return true;
    }

    bool onMotion(const MotionEvent& e)
    {
        if (! area.contains(e.pos))
        {
            if (state == BND_HOVER)
            {
                state = BND_DEFAULT;
                repaint();
                return true;
            }

            return false;
        }

        if (state == BND_DEFAULT)
        {
            state = BND_HOVER;
            repaint();
        }

        return true;
    }

    void onNanoDisplay() override
    {
        bndRadioButton(getContext(), 10, 40, 200, BND_WIDGET_HEIGHT, 0, state, BND_ICON_NONE, "radio blender style yeah");
    }

private:
    BNDwidgetState state;
    Rectangle<int> area;
};

// ------------------------------------------------------
// Test

class TestWidget : public NanoWidget
{
public:
    TestWidget(Window& parent)
        : NanoWidget(parent, NanoVG::CREATE_ANTIALIAS|NanoVG::CREATE_STENCIL_STROKES),
          opt(this),
          rb(this)
    {
        NVGcontext* const context(getContext());

        bndSetFont(nvgCreateFont(context, "system", "./blendish_res/DejaVuSans.ttf"));
        bndSetIconImage(nvgCreateImage(context, "./blendish_res/blender_icons16.png", 0));
    }

protected:
    void onNanoDisplay() override
    {
        glClearColor(0.3f, 0.3f, 0.32f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
    }

private:
    BlenderOption opt;
    BlenderRadioBox rb;
};

// ------------------------------------------------------
// main entry point

int main()
{
    StandaloneWindow win;
    TestWidget w(win);

    win.setSize(500, 500);
    win.setTitle("Blendish");
    win.exec();

    return 0;
}

// ------------------------------------------------------
