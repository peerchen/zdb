/**
 * Copyright (c) 2016, Paul Asmuth <paul@asmuth.com>
 * All rights reserved.
 * 
 * This file is part of the "libzdb" project. libzdb is free software licensed
 * under the 3-Clause BSD License (BSD-3-Clause).
 */
#pragma once
#include <stdlib.h>
#include <mutex>
#include <string>
#include "transaction.h"
#include "page_map.h"
#include "page_buffer.h"
#include "cursor.h"

namespace tsdb {

class TSDB {
public:

  static const size_t kMetaBlockSize;
  static const size_t kDefaultBlockSize;
  static const char kMagicBytes[4];

  enum SeekType {
    SEEK_FIRST,
    SEEK_LAST,
    SEEK_NONE
  };

  TSDB(const TSDB& o) = delete;
  TSDB& operator=(const TSDB& o) = delete;
  ~TSDB();

  static bool openDatabase(
      std::unique_ptr<TSDB>* db,
      const std::string& filename);

  static bool createDatabase(
      std::unique_ptr<TSDB>* db,
      const std::string& filename,
      size_t block_size = kDefaultBlockSize);

  bool createSeries(
      uint64_t series_id,
      uint64_t value_size,
      const std::string& metadata);

  bool listSeries(std::set<uint64_t>* series_ids);

  bool getCursor(
      uint64_t series_id,
      Cursor* cursor,
      bool readonly = true,
      SeekType seek_type = SEEK_FIRST);

  bool getSeriesMetadata(uint64_t series_id, std::string* metadata);

  //bool insertUInt64(
  //    uint64_t series_id,
  //    uint64_t time,
  //    uint64_t value);

  bool commit();

protected:

  TSDB(int fd, size_t fpos, size_t block_size);

  bool load();
  bool loadTransaction(
      uint64_t series_id,
      uint64_t disk_addr,
      uint64_t disk_size);

  // bool insert(
  //     uint64_t series_id,
  //     uint64_t time,
  //     const void* value,
  //     size_t value_size);

  bool allocPage(
      uint64_t min_size,
      uint64_t* page_addr,
      uint64_t* page_size);

  int fd_;
  size_t fpos_;
  size_t bsize_;
  PageMap page_map_;
  TransactionMap txn_map_;
  std::mutex commit_mutex_;
};

} // namespace tsdb

