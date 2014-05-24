/**
 * This file is part of the "FnordMetric" project
 *   Copyright (c) 2014 Paul Asmuth, Google Inc.
 *
 * Licensed under the MIT license (see LICENSE).
 */
#ifndef _FNORDMETRIC_METRIC_H
#define _FNORDMETRIC_METRIC_H

#include <stdlib.h>
#include <stdint.h>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <memory>
#include "schema.h"
#include "record.h"
#include "fnv.h"

namespace fnordmetric {

class IStorageCursor;

/*
class MetricDescription {
public:

  MetricDescription(const std::string& name) : name_(name) {}

  MetricDescription(const std::string& name, const std::string& unit) :
      name_(name),
      unit_(unit) {}

  MetricDescription(
      const std::string& name,
      const std::string& unit,
      const std::string& description) :
      name_(name),
      unit_(unit),
      description_(description) {}

  const std::string& getName() const {
    return name_;
  }

protected:
  std::string name_;
  std::string unit_;
  std::string description_;
};
*/

class IStreamKey {
public:

  //explicit IStreamKey(const std:string& name, const ISchema& schema);

  const std::string& getKeyString() const {
    return key_str_;
  }

protected:
  explicit IStreamKey(const std::string& key_str) : key_str_(key_str) {}

  const std::string key_str_;
};

template <typename... T>
class StreamKey : public IStreamKey {
public:

  explicit StreamKey(
      const std::string& name,
      T... fields) :
      IStreamKey(buildKeyString(name, fields...)) {}

protected:

  std::string buildKeyString(const std::string& name, T... fields) {
    std::stringstream ss;
    FNV<uint64_t> fnv;

    ss << std::hex << fnv.hash(name);

    buildKeyString(&ss, fields...);
    return ss.str();
  }

  template<typename... F>
  void buildKeyString(std::stringstream* ss, IField head, F... tail) {
    FNV<uint32_t> fnv;

    *ss << '-' << 
        static_cast<char>(head.getTypeId()) <<
        std::hex << fnv.hash(head.getName());

    buildKeyString(ss, tail...);
  }

  void buildKeyString(std::stringstream* ss) {}

};


class IStream {
public:

  explicit IStream(
      const IStreamKey& key,
      const ISchema& schema,
      //const MetricDescription& description,
      std::unique_ptr<IStorageCursor>&& cursor) :
      key_(key),
      schema_(schema),
      //description_(description),
      cursor_(std::move(cursor)) {}

  IStream(const IStream& copy) = delete;
  IStream& operator=(const IStream& copy) = delete;

  const ISchema& getSchema() const {
    return schema_;
  }

  const IStreamKey& getKey() const {
    return key_;
  }

  void appendRecord(const IRecord& record) const;

protected:

  const std::unique_ptr<IStorageCursor> cursor_;
  const IStreamKey key_;
  //const MetricDescription description_;
  const ISchema schema_;
};

template <typename... T>
class Stream : public IStream {
public:

  explicit Stream(
      const IStreamKey& key,
      const Schema<T...>& schema,
      //const MetricDescription& description,
      std::unique_ptr<IStorageCursor>&& cursor) :
      IStream(
          key,
          schema,
          //description,
          std::move(cursor)) {}

  Stream(const Stream& copy) = delete;
  Stream& operator=(const Stream& copy) = delete;

  void appendRecord(const typename T::ValueType&... values) const {
    Record<T...> record(values...);
    //fnordmetric::serialize::toBytesV(&sample, values...);
    IStream::appendRecord(record);
  }

};

}

#endif