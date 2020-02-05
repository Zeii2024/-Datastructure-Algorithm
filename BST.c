#include <stdio.h>
#include <stdlib.h>
/*
BST ����������
a. ���k��������������㣬��С�ڵ��ڽ��k
b. ���k��������������㣬�����ڵ��ڽ��k
c. k������Ҳ���Ƕ������������ݹ飩

BST�����������Ϊ�����������
������⣺https://editor.csdn.net/md/?articleId=101167476 
*/ 
/*
��ָ�봫�ݸ����������ں������޸�ָ���ֵ
Ҫ�������е�ָ�붨��Ϊ����ָ��
���ú���ʱ�� ָ��ǰ��ȡַ��&
�����е�*p�� ��Ϊ����ǰ��bt,
�����е�**p, ��Ϊ����ǰ��*bt. 
*/ 
typedef struct BST{
	int key;
	struct BST *lchild;
	struct BST *rchild;
}BST;

void create(BST **bst, int *key, int n);
int insert(BST **bt, int key);
void inorder(BST *bt);
BST *search(BST *bt, int key);  //search��Ҫһ��ָ��͹��ˣ�����Ҫ��������ָ�����ݽ����޸� 
int delnode(BST **p);
int del(BST **bt, int key);
int destroy(BST *bst); 

int main(void){
	int *key;
	
	int n, i=0;
	int num, search_key, del_key;
	printf("����n��\n");
	scanf("%d", &n);
	key = (int *)malloc(sizeof(int)*n);
	printf("��������:\n");
	for(i=0; i<n; i++){
		scanf("%d", &key[i]);
	}
	//���� 
	BST *bst = NULL;
	create(&bst, key, n);//������鴫��ָ�뼴��
	//������� 
	printf("���������\n");
	inorder(bst);
	//����Ԫ�� 
	printf("�������Ԫ��:\n");
	scanf("%d", &num);
	insert(&bst, num);
	printf("���������\n");
	inorder(bst);
	//����Ԫ�� 
	printf("�������Ԫ�أ�\n");
	scanf("%d", &search_key);
	BST *result = NULL;
	result = search(bst, search_key); //����ֵ��btָ�� 
	if(result)
		printf("����Ԫ�ص�ָ���ǣ�result->key = %d\n", result->key); //�����result��ΪBSTָ�� 
	//ɾ��Ԫ��
	printf("����Ҫɾ����Ԫ�أ�\n");
	scanf("%d", &del_key); 
	del(&bst, del_key);
	printf("���������\n");
	inorder(bst);
	//�ݻ�,�ݻٺ�Ҫ��ʹ�ñ����ؽ�bst 
	printf("�ݻ���\n");
	destroy(bst);
	//printf("*bst = %d\n", *bst);
	
	return 0;
}

//���� 
void create(BST **bst, int *key, int n){
	int i=0;
	for(i=0; i<n; i++){
		insert(bst, key[i]);	
	}
}

//���� 
int insert(BST **bt, int key){
	if(*bt == NULL){
		*bt = (BST*)malloc(sizeof(BST));
		if(*bt == NULL){
			printf("�����ڴ�ʧ��\n");
			return 0;
		}
		(*bt)->key = key;
		(*bt)->lchild = (*bt)->rchild = NULL;
		//printf("(*bt)->key=%d\n",(*bt)->key);
		return 1;
	}
	if(key == (*bt)->key){//����Ѵ��ڣ������ʧ�� 
		printf("%d�Ѵ��ڣ�\n", key);
		return 0;
	}
	else if(key < (*bt)->key)
		insert(&(*bt)->lchild, key);
	else
		insert(&(*bt)->rchild, key);	
	return 0;
}

//����   ����ָ�룬����ֵ��BSTָ�� 
BST *search(BST *bt, int key){
	if(bt == NULL){
		printf("����ʧ�ܣ�\n");
		return bt;
	}
	else{
		if(bt->key == key){
			return bt;
		}
		else if(key < bt->key)
			return search(bt->lchild, key);	
		else
			return search(bt->rchild, key);
	}	 
}

//ɾ���ڵ� 
int delnode(BST **p){
	//ɾ���ڵ���4�����
	BST *s, *q;
		
	if((*p)->lchild == NULL && (*p)->rchild == NULL){ //����������Ϊ��!!!!!!!!
		*p = NULL;  //����ָ���£�����ֱ����*p = NULL 
		return 1; 	
	}
	else if(!(*p)->lchild){//������Ϊ�� 
		q = *p;  //��qָ��p����������Ȼ���p��������Ų��p��λ�� 
		*p = (*p)->rchild; //����ط�Ҫ��ָ�������������ŵ�p�ĵ�ַ�� 
		free(q); //������qҪfree�� 
		return 1;
	}
	else if(!(*p)->rchild){//������Ϊ�� 
		q = *p;
		*p = (*p)->lchild;
		free(q);
		return 1;	
	}
	else{   //������������Ϊ�� 
		s = (*p)->lchild;
		q = *p;
		while(s->rchild){ //�ҵ����������p��ֱ��ǰ�� 
			q = s;
			s = s->rchild;
		}
		(*p)->key = s->key;  //��ǰ����ֵ��ֵ��p
	
		if(q != (*p))//���q = *p����whileûִ�У���p->lchild = s 
			q->rchild = s->lchild; //Ҷ�ӽڵ��ÿգ�����ʹ�丸�ڵ�ָ��գ�����ֱ�Ӷ�Ҷ�ӽ����� 
		else //���q = s 
			q->lchild = s->lchild;//q�����ڣ�p->lchild��Ϊs 
			
		free(s);			
	} 
	return 1;
} 

//ɾ��
int del(BST **bt, int key){
	if(*bt == NULL){
		printf("δ�ҵ�%d\n", key);
		return 0;
	}	
	if((*bt)->key == key){
		if(delnode(&(*bt)))
			printf("��ɾ��%d\n", key);
		return 1;
	}
	else if((*bt)->key > key)
		return del(&(*bt)->lchild, key);//��Ϊbt�е�ֵҪ�ı䣬����������봫��ʵֵ������Ϊ����ָ�� 
	else
		return del(&(*bt)->rchild, key);
	
}
 
//�ݻ���
int destroy(BST *bst){
	if(bst == NULL){
		printf("��Ϊ�գ�\n");
		return 0;
	}
	while(bst){
		del(&bst, bst->key);	
	}
	free(bst);
	printf("���Ѵݻ٣�\n");
	return 1;
}

//�������
void inorder(BST *bt){
	if(bt!=NULL){
		inorder(bt->lchild);
		printf("%d\n",bt->key);
		inorder(bt->rchild);
	}
}
