// lists and xml|txt file export
// files
// encrypt
// date and time

#ifndef CC_UTIL_H
#define CC_UTIL_H

// Global vars
/// collection framework vars


// utilites - dates, time
typedef struct  {
	unsigned int day;
	unsigned int year;
	unsigned int month;
	} CCDate;

extern char *CCStringFromDate(const CCDate *date);
extern char *CCStringFromDateWithFormat(const CCDate *date, const char *format);
extern int CCDateAreEquals(CCDate *date1, CCDate *date2);
extern int CCValidateDate(CCDate *date); // -1 if it is invalide, 0 if it's leap and 1 if it's common year

// COLLECTIONS FRAMEWORK
//////// TYPES
typedef enum {
	STATIC_OBJECTS, DYNAMIC_OBJECTS
	} CCListObjectMemoryType;

typedef enum {
	LIST_DEFAULT_ORDER, LIST_REVERSE_ORDER
	} ListOrderType;
	
typedef struct CCNo {
	struct CCNo *nextNode;
	struct CCNo *previous;
	void *data;
	} CCList, CCNode;
	
//////// GLOBAL VARS
extern CCListObjectMemoryType objectMemoryType;

//////// FUNCTIONS
extern int CCListAdd(CCList **list , void *data); // imp
extern int CCListInitWith(CCList **list, ...); // imp
extern int CCListRemoveAtIndex(CCList **list, int index); // imp
extern int CCListRemove(CCList **list, void *element, int (*comparator)(void *, void *)); //imp
extern int CCListIsEmpty(CCList *list); // imp
extern void CCListShow(CCList *list, ListOrderType orderType, void (*showData)(void *)); // imp
extern int CCListLength(CCList *list); // imp
extern int CCListFreeMemory(CCList **list); // imp // use only if each node was dynamic allocated
extern void * CCListIterator(CCList *list, ListOrderType orderType);


// IO framework
//// enum filetype, fileformat(txt, xml)
//// CCFileRename
//// CCFileSaveList
//// CCFileSaveListAsXML
//// CCFileSearch - string
//// CCFileSearch - the user supply a comparator
//// CCFileSearch - using ID.. create index concept(pairs)
//// CCFileReadList - normallist
//// CCFileReadList - using a custom parser
//// CCFileSaveToRandomAccess

// encryption

// for test	
extern void doIt();
	
#endif