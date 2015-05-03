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
#include "extra/String.hpp"

#include "src/nanovg/nanovg.h"
#include "src/oui-blendish/blendish.h"

// ------------------------------------------------------
// use namespace

USE_NAMESPACE_DISTRHO;
USE_NAMESPACE_DGL;

// ------------------------------------------------------
// Test

class BlendishCommon : public NanoWidget
{
public:
    enum State {
        kStateDefault = 0, // not interacting
        kStateHover   = 1, // the mouse is hovering over the control
        kStateActive  = 2  // the widget is activated (pressed) or in an active state (toggled)
    };

    BlendishCommon(NanoWidget* groupWidget)
        : NanoWidget(groupWidget),
          fState(kStateDefault)
    {
        NVGcontext* const context(getContext());

        if (nvgFindFont(context, "__dpf_blendish__") < 0)
        {
            bndSetFont(nvgCreateFont(context, "__dpf_blendish__", "./blendish_res/DejaVuSans.ttf"));
            bndSetIconImage(nvgCreateImage(context, "./blendish_res/blender_icons16.png", 0));
        }

        setSize(250, BND_WIDGET_HEIGHT);
    }

    State getCurrentState() const noexcept
    {
        return fState;
    }

protected:
    bool onMouse(const MouseEvent& e)
    {
        if (! e.press)
            return false;
        if (! contains(e.pos))
            return false;

        if (fState == kStateActive)
            fState = kStateHover;
        else
            fState = kStateActive;

        repaint();
        return true;
    }

    bool onMotion(const MotionEvent& e)
    {
        if (! contains(e.pos))
        {
            if (fState == kStateHover)
            {
                fState = kStateDefault;
                repaint();
                return true;
            }

            return false;
        }

        if (fState == kStateDefault)
        {
            fState = kStateHover;
            repaint();
        }

        return true;
    }

private:
    State fState;
};

// ------------------------------------------------------
// Test

class BlendishLabel : public BlendishCommon
{
public:
    BlendishLabel(NanoWidget* groupWidget)
        : BlendishCommon(groupWidget),
          fIconId(-1),
          fText()
    {
        setText("this is a label");
        //_updateBounds();
    }

    int getIconId() const noexcept
    {
        return fIconId;
    }

    void setIconId(int iconId) noexcept
    {
        if (fIconId == iconId)
            return;

        fIconId = iconId;
        _updateBounds();
        repaint();
    }

    const char* getText() const noexcept
    {
        return fText;
    }

    void setText(const char* text) noexcept
    {
        if (fText == text)
            return;

        fText = text;
        _updateBounds();
        repaint();
    }

protected:
    void onNanoDisplay() override
    {
        bndLabel(getContext(),
                 getAbsoluteX(), getAbsoluteY(), getWidth(), getHeight(),
                 fIconId, fText);
    }

private:
    int    fIconId;
    String fText;

    void _updateBounds()
    {
        const float width  = bndLabelWidth (getContext(), fIconId, fText);
        const float height = bndLabelHeight(getContext(), fIconId, fText, width);

        setSize(width, height);
    }
};

class BlendishToolButton : public BlendishCommon
{
public:
    BlendishToolButton(NanoWidget* groupWidget)
        : BlendishCommon(groupWidget) {}

protected:
    void onNanoDisplay() override
    {
        bndToolButton(getContext(),
                      getAbsoluteX(), getAbsoluteY(), getWidth(), getHeight(),
                      0, static_cast<BNDwidgetState>(getCurrentState()), BND_ICON_SOUND,
                      "this is a tool-button [sound]");
    }
};

class BlendishPushButton: public BlendishCommon
{
public:
    BlendishPushButton(NanoWidget* groupWidget)
        : BlendishCommon(groupWidget) {}

protected:
    void onNanoDisplay() override
    {
        bndRadioButton(getContext(),
                       getAbsoluteX(), getAbsoluteY(), getWidth(), getHeight(),
                       0, static_cast<BNDwidgetState>(getCurrentState()), BND_ICON_NEW,
                       "this is a push-button [file->new]");
    }
};

// text field here

