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


int test() 
{
	// store the result of calling functions
	int result;

	// a variable to store an MP3 track popped from the list
	MP3Track track;

	// a pointer to our doubly-linked list
	Playlist *listPtr = NULL;

	// initialise the list - passing the address of our
	// list pointer as an input so it can be modified 
	// to point to the memory allocated for the list
	result = createPlaylist(&listPtr);
	if (result != SUCCESS)
	{
		printf("An error occurred when attempting to initialise the list\n");
	}
	else
	{
		printf("List initialised successfully\n");
	}
	printf("\n");

	// try getting data at the current position
	// this should fail because the list is empty
	result = getCurrentTrack(listPtr, &track);
	if (result != INVALID_LIST_OPERATION)
	{
		printf("Error: should have detected attempt to get data from an empty list\n");
	}
	else
	{
		printf("Correctly identified attempt to get data from an empty list\n");
	}

	// try getting removing data at the current position
	// this should fail because the list is empty
	result = removeAtCurr(listPtr, &track, 1);
	if (result != INVALID_LIST_OPERATION)
	{
		printf("Error: should have detected attempt to remove data from an empty list\n");
	}
	else
	{
		printf("Correctly identified attempt to remove data from an empty list\n");
	}

	// try  moving 'curr' to the next node in the list
	// this should fail because the list is empty
	result = skipNext(listPtr);
	if (result != INVALID_LIST_OPERATION)
	{
		printf("Error: should have detected attempt to skip next list is empty\n");
	}
	else
	{
		printf("Correctly identified attempt to skip next when list is empty\n");
	}

	// try  moving 'curr' to the previous node in the list
	// this should fail because the list is empty
	result = skipPrev(listPtr);
	if (result != INVALID_LIST_OPERATION)
	{
		printf("Error: should have detected attempt to skip prev when list is empty\n");
	}
	else
	{
		printf("Correctly identified attempt to skip prev when list is empty\n");
	}
	printf("\n");

	// add a new item to the list
	char trackName[] = "White Christmas";
	int length = 233;
	result = insertAfterCurr(listPtr, trackName, length);
	if (result != SUCCESS)
	{
		printf("Error: failed to add new node to list\n");
	}
	else
	{
		printf("Inserting a new node into list successful\n");
	}
	printf("\n");

	// try  moving 'curr' to the next node in the list
	// this should fail because 'curr' is at the tail of the list, nothing after it
	result = skipNext(listPtr);
	if (result != INVALID_LIST_OPERATION)
	{
		printf("Error: should have detected attempt to move 'curr' next when it is already at the tail of the list\n");
	}
	else
	{
		printf("Correctly identified attempt to move 'curr' next when it is already at the tail of the list\n");
	}

	// try  moving 'curr' to the previous node in the list
	// this should fail because 'curr' is at the head of the list, nothing before it
	result = skipPrev(listPtr);
	if (result != INVALID_LIST_OPERATION)
	{
		printf("Error: should have detected attempt to move 'curr' previous when it is already at the head of the list\n");
	}
	else
	{
		printf("Correctly identified attempt to move 'curr' previous when it is already at the head of the list\n");
	}	

	// add another item to the list BUT this time with an erroneous / NULL track name
	result = insertAfterCurr(listPtr, NULL, 12);
	if (result != INVALID_INPUT_PARAMETER)
	{
		printf("Error: should have detected attempt to add another item to the list when the track name provided is 'NULL'\n");
	}
	else
	{
		printf("Correctly identified attempt to add another item to the list when the track name provided is 'NULL'\n");
	}
	printf("\n");

	// add another item to the list
	char trackName2[] = "Macarena";
	int length2 = 145;
	result = insertAfterCurr(listPtr, trackName2, length2);
	if (result != SUCCESS)
	{
		printf("Error: failed to add node 2 to list\n");
	}
	else
	{
		printf("Inserting node 2 into list successful\n");
	}
	printf("\n");
	
	// try getting data at the current position
	// We should get the first track in the list, where 'curr' is currently positioned
	result = getCurrentTrack(listPtr, &track);
	if (result != SUCCESS)
	{
		printf("Error: failed to getCurrentTrack() data for the newly added item in the playlist\n");
	}
	else
	{
		printf("Successfully managed to getCurrentTrack() data for the newly added item in the playlist\n");

		// check data retreived is correct
		if (strncmp(track.trackName, trackName, 49) != 0)
		{
			// tracks don't match
			printf("Error: track names don't match in the data obtained for the newly added item in the list\n");
		}
		else
		{
			if (track.trackLength != length)
			{				
				// track lengths don't match
				printf("Error: track lengths don't match in the data obtained for the newly added item in the list\n");
			}
			else
			{
				// all good
				printf("Track names and track lengths match correctly in the data obtained for the newly added item in the list\n");
			}
		}
	}
	printf("\n");

	// try  moving 'curr' to the next node in the list
	result = skipNext(listPtr);
	if (result != SUCCESS)
	{
		printf("Error: failed to move 'curr' to next node in list\n");
	}
	else
	{
		printf("Successfully managed to move 'curr' to next node in list\n");
	}
	printf("\n");

	// get the data for the new current item in the list and check it's validity
	result = getCurrentTrack(listPtr, &track);
	if (result != SUCCESS)
	{
		printf("Error: failed to getCurrentTrack() data for the next item in the list\n");
	}
	else
	{
		printf("Successfully managed to getCurrentTrack() data for the next item in the list\n");

		// check data retreived is correct
		if (strncmp(track.trackName, trackName2, 49) != 0)
		{
			// tracks don't match
			printf("Error: track names don't match in the data obtained for the next item in the list\n");
		}
		else
		{
			if (track.trackLength != length2)
			{				
				// track lengths don't match
				printf("Error: track lengths don't match in the data obtained for the next item in the list\n");
			}
			else
			{
				// all good
				printf("Track names and track lengths match correctly in the data obtained for the next item in list\n");
			}
		}
	}
	printf("\n");


	// try saving the list to a file
	result = savePlaylist(listPtr, "out.txt");
	if (result != SUCCESS)
	{
		printf("Error: failed to write playlist to file.\n");
	}
	else
	{
		printf("Successfully managed to write playlist to file\n");
	}
	printf("\n");

	// try removing a node
	result = removeAtCurr(listPtr, &track, 1);
	if (result != SUCCESS)		
	{
		printf("Error: failed to remove the node from the current position in the list\n");
	}
	else
	{
		printf("Successfully managed to remove the node from the current position in the list\n");

		// check data retreived is correct
		if (strncmp(track.trackName, trackName2, 49) != 0)
		{
			// tracks don't match
			printf("Error: track names don't match in data obtained from node removed\n");
		}
		else
		{
			if (track.trackLength != length2)
			{				
				// track lengths don't match
				printf("Error: track lengths don't match in data obtained from node removed\n");
			}
			else
			{
				// all good
				printf("Track name and track length are correct in the data obtained from the removed node\n");
			}
		}
	}
	printf("\n");

	// try emptying the list
	result = clearPlaylist(listPtr);
	if (result != SUCCESS)
	{
		printf("Error: failed to clear the playist\n");
	}
	else
	{
		printf("Successfully free-d the playlist\n");
	}
	printf("\n");

	// a pointer to a another doubly-linked list - this time to load from a file
	Playlist *listPtr2 = NULL;

	// attempt to load a playlist from a file
	result = loadPlaylist(&listPtr2, "test_playlist.txt");
	if (result != SUCCESS)
	{
		printf("An error occurred when attempting to load playlist from a file\n");
	}
	else
	{
		printf("Playlist loaded from file successfully\n");

		// display the contents of the list
		MP3Track *pTrack = listPtr2->head;
		while (pTrack!=NULL)
		{
			printf("Next track name is %s and track length %d\n", pTrack->trackName, pTrack->trackLength);
			pTrack = pTrack->next;
		}

		// free the memory for the playlist
		result = clearPlaylist(listPtr2);
		if (result != SUCCESS)
		{
			printf("Error: failed to free playlist loaded from file\n");
		}
		else
		{
			printf("Successfully free-d the playlist loaded from file\n");
		}
	}

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

	strcpy(testname, "track length check (should be <= 88000");
	result = insertAfterCurr(p, "Hey Brother", 88001);
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

int test_skip_next() {
	char testname [255];
	Playlist *p = NULL;
	int result = 0;

	printf("\n---TEST SKIP NEXT---\n");

	strcpy(testname, "check if pointer to list provided is valid");
	p = NULL;
	result = skipNext(p);
	printList(p);
	checkTest(result, SUCCESS, testname);

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
	// TODO Wednesday
	
	return 0;
}



int main() {
	// test_init();
	// test_add_after_iterator();
	// test_skip_next();
	// test_get_curr();
	test_remove();
	return 0;
}
