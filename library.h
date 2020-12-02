/****************************************************************************/
/*                                                                          */
/* This file contains the interface functions                               */
/* you should use for the wet ex 1                                          */
/*                                                                          */
/****************************************************************************/

/****************************************************************************/
/*                                                                          */
/* File Name : library.h                                                   */
/*                                                                          */
/****************************************************************************/

#ifndef _234218_WET1
#define _234218_WET1

#ifdef __cplusplus
extern "C" {
#endif

/* Return Values
 * ----------------------------------- */
typedef enum {
    SUCCESS = 0,
    FAILURE = -1,
    ALLOCATION_ERROR = -2,
    INVALID_INPUT = -3
} StatusType;


void *Init(); // Lior

StatusType AddCourse (void *DS, int courseID, int numOfClasses); // Tal

StatusType RemoveCourse(void *DS, int courseID); // Lior

StatusType WatchClass(void *DS, int courseID, int classID, int time); // Lior

StatusType TimeViewed(void *DS, int courseID, int classID, int *timeViewed); // Lior

StatusType GetMostViewedClasses(void *DS, int numOfClasses, int *courses, int *classes); // Tal

void Quit(void** DS); // Tal

#ifdef __cplusplus
}
#endif

#endif    /*_234218_WET1 */
