#include<iostream>
using namespace std;

class MaxHeap
{
	
public:
	MaxHeap(int* a, int n);
	void push(int number);
	int* heap;
	int heap_size;
	void pop();
	
};
class MinHeap
{
	
public:
	MinHeap(int* a, int n);
	void push(int number);
	int* heap;
	int heap_size;
	void pop();
};
void siftupMin(int* heap, int start)
{   
	int j = start, i = (j - 1) / 2;
	int temp = heap[j];
	while (j > 0)
	{
		if (heap[i] <= temp)
			break;
		else
		{
			heap[j] = heap[i];
			j = i;
			i = (i - 1) / 2;
		}
	}
	heap[j] = temp;
}

void siftupMax(int* heap, int start)
{
	int j = start, i = (j - 1) / 2;
	int temp = heap[j];
	while (j > 0)
	{
		if (heap[i] >= temp)
			break;
		else
		{
			heap[j] = heap[i];
			j = i;
			i = (i - 1) / 2;
		}
	}
	heap[j] = temp;
}


void MinHeap::push( int x)
{
	heap[heap_size] = x;
	siftupMin(heap, heap_size);
	heap_size++;
}
void MaxHeap::push(int x)
{
	heap[heap_size] = x;
	siftupMax(heap, heap_size);
	heap_size++;
}

void siftdownMin(int* heap, int start, int m)
{
	int i = start, j = 2 * i + 1;
	int temp = heap[i];
	while (j <= m)
	{
		if (j<m && heap[j]>heap[j + 1])
		j++;
		if (temp <= heap[j])
			break;
		else
		{
			heap[i] = heap[j];
			i = j;
			j = 2 * j + 1;
		}
	}
	heap[i] = temp;
}
void siftdownMax(int* heap, int start, int m)
{
	int i = start, j = 2 * i + 1;
	int temp = heap[i];
	while (j <= m)
	{
		if (j<m && heap[j]<heap[j + 1])
			j++;
		if (temp >= heap[j])
			break;
		else
		{
			heap[i] = heap[j];
			i = j;
			j = 2 * j + 1;
		}
	}
	heap[i] = temp;
}

void MinHeap::pop()
{
	heap[0] = heap[heap_size- 1];
	heap_size--;
	siftdownMin(heap, 0, heap_size - 1);
}
void MaxHeap::pop()
{
	heap[0] = heap[heap_size - 1];
	heap_size--;
	siftdownMax(heap, 0, heap_size - 1);
}

MinHeap::MinHeap(int* ax, int n)
{
	heap = ax;
	heap_size = n;
}

MaxHeap::MaxHeap(int* ax, int n)
{
	heap = ax;
	heap_size = n;
}

void addNum(MaxHeap& big_queue,MinHeap& small_queue,int num) {

	if (big_queue.heap_size==0) {
		big_queue.push(num);
		return;
	}
	
	if (big_queue.heap_size == small_queue.heap_size) {
		if (num < big_queue.heap[0]){
			big_queue.push(num);
		}
		else {
			small_queue.push(num);
		}
	}
	
	else if (big_queue.heap_size > small_queue.heap_size) {
		
		if (num > big_queue.heap[0]) {
			small_queue.push(num);
		}
		
		else {
			small_queue.push(big_queue.heap[0]);
			big_queue.pop();
			big_queue.push(num);
		}
	}
	
	else if (big_queue.heap_size < small_queue.heap_size) {
		if (num < small_queue.heap[0]) {
			big_queue.push(num);
		}
		else {
			big_queue.push(small_queue.heap[0]);
			small_queue.pop();
			small_queue.push(num);
		}
	}
}

int findMedian(MaxHeap big_queue, MinHeap small_queue) {
	
	if (big_queue.heap_size == small_queue.heap_size) {
		return (big_queue.heap[0] );
	}
	
	else if (big_queue.heap_size > small_queue.heap_size) {
		return big_queue.heap[0];
	}
	
	return small_queue.heap[0];
}
int main()
{
	int n=80000;
	int* arr = new int[n];
	int* brr = new int[n];
	MinHeap small_queue(arr,0);
	MaxHeap big_queue(brr,0);
	int num;
	while(scanf("%d",&num))
	{
		
 		addNum(big_queue, small_queue, num); 
		int x=findMedian(big_queue, small_queue);
		printf("%d	",x);
	}
    return 1;
}
