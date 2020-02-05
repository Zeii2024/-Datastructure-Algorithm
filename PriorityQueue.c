//�󶥶�
//�������https://editor.csdn.net/md/?articleId=100834974 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Type int 

/*�������ȶ��е����ݽṹ*/ 
typedef struct HeapStruct{
	int capacity; //������� 
	int size;
	Type *eles; 
}PriorityQueue;

//���ȶ��е�һ��λ�ã���0λ���ǿճ����ģ���1λ�÷ŵ�һ���� 

//��ʼ�����ȶ��� ,�����նѣ���ʼ��Ԫ��Ϊ0 
PriorityQueue *init(int max_size){        //�����ʼ��init����Ϊָ�뺯�����䷵��ֵ��ָ�룬����ֱ�Ӹ�ֵ��*pq 
	PriorityQueue *pq = NULL;
	
	//��������С�ĺϷ��� 
	if(max_size <= 0){
		printf("max_size is illeagel!\n");
		return NULL;		
	} 
	pq = malloc(sizeof(PriorityQueue));
	
	if(pq == NULL){
		printf("malloc failed!\n");
		return NULL;
	}
	//�±�Ϊ0��λ�ñ�������ʹ�� 
	pq->eles = malloc((max_size+1)*sizeof(Type));
	if(pq->eles == NULL){
		printf("eles malloc failed!\n");
		free(pq);
		return NULL;
	}
	
	//��ʼ�����г�Ա
	memset(pq->eles, 0, (max_size+1)*sizeof(Type));
	pq->capacity = max_size;
	pq->size = 0;
	 
	return pq;
}

//�ж��Ƿ�Ϊ�� 
int is_empty(PriorityQueue *pq){
	if(pq == NULL)
		return 0;
	if(pq->size == 0)
		return 1;
	else
		return 0; 
}

//�ж��Ƿ�Ϊ��
int is_full(PriorityQueue *pq){
	if(pq == NULL)
		return 0;
	if(pq->size == pq->capacity)
		return 1;
	else
		return 0;
}

//����
int push(Type value, PriorityQueue *pq){
	int i=0;
	 
	//�����ж϶����Ƿ�Ϊ�� 
	if(is_full(pq)){
		printf("Queue is Full!\n");
		return 0;
	}
	printf("push %d\n", value);
	
	//�����λ��+1,��Ϊ������Ŀ�Ѩ�����Ͻ���Ѩ�븸�ڵ�Ƚϣ�����ȸ��ڵ�����Ѩ���� 
	for(i = pq->size+1; value > pq->eles[i/2] && i>1; i/=2){
		pq->eles[i] = pq->eles[i/2];
	} 
	pq->eles[i] = value; //��value�ŵ����Ŀ�Ѩ�� 
	pq->size ++;
	return 1;	
}
//������ֵ 
int find_max(PriorityQueue *pq, Type *value){
	if(is_empty(pq)){
		printf("Queue is empty\n");
		return 0;
	}
	*value = pq->eles[1];
	return 1;
}

//ɾ�� 
int pop(PriorityQueue *pq, Type *max){
	int i=1;
	int maxchild = 0;
	
	
	//�ж��Ƿ�Ϊ�� 
	if(is_empty(pq)){
		printf("Queue is empty!\n");
		return 0;
	}
	//�Ȱ����һ��Ԫ��ȡ���� 
	Type last;
	last = pq->eles[pq->size];
	
	//ȡ�����ֵ 
	*max = pq->eles[1];
	printf("Pop %d\n", pq->eles[1]);
	pq->size --;
	if(pq->size == 0){ //���ֻ��һ��Ԫ��
		pq->eles[i] = 0; //ɾ��֮���Ϊ0 
		return 1;	
	}
	
	//����һ��Ԫ����Ϊ��Ѩ������������ 
	for(i=1; i * 2 < pq->size; i = maxchild){
		maxchild = i * 2;
		//ѡ�����������е����ֵ 
		if(pq->eles[maxchild] < pq->eles[maxchild+1] && maxchild != pq->size)
			maxchild += 1;
		
		//���last�ȿ�Ѩ����Ԫ��С�����Ѩ��Ҫ����
		if(last < pq->eles[maxchild])	
			pq->eles[i] = pq->eles[maxchild];
		else
			break;
	} 
	pq->eles[i] = last;
	return 1;	 
} 

//�ݻ� 
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
	//��������Ϊ6�����ȶ��� 
	PriorityQueue *pq = init(6); //init�ڶ���ʱ������Ϊָ�룬����䷵��ֵ�Ǹ�ָ�룬ֱ�Ӹ��Ƹ�pq 
	
	int arr[]={3,4,7,5,8,2,9,10} ;
	int i = 0;
	
	//��ͼ�������6����Ԫ�أ��������Ԫ�ؽ��޷����� 
	for(i = 0; i<8; i++){
		push(arr[i], pq);
	} 
	
	//������������
	printf("the value of pq are: ") ;
	for(i=0; i<pq->size; i++){
		printf("%d ", pq->eles[i+1]); 
	}
	printf("\n");
	printf("pq size is %d\n", pq->size);
	
	Type max;
	int size = pq->size;
	//ÿ�δӶѶ�ȡԪ��
	for(i=0; i<size; i++){
		if(find_max(pq, &max)){
			printf("the max is %d\n", max);
			pop(pq, &max);
		}	
	}
	printf("new size is %d\n", pq->size) ;
	
	//���ٶ��� 
	destroy(pq);
	
	return 0;
}
