#!/usr/bin/bash -l

# compiler
CC = icc

# cflags
STD     = -std=c99
DEBUG   = -Wall -g
OPT     = -fast
CFLAGS  = $(STD) $(DEBUG) $(OPT) 
