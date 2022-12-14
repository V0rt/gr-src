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


#ifndef INCLUDED_SRC_SIGNAL_SRC_H
#define INCLUDED_SRC_SIGNAL_SRC_H

#include <src/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace src {

    /*!
     * \brief <+description of block+>
     * \ingroup src
     *
     */
    class SRC_API signal_src : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<signal_src> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of src::signal_src.
       *
       * To avoid accidental use of raw pointers, src::signal_src's
       * constructor is in a private implementation
       * class. src::signal_src::make is the public interface for
       * creating new instances.
       */
      static sptr make(const char* filename);
    };

  } // namespace src
} // namespace gr

#endif /* INCLUDED_SRC_SIGNAL_SRC_H */

