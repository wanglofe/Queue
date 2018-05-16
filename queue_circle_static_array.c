//Author:	Kevin
//Date:		20180516

#include <stdio.h>

#define QUEUE_SIZE	32
#define QUEUE_EMPTY	-9999
#define QUEUE_FULL	-1

typedef int queue_t;

static int front = 0;
static int rear = 0;
static size_t m_queue_length = 0;
static queue_t queue[QUEUE_SIZE];

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
	//tail insert
	if(rear == QUEUE_SIZE) {
		rear = 0;
	}
	queue[rear++] = val;
	m_queue_length++;
	return 0;
}

int queue_delete(void)
{
	if(queue_isempty()) {
		return QUEUE_EMPTY;
	}
	//delete the first one
	if(front == QUEUE_SIZE) {
		front = 0;
	}
	front++;
	m_queue_length--;
	return 0;
}

int queue_first(void)
{
	if(queue_isempty()) {
		return QUEUE_EMPTY;
	}
	return queue[front];	
}

int queue_isempty(void)
{
	return m_queue_length == 0;
}

int queue_isfull(void)
{
	return m_queue_length == QUEUE_SIZE;
}

size_t queue_length(void)
{
	return m_queue_length;
}

int queue_destroy(void)
{
	m_queue_length = 0;
	front = 0;
	rear = 0;
	return 0;
}

void queue_print(void)
{
	int i;
	int tmp_front = front/*, tmp_rear = rear*/;
	for(i=0; i<m_queue_length; i++) {
		if(tmp_front == QUEUE_SIZE) {
			tmp_front = 0;
		}
		fprintf(stdout, "%d ", queue[tmp_front++]);
	}
	putchar('\n');
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

}

