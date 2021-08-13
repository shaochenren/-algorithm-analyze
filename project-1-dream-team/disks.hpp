///////////////////////////////////////////////////////////////////////////////
// disks.hpp
//
// Definitions for two algorithms that each solve the alternating disks
// problem.
//
// As provided, this header has four functions marked with TODO comments.
// You need to write in your own implementation of these functions.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <sstream>
#include <string>
#include <vector>

// TODO
#include <functional>
#include <iostream>
using namespace std;
enum disk_color { DISK_DARK, DISK_LIGHT};

class disk_state {
private:
  std::vector<disk_color> _colors;

public:
  disk_state(size_t light_count)
    : _colors(light_count * 2, DISK_DARK) {

    assert(light_count > 0);

    for (size_t i = 1; i < _colors.size(); i += 2) {
      _colors[i] = DISK_LIGHT;
    }
  }

  bool operator== (const disk_state& rhs) const {
    return std::equal(_colors.begin(), _colors.end(), rhs._colors.begin());
  }

  size_t total_count() const {
    return _colors.size();
  }

  size_t light_count() const {
    return total_count() / 2;
  }

  size_t dark_count() const {
    return light_count();
  }

  bool is_index(size_t i) const {
    return (i < total_count());
  }

  disk_color get(size_t index) const {
    assert(is_index(index));
    return _colors[index];
  }

  void swap(size_t left_index) {
    assert(is_index(left_index));
    auto right_index = left_index + 1;
    assert(is_index(right_index));
    std::swap(_colors[left_index], _colors[right_index]);
  }

  std::string to_string() const {
    std::stringstream ss;
    bool first = true;
    for (auto color : _colors) {
      if (!first) {
        ss << " ";
      }

      if (color == DISK_LIGHT) {
        ss << "L";
      } else {
        ss << "D";
      }

      first = false;
    }
    return ss.str();
  }

  // Return true when this disk_state is in alternating format. That means
  // that the first disk at index 0 is dark, the second disk at index 1
  // is light, and so on for the entire row of disks.
  bool is_initialized() const {
    bool a = true;
    for (size_t i = 0; i < total_count(); i += 2) {
      if(_colors[i]== DISK_LIGHT){
        a = false;
      }
    }
    for (size_t i = 1; i < total_count(); i += 2) {
      if(_colors[i]== DISK_DARK){
        a = false;
    }
  }
    return a;/// statement, and then delete these comments.
    // TODO: Write code for this function, including rewriting the return
    // statement, and then delete these comments.

}

  // Return true when this disk_state is fully sorted, with all dark disks
  // on the left (low indices) and all light disks on the right (high
  // indices).
  bool is_sorted() const {
    // declare and initialize the return bool and the halfway point
    bool answer = true;
    int middle = _colors.size()/2;
      // for loop to travers through first half to make sure it's dark
      for (int i = 0; i < middle; i++) {
        // if one light is found, declare false and break loop
        if(_colors[i] == DISK_LIGHT) {
          answer = false;
          break;
        }
      }
      return answer;
    }
  };

// Data structure for the output of the alternating disks problem. That
// includes both the final disk_state, as well as a count of the number
// of swaps performed.
class sorted_disks {
private:
  disk_state _after;
  unsigned _swap_count;

public:

  sorted_disks(const disk_state& after, unsigned swap_count)
    : _after(after), _swap_count(swap_count) { }

  sorted_disks(disk_state&& after, unsigned swap_count)
    : _after(after), _swap_count(swap_count) { }

  const disk_state& after() const {
    return _after;
  }

  unsigned swap_count() const {
    return _swap_count;
  }
};

// Algorithm that sorts disks using the alternate algorithm.
sorted_disks sort_alternate(const disk_state &before) {
  disk_state after = disk_state(before.dark_count());
  unsigned index = 0;

  for (size_t i = 0; i < after.dark_count(); i++) {
    // if i is odd then this if is true
    if (i % 2) {
      for (size_t j = 1; j < after.total_count() - 1; j += 2) {
        // assign current values with new j values
        disk_color swap = after.get(j);
        disk_color swap1 = after.get(j + 1);
        // testing the j value and the one next to compare if dark and light touch
        if (swap == DISK_LIGHT && swap1 == DISK_DARK) {
          // if so than swap and increment
          after.swap(j);
          index++;
        }}}
  // if i is even, i%2 is false and falls into else statement
  else {
      for (size_t i = 0; i < after.total_count(); i += 2) {
        // assign current values with new j values
        disk_color swap = after.get(i);
        disk_color swap1 = after.get(i + 1);
        // testing the j value and the one next to compare if dark and light
        if (swap == DISK_LIGHT && swap1 == DISK_DARK) {
          // if so than swap and increment
          after.swap(i);
          index++;
        }}}
  }
  return sorted_disks(after, index);
}
// Algorithm that sorts disks using the lawnmower algorithm.
sorted_disks sort_lawnmower(const disk_state& before) {
  disk_state after = disk_state(before.dark_count());
  unsigned swaps = 0;

  for (size_t i = 0; i < after.dark_count(); i++) {
    // if i is odd then this if is true
    if (i%2) {
      size_t element = after.total_count()-1;
      // traverse through dark count while decreasing element
      for (size_t j = 0; j < (after.dark_count() - 1); j++) {
        element -= 2;
        // assign current and following with newer values
        disk_color current = after.get(element);
        disk_color following = after.get(element + 1);
        // if a dark and light are next to eachother, swap them
        if (current == DISK_LIGHT && following == DISK_DARK) {
          after.swap(element);
          swaps++;
        }}}
    // if i is even, i%2 is false and falls into else statement
    else {
      // for loop to traverse through array incrementing by 2
      for (size_t i = 0; i < after.total_count(); i += 2) {
        // assign current and following to new i values in array
        disk_color current = after.get(i);
        disk_color following = after.get(i+1);
        // if a dark and light are next to eachother, swap them
        if (current == DISK_LIGHT && following == DISK_DARK) {
          after.swap(i);
          swaps++;
        }}}
  }
return sorted_disks(after, swaps);
}
