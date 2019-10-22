/*
TODO
*/
#include <stdio.h>
#include <stdlib.h>
#include "playlist.h"
#include <string.h>
/* Create a new, empty playlist, storing a pointer to it in the variable
   provided (e.g. listPtr) */
int createPlaylist(Playlist **listPtr) {
  if (listPtr == NULL)
    return INVALID_INPUT_PARAMETER;

  if (*listPtr != NULL )
    return INVALID_INPUT_PARAMETER;

  *listPtr = (Playlist*)myMalloc(sizeof(Playlist));

  if (*listPtr == NULL)
    return MEMORY_ALLOCATION_ERROR;

  (*listPtr)->head = NULL;
  (*listPtr)->tail = NULL;
  (*listPtr)->curr = NULL;
  return SUCCESS;
}

/* Add a new MP3 track into the playlist immediately
   BEFORE the current position in the list */
int insertBeforeCurr(Playlist* listPtr, char trackName[], int trackLength) {
     return NOT_IMPLEMENTED;
}

/* Add a new MP3 track into the playlist immediately
   AFTER the current position in the list */
int insertAfterCurr(Playlist* listPtr, char trackName[], int trackLength) {
  if (listPtr == NULL )
    return INVALID_INPUT_PARAMETER;
  if ( strlen(trackName) > 49 || strlen(trackName) < 1)
    return INVALID_INPUT_PARAMETER;
if (trackLength <= 0)
    return INVALID_INPUT_PARAMETER;
if (trackLength > 88000) 
     return INVALID_INPUT_PARAMETER;

MP3Track *pTrack = (MP3Track*)myMalloc(sizeof(MP3Track));
if (pTrack == NULL)
      return MEMORY_ALLOCATION_ERROR;

strcpy(pTrack->trackName, trackName);
pTrack->trackLength = trackLength;
pTrack->prev = NULL;
pTrack->next = NULL;

// case list is empty
if (listPtr->curr == NULL){
  listPtr->head = pTrack;
  listPtr->tail = pTrack;
  listPtr->curr = pTrack;
} 
// if curr is at tail
else if (listPtr->curr == listPtr->tail){
pTrack->prev = listPtr->curr;
  listPtr->curr->next = pTrack;
  listPtr->tail = pTrack;
}
// if current is in the middle
else {
     pTrack->prev = listPtr->curr;
     pTrack->next = listPtr->curr->next;
     listPtr->curr->next->prev = pTrack;
     listPtr->curr->next = pTrack;

}
     return SUCCESS;
}

/* Skip to the next track in the playlist, i.e. shift 'curr' one
   position forward in the list */
int skipNext(Playlist* listPtr) {
     if (listPtr == NULL) 
          return INVALID_INPUT_PARAMETER;

     if (listPtr->curr == NULL || listPtr->curr->next == NULL) {
          return INVALID_LIST_OPERATION;
     }
     listPtr->curr = listPtr->curr->next;
     return SUCCESS;
}

/* Skip to the previous track in the playlist, i.e. shift 'curr' one
   position back in the list */
int skipPrev(Playlist* listPtr) {
     return NOT_IMPLEMENTED;
}

/* Get the data for the current track in the playlist */
int getCurrentTrack(Playlist* listPtr, MP3Track *pTrack) {
     if (listPtr == NULL) 
          return INVALID_INPUT_PARAMETER;
     if (listPtr->curr == NULL) 
          return INVALID_LIST_OPERATION;

     pTrack->trackLength = listPtr->curr->trackLength;
     pTrack->next = listPtr->curr->next;
     pTrack->prev = listPtr->curr->prev;
     strcpy(pTrack->trackName, listPtr->curr->trackName);

     return SUCCESS;
}

/* Remove the MP3 track from the current position in the list. The track data should be copied into
   the variable provided (*pTrack) for confirmation. The variable ‘moveForward’ is used to suggest
   what happens to the ‘curr’ pointer in the list after the track is removed. If ‘moveForward’ is set
   to 1 then the ‘curr’ pointer should be set to point to the next track in the list, immediately
   after the one which has just been removed. Otherwise, ‘curr’ should be set to point to the previous
   track in the list, immediately prior to the one which has just been removed. */
