# ***************************************************************************
# Copyright (c) 2011, 2012 Digi International Inc.,
# All rights not expressly granted are reserved.
# 
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at http://mozilla.org/MPL/2.0/.
# 
# Digi International Inc. 11001 Bren Road East, Minnetonka, MN 55343
#
# ***************************************************************************
#
#  Type 'make help' for more information.

include $(CONNECTOR_RULES)

LIB_SRC_DIR=./private
SAMPLE_DIR=./public/sample
PUBLIC_HDR_DIR=./public/include
OBJDIR=$(LIB_SRC_DIR)

ifeq ($(LITTLE_ENDIAN),true)
DFLAGS += -D_LITTLE_ENDIAN
endif

ifneq ($(FACILITY_FW), false)
DFLAGS += -D_FIRMWARE_FACILITY
endif

ifneq ($(COMPRESSION), false)
DFLAGS += -DCONNECTOR_COMPRESSION_BUILTIN
endif

ifneq ($(DATA_SERVICE), false)
DFLAGS += -DCONNECTOR_DATA_SERVICE
endif

ifeq ($(DEBUG),true)
DFLAGS += -DDEBUG -g
else
DFLAGS += -DNDEBUG -O2
endif

CFLAGS += $(DFLAGS) -I$(PUBLIC_HDR_DIR) -I./private -Wall -Werror -Wextra -Wpointer-arith -std=c99

vpath $(LIB_SRC_DIR)/%.c
vpath $(LIB_SRC_DIR)/%.h

# Default LIBDIR is the currect directory
ifeq ($(LIBDIR),)
	LIBDIR = ./
endif

ifeq ($(LDFLAGS),)
LDFLAGS = -shared
endif

# By default build a static library
ifneq ($(SHARED_LIBRARY), true)
LIB =$(LIBDIR)/libidigi.a
else
LIB =$(LIBDIR)/libidigi.so
endif

all: $(LIB)

OBJS = $(OBJDIR)/connector_api.o

$(OBJS): $(LIB_SRC_DIR)/*.c $(LIB_SRC_DIR)/*.h $(PUBLIC_HDR_DIR)/*.h

$(LIB): $(OBJS)

ifeq ($(SHARED_LIBRARY), true)
	$(LD) $(LDFLAGS) $^ -o $@
else
	$(AR) $(ARFLAGS) $@ $^
endif

MAKE= make CONNECTOR_RULES="../../../$(CONNECTOR_RULES)" DEBUG="$(DEBUG)" DFLAGS="$(DFLAGS)" LIB="../../../$(LIBDIR)" COMPRESSION="$(COMPRESSION)"

linux:
	echo "building" $(SAMPLE_DIR)/linux;\
	TARGETDIR=`pwd` ; cd $(SAMPLE_DIR)/linux;\
	$(MAKE) -f Makefile all;\
	cd $${TARGETDIR};

.PHONY: clean
clean:
	-rm -f $(OBJS) $(LIB)
	TARGETDIR=`pwd` ; cd $(SAMPLE_DIR)/linux;\
	$(MAKE) -f Makefile clean;\
	cd $${TARGETDIR};\

.PHONY: help
help:
	@echo "This makefile only supports the GNU toolchain"
	@echo "Options:"
	@echo "    CONNECTOR_RULES   = Location and name of toolset"
	@echo "    LIBDIR        = Location of library"
	@echo "    DEBUG         = true or false for debugging"
	@echo "    LITTLE_ENDIAN = true or false for little endian"
	@echo "    FACILITY_FW   = true or false for firmware upgrade capability"
	@echo "    DATA_SERVICE  = true or false for data service capability"
	@echo "    SHARED_LIBRARY = true or false for building shared library"
	@echo "Targets:"
	@echo "    all           - Build idigi library"
	@echo "    linux         - Build linux sample"
	@echo "    clean         - Delete all object files"
	@echo "CONNECTOR_RULES contain the following:"
	@echo "    CC            - Pointer to compiler"
	@echo "    LD            - Pointer to linker"
	@echo "    CFLAGS        - Options to the compiler"
	@echo "    LDFLAGS       - Options to the linker"
