const int mult[10][10] = {{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, {1, 2, 3, 4, 0, 6, 7, 8, 9, 5}, {2, 3, 4, 0, 1, 7, 8, 9, 5, 6}, {3, 4, 0, 1, 2, 8, 9, 5, 6, 7}, {4, 0, 1, 2, 3, 9, 5, 6, 7, 8}, {5, 9, 8, 7, 6, 0, 4, 3, 2, 1}, {6, 5, 9, 8, 7, 1, 0, 4, 3, 2}, {7, 6, 5, 9, 8, 2, 1, 0, 4, 3}, {8, 7, 6, 5, 9, 3, 2, 1, 0, 4}, {9, 8, 7, 6, 5, 4, 3, 2, 1, 0}};
const int perm[10][10] = {{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, {1, 5, 7, 6, 2, 8, 3, 0, 9, 4}, {5, 8, 0, 3, 7, 9, 6, 1, 4, 2}, {8, 9, 1, 6, 0, 4, 3, 5, 2, 7}, {9, 4, 5, 3, 1, 2, 6, 8, 7, 0}, {4, 2, 8, 6, 5, 7, 3, 9, 0, 1}, {2, 7, 9, 3, 8, 0, 6, 4, 1, 5}, {7, 0, 4, 6, 9, 1, 3, 2, 5, 8}};
const int inv[10] = {0, 4, 3, 2, 1, 5, 6, 7, 8, 9};

int verhoeff_digit(const char* data, unsigned long length) {
  if (*data == '\0') return 0;

  int d = 0;
  int i = 0;
  int x = 0;

  data += length-1;

  do {
    d = *data-- - 48;
    if (d > 9) return -1;
    x = mult[x][perm[++i%8][d]];
  } while(*data);

  return inv[x];
}

int verhoeff_valid(const char* data, unsigned long length) {
  if (*data == '\0') return 0;

  int d = 0;
  int i = 0;
  int x = 0;

  data += length-1;

  do {
    d = *data-- - 48;
    if (d > 9) return -1;
    x = mult[x][perm[i++%8][d]];
  } while(*data);

  return x == 0;
}
