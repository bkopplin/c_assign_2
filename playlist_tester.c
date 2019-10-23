#include <stdio.h>
#include <stdlib.h>
#include "playlist.h"
#include <string.h>

/* A function (and global) that can trigger malloc fails on demand. */
int mallocFail = 0;
void* myMalloc(size_t size) {
	if (mallocFail) { return NULL; }
	else { return malloc(size); }
}

int passTest(char testName[]) {
	printf("passed test: %s\n", testName);
	return 0;
}

int failTest(char testName[]) {
	printf("failed test: %s\n", testName);
	return 0;
}

int checkTest(int result, int expected_error_code, char testName[]) {
	(result == expected_error_code ? passTest(testName) : failTest(testName));
	return 0;
}

/*
checks wheather a MP3Track object has certain fields
*/
int compare_track(MP3Track* track, char trackName[], int trackLength) {
	if (track == NULL)
		return INVALID_INPUT_PARAMETER;

	if (strcmp(track->trackName, trackName) != 0)
		return 1;

	if (track->trackLength != trackLength)
		return 1;

	return 0;
}

int test_init() {
	char testname [255];
	Playlist *p;
	int result = 0;

	strcpy(testname, "initialise non-null pointer");
	result = createPlaylist(&p);
	checkTest(result, INVALID_INPUT_PARAMETER, testname);

	strcpy(testname, "initialise null pointer");
	p = NULL;
	result = createPlaylist(&p);
	checkTest(result, SUCCESS, testname);

	strcpy(testname, "handle memory failure");
	p = NULL;
	mallocFail = 1;
	result = createPlaylist(&p);
	mallocFail = 0;
	checkTest(result, MEMORY_ALLOCATION_ERROR, testname);

	return 0;
}

int test_add_after_iterator() {
	char testname [255];
	Playlist *p = NULL;
	int result = 0;
	createPlaylist(&p);

	printf("\n---TEST INSERT AFTER CURR---\n");

	strcpy(testname, "add to beginning of list");
	result = insertAfterCurr(p, "Wake me up", 3.41);
	// printList(p);
	checkTest(result, SUCCESS, testname);

	strcpy(testname, "add to end of list");
	result = insertAfterCurr(p, "You make me", 3.12);
	// printList(p);
	checkTest(result, SUCCESS, testname);

	strcpy(testname, "add to middle of list");
	result = insertAfterCurr(p, "Hey Brother", 4.48);
	// printList(p);
	checkTest(result, SUCCESS, testname);

	strcpy(testname, "initialise node with a too big string");
	result = insertAfterCurr(p, "This is a string that is more than 49 characters long and will therefore fail to be stored inside the list node", 4.48);
	// printList(p);
	checkTest(result, INVALID_INPUT_PARAMETER, testname);

	strcpy(testname, "initialise node with an empty string");
	result = insertAfterCurr(p, "", 4.48);
	// printList(p);
	checkTest(result, INVALID_INPUT_PARAMETER, testname);

	strcpy(testname, "track length check (should be > 0)");
	result = insertAfterCurr(p, "Hey Brother", 0);
	// printList(p);
	checkTest(result, INVALID_INPUT_PARAMETER, testname);

	strcpy(testname, "check if pointer to list provided is valid");
	p = NULL;
	result = insertAfterCurr(p, "Hey Brother", 3.21);
	// printList(p);
	checkTest(result, INVALID_INPUT_PARAMETER, testname);

	return 0;
}

int test_add_before_iterator() {
	char testname [255];
	Playlist *p = NULL;
	int result = 0;
	createPlaylist(&p);

	printf("\n---TEST INSERT BEFORE CURR---\n");

	strcpy(testname, "add to empty list");
	result = insertBeforeCurr(p, "Wake me up", 3.41);
	printList(p);
	checkTest(result, SUCCESS, testname);

	strcpy(testname, "add to beginning of list");
	result = insertBeforeCurr(p, "You make me", 3.12);
	printList(p);
	checkTest(result, SUCCESS, testname);

	strcpy(testname, "add to middle of list");
	result = insertBeforeCurr(p, "Hey Brother", 4.48);
	printList(p);
	checkTest(result, SUCCESS, testname);

	strcpy(testname, "initialise node with a too big string");
	result = insertBeforeCurr(p, "This is a string that is more than 49 characters long and will therefore fail to be stored inside the list node", 4.48);
	printList(p);
	checkTest(result, INVALID_INPUT_PARAMETER, testname);

	strcpy(testname, "initialise node with an empty string");
	result = insertBeforeCurr(p, "", 4.48);
	printList(p);
	checkTest(result, INVALID_INPUT_PARAMETER, testname);

	strcpy(testname, "track length check (should be <= 88000");
	result = insertBeforeCurr(p, "Hey Brother", 88001);
	printList(p);
	checkTest(result, INVALID_INPUT_PARAMETER, testname);

	strcpy(testname, "track length check (should be > 0)");
	result = insertBeforeCurr(p, "Hey Brother", 0);
	printList(p);
	checkTest(result, INVALID_INPUT_PARAMETER, testname);

	strcpy(testname, "check if pointer to list provided is valid");
	p = NULL;
	result = insertBeforeCurr(p, "Hey Brother", 3.21);
	printList(p);
	checkTest(result, INVALID_INPUT_PARAMETER, testname);

	return 0;
}

