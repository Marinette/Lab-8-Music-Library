//
// APS105-F15 Lab 8 Lab8.c
//
// This is a program written to maintain a personal music library, 
// using a linked list to hold the songs in the library.
//
// Author: <Your Name Goes Here>
// Student Number: <Your Student Number Goes Here>
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

// A node in the linked list

// Each string in the node is declared as a character pointer variable,
// so they need to be dynamically allocated using the malloc() function,
// and deallocated using the free() function after use.

typedef struct node
{
    char *songName;
    char *artist;
    char *genre;
    struct node *link;
} Node;

typedef Node node;

// Declarations of linked list functions
//
// Declare your own linked list functions here.
//
node *newNode(char songName[], char artist[], char genre[], node *link) {
  node *new;

  new = (node *) malloc(sizeof(node));  
  // returns NULL if no memory

  if (new != NULL) {

      new -> songName = (char*)malloc(sizeof(char)*strlen(songName));
      new -> songName = songName;
      
      new -> artist = (char*)malloc(sizeof(char)*strlen(artist));
      new -> artist = artist;
      
      new -> genre = (char*)malloc(sizeof(char)*strlen(genre));
      new -> genre = genre;

  }

  return new;
}

// Searching through the linked list for a particular value
// returns false if not found
bool searchSongNames(node *head, char searchKey[], node *nodeOfFoundName) {
  nodeOfFoundName = NULL;  
  node *current = head;
  bool songNameFound = false;

  while (current != NULL && songNameFound == false) {
      
    if (current -> songName == searchKey) {
        songNameFound = true;
        nodeOfFoundName = current;
        return(songNameFound);
    }

    else current = current->link;
  }
  // if above loop found searchKey, current will point to it; otherwise

  return (songNameFound);
}

// Inserting the new node into the existing library
node *insertNodeInOrder(node *head, char inputSongName[],
        char inputArtist[], char inputGenre[]) {
    
   if (head == NULL || strcmp(inputSongName,head -> songName)<0)
     // if head is null then list is empty, thus new node is the beginning
       //of the list
     return newNode(inputSongName, inputArtist, inputGenre, head); 

   node *current = head;

   while (current -> link != NULL &&
           strcmp(inputSongName,current -> link -> songName)>0)
     current = current -> link;

   node *oldCurrent = current;
   current -> link = 
           newNode(inputSongName, inputArtist, inputGenre, current -> link);
   current -> link -> link = oldCurrent -> link;
   return head;
}


//printing all of the music saved

void printList(node *head) {
  node *current = head;

  while (current != NULL) {
    printf("%s\n", current -> songName);
    current = current -> link;
  }
}

// Declarations of support functions
// See below the main function for descriptions of what these functions do

void getStringFromUserInput(char s[], int arraySize);
void songNameDuplicate(char songName[]);
void songNameFound(char songName[]);
void songNameNotFound(char songName[]);
void songNameDeleted(char songName[]);
void artistFound(char artist[]);
void artistNotFound(char artist[]);
void printMusicLibraryEmpty(void);
void printMusicLibraryTitle(void);

const int MAX_LENGTH = 1024;

int main(void) {
    // Declare the head of the linked list.

    Node *head = NULL;
    
    // Announce the start of the program
    printf("%s", "Personal Music Library.\n\n");
    printf("%s", "Commands are I (insert), D (delete), S (search by song name),\n"
         "P (print), Q (quit).\n");
    
    char response;
    char input[MAX_LENGTH + 1];
    char inputArtist[MAX_LENGTH+1];
    char inputGenre[MAX_LENGTH +1 ];
    
    do {
        printf("\nCommand?: ");
        getStringFromUserInput(input, MAX_LENGTH);

        // Response is the first character entered by user.
        // Convert to uppercase to simplify later comparisons.
        response = toupper(input[0]);

        if (response == 'I') {
            // Insert a song into the linked list.
            // Maintain the list in alphabetical order by song name.

             printf("Song name: ");
             getStringFromUserInput(input, MAX_LENGTH);
             
             printf("Artist: ");
             getStringFromUserInput(inputArtist, MAX_LENGTH);
             
             printf("Genre: ");
             getStringFromUserInput(inputGenre, MAX_LENGTH);            

             //search through list to find any possible nodes with the song name
             //if not found, returns false
             
             node *addressOfSameNameNode;
             bool songNameFound = searchSongNames(head, input,
                     addressOfSameNameNode);

            if (songNameFound == true) {
                songNameDuplicate(input);
            }
             
             //song name not already in library
             else if (songNameFound == false) {
                 
                 //create a new node in alphabetical order
                 head = insertNodeInOrder(head, input, 
                         inputArtist, inputGenre);                 
                 
             }
             
        }
        
        
        else if (response == 'D') {
            // Delete a song from the list.

            printf("\nEnter the name of the song to be deleted: ");

            //   ADD STATEMENT(S) HERE

        }
        else if (response == 'S') {
            // Search for a song by its name.

            printf("\nEnter the name of the song to search for: ");
            getStringFromUserInput(input, MAX_LENGTH);
            node *addressOfSameNameNode;
            bool sameSongFound = searchSongNames(head, input, 
                    addressOfSameNameNode);
            
            if (sameSongFound == true) {
                
                songNameFound(input);
                printf("%s\n%s\n%s\n", addressOfSameNameNode->songName,
                        addressOfSameNameNode ->artist, 
                        addressOfSameNameNode ->genre);
            }
            

        }
        else if (response == 'P') {
            // Print the music library.

            printList(head);

        }
        else if (response == 'Q') {
            ; // do nothing, we'll catch this below
        }
        else {
            // do this if no command matched ...
            printf("\nInvalid command.\n");
        }
    } while (response != 'Q');
  
    // Delete the entire linked list.
    //   ADD STATEMENT(S) HERE

    // Print the linked list to confirm deletion.
    //   ADD STATEMENT(S) HERE

    return 0;
}

// Support Function Definitions

// Prompt the user for a string safely, without buffer overflow
void getStringFromUserInput(char s[], int maxStrLength) {
    int i = 0;
    char c;

    while (i < maxStrLength && (c = getchar()) != '\n')
      s[i++] = c;

    s[i] = '\0';
}

// Function to call when the user is trying to insert a song name 
// that is already in the personal music library.
void songNameDuplicate(char songName[])
{
    printf("\nA song with the name '%s' is already in the music library.\n"
           "No new song entered.\n", songName);
}

// Function to call when a song name was found in the personal music library.
void songNameFound(char songName[])
{
    printf("\nThe song name '%s' was found in the music library.\n",
           songName);
}

// Function to call when a song name was not found in the personal music library.
void songNameNotFound(char songName[])
{
    printf("\nThe song name '%s' was not found in the music library.\n",
           songName);
}

// Function to call when a song name that is to be deleted
// was found in the personal music library.
void songNameDeleted(char songName[])
{
    printf("\nDeleting a song with name '%s' from the music library.\n",
           songName);
}

// Function to call when printing an empty music library.
void printMusicLibraryEmpty(void)
{
    printf("\nThe music library is empty.\n");
}

// Function to call to print a title when the entire music library is printed.
void printMusicLibraryTitle(void)
{
    printf("\nMy Personal Music Library: \n");
}

// Add your functions below this line.

//   ADD STATEMENT(S) HERE