CXX = clang++
CFLAGS = -g -Wall --std=c++17

LIBS = `pkg-config --static --libs glew SDL2`

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

BIN_NAME = glengine

INCLUDE =

SOURCES = $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/**/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%.o,$(basename $(SOURCES)))

SHADERS_GLSL = $(wildcard $(SRC_DIR)/**/*.glsl)
SHADERS_OBJS = $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%.o,$(basename $(SHADERS_GLSL)))

ifeq ($(OS),Windows_NT)
	BIN_NAME := $(BIN_NAME).exe

	LIBS += -lopengl32
endif

all: $(BIN_DIR)/$(BIN_NAME)

clean:
	rm -f $(BIN_DIR)/$(BIN_NAME) $(OBJECTS) $(OBJECTS:.o=.d)

$(shell mkdir -p $(BIN_DIR) >/dev/null)

$(BIN_DIR)/$(BIN_NAME): $(OBJECTS) $(SHADERS_OBJS)
	$(CXX) -o $(BIN_DIR)/$(BIN_NAME) $(LDFLAGS) $(OBJECTS) $(SHADERS_OBJS) $(LIBS)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.glsl
	@mkdir -p $(dir $@)
	$(LD) -r -b binary -o $@ $<

DEPFLAGS = -MT $@ -MMD -MP -MF $(OBJ_DIR)/$*.Td

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp $(OBJ_DIR)/%.d
	@mkdir -p $(dir $@)
	$(CXX) $(DEPFLAGS) $(CFLAGS) -c $(INCLUDE) -o $@ $<
	@mv -f $(OBJ_DIR)/$*.Td $(OBJ_DIR)/$*.d && touch $@

$(OBJ_DIR)/%.d: ;
.PRECIOUS: $(OBJ_DIR)/%.d

include $(wildcard $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%.d,$(basename $(SOURCES_EDITOR) $(SOURCES_GAME) $(SOURCES_SHARED))))
