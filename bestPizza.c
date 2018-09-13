#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CHAR 64
#define PI 3.14159265358979323846

struct pizza{
  char pizzaName[MAX_CHAR];
  float pizzaSize;
  float pizzaPrice;
  float pizzaPerDollar;
  struct pizza* next; // we're gonna use linked lists since that is able to change the size of our list; arrays can't
};

void addPizza(struct pizza** pHead, struct pizza* pInsert){
  struct pizza* current;
  int nameComp;

  if ((*pHead)->next == NULL){ // OUTERMOST IF STATEMENT: CHECKS TO SEE IF THERE'S ONLY ONE NODE SO FAR
  nameComp = strcmp((*pHead)->pizzaName, pInsert->pizzaName); // initializes nameComp to make it cleaner
  if (((*pHead)->pizzaPerDollar < pInsert->pizzaPerDollar) || // we put the node we want to insert in front if the head's pizzaPerDollar is les
  ((*pHead)->pizzaPerDollar == pInsert->pizzaPerDollar) && nameComp > 0){  // or if they have the same cost, we put the first alphabetically in front
    pInsert->next = *pHead; // we set the current head as the thing after what we just inserted
    *pHead = pInsert; // and then we make the thing we just inserted as the new head
  }
  else {
    (*pHead)->next = pInsert; // otherwise, we just insert it after the current lone head
  }
}
else{ // this else statement is for when the list has more than one node
  current = *pHead; // this is a temp node we use so we can traverse through the list
  if ((current->pizzaPerDollar < pInsert->pizzaPerDollar) || (current->pizzaPerDollar == pInsert->pizzaPerDollar && strcmp(current->pizzaName,pInsert->pizzaName) > 0)){
    pInsert->next = *pHead;
    *pHead = pInsert;
  }
  else{
    while ((current->next != NULL && current->next->pizzaPerDollar > pInsert->pizzaPerDollar) || // we keep traversing if current node's pizzaPerDollar is more than what we want to insert
    (current->next != NULL && current->next->pizzaPerDollar == pInsert->pizzaPerDollar &&
      strcmp(current->next->pizzaName, pInsert->pizzaName) < 0)){ // or if they have the same pizzaPerDollar, but the thing we want to insert is later alphabetically
        current = current->next;
      } // once we exited the while loop we are where we want to inser the new node
      pInsert->next = current->next; // we connect the nodes
      current->next = pInsert;
    }
  }
}

int main(int argc, char* argv[]) {
  FILE *fr; /// declaring the file we want to open
  char line[MAX_CHAR]; // pizza names are 64 characters or less, and numbers can't be that long so it makes sense to set this as how long a line would be
  float pSize;
  float pPrice;
  struct pizza* head = (struct pizza*) malloc(sizeof(struct pizza));;
  struct pizza* newPizza;
  struct pizza* temp;
  struct pizza* inserted;

  for (int i = 1; i < argc; i++){ // takes into account if multiple files in command line
    fr = fopen(argv[i], "r"); // opens the pizza file

    // EXIT CASE: IF THE FILE DOESN'T EXIST, DON'T EVEN BOTHER
    if (fr == NULL){ // in the case that pizzainfo.txt not in directory
      printf("pizzainfo.txt can't be found in the directory!\n");
      exit(EXIT_FAILURE);
    }

    // EXIT CASE: IF THE FILE IS EMPTY, THEN JUST REPORT IT'S EMPTY
    if (fscanf(fr, "%s", &line) == EOF) { // checks to see if empty file
      printf("PIZZA FILE IS EMPTY\n");
      free(head);
      return EXIT_SUCCESS;
    }

    // WE WANT TO ASSIGN VALUES TO HEAD FIRST BEFORE WE CHECK IF THERE ARE OTHER PIZZAS
    strcpy(head->pizzaName,line);
    fscanf(fr, "%f", &pSize);
    head->pizzaSize = pSize;
    fscanf(fr, "%f", &pPrice);
    head->pizzaPrice = pPrice;

    if (pPrice == 0) head->pizzaPerDollar = 0;
    else head->pizzaPerDollar = ((PI/4)*(pSize)*(pSize)) / pPrice;
    head->next = NULL;
    fscanf(fr, "%s", line);

    // WE NOW ITERATE THROUGH THE OTHER PIZZAS IN THE FILE
    while (strcmp(line,"DONE") != 0){
      newPizza = (struct pizza*) malloc(sizeof(struct pizza)); // THIS IS WHERE ITS MESSING UP
      strcpy(newPizza->pizzaName, line);
      fscanf(fr, "%f", &pSize);
      newPizza->pizzaSize = pSize;
      fscanf(fr, "%f", &pPrice);
      newPizza->pizzaPrice = pPrice;

      if (pPrice == 0) newPizza->pizzaPerDollar = 0;
      else newPizza->pizzaPerDollar = ((PI/4)*(pSize)*(pSize)) / pPrice;
      newPizza->next = NULL;
      addPizza(&head, newPizza);
      fscanf(fr, "%s", line);
    }

    // WE NOW PRINT IT OUT AS EXPECTED
    while(head != NULL){
      printf("%s %f\n", head->pizzaName, head->pizzaPerDollar);
      temp = head;
      head = head->next;
      free(temp); // we clear each pizza we allocated memory for earlier
    }
    
    fclose(fr);
  }
  return EXIT_SUCCESS;
}
