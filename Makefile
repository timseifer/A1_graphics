ASSIGN    = a1

BREWPATH  = $(shell brew --prefix)
CXX       = $(shell fltk-config --cxx) -std=c++11 -D_CRT_SECURE_NO_WARNINGS -DGL_SILENCE_DEPRECATION -Wno-macro-redefined
CXXFLAGS  = $(shell fltk-config --cxxflags) -I$(BREWPATH)/include
LDFLAGS   = $(shell fltk-config --ldflags --use-gl --use-images) -L$(BREWPATH)/lib
   
POSTBUILD = fltk-config --post # build .app folder for osx. (does nothing on pc)

$(ASSIGN): % : main.o MyGLCanvas.o
	$(CXX) $(LDFLAGS) $^ -o $@
	$(POSTBUILD) $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

clean:
	rm -rf $(ASSIGN) $(ASSIGN).app *.o *~ *.dSYM