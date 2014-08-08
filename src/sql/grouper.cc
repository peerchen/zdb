/**
 * This file is part of the "FnordMetric" project
 *   Copyright (c) 2011-2014 Paul Asmuth, Google Inc.
 *
 * FnordMetric is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License v3.0. You should have received a
 * copy of the GNU General Public License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <string>
#include <vector>
#include <assert.h>
#include "grouper.h"

namespace fnordmetric {
namespace query {

Grouper::Grouper(int levels) : levels_(levels) {
  printf("new grouper with %i levels\n", levels);
}

}
}