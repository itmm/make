EXE = make
SRCs = make.cpp
OBJs = make.o
MDs = index.md stack.md

CXX_ = $(CXX) $(CPPFLAGS) $(CXXFLAGS)

all: $(EXE)

%.o: %.cpp
	@echo "C++ $@"
	@$(CXX_) -c $< -o $@

$(EXE): $(OBJs)
	@echo "LD $@"
	@$(CXX_) -o $@ $^

$(SRCs): $(MDs)
	@echo "HX $@"
	@if which hx >/dev/null; then \
		hx; \
	else echo "!! NO HX"; fi

clean:
	@echo "RM"
	@rm -f $(EXE) $(OBJs) hx-run

full-clean: clean
	@rm -f $(SRCs)

.PHONY: all clean full-clean