class BlendishCheckbox : public BlendishCommon
{
public:
    BlendishCheckbox(NanoWidget* groupWidget)
        : BlendishCommon(groupWidget) {}

protected:
    void onNanoDisplay() override
    {
        bndOptionButton(getContext(),
                        getAbsoluteX(), getAbsoluteY(), getWidth(), getHeight(),
                        static_cast<BNDwidgetState>(getCurrentState()),
                        "this is a checkbox");
    }
};

class BlendishComboBox : public BlendishCommon
{
public:
    BlendishComboBox(NanoWidget* groupWidget)
        : BlendishCommon(groupWidget) {}

protected:
    void onNanoDisplay() override
    {
        bndChoiceButton(getContext(),
                        getAbsoluteX(), getAbsoluteY(), getWidth(), getHeight(),
                        0, static_cast<BNDwidgetState>(getCurrentState()), BND_ICON_NEW,
                        "this is a combobox");

        // bndMenuBackground
        // bndMenuLabel
        // bndMenuItem
    }
};

class BlendishColorButton : public BlendishCommon
{
public:
    BlendishColorButton(NanoWidget* groupWidget)
        : BlendishCommon(groupWidget) {}

protected:
    void onNanoDisplay() override
    {
        bndColorButton(getContext(),
                       getAbsoluteX(), getAbsoluteY(), getWidth(), getHeight(),
                       BND_DEFAULT,
                       Color::fromHTML("#132487"));
    }
};

// bndNumberField

class BlendishSlider : public BlendishCommon
{
public:
    BlendishSlider(NanoWidget* groupWidget)
        : BlendishCommon(groupWidget) {}

protected:
    void onNanoDisplay() override
    {
        bndSlider(getContext(),
                  getAbsoluteX(), getAbsoluteY(), getWidth(), getHeight(),
                  0, static_cast<BNDwidgetState>(getCurrentState()),
                  0.25f, "this is a slider", "and value");
    }
};

class BlendishScrollBar : public BlendishCommon
{
public:
    BlendishScrollBar(NanoWidget* groupWidget, bool horizontal)
        : BlendishCommon(groupWidget)
    {
        if (horizontal)
            setSize(250, BND_SCROLLBAR_HEIGHT);
        else
            setSize(BND_SCROLLBAR_WIDTH, 200);
    }

protected:
    void onNanoDisplay() override
    {
        bndScrollBar(getContext(),
                     getAbsoluteX(), getAbsoluteY(), getWidth(), getHeight(),
                     static_cast<BNDwidgetState>(getCurrentState()),
                     0.25f, 0.5f);
    }
};

// bndTooltipBackground
// bndNodePort
// bndNodeWire
// bndColoredNodeWire
// bndNodeBackground
// bndSplitterWidgets
// bndJoinAreaOverlay

// ------------------------------------------------------
// Test

class TestWidget : public NanoWidget
{
public:
    TestWidget(Window& parent)
        : NanoWidget(parent, NanoVG::CREATE_ANTIALIAS|NanoVG::CREATE_STENCIL_STROKES),
          w0(this),
          w1(this),
          w2(this),
          w3(this),
          w4(this),
          w5(this),
          w6(this),
          w7(this, true),
          w7b(this, false)
    {
        w0.setAbsolutePos(10, 10+25*0);
        w1.setAbsolutePos(10, 10+25*1);
        w2.setAbsolutePos(10, 10+25*2);
        w3.setAbsolutePos(10, 10+25*3);
        w4.setAbsolutePos(10, 10+25*4);
        w5.setAbsolutePos(10, 10+25*5);
        w6.setAbsolutePos(10, 10+25*6);
        w7.setAbsolutePos(10, 10+25*7);
        //w8.setAbsolutePos(10, 10+25*8);
        //w9.setAbsolutePos(10, 10+25*9);

        w7b.setAbsolutePos(470, 10);
    }

protected:
    void onNanoDisplay() override
    {
        glClearColor(0.3f, 0.3f, 0.32f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
    }

private:
    BlendishLabel w0;
    BlendishToolButton w1;
    BlendishPushButton w2;
    BlendishCheckbox w3;
    BlendishComboBox w4;
    BlendishColorButton w5;
    BlendishSlider w6;
    BlendishScrollBar w7;
    BlendishScrollBar w7b;
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
