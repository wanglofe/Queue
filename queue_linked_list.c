// Author:	Kevin
// Date:	20180517

#include <stdio.h>
#include <stdlib.h>

#ifdef _DEBUG
#define DEBUG(fmt, arg...) printf(fmt, ##arg)
#else
#define DEBUG(fmt, arg...)
#endif

#define QUEUE_FULL	-1
#define QUEUE_EMPTY	-9999

typedef int queue_t;
typedef struct sll {
	queue_t val;
	struct sll *next;
} sll_t;

static sll_t *header = NULL;
static sll_t *rear = NULL;
static size_t m_queue_length = 0;

// handler declarations
int	queue_insert(queue_t val);
int	queue_delete(void);
queue_t	queue_first(void);
int	queue_isempty(void);
int	queue_isfull(void);
size_t	queue_length(void);
int	queue_destroy(void);
void	queue_print(void);


// handlers
int queue_insert(queue_t val)
{
	if(queue_isfull()) {
		return QUEUE_FULL;
	}
	sll_t *newnode = malloc(sizeof(sll_t));
	if(!newnode) {
		return -1;
	}
	newnode->val = val;
	// tail insert
	newnode->next = NULL;
	
	DEBUG("newnode: %p, %d\n", newnode, newnode->val);	
	
	if(!header) {
		header = rear = newnode;
	} else {
		rear->next = newnode;
		rear = newnode;
	}
	m_queue_length++;
	return 0;
}

int queue_delete(void)
{
	if(queue_isempty()) {
		return QUEUE_EMPTY;
	}
	sll_t *tmp = header;
	if(m_queue_length == 1) {//header = rear
		header = rear = NULL;
	} else {
		header = header->next;
	}
	free(tmp);
	m_queue_length--;
	return 0;
}	

queue_t queue_first(void)
{
	if(queue_isempty()) {
		return QUEUE_EMPTY;
	}
	return header->val;	
}
		
int queue_isempty(void)
{
	return m_queue_length == 0;
}

int queue_isfull(void)
{
	/* never */
	return 0;
}

size_t queue_length(void)
{
	return m_queue_length;
}

int queue_destroy(void)
{
	sll_t *tmp;
	while(header) {
		tmp = header;
		header = header->next;
		free(tmp);
	}
	header = rear = NULL;
	m_queue_length = 0;
	return 0;
}

void queue_print(void)
{
	sll_t *tmp = header;
	while(tmp) {
		DEBUG(stdout, "%p--%d ", header, header->val);
		fprintf(stdout, "%d ", tmp->val);
		tmp = tmp->next;
	}
	fprintf(stdout, "\n");
}


// test
void main(void)
{
	int i = 0;
	for(i=0; i<32; i++) {
		queue_insert(i);
	}
	queue_print();
	printf("[queue] empty: %d, full: %d, length:%d\n", queue_isempty(), queue_isfull(), queue_length());
	printf("[queue] first: %d\n", queue_first());
	
	for(i=0; i<15; i++) {
		queue_delete();
	}
	queue_print();
	printf("[queue] empty: %d, full: %d, length:%d\n", queue_isempty(), queue_isfull(), queue_length());

	for(i=50; i<65; i++) {
		queue_insert(i);
	}
	queue_print();
	printf("[queue] empty: %d, full: %d, length:%d\n", queue_isempty(), queue_isfull(), queue_length());
	printf("[queue] first: %d\n", queue_first());

	queue_destroy();
	printf("[queue] empty: %d, full: %d, length:%d\n", queue_isempty(), queue_isfull(), queue_length());
}
