/** -*- Mode: C++ -*-
 * Command line parsing.
 *
 * Copyright (C) 2010, Julian Stecklina <jsteckli@os.inf.tu-dresden.de>
 * Economic rights: Technische Universitaet Dresden (Germany)
 *
 * This file is part of Vancouver.
 *
 * Vancouver.nova is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * Vancouver.nova is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License version 2 for more details.
 */

#pragma once

class Cmdline {

public:

#define CASE_WHITESPACE \
  case ' ':             \
 case '\t':             \
 case '\r':             \
 case '\n':             \
 case '\f':
  
  // Parse a string into substrings separated by spaces. Backspaces
  // quote spaces. To insert a literal backspace, use \\. cmdline is
  // modified.
  static unsigned parse(char *cmdline, char *argv[], unsigned argv_size)
  {
    enum {
      WHITESPACE,
      ARG,
      QUOTE,
    } state = WHITESPACE;

    unsigned cur = 0;

    while ((cur < argv_size) && (*cmdline != 0)) {
      char c = *cmdline;

      switch (state) {
      case WHITESPACE:
        switch (c) {
          CASE_WHITESPACE
            break;
        default:
          argv[cur] = cmdline;
          state = ARG;
          break;
        }
        break;
      case ARG:
        switch (c) {
          CASE_WHITESPACE
            *cmdline = 0; cur++;
          state = WHITESPACE;
          break;
        case '\\':
          state = QUOTE;
          // FALLTHROUGH
        default:
          break;
        }
        break;
      case QUOTE:
        // Eat any character
        state = ARG;
        break;
      }
      cmdline++;
    }

    if (state != WHITESPACE) cur++;
    return cur;
  }

};

// EOF
