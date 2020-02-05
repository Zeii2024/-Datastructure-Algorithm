#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Type int

/*ʵ��һ��֧�ֶ�̬���ݵ����� */ 

typedef struct Array{
	int size;
	int used;
	Type *arr;
}Array;

void alloc(Array *array);             //�����ڴ�
void dump(Array *array);             //˳�����
int insert(Array *array, Type elem); //����/����
int delete(Array *array, int index); //ɾ��
int search(Array *array, Type elem); //���� 

int main(void){
	int index;
	Array array = {10, 0, NULL};//����ֱ�Ӹ�ֵ 
	alloc(&array);
	if(!array.arr){
		printf("alloc wrong!\n");
		return -1;
	}
	
	insert(&array, 1);           //ΪʲôҪ��ȡַ�����أ�������ȡ��ַ������Ӧ��ַ���ڴ���в����� 
	insert(&array, 4);           //���ݽṹ�н������ָ���Ӧ�ڴ������Ҫ�ı䣬������ֻ�ı�ָ��ָ��ķ�������Ҫʹ��ȡַ��& 
	insert(&array, 3);
	insert(&array, 2);
	printf("=== insert 1, 3, 4, 2\n");
	printf("=== array.used = %d\n", array.used);  //Ϊʲô���������array.used�������о�Ҫ��array->used 
	dump(&array);
	
	index = search(&array, 2);
	if(index !=-1){
		printf("2 �ǵ�%d��Ԫ��\n", index);
	} 
	else{
		printf("2 is not in array!\n");
	}
	index = search(&array, 8);
	if(index != -1){
		printf("8 �ǵ�%d��Ԫ��\n", index);
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
		printf("��������!\n");
		return 0;
	}
	//ʵ��һ����������
	for(index = 0; index < array->used; index ++){
		if(array->arr[index] > elem)
			break;
	} 
	if( index < array->used){
		memmove(&array->arr[index+1], &array->arr[index], (array->used - index)*sizeof(Type));//�ƶ�/�����ڴ�����,ǧ��Ҫ�ǵ�*sizeof() 
	}
	array->arr[index] = elem;
	array->used++;
	
	return 1;
}

//delete
int delete(Array *array, int index){
	if (array->used == 0){
		printf("�����ѿ�!\n");
		return 0;
	}
	if(index<0 || index > array->used){
		printf("index����!\n");
		return -1;
	}
	memmove(&array->arr[index], &array->arr[index+1], (array->used-index-1)*sizeof(Type));//�ƶ��ڴ����� 
	array->used--; //ʵ�������һ����Ԫû����գ����ǰ����������� 
	
	return 1;
}

//search
int search(Array *array, Type elem){
	int index;
	for(index=0; index<array->used; index++){
		if(array->arr[index] == elem){
			return index;
		if(array->arr[index] > elem) //���˱�elem���Ԫ�ؾͿ��Է����� 
			return -1;
		}
	}
	return -1;
}
