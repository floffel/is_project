#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
//#include <string.h>

int transitions; // transitions between char -> char, f.e. tom: t->0,o->m = 2 transitions
double occurences[26][26];

void fill_occurences(char* file) {
  FILE* fp;
  char* line=NULL;
  size_t len=0;
  ssize_t read;
  
  transitions=0;

  // initial filling
  for(int i=0; i<26; i++)
    for(int j=0; j<26; j++)
      occurences[i][j] = 0;

  fp = fopen(file, "r");

  while((read = getline(&line, &len, fp)) != -1) {
    int last = -1;

    for(int i=0; i < read-2; i++) {
      int cur = (int)(tolower(line[i])) - 97;
      if(last >= 0 && last < 26 && // only lowercase char in last 
          cur >= 0 && cur < 26) { // only lowercase char in cur
        occurences[last][cur]++;
        transitions++;
      }
      else
        last = ((int)tolower(line[i])) - 97; 
    }

  }

  fclose(fp);
  if(line)
    free(line);
}

void calculate_percentage() {
  for(int i=0; i<26; i++)
    for(int j=0; j<26; j++)
      occurences[i][j] /= (double)transitions;
}

void print_table() {
  // headline
  printf(" ");
  for(int i=0; i<26; i++)
    printf(" %3c ", (char)(97+i));
  printf("\n");

  // contents
  for(int i=0; i<26; i++) {
    printf("%c", (97+i));
    for(int j=0; j<26; j++) {
      printf(" %3g ", occurences[i][j]);
    }
    printf("\n");
  }
}

int main(void) {
  fill_occurences("names.txt");

  printf("****Raw:****\n");
  print_table();

  printf("***Percentages:****\n");
  calculate_percentage();
  print_table();

  exit(EXIT_SUCCESS);
}
