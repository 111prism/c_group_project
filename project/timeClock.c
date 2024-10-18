#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main() {
  time_t now;
  struct tm *currentTime;
  char timeStr[100], start[100], finish[100], checkIn[100], checkOut[100];
  char sHr[2], sMin[2], sSec[2], fHr[2], fMin[2], fSec[2];
  int valueZero = 48;
  int shr, smin, ssec, fhr, fmin, fsec, hr, min, sec;
  float totalWorked;

  while (strcmp(checkIn, "\n") != 0) {
    printf("Hello there are you ready to clock in for today?\nPress enter to clock in.\nIf you want to exit press space then press enter.\n");
    scanf("%c", checkIn);
    if (strcmp(checkIn, " ") == 0) {
      printf("\nOkay have a wonderful day.\n");
      fprintf(stderr, "User pressed space\n");
      exit(EXIT_FAILURE);
    }
  }

  now = time(NULL);
  currentTime = localtime(&now);
  strcpy(timeStr, asctime(currentTime));
  printf("Start time: %s\n", timeStr);
  strcpy(start, timeStr);

  while (strcmp(checkOut, "\n") != 0) {
    printf("Hello again are you done for today?\nPress enter to clock out.\n");
    scanf("%c", checkOut);
  }

  if (strcmp(checkOut, "\n") == 0) {
    now = time(NULL);
    currentTime = localtime(&now);
    strcpy(timeStr, asctime(currentTime));
    printf("Finish time: %s\n", timeStr);
    strcpy(finish, timeStr);
  }

  sHr[0] = start[11];
  sHr[1] = start[12];
  sMin[0] = start[14];
  sMin[1] = start[15];
  sSec[0] = start[17];
  sSec[1] = start[18];

  fHr[0] = finish[11];
  fHr[1] = finish[12];
  fMin[0] = finish[14];
  fMin[1] = finish[15];
  fSec[0] = finish[17];
  fSec[1] = finish[18];

  shr = atoi(sHr);
  smin = atoi(sMin);
  ssec = atoi(sSec);
  fhr = atoi(fHr);
  fmin = atoi(fMin);
  fsec = atoi(fSec);

  hr = fhr - shr;
  min = fmin - smin;
  sec = fsec - ssec;

  //printf("%d %d %d\n", shr, fhr, hr);
  //printf("%d %d %d\n", smin, fmin, min);
  //printf("%d %d %d\n", ssec, fsec, sec);
  //printf("%c %c %c\n", sHr[0], sMin[0], sSec[0]);
  //printf("%c %c %c\n", fHr[0], fMin[0], fSec[0]);
  //printf("%c %c %c\n", sHr[1], sMin[1], sSec[1]);
  //printf("%c %c %c\n", fHr[1], fMin[1], fSec[1])
  printf("%s %s %s\n", sHr, sMin, sSec);
  printf("%s %s %s\n", fHr, fMin, fSec);

  return 0;
}
