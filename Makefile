#!/usr/bin/make -f
# Makefile for DPF examples #
# ------------------------- #
# Created by falkTX
#

include dpf/Makefile.base.mk

all: libs examples

# --------------------------------------------------------------

libs:
	$(MAKE) -C dpf/dgl

examples: libs
	$(MAKE) build -C examples

# --------------------------------------------------------------

clean:
	$(MAKE) clean -C dpf/dgl
	$(MAKE) clean -C examples

# --------------------------------------------------------------

.PHONY: examples