int removeAtCurr(Playlist* listPtr, MP3Track *pTrack, int moveForward) {
     if (listPtr == NULL )
          return INVALID_INPUT_PARAMETER;
     if (listPtr->curr == NULL)
          return INVALID_LIST_OPERATION;
     if (moveForward != 1 && moveForward != 0)
          return INVALID_INPUT_PARAMETER; // TODO what does the tester expect?

     // copy curr to pTrack
      pTrack->trackLength = listPtr->curr->trackLength;
     pTrack->next = listPtr->curr->next;
     pTrack->prev = listPtr->curr->prev;
     strcpy(pTrack->trackName, listPtr->curr->trackName);
     MP3Track *to_remove = listPtr->curr;

     // if there is only one element left in the queue
     if (listPtr->head == listPtr->tail) {
          
          listPtr->curr = NULL;
          listPtr->head = NULL;
          listPtr->tail = NULL;
          return SUCCESS;
     }
     printf("\n%s\n%s\n", listPtr->head->trackName, listPtr->tail->trackName);

     // remove node
     // point to next track after removal
     if (moveForward == 1) {
         
          
          // if current is same as head
          if (listPtr->curr == listPtr->head) {
               
               listPtr->head = listPtr->curr->next;
               listPtr->head->prev = NULL;
               listPtr->curr = listPtr->head;
               free(to_remove);

               return SUCCESS;
          } 
           // if curr is same as tail
          else if (listPtr->curr == listPtr->tail) {
               // TODO ask wheather error code or move backwards (cause it's the last element, and it can't move forwards)
               // move backwards for now
               listPtr->tail = listPtr->curr->prev;
               listPtr->tail->next = NULL;
               free(listPtr->curr);
               listPtr->curr = listPtr->tail;
               return SUCCESS;
          } 
          // is curr is in the middle of the list
          else {
               listPtr->curr->prev->next = listPtr->curr->next;
               listPtr->curr->next->prev = listPtr->curr->prev;
               listPtr->curr = listPtr->curr->next;
               free(to_remove);
               return SUCCESS;
          }
     } 
     // point to prev track after removal
     else {
          // if current is same as head
          if (listPtr->curr == listPtr->head) {
               // TODO ask wheather error code or move backwards (cause it's the last element, and it can't move forwards)
               // move forwards for now
               
               listPtr->head = listPtr->curr->next;
               listPtr->head->prev = NULL;
               listPtr->curr = listPtr->head;
               free(to_remove);

               return SUCCESS;
          } 
           // if curr is same as tail
          else if (listPtr->curr == listPtr->tail) {
               // TODO ask wheather error code or move backwards (cause it's the last element, and it can't move forwards)
               // move backwards for now
               listPtr->tail = listPtr->curr->prev;
               listPtr->tail->next = NULL;
               free(listPtr->curr);
               listPtr->curr = listPtr->tail;
               return SUCCESS;
          } 
          // is curr is in the middle of the list
          else {
               listPtr->curr->prev->next = listPtr->curr->next;
               listPtr->curr->next->prev = listPtr->curr->prev;
               listPtr->curr = listPtr->curr->prev; // TODO only line that differs from moveForward = 1
               free(to_remove);
               return SUCCESS;
          }
     }
}

/* Empty the entire contents of the playlist, freeing up any memory that it currently uses */
int clearPlaylist(Playlist* listPtr) {
     return NOT_IMPLEMENTED;
}

/* save details of all of the tracks in the playlist into the given file */
int savePlaylist(Playlist *listPtr, char filename[]) {
     return NOT_IMPLEMENTED;
}

/* This function is similar to 'createPlaylist'. It should create a new, empty playlist BUT
   then also load the details of a playlist from the given file (a list of track names and
   track lengths) {
     return NOT_IMPLEMENTED;
} insert these as new MP3 tracks into your playlist, and store a pointer to
   the newly created playlist into the variable provided (e.g. listPtr)  */
int loadPlaylist(Playlist **listPtr, char filename[]) {
     return NOT_IMPLEMENTED;
}

int printList(Playlist *listPtr) {
     if (listPtr == NULL) 
          return INVALID_INPUT_PARAMETER;
     if (listPtr->head == NULL) 
          return INVALID_LIST_OPERATION;

     MP3Track *temp = (MP3Track*)myMalloc(sizeof(MP3Track));
     temp = listPtr->head;
     char isHead;
     char isTail;

     while (temp!= NULL) {
          if (temp == listPtr->head) { isHead = '*';}
          else {isHead = '\0';}
          if (temp == listPtr->tail) { isTail = '$';}
          else { isTail = '\0';}

          // ((temp == listPtr->head) ? isHead = '*' : isHead = '\O');

          if (temp == listPtr->curr) {
          printf("%c( %s, %d )%c ", isHead, temp->trackName, temp->trackLength, isTail);
          } else {
          printf("%c[ %s, %d ]%c ", isHead, temp->trackName, temp->trackLength, isTail);
          }
          temp = temp->next;
     }
     printf("\n");
     return 0;
}