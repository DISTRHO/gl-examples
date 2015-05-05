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

// ------------------------------------------------------
// Test class

class FileBrowserTest : public StandaloneWindow
{
public:
    FileBrowserTest()
        : StandaloneWindow()
    {
        _openFileBrowser();
    }

protected:
    void fileBrowserSelected(const char* filename) override
    {
        if (filename != nullptr)
            d_stdout("File Selected: %s", filename);
        else
            d_stdout("File browser closed without selecting any files");

        _openFileBrowser();
    }

    void _openFileBrowser()
    {
        FileBrowserOptions o;
        openFileBrowser(o);
    }
};

// ------------------------------------------------------
// main entry point

int main()
{
    FileBrowserTest swin;

    swin.setSize(300, 300);
    swin.setTitle("FileBrowser Test");

    swin.exec();

    return 0;
}

// ------------------------------------------------------
