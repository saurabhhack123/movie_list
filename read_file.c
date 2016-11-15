#include "read_file.h"  /* Include the header here, to obtain the function declaration */


int length(struct FILM **head) {
   int length = 0;
    for(struct FILM *current =*head;current != NULL; current = current->next) {
        length++; 
      }
   return length;
}

void printList(struct FILM *curr) {
   printf("\n[ ");
    
   //start from the beginning
   while(curr != NULL) {
      printf("(%d,%s,%d,%s,%s,%d,%f) ",curr->key,curr->name,curr->release,curr->rating,curr->genre,curr->lengthmins,curr->ranking);

      curr = curr->next;
   }
   printf(" ]");
}



//insert link at the first location
void insertFirst(struct FILM **head,int key,char* line) {
   //create a link
   struct FILM *link = (struct FILM*) malloc(sizeof(struct FILM));
   char *token;
   const char s[2] = ",";
   token = strtok(line,s);
   int count = 1;
   int release,lengthmins;
   float ranking;
   link->key=key;
   while( token != NULL) 
   {
      
      if(count==1)
        strcpy(link->name, token); 
      if(count==2)
         {sscanf (token, "%d", &release); link->release = release;}
      if(count==3)
        strcpy(link->rating, token);
      if(count==4)
        strcpy(link->genre, token);
      if(count==5)
        { sscanf (token, "%d", &lengthmins); link->lengthmins = lengthmins;}
      if(count==6)
        { sscanf (token, "%f", &ranking); link->ranking = ranking;}

      token = strtok(NULL,s);
      count=count+1;
   } 
 
   //point it to old first FILM
   link->next = *head;
    
   //point first to new first FILM
   *head = link;
}




void sort(struct FILM* head){

   int i, j, k, tempKey, tempData;
   struct FILM *current;
   struct FILM *next;
   
   int size = length(&head);

   k = size ;
  
   for ( i = 0 ; i < size - 1 ; i++, k-- ) {
      current = head;
      next = current->next;
    
      for ( j = 1 ; j < k ; j++ ) {   
    
         if ( current->release > next->release ) {
            tempData = current->release;
            current->release = next->release;
            next->release = tempData;
            
            tempKey = current->key;
            current->key = next->key;
            next->key = tempKey;
         }
      
         current = current->next;
         next = next->next;
      }
   }

   printf("\n[ ");
   struct FILM *curr=head; 
   //start from the beginning
   while(curr != NULL) {
      printf("(%d,%s,%d,%s,%s,%d,%f) ",curr->key,curr->name,curr->release,curr->rating,curr->genre,curr->lengthmins,curr->ranking);

      curr = curr->next;
   }
   printf(" ]");


}

struct FILM* delete(struct FILM *head,int key) {

   //start from the first link
   struct FILM* current = head;
   struct FILM* previous = NULL;
  
   //if list is empty
   if(head == NULL) {
      return NULL;
   }

   //navigate through list
   while(current->key != key) {

      //if it is last FILM
      if(current->next == NULL) {
         return NULL;
      } else {
         //store reference to current link
         previous = current;
         //move to next link
         current = current->next;
      }
   }

   //found a match, update the link
   if(current == head) {
      //change first to point to next link
      head = head->next;
   } else {
      //bypass the current link
      previous->next = current->next;
   }    
  
   return current;
}



void print_highest_rated_film(struct FILM* head){
   struct FILM *curr = head;
   float ranking_map[300] = {1.00}; // ranking hash_map
   char *name_map[300];

   //start from the beginning
   while(curr != NULL) {
      ranking_map[curr->key] = curr->ranking;
      name_map[curr->key] = curr->name;
      curr = curr->next;
   }
   float HIGH_RANKING = 0.0;
   int HIGH_RANKING_KEY;
  
   // find HIGH_RANKING KEY
   for(int i=1;i<=250;i++){
       if(ranking_map[i]>HIGH_RANKING){
            HIGH_RANKING = ranking_map[i];
            HIGH_RANKING_KEY = i;
       }
   }

   printf("\nHIGHEST RATED MOVIE : %s with ranking %f\n",name_map[HIGH_RANKING_KEY],ranking_map[HIGH_RANKING_KEY]);

}

void print_shortest_title_film(struct FILM* head){

   struct FILM *curr = head;
   int name_map[252];  // declare name map

   //start from the beginning
   while(curr != NULL) {
      name_map[curr->key] = strlen(curr->name);
      curr = curr->next;
   }

   int SHORTEST_LENTH_MOVIE=1000;
   int SHORTEST_LENTH_MOVIE_KEY;
   
   //  find SHORTEST_LENTH_MOVIE key
   for(int i=1;i<=250;i++){
       if(name_map[i]<SHORTEST_LENTH_MOVIE ){
           SHORTEST_LENTH_MOVIE = name_map[i];
            SHORTEST_LENTH_MOVIE_KEY = i;
       }
   }

  struct FILM *curr_t = head;
   
   while(curr_t != NULL) {
      // if found
      if (curr_t->key==SHORTEST_LENTH_MOVIE_KEY) {
          // contains
        printf("SHORTEST_LENTH_MOVIE: %s\n",curr_t->name);
        break;
       }
      curr_t = curr_t->next;
   }
  
}

