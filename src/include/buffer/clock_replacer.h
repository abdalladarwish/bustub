//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// clock_replacer.h
//
// Identification: src/include/buffer/clock_replacer.h
//
// Copyright (c) 2015-2019, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#pragma once

#include <storage/disk/disk_manager.h>
#include <list>
#include <mutex>  // NOLINT
#include <vector>

#include "buffer/replacer.h"
#include "common/config.h"
#define INVALID_FRAME_ID -1
namespace bustub {

/**
 * ClockReplacer implements the clock replacement policy, which approximates the Least Recently Used policy.
 */
class ClockReplacer : public Replacer {
 public:
  /**
   * Create a new ClockReplacer.
   * @param num_pages the maximum number of pages the ClockReplacer will be required to store
   */
  explicit ClockReplacer(size_t num_pages);

  /**
   * Destroys the ClockReplacer.
   */
  ~ClockReplacer() override;

  bool Victim(frame_id_t *frame_id) override;

  void Pin(frame_id_t frame_id) override;

  void Unpin(frame_id_t frame_id) override;

  size_t Size() override;

 private:
  // TODO(student): implement me!
  size_t num_pages;
  std::vector<bool> frame_exist;
  std::vector<ref_t> refs;
  std::vector<bool> pins;
  size_t current_hand_position = 0;
  size_t frames_count = 0;
  bool VictimInternal(frame_id_t *frame_id, size_t upperBound);
};

}  // namespace bustub
