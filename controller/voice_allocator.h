// Copyright 2011 Olivier Gillet.
//
// Author: Olivier Gillet (ol.gillet@gmail.com)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// -----------------------------------------------------------------------------
//
// Polyphonic voice allocator.

#ifndef CONTROLLER_VOICE_ALLOCATOR_H_
#define CONTROLLER_VOICE_ALLOCATOR_H_

#include "avrlib/base.h"

static const uint8_t kMaxPolyphony = 12;

namespace ambika {

class VoiceAllocator {
 public: 
  VoiceAllocator() { }
  void Init() { size_ = 0; Clear(); }
  void set_size(uint8_t size) {
    size_ = size;
  }
  void set_cyclic_mode(bool cyclic_mode) {
    cyclic_allocator_ = cyclic_mode ? 0 : 0xff;
  }
  
  uint8_t NoteOn(uint8_t note);
  uint8_t NoteOff(uint8_t note);
  uint8_t Find(uint8_t note) const;
  void Clear();
  void ClearNotes();
  uint8_t size() const { return size_; }

 private:
  void Touch(uint8_t voice);
   
  uint8_t pool_[kMaxPolyphony];
  // Holds the indices of the voices sorted by most recent usage.
  uint8_t lru_[kMaxPolyphony];
  uint8_t size_;
  uint8_t cyclic_allocator_;

  DISALLOW_COPY_AND_ASSIGN(VoiceAllocator);
};

}  // namespace ambika

#endif  // CONTROLLER_VOICE_ALLOCATOR_H_
