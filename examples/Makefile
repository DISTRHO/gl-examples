#!/usr/bin/make -f
# Makefile for DPF examples #
# ------------------------- #
# Created by falkTX
#

include ../dpf/dgl/Makefile.mk

# --------------------------------------------------------------

BUILD_CXX_FLAGS += -I../dpf/distrho -I../dpf/dgl
LINK_FLAGS      += -L../dpf -ldgl $(DGL_LIBS)

WINDRES ?= windres

# --------------------------------------------------------------

ifeq ($(WIN32),true)
TARGETS = app.exe color.exe demo.exe demo-multi demo-subwidgets,exe images.exe nanovg.exe rectangles.exe shapes.exe text.exe
else
TARGETS = app blendish color demo demo-multi demo-subwidgets images nanovg nanovg2 rectangles shapes text
# TARGETS = blendish demo-subwidgets
endif

# --------------------------------------------------------------

all: ../libdgl.a $(TARGETS)
build: $(TARGETS)

clean:
	rm -f $(TARGETS) win32/distrho.o

debug:
	$(MAKE) DEBUG=true

# --------------------------------------------------------------

../libdgl.a: .FORCE
	$(MAKE) -C ../dpf/dgl

# --------------------------------------------------------------

app: app.cpp ../dpf/dgl/*
	$(CXX) $< $(BUILD_CXX_FLAGS) $(LINK_FLAGS) -o $@

blendish: blendish.cpp ../dpf/dgl/*
	$(CXX) $< $(BUILD_CXX_FLAGS) $(LINK_FLAGS) -o $@

color: color.cpp widgets/ExampleColorWidget.hpp ../dpf/dgl/*
	$(CXX) $< $(BUILD_CXX_FLAGS) $(LINK_FLAGS) -o $@

demo: demo.cpp widgets/* ../dpf/dgl/*
	$(CXX) $< $(BUILD_CXX_FLAGS) $(LINK_FLAGS) -o $@

demo-multi: demo-multi.cpp widgets/* ../dpf/dgl/*
	$(CXX) $< $(BUILD_CXX_FLAGS) $(LINK_FLAGS) -o $@

demo-subwidgets: demo-subwidgets.cpp widgets/* ../dpf/dgl/*
	$(CXX) $< $(BUILD_CXX_FLAGS) $(LINK_FLAGS) -o $@

images: images.cpp widgets/ExampleImagesWidget.hpp images_res/* ../dpf/dgl/*
	$(CXX) $< $(BUILD_CXX_FLAGS) $(LINK_FLAGS) -o $@

nanovg: nanovg.cpp widgets/NanoPerfWidget.hpp nanovg_res/* ../dpf/dgl/*
	$(CXX) $< $(BUILD_CXX_FLAGS) -I../dpf/dgl/src/nanovg $(LINK_FLAGS) -o $@

nanovg2: nanovg2.cpp widgets/NanoPerfWidget.hpp ../dpf/dgl/*
	$(CXX) $< $(BUILD_CXX_FLAGS) $(LINK_FLAGS) -o $@

rectangles: rectangles.cpp widgets/ExampleRectanglesWidget.hpp ../dpf/dgl/*
	$(CXX) $< $(BUILD_CXX_FLAGS) $(LINK_FLAGS) -o $@

shapes: shapes.cpp widgets/ExampleShapesWidget.hpp ../dpf/dgl/*
	$(CXX) $< $(BUILD_CXX_FLAGS) $(LINK_FLAGS) -o $@

text: text.cpp widgets/ExampleTextWidget.hpp ../dpf/dgl/*
	$(CXX) $< $(BUILD_CXX_FLAGS) $(LINK_FLAGS) -o $@

# --------------------------------------------------------------

cairo: cairo.cpp ../dpf/dgl/*
	$(CXX) $< $(BUILD_CXX_FLAGS) $(shell pkg-config --cflags --libs cairo) $(LINK_FLAGS) -o $@

file-browser: file-browser.cpp ../dpf/dgl/* ../dpf/dgl/src/sofd/*
	$(CXX) $< $(BUILD_CXX_FLAGS) $(LINK_FLAGS) -o $@

ntk: ntk.cpp ../dpf/dgl/*
	$(CXX) $< $(BUILD_CXX_FLAGS) -I../dpf/distrho -Intk_res $(shell pkg-config --cflags --libs ntk_images ntk liblo jack) $(LINK_FLAGS) -o $@

qt-embed: qt-embed.cpp ../dpf/dgl/*
	$(CXX) $< $(BUILD_CXX_FLAGS) $(shell pkg-config --cflags --libs QtCore QtGui) $(LINK_FLAGS) -o $@

# --------------------------------------------------------------

%.exe: %.cpp win32/distrho.o
	$(CXX) $^ $(BUILD_CXX_FLAGS) $(LINK_FLAGS) -mwindows -o $@

win32/distrho.o: win32/distrho.rc
	$(WINDRES) -i $< -o $@ -O coff

# --------------------------------------------------------------

.FORCE:
.PHONY: .FORCE

# --------------------------------------------------------------
