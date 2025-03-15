EXE = processImage

OBJS_DIR = .objs

OBJS_STUDENT = processImage.o
OBJS_PROVIDED = main.o rgbapixel.o png.o

CXX = g++
LD = g++
CXXFLAGS = -g -O0 -MMD -MP -c -Werror -pedantic

LDFLAGS = -lpng

all: $(EXE)

# Pattern rules for object files
$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

# Create directories
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(EXE):
	$(LD) $^ $(LDFLAGS) -o $@

# Executable dependencies
$(EXE):      $(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_PROVIDED))

# Include automatically generated dependencies
-include $(OBJS_DIR)/*.d

clean:
	rm -rf $(EXE) $(OBJS_DIR)

tidy: clean
	rm -rf doc out.png

.PHONY: all tidy clean