void print_no_of_films_after_removing_r(struct FILM** head){
    
   struct FILM *curr = *head;
   int size_now = length(head);
   printf("Size before deleting R RATED FILM : %d\n",size_now);
   //start from the beginning
   while(curr != NULL) {
      if(!strcmp(curr->rating,"\"R\""))
          delete(*head,curr->key);
        curr = curr->next;
   }
   size_now = length(head);
   printf("Size after deleting R RATED FILM : %d\n",size_now);
}

void print_tenth_highest_rated_sci_fic(struct FILM* head){

  struct FILM *curr = head;
  struct FILM *sci_fic_head = NULL;
  float ranking;

   //start from the beginning
  while(curr != NULL) {
      //  filter sci_fic movies
      if (strstr(curr->genre, "Sci-Fi") != NULL) {
        struct FILM *link = (struct FILM*) malloc(sizeof(struct FILM));
        link->key = curr->key;
        strcpy(link->name,curr->name);
        link->ranking = curr->ranking;
        link->next = sci_fic_head;
        sci_fic_head = link;
       }
      curr = curr->next;
   }
   
  
   int i, j, k, tempKey, tempData;
   struct FILM *current;
   struct FILM *next;
   
   int length = 0;
   for(struct FILM *current =sci_fic_head;current != NULL; current = current->next) {
        length++; 
   }

   int size = length;
   k = size ;
   //  sort the sci_fic_head list
   for ( i = 0 ; i < size - 1 ; i++, k-- ) {
      current = sci_fic_head;
      next = sci_fic_head->next;
    
      for ( j = 1 ; j < k ; j++ ) {   
    
         if ( current->ranking > next->ranking ) {
            tempData = current->ranking;
            current->ranking = next->ranking;
            next->ranking = tempData;
            
            tempKey = current->key;
            current->key = next->key;
            next->key = tempKey;
         }
      
         current = current->next;
         next = next->next;
      }
   }    
   
  struct FILM *curr_t = sci_fic_head;
  int count=1;
  while(curr_t != NULL) {
      // if found
      if(count==10)
        { printf("\nTenth_highest_rated_sci_fic: %s",curr_t->name); break;}

      curr_t = curr_t->next;
      count=count+1;
   }

}

int thirdLargest(int arr[], int arr_size)
{  
    int key;
    /* There should be atleast three elements */
    int INT_MIN = -999;
    if (arr_size < 3)
    {
        printf(" Invalid Input ");
        return -1;
    }
 
    // Find first largest element
    int first = arr[0];
    for (int i = 1; i < arr_size ; i++)
        if (arr[i] > first)
            first = arr[i];
 
    // Find second largest element
    int second = INT_MIN;
    for (int i = 0; i < arr_size ; i++)
        if (arr[i] > second && arr[i] < first)
            second = arr[i];
 
    // Find third largest element
    int third = INT_MIN;
    for (int i = 0; i < arr_size ; i++)
        if (arr[i] > third && arr[i] < second)
            { third = arr[i]; key = i;}
 
    return key;
}

void print_third_long_film_noir(struct FILM* head) {
   struct FILM *curr = head;
   int duration[252] = {0}; // hash_map

   //start from the beginning
   while(curr != NULL) {
      // apply filter
      if (strstr(curr->genre, "Film-Noir") != NULL) {
          // contains
        duration[curr->key] = curr->lengthmins;
       }
      curr = curr->next;
   }

   int third_larget_key = thirdLargest(duration,250);
   struct FILM *curr_t = head;
   
   while(curr_t != NULL) {
   
      if (curr_t->key==third_larget_key) {
          // contains
        printf("\nThird longest Film-Noir: %s",curr_t->name);
       }
      curr_t = curr_t->next;
   }    
}



int main(void)
{
    struct FILM *head = NULL;
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("films.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    int pos = 1;
    int key = 1;
    while ((read = getline(&line, &len, fp)) != -1) {
        insertFirst(&head,key,line);       
        key=key+1;

    }
    
    fclose(fp);
    if (line)
        free(line);

    printList(head);
    printf("\nSorting\n");
    sort(head);
    print_third_long_film_noir(head);
    print_tenth_highest_rated_sci_fic(head);
    print_highest_rated_film(head);
    print_shortest_title_film(head);
    print_no_of_films_after_removing_r(&head);

    exit(EXIT_SUCCESS);
}