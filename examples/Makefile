#!/usr/bin/make -f
# Makefile for DPF examples #
# ------------------------- #
# Created by falkTX
#

include ../dpf/dgl/Makefile.mk

# --------------------------------------------------------------

BUILD_CXX_FLAGS += -I../dpf/dgl
LINK_FLAGS      += -L../dpf -ldgl $(DGL_LIBS)

# --------------------------------------------------------------

ifeq ($(WIN32),true)
TARGETS = app.exe color.exe demo.exe images.exe rectangles.exe
LINK_FLAGS += -mwindows
else
TARGETS = app color demo images rectangles
endif

# --------------------------------------------------------------

all: ../libdgl.a $(TARGETS)
build: $(TARGETS)

clean:
	$(RM) $(TARGETS)

debug:
	$(MAKE) DEBUG=true

# --------------------------------------------------------------

%.exe: %
	rm -f $*.exe
	mv $* $*.exe
	ln -sf $*.exe $*

../libdgl.a: .FORCE
	$(MAKE) -C ../dpf/dgl

# --------------------------------------------------------------

app: app.cpp ../dpf/dgl/*
	$(CXX) $< $(BUILD_CXX_FLAGS) $(LINK_FLAGS) -o $@

color: color.cpp ../dpf/dgl/*
	$(CXX) $< $(BUILD_CXX_FLAGS) $(LINK_FLAGS) -o $@

demo: demo.cpp ../dpf/dgl/*
	$(CXX) $< $(BUILD_CXX_FLAGS) $(LINK_FLAGS) -o $@

images: images.cpp images_src/* ../dpf/dgl/*
	$(CXX) $< $(BUILD_CXX_FLAGS) $(LINK_FLAGS) -o $@

rectangles: rectangles.cpp ../dpf/dgl/*
	$(CXX) $< $(BUILD_CXX_FLAGS) $(LINK_FLAGS) -o $@

# --------------------------------------------------------------

cairo: cairo.cpp ../dgl/*
	$(CXX) $< $(BUILD_CXX_FLAGS) $(shell pkg-config --cflags --libs cairo) $(LINK_FLAGS) -o $@

text: text.cpp ../dgl/*
	$(CXX) $< $(BUILD_CXX_FLAGS) $(LINK_FLAGS) -o $@

# --------------------------------------------------------------

.FORCE:
.PHONY: .FORCE

# --------------------------------------------------------------
