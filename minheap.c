#define LCHILD(x) 2 * x + 1
#define RCHILD(x) 2 * x + 2
#define PARENT(x) (x-1) / 2

#include <stdio.h>

#include "minheap.h"

#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"

void insertNode(minheap *hp, struct proc * data)
{
    if((hp->num_procs) == 64)
    {
        cprintf("Error: more than 64 processes??\n");
        return;
    }

    // Positioning the node at the right position in the min heap
    int i;
    i = (hp->num_procs)++;
    while(i && data->priority < hp->minHeap[PARENT(i)].data->priority)
    {
        hp->minHeap[i] = hp->minHeap[PARENT(i)];
        i = PARENT(i);
    }
    hp->minHeap[i].data = data;
}

void swap(node *n1, node *n2)
{
    node temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}

void heapify(minheap *hp, int i)
{
    int smallest = (LCHILD(i) < hp->num_procs && hp->minHeap[LCHILD(i)].data->priority < hp->minHeap[i].data->priority) ? LCHILD(i) : i;
    if(RCHILD(i) < hp->num_procs && hp->minHeap[RCHILD(i)].data->priority < hp->minHeap[smallest].data->priority)
    {
        smallest = RCHILD(i);
    }
    if(smallest != i)
    {
        swap(&(hp->minHeap[i]), &(hp->minHeap[smallest]));
        heapify(hp, smallest);
    }
}

struct proc * popNode(minheap *hp)
{
	struct proc * ret_proc;	
    if(hp->num_procs)
    {
        //cprintf("Popping process with PID : %d\n\n", hp->minHeap[0].data->pid);
        ret_proc = hp->minHeap[0].data;
        hp->minHeap[0] = hp->minHeap[--(hp->num_procs)];
        heapify(hp, 0);
        return ret_proc;
    }
    else
    {
        cprintf("\nMin Heap is empty!\n");
        return NULL;
    }
}

extern uint ticks;

void calcInitPr(struct proc * p)
{
    p->priority=0;
    p->times_sched=0;
    p->runningTime=0;
    p->birthTime=ticks;
}

void calcPr(struct proc * p)
{
    if (ticks - p->birthTime)
    {
        p->priority = (double)(p->runningTime)/(double)(ticks - p->birthTime) * 100000;
    }
    else
    {
        if (!p->runningTime)
        {
            p->priority=0;
        }
    }
}