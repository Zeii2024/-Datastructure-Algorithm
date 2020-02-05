#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Type int

/*实现一个支持动态扩容的数组 */ 

typedef struct Array{
	int size;
	int used;
	Type *arr;
}Array;

void alloc(Array *array);             //分配内存
void dump(Array *array);             //顺序输出
int insert(Array *array, Type elem); //插入/扩容
int delete(Array *array, int index); //删除
int search(Array *array, Type elem); //搜索 

int main(void){
	int index;
	Array array = {10, 0, NULL};//可以直接赋值 
	alloc(&array);
	if(!array.arr){
		printf("alloc wrong!\n");
		return -1;
	}
	
	insert(&array, 1);           //为什么要用取址操作呢？？？？取地址，对相应地址的内存进行操作？ 
	insert(&array, 4);           //数据结构中讲：这个指针对应内存的内容要改变，而不是只改变指针指向的方向，则需要使用取址符& 
	insert(&array, 3);
	insert(&array, 2);
	printf("=== insert 1, 3, 4, 2\n");
	printf("=== array.used = %d\n", array.used);  //为什么这里可以用array.used，函数中就要用array->used 
	dump(&array);
	
	index = search(&array, 2);
	if(index !=-1){
		printf("2 是第%d个元素\n", index);
	} 
	else{
		printf("2 is not in array!\n");
	}
	index = search(&array, 8);
	if(index != -1){
		printf("8 是第%d个元素\n", index);
	} 
	else{
		printf("8 is not in array!\n");
	}
	
	printf("=== delete [6]\n");
	delete(&array, 6);
	dump(&array);
	
	printf("=== delete [1]\n");
	delete(&array, 1);
	
	dump(&array);

	return 0;	
} 

//alloc
void alloc(Array *array){
	array->arr = (Type *)malloc(array->used);
} 

//dump
void dump(Array *array){
	int index;
	for(index = 0; index < array->used; index++){
		printf("[%d]: %d\n", index, array->arr[index]);
	}
}

//insert
int insert(Array *array, Type elem){
	int index;
	if(array->used >= array->size){
		printf("数组已满!\n");
		return 0;
	}
	//实现一个有序数组
	for(index = 0; index < array->used; index ++){
		if(array->arr[index] > elem)
			break;
	} 
	if( index < array->used){
		memmove(&array->arr[index+1], &array->arr[index], (array->used - index)*sizeof(Type));//移动/复制内存内容,千万要记得*sizeof() 
	}
	array->arr[index] = elem;
	array->used++;
	
	return 1;
}

//delete
int delete(Array *array, int index){
	if (array->used == 0){
		printf("数组已空!\n");
		return 0;
	}
	if(index<0 || index > array->used){
		printf("index有误!\n");
		return -1;
	}
	memmove(&array->arr[index], &array->arr[index+1], (array->used-index-1)*sizeof(Type));//移动内存内容 
	array->used--; //实际上最后一个单元没有清空，而是把内容舍弃掉 
	
	return 1;
}

//search
int search(Array *array, Type elem){
	int index;
	for(index=0; index<array->used; index++){
		if(array->arr[index] == elem){
			return index;
		if(array->arr[index] > elem) //到了比elem大的元素就可以返回了 
			return -1;
		}
	}
	return -1;
}
