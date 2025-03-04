/*  Create my own element type.*/
typedef int elementType;
/*  The nodes of the BST.*/
typedef struct node {
    elementType item;   /* The content of the node.*/
    struct node *left;   /* The left children of the node.*/
    struct node *right;  /* The right children of the node.*/
} treeNode;
/*  The pointer to treeNode.*/
typedef treeNode *ptrTreeNode;
/*  The BST. */
typedef ptrTreeNode BST;

BST add(BST, elementType);

ptrTreeNode createNode(elementType i);

int find(BST Tree, ptrTreeNode node, elementType sum, int mode);

int search(BST Tree, elementType b);

void freeTree(BST);
