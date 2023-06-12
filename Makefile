COMPILER ?= clang
LINKER ?= ld.lld
RUSTC ?= rustc
CARGO ?= cargo
TARGET ?= $(shell $(RUSTC) -Z unstable-options --print target-spec-json | grep llvm-target | cut -d '"' -f4)
RELEASE ?= false

RELEASE_FLAGS =
BUILDTYPE = debug
ifeq ($(RELEASE), 1)
	BUILDTYPE = release
	RELEASE_FLAGS = --release
endif

CSUARCH =
CCTRIPLE =
ACTUAL_TARGET =
CRTFLAGS = -nostdlib -nostdinc -ffreestanding -fno-stack-protector
CARGO_FLAGS = -Ztls-model=initial-exec
LINKER_FLAGS = -shared -nostdlib -z now -z relro -z noexecstack --icf=safe

ifneq (,$(findstring aarch64,$(TARGET)))
	CSUARCH = arm64
	CCTRIPLE = aarch64-linux-ouma
	ACTUAL_TARGET = aarch64-unknown-linux-ouma
else ifneq (,$(findstring x86_64,$(TARGET)))
	CSUARCH = x86_64
	CCTRIPLE = x86_64-linux-ouma
	ACTUAL_TARGET = x86_64-unknown-linux-ouma
else
	$(error Platform is not supported)
endif
CRTFLAGS += -target $(CCTRIPLE) -Iinclude -Iinclude/$(CCTRIPLE) -Icsu

BUILDDIR = $(shell pwd)/target/$(ACTUAL_TARGET)/$(BUILDTYPE)

CARGO_TARGETS = \
	$(BUILDDIR)/libc.a \
	$(BUILDDIR)/libc.so

CRT_TARGETS = \
	$(BUILDDIR)/ouma_rt.crt1.o \
	$(BUILDDIR)/ouma_rt.crti.o \
	$(BUILDDIR)/ouma_rt.crtn.o

ALL_TARGETS = \
	$(CARGO_TARGETS) \
	$(CRT_TARGETS)

.PHONY: all clean

all: $(ALL_TARGETS)

$(BUILDDIR)/libc.a:
	$(CARGO) +nightly rustc $(RELEASE_FLAGS) --target=$(shell pwd)/src/specs/$(ACTUAL_TARGET).json -- $(CARGO_FLAGS)

$(BUILDDIR)/ouma_rt.crt1.o: csu/$(CSUARCH)/crt1.S
	$(COMPILER) $(CRTFLAGS) -c $< -o $@

$(BUILDDIR)/ouma_rt.crti.o: csu/$(CSUARCH)/crti.S
	$(COMPILER) $(CRTFLAGS) -c $< -o $@

$(BUILDDIR)/ouma_rt.crtn.o: csu/$(CSUARCH)/crtn.S
	$(COMPILER) $(CRTFLAGS) -c $< -o $@

$(BUILDDIR)/libc.so: $(BUILDDIR)/libc.a
	$(LINKER) $(LINKER_FLAGS) -o $@ --whole-archive $< --no-whole-archive

clean: all
	rm -rf $(ALL_TARGETS) target

.NOTPARALLEL:
