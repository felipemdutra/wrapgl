LIB_NAME = wrapgl
LIB_STATIC = lib$(LIB_NAME).a

CXX = g++
CXXFLAGS = -Isrc -Wall -Wextra -O2
LDFLAGS =
LDLIBS = -lGLEW -lglfw

SRC_DIR = src/wrapgl
OBJ_DIR = build
DBG_OBJ_DIR = build-debug

BIN_DIR = bin
DBG_BIN_DIR = bin-debug

INSTALL_PREFIX = /usr/local

SRCS = $(shell find $(SRC_DIR) -name '*.cpp')
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
DBG_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(DBG_OBJ_DIR)/%.o,$(SRCS))

.PHONY: all clean debug install uninstall

all: $(BIN_DIR)/$(LIB_STATIC)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR)/$(LIB_STATIC): $(OBJS)
	@mkdir -p $(BIN_DIR)
	ar rcs $@ $^

debug: CXXFLAGS = -Isrc -Wall -Wextra -g -O0
debug: $(DBG_BIN_DIR)/$(LIB_STATIC)

$(DBG_OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(DBG_BIN_DIR)/$(LIB_STATIC): $(DBG_OBJS)
	@mkdir -p $(DBG_BIN_DIR)
	ar rcs $@ $^

clean:
	rm -rf $(OBJ_DIR) $(DBG_OBJ_DIR) $(BIN_DIR) $(DBG_BIN_DIR)

install: $(BIN_DIR)/$(LIB_STATIC)
	@echo "Installing $(BIN_DIR)/$(LIB_STATIC) to $(INSTALL_PREFIX)/lib/"
	install -Dm644 $(BIN_DIR)/$(LIB_STATIC) $(INSTALL_PREFIX)/lib/$(LIB_STATIC)

	@echo "Installing header files to $(INSTALL_PREFIX)/include/$(LIB_NAME)/"
	@cd $(SRC_DIR) && \
	find . -name '*.h' -print | while read file; do \
	  echo "  -> $$file"; \
	  install -Dm644 "$$file" "$(INSTALL_PREFIX)/include/$(LIB_NAME)/$$file"; \
	done

uninstall:
	@echo "Removing $(INSTALL_PREFIX)/lib/$(LIB_STATIC)"
	rm -f $(INSTALL_PREFIX)/lib/$(LIB_STATIC)

	@echo "Removing all installed headers under $(INSTALL_PREFIX)/include/$(LIB_NAME)/"
	rm -rf $(INSTALL_PREFIX)/include/$(LIB_NAME)

