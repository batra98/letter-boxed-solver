#define _GNU_SOURCE
#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// NOTE: check special cases like blank spaces etc

struct TrieNode {
  struct TrieNode *child[26];
  bool is_end_of_word;
};

struct TrieNode *getNode() {
  struct TrieNode *node = (struct TrieNode *)malloc(sizeof(struct TrieNode));

  node->is_end_of_word = false;

  for (int i = 0; i < 26; i++) {
    node->child[i] = NULL;
  }
  return node;
}

void insert(struct TrieNode *root, char word[]) {
  struct TrieNode *curr = root;
  int n = strlen(word);

  // printf("%s\n", word);

  for (int i = 0; i < n; i++) {
    int idx = word[i] - 'a';
    if (!curr->child[idx]) {
      curr->child[idx] = getNode();
    }
    curr = curr->child[idx];
  }
  curr->is_end_of_word = true;
}

bool search(struct TrieNode *root, char word[]) {
  struct TrieNode *curr = root;

  int n = strlen(word);

  for (int i = 0; i < n; i++) {
    int idx = word[i] - 'a';
    if (!curr->child[idx])
      return false;

    curr = curr->child[idx];
  }
  if (curr != NULL && curr->is_end_of_word == true)
    return true;
  else
    return false;
}

int main(int argc, char *argv[]) {

  /* wrong number of arguments */
  if (argc != 3)
    return 1;

  /* Open the board file */
  // NOTE: will board will always argument 1?
  FILE *fp = fopen(argv[1], "r");

  if (!fp) {
    return 1;
  }

  int position_map[26];
  bool is_char_used[26];

  for (int i = 0; i < 26; i++) {
    position_map[i] = -1;
    is_char_used[i] = false;
  }

  int idx = 0;
  int c;
  while ((c = fgetc(fp)) != EOF) {
    if (c == 10) {
      idx++;
      continue;
    }

    if (c > 122 || c < 97) {
      // NOTE: What to do if invalid char?;
      printf("Invalid board\n");
      return 1;
    }

    if (position_map[c - 'a'] == -1)
      position_map[c - 'a'] = idx;
    else {
      printf("Invalid board\n");
      return 1;
    }
  }

  if (idx < 3) {
    printf("Invalid board\n");
    return 1;
  }
  /*
    for (int i = 0; i < 26; i++) {
      printf("%c %d\n", (char)(i + 'a'), position_map[i]);
    }
    printf("\n");
  */

  FILE *fp2 = fopen(argv[2], "r");
  if (!fp2) {
    return 1;
  }

  char *dict_line = NULL;
  size_t len = 0;
  int nread;

  struct TrieNode *root = getNode();
  while ((nread = getline(&dict_line, &len, fp2)) != -1) {
    dict_line[strcspn(dict_line, "\n")] = 0;
    //  printf("%s %d\n", dict_line, nread);

    insert(root, dict_line);
  }

  char *solution_line = NULL;
  size_t solution_line_len = 0;
  char *prev_solution_line = NULL;

  while ((nread = getline(&solution_line, &solution_line_len, stdin)) != -1) {

    solution_line[strcspn(solution_line, "\n")] = 0;
    int n = strlen(solution_line);
    // printf("%s %d\n", solution_line, n);
    //  check if it's a valid letter, i.e. present on the board
    for (int i = 0; i < n; i++) {
      if (position_map[solution_line[i] - 'a'] == -1) {
        printf("Used a letter not present on the board\n");
        return 0;
      }

      // check if previous letter match
      if (i == 0 && prev_solution_line != NULL) {
        // printf("prev = %s\n", prev_solution_line);
        int m = strlen(prev_solution_line);
        if (prev_solution_line[m - 1] != solution_line[i]) {
          printf("First letter of word does not match last letter of previous "
                 "word\n");
          return 0;
        }
      }

      // check if not used consecutively
      if (i > 0) {
        if (position_map[solution_line[i] - 'a'] ==
            position_map[solution_line[i - 1] - 'a']) {
          printf("Same-side letter used consecutively\n");
          return 0;
        }
      }
    }

    if (search(root, solution_line) == false) {
      printf("Word not found in dictionary\n");
      return 0;
    }

    for (int i = 0; i < n; i++) {
      is_char_used[solution_line[i] - 'a'] = true;
    }
    prev_solution_line = (char *)malloc(n + 1);
    strcpy(prev_solution_line, solution_line);
    // prev_solution_line = solution_line;
  }

  /// check all letters are used.

  for (int i = 0; i < 26; i++) {
    if (position_map[i] == -1)
      continue;

    if (is_char_used[i] == false) {
      printf("Not all letters used\n");
      return 0;
    }
  }

  printf("Correct\n");

  fclose(fp);
  fclose(fp2);

  return 0;
}
