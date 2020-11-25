EXE = make
SRCs = make.cpp
OBJs = make.o
MDs = index.md
HX_RUN = hx-run

CXX_ = $(CXX) $(CPPFLAGS) $(CXXFLAGS)

all: $(EXE)

$(SRCs): $(HX_RUN)

%.o: %.cpp
	@echo "C++ $@"
	@$(CXX_) -c $< -o $@

$(EXE): $(OBJs)
	@echo "LD $@"
	@$(CXX_) -o $@ $^

$(HX_RUN): $(MDs)
	@echo "HX"
	@date >$(HX_RUN)
	@if which hx >/dev/null; then hx; else echo "!! NO HX"; fi

clean:
	@echo "RM"
	@rm -f $(EXE) $(OBJs) hx-run

full-clean: clean
	@rm -f $(SRCs)

.PHONY: all clean full-clean
