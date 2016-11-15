#ifndef READ_FILE_H_   /* Include guard */
#define READ_FILE_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct FILM {
   int key;
   char name[50];
   int release;
   char rating[50]; // rating
   char genre[50];
   int  lengthmins;
   float ranking; // ranking
   struct FILM *next;
};

int length(struct FILM **head);
void printList(struct FILM *curr);
void insertFirst(struct FILM **head,int key,char* line);

void sort(struct FILM* head);
struct FILM* delete(struct FILM *head,int key);
void print_highest_rated_film(struct FILM* head);
void print_shortest_title_film(struct FILM* head);
void print_no_of_films_after_removing_r(struct FILM** head);
void print_tenth_highest_rated_sci_fic(struct FILM* head);
int thirdLargest(int arr[], int arr_size);
void print_third_long_film_noir(struct FILM* head);


#endif 