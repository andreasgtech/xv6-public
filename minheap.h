typedef struct node
{
	struct proc * data;
} node ;

typedef struct minheap
{
	int num_procs;
	node minHeap[64];
} minheap ;

void insertNode(minheap *hp, struct proc * data);
void swap(node *n1, node *n2);
void heapify(minheap *hp, int i);
struct proc * popNode(minheap *hp);
void calcInitPr(struct proc * p);
void calcPr(struct proc * p);