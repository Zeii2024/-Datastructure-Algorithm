//大顶堆
//博客详解https://editor.csdn.net/md/?articleId=100834974 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Type int 

/*定义优先队列的数据结构*/ 
typedef struct HeapStruct{
	int capacity; //最大容量 
	int size;
	Type *eles; 
}PriorityQueue;

//优先队列第一个位置，即0位置是空出来的，从1位置放第一个数 

//初始化优先队列 ,创建空堆，初始化元素为0 
PriorityQueue *init(int max_size){        //这里初始化init定义为指针函数，其返回值是指针，可以直接赋值给*pq 
	PriorityQueue *pq = NULL;
	
	//检查输入大小的合法性 
	if(max_size <= 0){
		printf("max_size is illeagel!\n");
		return NULL;		
	} 
	pq = malloc(sizeof(PriorityQueue));
	
	if(pq == NULL){
		printf("malloc failed!\n");
		return NULL;
	}
	//下标为0的位置保留，不使用 
	pq->eles = malloc((max_size+1)*sizeof(Type));
	if(pq->eles == NULL){
		printf("eles malloc failed!\n");
		free(pq);
		return NULL;
	}
	
	//初始化队列成员
	memset(pq->eles, 0, (max_size+1)*sizeof(Type));
	pq->capacity = max_size;
	pq->size = 0;
	 
	return pq;
}

//判断是否为空 
int is_empty(PriorityQueue *pq){
	if(pq == NULL)
		return 0;
	if(pq->size == 0)
		return 1;
	else
		return 0; 
}

//判断是否为满
int is_full(PriorityQueue *pq){
	if(pq == NULL)
		return 0;
	if(pq->size == pq->capacity)
		return 1;
	else
		return 0;
}

//插入
int push(Type value, PriorityQueue *pq){
	int i=0;
	 
	//首先判断队列是否为满 
	if(is_full(pq)){
		printf("Queue is Full!\n");
		return 0;
	}
	printf("push %d\n", value);
	
	//将最后位置+1,作为待插入的空穴，不断将空穴与父节点比较，如果比父节点大，则空穴上移 
	for(i = pq->size+1; value > pq->eles[i/2] && i>1; i/=2){
		pq->eles[i] = pq->eles[i/2];
	} 
	pq->eles[i] = value; //将value放到最后的空穴中 
	pq->size ++;
	return 1;	
}
//查找最值 
int find_max(PriorityQueue *pq, Type *value){
	if(is_empty(pq)){
		printf("Queue is empty\n");
		return 0;
	}
	*value = pq->eles[1];
	return 1;
}

//删除 
int pop(PriorityQueue *pq, Type *max){
	int i=1;
	int maxchild = 0;
	
	
	//判断是否为空 
	if(is_empty(pq)){
		printf("Queue is empty!\n");
		return 0;
	}
	//先把最后一个元素取出来 
	Type last;
	last = pq->eles[pq->size];
	
	//取得最大值 
	*max = pq->eles[1];
	printf("Pop %d\n", pq->eles[1]);
	pq->size --;
	if(pq->size == 0){ //如果只有一个元素
		pq->eles[i] = 0; //删除之后变为0 
		return 1;	
	}
	
	//将第一个元素作为空穴，并不断下移 
	for(i=1; i * 2 < pq->size; i = maxchild){
		maxchild = i * 2;
		//选择两个孩子中的最大值 
		if(pq->eles[maxchild] < pq->eles[maxchild+1] && maxchild != pq->size)
			maxchild += 1;
		
		//如果last比空穴处的元素小，则空穴还要往下
		if(last < pq->eles[maxchild])	
			pq->eles[i] = pq->eles[maxchild];
		else
			break;
	} 
	pq->eles[i] = last;
	return 1;	 
} 

//摧毁 
int destroy(PriorityQueue *pq) {
	if(pq == NULL){
		return 0;
	}
	free(pq->eles);
	pq->eles = NULL;
	free(pq);
	pq = NULL;
	
	printf("destroy success\n");
	return 1;
}

int main(void){
	//创建容量为6的优先队列 
	PriorityQueue *pq = init(6); //init在定义时，定义为指针，因此其返回值是个指针，直接复制给pq 
	
	int arr[]={3,4,7,5,8,2,9,10} ;
	int i = 0;
	
	//试图插入多于6个的元素，最后两个元素将无法插入 
	for(i = 0; i<8; i++){
		push(arr[i], pq);
	} 
	
	//遍历队列内容
	printf("the value of pq are: ") ;
	for(i=0; i<pq->size; i++){
		printf("%d ", pq->eles[i+1]); 
	}
	printf("\n");
	printf("pq size is %d\n", pq->size);
	
	Type max;
	int size = pq->size;
	//每次从堆顶取元素
	for(i=0; i<size; i++){
		if(find_max(pq, &max)){
			printf("the max is %d\n", max);
			pop(pq, &max);
		}	
	}
	printf("new size is %d\n", pq->size) ;
	
	//销毁队列 
	destroy(pq);
	
	return 0;
}
