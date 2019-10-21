#include "playlist.h"
/* Create a new, empty playlist, storing a pointer to it in the variable
   provided (e.g. listPtr) */
int createPlaylist(Playlist **listPtr) {
  // if (listPtr == NULL)
  //   return INVALID_INPUT_PARAMETER;
  //
  // *listPtr = (Playlist*)myMalloc(sizeof(Playlist));
  //
  // if (*listPtr == NULL)
  //   return MEMORY_ALLOCATION_ERROR
  //
  // (*listPtr)->head = NULL;
  // (*listPtr)->tail = NULL;
  // (*listPtr)->curr = NULL;
  return NOT_IMPLEMENTED;
}

/* Add a new MP3 track into the playlist immediately
   BEFORE the current position in the list */
int insertBeforeCurr(Playlist* listPtr, char trackName[], int trackLength) {
     return NOT_IMPLEMENTED;
}

/* Add a new MP3 track into the playlist immediately
   AFTER the current position in the list */
int insertAfterCurr(Playlist* listPtr, char trackName[], int trackLength) {
     return NOT_IMPLEMENTED;
}

/* Skip to the next track in the playlist, i.e. shift 'curr' one
   position forward in the list */
int skipNext(Playlist* listPtr) {
     return NOT_IMPLEMENTED;
}

/* Skip to the previous track in the playlist, i.e. shift 'curr' one
   position back in the list */
int skipPrev(Playlist* listPtr) {
     return NOT_IMPLEMENTED;
}

/* Get the data for the current track in the playlist */
int getCurrentTrack(Playlist* listPtr, MP3Track *pTrack) {
     return NOT_IMPLEMENTED;
}

/* Remove the MP3 track from the current position in the list. The track data should be copied into
   the variable provided (*pTrack) for confirmation. The variable ‘moveForward’ is used to suggest
   what happens to the ‘curr’ pointer in the list after the track is removed. If ‘moveForward’ is set
   to 1 then the ‘curr’ pointer should be set to point to the next track in the list, immediately
   after the one which has just been removed. Otherwise, ‘curr’ should be set to point to the previous
   track in the list, immediately prior to the one which has just been removed. */
int removeAtCurr(Playlist* listPtr, MP3Track *pTrack, int moveForward) {
     return NOT_IMPLEMENTED;
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
