/*******************************************************************************
 * @author		: Rohan Jyoti (Github: RohanJ)
 * @filename	: queue.c
 * @purpose		: Queue Library implemented using singly-linked lists.
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include <ckit/queue.h>


struct queue_node
{
	void *item;
	struct queue_node *next;
};


/*******************************************************************************
 * @author	: Rohan Jyoti
 * @name	: queue_init
 * @param	: q is a Dictionary Data Structure
 * @return	: void
 * @purpose	: Initialize the queue data structure. This function should be
 *              called first. 
 ******************************************************************************/
void queue_init(queue_t *q)
{
	q->head = NULL;
	q->tail = NULL;
	q->size = 0;
}


/*******************************************************************************
 * @author	: Rohan Jyoti
 * @name	: queue_destroy
 * @param	: q is a Dictionary Data Structure
 * @return	: void
 * @purpose	: Frees all memory associated with internal queue structure. 
 *            WARNING: Memory associated with the item is NOT freed.
 *            That is up to the user to free.
 ******************************************************************************/
void queue_destroy(queue_t *q)
{
	while(queue_size(q) > 0)
		queue_dequeue(q);
}


/*******************************************************************************
 * @author	: Rohan Jyoti
 * @name	: queue_dequeue
 * @param	: q is a Dictionary Data Structure
 * @return	: void * to the item contained in the queue node
 * @purpose	: Returns a pointer to the front of the queue. 
 *            Front element of queue is freed (just the internal strucutre)
 *            Returns NULL if queue is empty
 ******************************************************************************/
void *queue_dequeue(queue_t *q)
{
	struct queue_node *front;
	void *item;

	if(queue_size(q) == 0)
		return NULL;

	front = q->head;
	q->head = q->head->next;
	q->size--;

	item = front->item;
	free(front);

	if(queue_size(q) == 0)
    {
		q->head = NULL;
		q->tail = NULL;
	}

	return item;
}


/*******************************************************************************
 * @author	: Rohan Jyoti
 * @name	: queue_init
 * @param	: q is a Dictionary Data Structure, pos is the position at which
 *              you want to remove
 * @return	: void * to the item at specified position
 * @purpose	: Return a pointer to the item at specified position
 *            Internal Element is removed
 *            Return NULL if queue is empty or position is invalid
 ******************************************************************************/
void *queue_remove_at(queue_t *q, int pos)
{
	if( pos < 0 || q->size-1 < (unsigned int)pos)
		return NULL;
	
    q->size--;
	struct queue_node *cur = q->head;
	struct queue_node *prev = NULL;
	
    while(pos--)
    {
		prev = cur;
		cur = cur->next;
	}

	if(cur == q->head)
    {
		q->head = cur->next;
		if(q->head == NULL)
			q->tail = NULL;
		void *item = cur->item;
		free(cur);
		return item;
	}
    else if(cur == q->tail)
    {
		q->tail = prev;
		prev->next = NULL;
		void *item = cur->item;
		free(cur);
		return item;
	}
    else
    {
		prev->next = cur->next;
		void *item = cur->item;
		free(cur);
		return item;
	}
}


/*******************************************************************************
 * @author	: Rohan Jyoti
 * @name	: queue_init
 * @param	: q is a Dictionary Data Structure, pos is the position at which
 *              you want to retrieve
 * @return	: void * to the item at specified position
 * @purpose	: Return a pointer to the item at specified position
 *            Internal Element is NOT removed
 *            Return NULL if queue is empty or position is invalid
 ******************************************************************************/
void *queue_at(queue_t *q, int pos)
{
	int i;
	struct queue_node *node;
	if(q == NULL)
		return NULL;
		

	for(i=0, node=q->head; i<pos && node != NULL; i++)
        node=node->next;
	if(i != pos)
		return 0;
	else
		return node->item;

}


/*******************************************************************************
 * @author	: Rohan Jyoti
 * @name	: queue_enqueue
 * @param	: q is a Dictionary Data Structure, item is the data (user allocated)
 * @return	: void
 * @purpose	: Add a new queue node to the queue data structure
 ******************************************************************************/
void queue_enqueue(queue_t *q, void *item)
{
	struct queue_node *back = malloc(sizeof(struct queue_node));

	back->item = item;
	back->next = NULL;

	if(queue_size(q) == 0)
        q->head = back;
	else
		q->tail->next = back;

	q->tail = back;
	q->size++;
}


/*******************************************************************************
 * @author	: Rohan Jyoti
 * @name	: queue_enqueue
 * @param	: q is a Dictionary Data Structure
 * @return	: unsigned int
 * @purpose	: Returns the number of elements in the queue data structure
 ******************************************************************************/
unsigned int queue_size(queue_t *q)
{
	return q->size;
}



/*******************************************************************************
 * @author	: Rohan Jyoti
 * @name	: queue_iterate
 * @param	: q is a Dictionary Data Structure, (*iter_function) is a function
 *              pointer to the function you want to apply, arg is a pass through
 *              variable.
 * @return	: void
 * @purpose	: An iterator for the queue data structure
 ******************************************************************************/
void queue_iterate(queue_t *q, void (*iter_func)(void *, void *), void *arg)
{
	struct queue_node *node;
	if(queue_size(q) == 0)
		return;

	node = q->head;
	while(node != NULL)
    {
		iter_func(node->item, arg);
		node = node->next;
	}
}
