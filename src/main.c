int verhoeff_digit(const char* data, unsigned long length);
int verhoeff_valid(const char* data, unsigned long length);

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

double diff(double start, double end) {
  if ((end - start) < 0) {
    return 1000000000 + end - start;
  } else {
  return end - start;
  }
  return 0;
}


void expectValid(char* a) {
  if (!verhoeff_valid(a, strlen(a))) {
    printf("`%s` expected to be valid\n\n", a);
    exit(EXIT_FAILURE);
  }
}

void expectDigit(char* a, int digit) {
  int d = verhoeff_digit(a, strlen(a));

  if (d != digit) {
    printf("`%s` expected digit %d but got %d instead\n\n", a, digit, d);
    exit(EXIT_FAILURE);
  }
}

int main() {
  // expectations
  expectDigit("", 0);
  expectDigit("75872", 2);
  expectDigit("12345", 1);
  expectDigit("142857", 0);
  expectDigit("123456789012", 0);
  expectDigit("8473643095483728456789", 2);
  expectDigit("ZZZ", -1);

  expectValid("84736430954837284567892");

  // micro benchmark
  int i;
  unsigned int times = 50000000;

  double total_time = 0;
  double clock_cost = 0;

  struct timespec t1;
  struct timespec t2;

  char* string = "00123014764700968325";
  unsigned int l = strlen(string);

  clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
  for (i = 0; i < times; ++i) verhoeff_digit(string, l);
  clock_gettime(CLOCK_MONOTONIC_RAW, &t2);

  printf("%d ps/op\n", (int)(1000*diff(t1.tv_nsec, t2.tv_nsec)/times));

  return 0;
}
