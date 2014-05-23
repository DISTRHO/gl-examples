#!/usr/bin/make -f
# Makefile for DPF examples #
# ------------------------- #
# Created by falkTX
#

include ../dpf/dgl/Makefile.mk

# --------------------------------------------------------------

BUILD_CXX_FLAGS += -I../dpf/dgl
LINK_FLAGS      += -L../dpf -ldgl $(DGL_LIBS)

WINDRES ?= windres

# --------------------------------------------------------------

ifeq ($(WIN32),true)
TARGETS = app.exe color.exe demo.exe images.exe nanovg.exe rectangles.exe shapes.exe
else
TARGETS = app color demo images nanovg rectangles shapes
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

color: color.cpp ../dpf/dgl/*
	$(CXX) $< $(BUILD_CXX_FLAGS) $(LINK_FLAGS) -o $@

demo: demo.cpp widgets/* ../dpf/dgl/*
	$(CXX) $< $(BUILD_CXX_FLAGS) $(LINK_FLAGS) -o $@

images: images.cpp images_res/* ../dpf/dgl/*
	$(CXX) $< $(BUILD_CXX_FLAGS) $(LINK_FLAGS) -o $@

nanovg: nanovg.cpp nanovg.a nanovg_res/* nanovg_src/* ../dpf/dgl/*
	$(CXX) $< nanovg.a $(BUILD_CXX_FLAGS) -Inanovg_src $(LINK_FLAGS) -o $@

rectangles: rectangles.cpp ../dpf/dgl/*
	$(CXX) $< $(BUILD_CXX_FLAGS) $(LINK_FLAGS) -o $@

shapes: shapes.cpp ../dpf/dgl/*
	$(CXX) $< $(BUILD_CXX_FLAGS) $(LINK_FLAGS) -o $@

# --------------------------------------------------------------

cairo: cairo.cpp ../dpf/dgl/*
	$(CXX) $< $(BUILD_CXX_FLAGS) $(shell pkg-config --cflags --libs cairo) $(LINK_FLAGS) -o $@

qt-embed: qt-embed.cpp ../dpf/dgl/*
	$(CXX) $< $(BUILD_CXX_FLAGS) $(shell pkg-config --cflags --libs QtCore QtGui) $(LINK_FLAGS) -o $@

text: text.cpp ../dpf/dgl/*
	$(CXX) $< $(BUILD_CXX_FLAGS) $(LINK_FLAGS) -o $@

# --------------------------------------------------------------

%.exe: %.cpp win32/distrho.o
	$(CXX) $^ $(BUILD_CXX_FLAGS) $(LINK_FLAGS) -mwindows -o $@

nanovg.a: nanovg_src/*
	$(CC) nanovg_src/nanovg.c    -c -o nanovg_src/nanovg.c.o
	$(CC) nanovg_src/stb_image.c -c -o nanovg_src/stb_image.c.o
	rm -f nanovg.a
	ar crs nanovg.a nanovg_src/*.o

win32/distrho.o: win32/distrho.rc
	$(WINDRES) -i $< -o $@ -O coff

# --------------------------------------------------------------

.FORCE:
.PHONY: .FORCE

# --------------------------------------------------------------
