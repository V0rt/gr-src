/* -*- c++ -*- */
/* 
 * Copyright 2020 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "signal_src_impl.h"

namespace gr {
    namespace src {

        signal_src::sptr
        signal_src::make(const char *filename) {
            return gnuradio::get_initial_sptr
                    (new signal_src_impl(filename));
        }

        /*
         * The private constructor
         */
        signal_src_impl::signal_src_impl(const char *filename)
                : gr::sync_block("signal_src",
                                 gr::io_signature::make(0, 0, 0),
                                 gr::io_signature::make(1, 1, sizeof(gr_complex))),
                  d_path(filename) {
            std::fstream fin(d_path, std::ios_base::in | std::ios_base::binary);
            if (!fin.is_open()) {
                std::cout << "Error: Falied to open file " << d_path << std::endl;
            } else {
                std::cout << "Ok: File found " << d_path << std::endl;
            }

            fin.seekg(0, std::ios_base::end);
            file_size_bytes = fin.tellg();
            signal_length_samples = file_size_bytes / sizeof(gr_complex);
            std::cout << signal_length_samples << " samples " << std::endl;
            fin.seekg(0, std::ios_base::beg);

            gr_complex tmp = gr_complex(2, 2);
            for (int sample = 0; sample < signal_length_samples; ++sample) {
                fin.read(reinterpret_cast<char *>(&tmp), sizeof(gr_complex));
                std::cout << tmp << std::endl;
                Signal.push_back(tmp);
            }

            std::cout << "Signal.size()" << Signal.size() << std::endl;
        }

        /*
         * Our virtual destructor.
         */
        signal_src_impl::~signal_src_impl() {
        }

        int
        signal_src_impl::work(int noutput_items,
                              gr_vector_const_void_star &input_items,
                              gr_vector_void_star &output_items) {
            gr_complex *out = (gr_complex *) output_items[0];

            // Do <+signal processing+>
            for (int i = 0; i < noutput_items; ++i) {
                out[i] = Signal[signal_ptr];
                signal_ptr++;
                if (signal_ptr == signal_length_samples)
                    signal_ptr = 0;
            }
            // Tell runtime system how many output items we produced.
            return noutput_items;
        }

    } /* namespace src */
} /* namespace gr */

