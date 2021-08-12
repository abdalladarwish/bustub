//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// clock_replacer.cpp
//
// Identification: src/buffer/clock_replacer.cpp
//
// Copyright (c) 2015-2019, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "buffer/clock_replacer.h"
namespace bustub {

ClockReplacer::ClockReplacer(size_t num_pages)
    : num_pages{num_pages},
      frame_exist{std::vector<bool>(num_pages, false)},
      refs{std::vector<bool>(num_pages, false)},
      frame_pinned{std::vector<bool>(num_pages, false)} {}

ClockReplacer::~ClockReplacer() = default;

bool ClockReplacer::Victim(frame_id_t *frame_id) {
  auto temp_current_hand_position = current_hand_position;
  if (VictimInternal(frame_id, num_pages)) {
    return true;
  }
  current_hand_position = 0;
  return VictimInternal(frame_id, temp_current_hand_position);
}

bool ClockReplacer::VictimInternal(frame_id_t *frame_id, size_t upperBound) {
  while (current_hand_position < upperBound) {
    if (frame_exist[current_hand_position]) {
      if (refs[current_hand_position]) {
        refs[current_hand_position] = false;
        current_hand_position++;
      } else {
        *frame_id = static_cast<frame_id_t>(current_hand_position);
        frame_exist[current_hand_position] = false;
        frames_count--;
        current_hand_position++;
        return true;
      }
    } else {
      current_hand_position++;
    }
  }
  *frame_id = INVALID_FRAME_ID;
  return false;
}

void ClockReplacer::Pin(frame_id_t frame_id) {
  if (frame_id > -1 && frame_id < static_cast<frame_id_t>(num_pages)) {
    if (frame_exist[frame_id]) {
      frame_pinned[frame_id] = true;
      frame_exist[frame_id] = false;
      frames_count--;
    }
  }
}

void ClockReplacer::Unpin(frame_id_t frame_id) {
  if (frame_id > -1 && frame_id < static_cast<frame_id_t>(num_pages)) {
    if (!frame_exist[frame_id]) {
      frame_exist[frame_id] = true;
      frames_count++;
    }
    if (frame_pinned[frame_id]) {
      frame_pinned[frame_id] = false;
      refs[frame_id] = true;
    }else{
      refs[frame_id] = false;
    }
  }
}

size_t ClockReplacer::Size() { return frames_count; }
}  // namespace bustub