int test_skip_next() {
	char testname [255];
	Playlist *p = NULL;
	int result = 0;

	printf("\n---TEST SKIP NEXT---\n");

	strcpy(testname, "check if pointer to list provided is valid");
	p = NULL;
	result = skipNext(p);
	printList(p);
	checkTest(result, INVALID_INPUT_PARAMETER, testname);

	strcpy(testname, "move iterator by one");
	createPlaylist(&p);
	insertAfterCurr(p, "Hey Brother", 4.34);
	insertAfterCurr(p, "Addicted to you", 3.22);
	result = skipNext(p);
	printList(p);
	checkTest(result, SUCCESS, testname);

	strcpy(testname, "skip next when iterator is at the last element");
	result = skipNext(p);
	printList(p);
	checkTest(result, INVALID_LIST_OPERATION, testname);

	return 0;
}

int test_skip_prev() {
	char testname [255];
	Playlist *p = NULL;
	int result = 0;

	printf("\n---TEST SKIP PREV---\n");

	strcpy(testname, "check if pointer to list provided is valid");
	p = NULL;
	result = skipNext(p);
	printList(p);
	checkTest(result, INVALID_INPUT_PARAMETER, testname);

	// init list
	createPlaylist(&p);

	strcpy(testname, "skip next when there are no elements in the list");
	result = skipNext(p);
	printList(p);
	checkTest(result, INVALID_LIST_OPERATION, testname);

	insertAfterCurr(p, "Hey Brother", 4.34);
	strcpy(testname, "skip next when iterator is at the first element");
	result = skipNext(p);
	printList(p);
	checkTest(result, INVALID_LIST_OPERATION, testname);

	strcpy(testname, "move iterator by one");
	insertAfterCurr(p, "Addicted to you", 3.22);
	skipNext(p);
	printList(p);
	result = skipPrev(p);
	printList(p);
	checkTest(result, SUCCESS, testname);

	return 0;
}

int test_get_curr() {
	char testname [255];
	Playlist *p = NULL;
	int result = 0;
	createPlaylist(&p);
	MP3Track myTrack;
printf("\n---TEST get current---\n");

	strcpy(testname, "get current track from empty playlist");
	result = getCurrentTrack(p, &myTrack);
	checkTest(result, INVALID_LIST_OPERATION, testname);

	// create list nodes
	insertAfterCurr(p, "Hey Brother", 123);
	insertAfterCurr(p, "Addicted to you", 456);
	insertAfterCurr(p, "Shame on me", 789);
	skipNext(p);

	strcpy(testname, "get current track");
	result = getCurrentTrack(p, &myTrack);
	printf("[%s, %d]\nnext: %s, prev: %s\n", myTrack.trackName, myTrack.trackLength, myTrack.next->trackName, myTrack.prev->trackName);
	printList(p);
	checkTest(result, SUCCESS, testname);


	return 0;
}

