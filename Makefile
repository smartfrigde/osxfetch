CC ?= cc

SRC := src/main.c
BIN_DIR := build
TARGET := $(BIN_DIR)/osxfetch

# Build profile:
#   auto      - detect from current machine (default)
#   arm64     - Apple Silicon
#   ppc       - PowerPC-era Macs
#   intel     - 64-bit Intel Macs
#   intel32   - 32-bit Intel Macs
#   universal-intel - i386 + x86_64 fat binary
PROFILE ?= auto

# Keep flags conservative for old Apple toolchains.
CFLAGS_COMMON := -O2 -Wall
LDFLAGS := -framework IOKit -framework CoreFoundation -framework CoreServices

.PHONY: all run clean help arm64 ppc intel intel32 universal-intel

# Default: build + run
all: run

run: $(TARGET)
	@echo "Running $(TARGET)..."
	@./$(TARGET)

$(TARGET): $(SRC) $(BIN_DIR)
	@profile="$(PROFILE)"; \
	if [ "$$profile" = "auto" ]; then \
		arch="$$(uname -m)"; \
		case "$$arch" in \
			arm64|aarch64) profile="arm64" ;; \
			ppc|powerpc*)  profile="ppc" ;; \
			i386|i686)     profile="intel32" ;; \
			x86_64)        profile="intel" ;; \
			*)             profile="generic" ;; \
		esac; \
	fi; \
	case "$$profile" in \
		arm64)          ARCH_FLAGS="-arch arm64" ;; \
		ppc)            ARCH_FLAGS="-arch ppc" ;; \
		intel)          ARCH_FLAGS="-arch x86_64" ;; \
		intel32)        ARCH_FLAGS="-arch i386" ;; \
		universal-intel) ARCH_FLAGS="-arch i386 -arch x86_64" ;; \
		generic)        ARCH_FLAGS="" ;; \
		*) echo "Unknown PROFILE='$$profile'"; exit 1 ;; \
	esac; \
	echo "Building profile=$$profile"; \
	echo "$(CC) $(CFLAGS_COMMON) $$ARCH_FLAGS $(SRC) -o $(TARGET) $(LDFLAGS)"; \
	$(CC) $(CFLAGS_COMMON) $$ARCH_FLAGS $(SRC) -o $(TARGET) $(LDFLAGS)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

# Convenience profile targets
arm64:
	@$(MAKE) PROFILE=arm64 run

ppc:
	@$(MAKE) PROFILE=ppc run

intel:
	@$(MAKE) PROFILE=intel run

intel32:
	@$(MAKE) PROFILE=intel32 run

universal-intel:
	@$(MAKE) PROFILE=universal-intel run

clean:
	@rm -rf $(BIN_DIR)

help:
	@echo "osxfetch Makefile"
	@echo
	@echo "Default target: make (build + run with PROFILE=auto)"
	@echo
	@echo "Profiles:"
	@echo "  make arm64            # modern Apple Silicon"
	@echo "  make ppc              # PowerPC-era Macs (10.0-10.5)"
	@echo "  make intel            # Intel 64-bit (10.5-10.15)"
	@echo "  make intel32          # Intel 32-bit (where supported)"
	@echo "  make universal-intel  # i386 + x86_64 fat binary"
	@echo
	@echo "Other:"
	@echo "  make clean"
