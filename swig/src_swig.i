/* -*- c++ -*- */

#define SRC_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "src_swig_doc.i"

%{
#include "src/signal_src.h"
%}


%include "src/signal_src.h"
GR_SWIG_BLOCK_MAGIC2(src, signal_src);