int test_remove() {
	char testname [255];
	Playlist *p = NULL;
	int result = 0;
	createPlaylist(&p);
	MP3Track myTrack;

	printf("\n---TEST REMOVE and SKIP FORWARDS---\n");

	// add nodes
	insertAfterCurr(p, "Hey Brother", 123);
	insertAfterCurr(p, "Addicted to you", 456);
	insertAfterCurr(p, "Touch me", 32432);
	char t_name [] = "Shame on me";
	int t_length = 3244;
	insertAfterCurr(p, t_name, t_length);
	printList(p);

	strcpy(testname, "remove from head");
	result = removeAtCurr(p, &myTrack, 1);
	printList(p);
	checkTest(result, SUCCESS, testname);

	strcpy(testname, "remove from middle");
	skipNext(p);
	result = removeAtCurr(p, &myTrack, 1);
	printList(p);
	checkTest(result, SUCCESS, testname);

	strcpy(testname, "remove from tail");
	result = removeAtCurr(p, &myTrack, 1);
	printList(p);
	checkTest(result, SUCCESS, testname);

	strcpy(testname, "remove from list containing only one element");
	result = removeAtCurr(p, &myTrack, 1);
	printList(p);
	checkTest(result, SUCCESS, testname);


	strcpy(testname, "remove from empty list");
	result = removeAtCurr(p, &myTrack, 1);
	printList(p);
	checkTest(result, INVALID_LIST_OPERATION, testname);

	printf("\n---TEST REMOVE and SKIP BACKWARDS---\n");

	// add notes to list
	insertAfterCurr(p, "Hey Brother", 123);
	insertAfterCurr(p, "Addicted to you", 456);
	insertAfterCurr(p, "Touch me", 32432);
	strcpy(t_name, "Shame on me");
	t_length = 3244;
	insertAfterCurr(p, t_name, t_length);
	printList(p);

	strcpy(testname, "remove from head");
	result = removeAtCurr(p, &myTrack, 0);
	printList(p);
	checkTest(result, SUCCESS, testname);


	strcpy(testname, "remove from middle");
	skipNext(p);
		printList(p);
	result = removeAtCurr(p, &myTrack, 0);
	printList(p);
	checkTest(result, SUCCESS, testname);

	skipNext(p);
	skipNext(p);
	printList(p);
	strcpy(testname, "remove from tail");
	result = removeAtCurr(p, &myTrack, 0);
	printList(p);
	checkTest(result, SUCCESS, testname);

	strcpy(testname, "remove from list containing only one element");
	result = removeAtCurr(p, &myTrack, 0);
	printList(p);
	checkTest(result, SUCCESS, testname);


	strcpy(testname, "remove from empty list");
	result = removeAtCurr(p, &myTrack, 0);
	printList(p);
	checkTest(result, INVALID_LIST_OPERATION, testname);
	return 0;
}

int test_clear_list() {
	char testname [255];
	Playlist *p = NULL;
	int result = 0;
	createPlaylist(&p);
	insertAfterCurr(p, "Hey Brother", 123);
	insertAfterCurr(p, "Addicted to you", 456);
	insertAfterCurr(p, "Touch me", 32432);

	printf("\n---TEST CLEAR LIST---\n");

	strcpy(testname, "check if list was cleaned");
	printList(p);
	result = clearPlaylist(p);
	p = NULL;
	printList(p);
	checkTest(result, SUCCESS, testname);

	strcpy(testname, "check if playlist is actually clean");
	result = insertAfterCurr(p, "test", 123);
	checkTest(result, INVALID_INPUT_PARAMETER, testname);



	return 0;
}

int test_save_to_file() {
	char testname [255];
	Playlist *p = NULL;
	int result = 0;

	printf("\n---TEST SAVE TO FILE---\n");

	strcpy(testname, "Try to save a not initialized playlist");
	result = savePlaylist(p, "test_save1.txt");
	checkTest(result, INVALID_INPUT_PARAMETER, testname);

	createPlaylist(&p);

	strcpy(testname, "try to save a file with an empty filename");
	result = savePlaylist(p, "");
	checkTest(result, FILE_IO_ERROR, testname);

	strcpy(testname, "save an empty playlist");
	result = savePlaylist(p, "test_save_empty_playlist.txt");
	checkTest(result, SUCCESS, testname); // TODO what to return when empty

	// add tracks
	insertAfterCurr(p, "Hey Brother", 123);
	insertAfterCurr(p, "Addicted to you", 456);
	insertAfterCurr(p, "Touch me", 32432);


	strcpy(testname, "save a playlist");
	result = savePlaylist(p, "test_save_playlist.txt");
	checkTest(result, SUCCESS, testname);

	return 0;
}

int test_load_playlist() {
	char testname [255];
	Playlist *p = NULL;
	int result = 0;

	printf("\n---TEST LOAD FROM FILE---\n");

	strcpy(testname, "Try to load from a non-existing file");
	result = loadPlaylist(&p, "NNNNNNNNNNNN");
	checkTest(result, FILE_IO_ERROR, testname);

	strcpy(testname, "Try to load from a file with empty filename");
	result = loadPlaylist(&p, "");
	checkTest(result, FILE_IO_ERROR, testname);

	strcpy(testname, "Read in playlist");
	result = loadPlaylist(&p, "test_playlist.txt");
	checkTest(result, SUCCESS, testname);
	printList(p);

	return 0;
}

int main() {
	test_init();
	test_add_after_iterator();
	test_add_before_iterator();
	test_skip_next();
	test_skip_prev();
	test_get_curr();
	test_remove();
	test_clear_list();
	test_save_to_file();
	test_load_playlist();
	return 0;
}
