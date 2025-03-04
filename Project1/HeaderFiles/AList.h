/*  Create my own element type.*/
typedef int elementType;
/*  AList is a structure, 
    which consists of an array and its size. */
typedef struct alist {
    elementType *a;
    int size;
} AList;
/*  The pointer to AList. */
typedef AList *ptrToAList;
/*  The pointer to element type */
typedef elementType *elementArray;

ptrToAList createList(int);

void addLast(ptrToAList, elementType);

void mergeSort(ptrToAList);

int findOut(elementType, ptrToAList, int);

int flash(int *, elementArray, elementType);

int myMergeSort(elementArray, int);

void freeAList(ptrToAList);