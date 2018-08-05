#*******************************************************************************
# File:         Makefile
# Author:       solek17
# Copyright:    2018 Copyright solek17
# License:      GNU GENERAL PUBLIC LICENSE  Version 3
# Credits:      Inspired by Neil Butterworth (https://latedev.wordpress.com) 
# Description:  Generic project makefile
# Changelog:
#   - 21.07.2018 - Initial version
#
#*******************************************************************************

# Product data
## Name. Executable will have it's name.
PRODUCT = skrzat
## Source structure.
BINDIR = bin
INCDIR = inc
OBJDIR = obj
SRCDIR = src

# Compiler 
## Which compiler to use.
CC = gcc
## Include directories
INCDIRS = -I$(INCDIR)
## Which compilation flags to use
CFLAGS = -std=c99 -Wall -Werror -g $(INCDIRS)
## Which linker to use.
LINKER = gcc
## Which linker flags to use
LDFLAGS = -std=c99 -Wall

# Lists of DEP/SRC/OBJ files
SRCFILES := $(wildcard $(SRCDIR)/*.c)
OBJFILES := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCFILES))
DEPFILES := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.d,$(SRCFILES))

# Terminal colors
COLOR_DEFAULT = \033[0m
COLOR_GREEN   = \033[0;32m
COLOR_RED     = \033[0;31m

$(BINDIR)/$(PRODUCT): $(OBJFILES)
	@echo "$(COLOR_GREEN)[ + ] Linking objects: $(OBJFILES)$(COLOR_DEFAULT)"
	$(LINKER) $(LDFLAGS) $^ -o $@
	@echo "$(COLOR_GREEN)[ + ] Product ready in $(BINDIR)/$(PRODUCT)$(COLOR_DEFAULT)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo "$(COLOR_GREEN)[ + ] Creating object: $< $(COLOR_DEFAULT)"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.d: $(SRCDIR)/%.c
	@echo "$(COLOR_GREEN)[ + ] Creating dependency: $< $(COLOR_DEFAULT)"
	$(CC) $(INCDIRS) -MM $< | sed -e 's%^%$@ %' -e 's% % $(OBJDIR)/%' > $@

-include $(DEPFILES)

.PHONY: structure
structure:
	mkdir $(BINDIR)
	mkdir $(OBJDIR)
	@echo "Structure complete"

.PHONY: clean
clean:
	rm $(OBJFILES)
	rm $(DEPFILES)
	rm $(BINDIR)/$(PRODUCT)
	@echo "Cleanup complete!"

.PHONY: remove
remove:
	@$(rm) $(BINDIR)/$(PRODUCT)
	@echo "Executable removed!"


