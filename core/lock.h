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
#include <stdlib.h>
#include <pthread.h>

namespace zdb {

class lock_guard {
public:
  lock_guard(pthread_rwlock_t* lock);
  lock_guard(const lock_guard& o) = delete;
  ~lock_guard();
  lock_guard& operator=(const lock_guard& o) = delete;

  void lock_write();
  void lock_read();

protected:
  pthread_rwlock_t* lock;
  bool locked;
};

} // namespace zdb
