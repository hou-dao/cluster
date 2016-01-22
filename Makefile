#!/usr/bin/bash -l
#
# Written by Houdao ZHANG
# mtailto: houdao829@gmail.com
#
include Makefile.inc

##==      TARGET     ==##

PROGRAM = ./bin/kmeans.X

## Binary directory
BINDIR  = bin

## Header directory
INCPRE  = -I .
INCSUB  = include
INCDIR  = $(addprefix $(INCPRE)/,$(INCSUB))

## Source directory
SRCPRE  = .
SRCSUB  = src
SRCDIR  = $(addprefix $(SRCPRE)/,$(SRCSUB))

## Object directory
OBJPRE  = objs
OBJDIR  = $(addprefix $(OBJPRE)/,$(SRCSUB))

## Source files
SRC     = $(foreach sdir,$(SRCDIR),$(wildcard $(sdir)/*.c))

## Object files
OBJ     = $(patsubst $(SRCPRE)/%.c,$(OBJPRE)/%.o,$(SRC))

## FLAGS & LDFLAGS

CFLAGS += $(INCDIR)  

LIBDIRS = 

LDFLAGS = -mkl

##==    Compiling    ==##

vpath %.c $(SRCDIR)

define make-obj
  $1/%.o: %.c   ; $(CC) $(CFLAGS) -c $$< -o $$@
endef


##==     OPTIONS     ==##

.PHONY: all checkdirs clean cleanall rebuild

all: checkdirs $(PROGRAM)

checkdirs: $(BINDIR) $(OBJDIR)

$(BINDIR):
	@mkdir -p $@

$(OBJDIR):
	@mkdir -p $@

$(PROGRAM): $(OBJ)
	@echo "============================="
	@echo "Linking Program $@ "
	@echo "============================="
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo "==      Link finished      =="

clean:
	@rm -rf $(OBJDIR)

cleanall: clean
	@rm -rf $(BINDIR)

rebuild: clean all

$(foreach odir, $(OBJDIR), $(eval $(call make-obj, $(odir))))
