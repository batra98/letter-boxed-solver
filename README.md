---
title: CS 537 Project 1
layout: default
---


Name: Gaurav Batra
CS Login: gbatra
Wisc ID: 9087090024
Email: gbatra3@wisc.edu

## Implementation Details

### Board

- keep a track of the char positions (line number indexed 0) in `int: position_map` and whether a char has been used in `bool: is_char_used` arrays which are of size 26 each.
- read the board char by char checking for invalid chars and repetitions.

### Dict

- initialize a trie. 
- Read input line by line using `getline`.
- strip `\n` as the trie node supports storing only a-z.
- insert the word in trie. Worst Case Space Complexity of (O(26*(length of longest word)))

### User input

- read word line by line using `getline`.
- Checks (in order):
  - `Used a letter not on the board` using `position_map`.
  - `First letter of word does not match last letter of previous word`. (done by storing a copy of the previous user input). 
  - `Same-side letter used consecutively` using `position_map`.
  - `Word not found in dictionary` by searching the word in trie.

- mark the chars as seen in `is_char_used`.
- return `Correct` is game completion using `function: did_we_win`.
- store a copy of the current word to check in next iteration.

After all the words have been processed:
Return:
  - `Correct` if `did_we_win` return true;
  - else: `Not all letters used`




### function: did_we_win

```C
bool did_we_win(int *position_map, bool *is_char_used) {
  for (int i = 0; i < 26; i++) {
    if (position_map[i] == -1)
      continue;

    if (is_char_used[i] == false) {
      return false;
    }
  }

  return true;
}




```
```
```
```

```
```
```
