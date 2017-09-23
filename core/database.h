/**
 * This file is part of the "FnordMetric" project
 *   Copyright (c) 2016 Paul Asmuth <paul@asmuth.com>
 *
 * FnordMetric is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License v3.0. You should have received a
 * copy of the GNU General Public License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#pragma once
#include "tuple.h"
#include "metadata.h"

namespace zdb {

struct database {

  database(metadata&& meta, bool readonly);
  database(const database& o) = delete;
  database(database&& o) = delete;
  ~database();

  void close();

  int cursor_init(
      const std::string& table_name,
      cursor_ref* cursor);

  int commit();

  metadata meta;
  const bool readonly;
  pthread_rwlock_t lock;
};

} // namespace zdb
