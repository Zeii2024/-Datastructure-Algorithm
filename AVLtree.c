/*
AVL������ƽ�������
һ���������������������������|�߶Ȳ�| <= 1 
�������������ͬ���ǣ��ڲ��룬ɾ�������󣬶���ƽ������Ĳ���
���µ���ƽ����AVL���ص㣬����4�������LL��RR��LR��RL. 
*/
#include <stdio.h>
#include <stdlib.h>
#define Type int 
#define MAX(a, b)  ((a) > (b) ? (a) : (b))        //�����ֵ 
#define HEIGHT(p)  ((p==NULL) ? 0 : (p->height))  //�ڵ�߶� 

typedef struct AVL{
	Type key;
	int height;
	struct AVL *lchild;
	struct AVL *rchild;
}AVL, *AVLtree; 

int tree_height(AVL *bt);
AVLtree LL_rotation(AVL *bt);
AVLtree RR_rotation(AVL *bt);
AVLtree LR_rotation(AVL *bt);
AVLtree RL_rotation(AVL *bt);
AVLtree search(AVL *bt, Type key);
void create(AVL **bt, Type *key, int n);
int insert(AVL **bt, Type key);
int delnode(AVL **bt, AVL **p);
int deltree(AVL **bt, Type key);
void inorder(AVL *bt);
int destroy(AVL **bt);

//���ĸ߶� 
int tree_height(AVL *bt){
	return HEIGHT(bt);
}

//��ת
//LL_rotation
AVLtree LL_rotation(AVL *bt){
	AVL *new_bt = NULL;
	
	new_bt = bt->lchild;
	bt->lchild = new_bt->rchild;
	new_bt->rchild = bt;
	
	bt->height = MAX(HEIGHT(bt->lchild), HEIGHT(bt->rchild)) + 1;
	new_bt->height = MAX(HEIGHT(new_bt->lchild), bt->height) + 1;
	
	return new_bt;
}

//RR_rotation
AVLtree RR_rotation(AVL *bt){
	AVL *new_bt = NULL;
	
	new_bt = bt->rchild;
	bt->rchild = new_bt->lchild;
	new_bt->lchild = bt;
	
	bt->height = MAX(HEIGHT(bt->lchild), HEIGHT(bt->rchild)) + 1;
	new_bt->height = MAX(HEIGHT(new_bt->rchild), bt->height) + 1;
	
	return new_bt;
}

//LR_rotation
AVLtree LR_rotation(AVL *bt){
	bt->lchild = RR_rotation(bt->lchild);
	return LL_rotation(bt);
}

//RL_rotation
AVLtree RL_rotation(AVL *bt){
	bt->rchild = LL_rotation(bt->rchild);
	return RR_rotation(bt);
}

//main���� 
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
	AVL *avltree = NULL;
	create(&avltree, key, n); 
	inorder(avltree);
	//����
	printf("����Ҫ���ҵ�Ԫ��:");
	scanf("%d", &search_key);
	AVL *search_result = NULL;
	search_result = search(avltree, search_key); 
	if(search_result)
		printf("�ҵ���Ԫ��%d,��ڵ�߶�Ϊ��%d\n", search_result->key, search_result->height);
	//���� 
	printf("����Ҫ�����Ԫ��:\n");
	scanf("%d", &num);
	insert(&avltree, num);
	inorder(avltree); 
	printf("���ĸ߶�Ϊ:%d\n", tree_height(avltree));
	//ɾ��
	printf("����Ҫɾ����Ԫ��:\n");
	scanf("%d", &del_key); 
	deltree(&avltree, del_key);	
	printf("���������\n");
	inorder(avltree);
	printf("���ĸ߶�Ϊ:%d\n", tree_height(avltree));
	//�ݻ� 
	printf("�ݻ���\n");
	destroy(&avltree);
}

//create
void create(AVL **bt, Type *key, int n){//����ָ�� 
	int i = 0;
	for(i; i<n; i++)
		insert(bt, key[i]);
}

//insert
int insert(AVL **bt, Type key){
	if(*bt == NULL){
		*bt = (AVL*)malloc(sizeof(AVL));
		if(*bt == NULL){
			printf("�����ڴ�ʧ�ܣ�\n");
			return 0;
		}
		(*bt)->key = key;
		printf("*bt->key = %d\n", (*bt)->key);
		(*bt)->lchild = (*bt)->rchild =NULL;
		(*bt)->height = 1;
	}
	else if(key < (*bt)->key){
		insert(&(*bt)->lchild, key);//�ݹ���룬��������ƽ�� 

		if(HEIGHT((*bt)->lchild) - HEIGHT((*bt)->rchild) == 2){//ͬ��Ҫ�ж����� 
			if(key < (*bt)->lchild->key){
				(*bt) = LL_rotation(*bt);
				printf("LL_rotation\n");
			}
				
			else{
				(*bt) = LR_rotation(*bt);
				printf("LR_rotation\n");
			}	
		}
	}
	else if(key > (*bt)->key){
		insert(&(*bt)->rchild, key);

		if(HEIGHT((*bt)->rchild) - HEIGHT((*bt)->lchild) == 2){
			if(key > (*bt)->rchild->key){
				(*bt) = RR_rotation(*bt);
				printf("RR_rotation\n");
			}	
			else{
				(*bt) = RL_rotation(*bt);
				printf("RL_rotation\n");
			}		
		}	
	}
	else{
		printf("%d�Ѵ��ڣ��޷����룡\n", key);
		return 0; 
	}
	//���½ڵ�߶ȷ������ 
	(*bt)->height = MAX(HEIGHT((*bt)->lchild), HEIGHT((*bt)->rchild)) + 1;
	return 1;	
}
//search
AVLtree search(AVL *bt, Type key){//�ݹ�����������ָ�� 
	if(bt){
		if(key == bt->key){
			return bt;
		}
		else if(key < bt->key)
			return search(bt->lchild, key);
		else
			return search(bt->rchild, key);
	}
	printf("δ�ҵ�%d!\n", key);
	return NULL;
}

//delnode
int delnode(AVL **bt, AVL **p){   //��ӵĲ�������ɾ�� 
	AVL *q, *s, *t;
	
	if(!(*bt) || !(*p)){
		printf("ɾ��ʧ��!\n");
		return 0;
	} 
	//����һϵ�еĲ�����ȻҪ��(*bt)������(*p)!!! ��Ϊpֻ��search���ص�ָ��,���ݲ�������Ҫ��bt                       
	else if((*p)->key == (*bt)->key){ //�ҵ���ɾ���ڵ��,ɾ��������BST������ͬ                
		if(!(*bt)->lchild && !(*bt)->rchild){//����������Ϊ��                            
			*bt = NULL;                                                                  
		}                                                                                
		else if(!(*bt)->lchild){//������Ϊ��                                             
			q = *bt;                                                           //1.ɾ���ڵ㣬p->key = bt->keyʱ����Ϊ������������Ϊ�գ�������Ϊ���������    
			*bt = (*bt)->rchild;                                               //2.��������������ʱ���������������ҵ�s,��ֵ��bt��Ȼ��delete s.������ƽ�ⲻ�����
			free(q);		                                                   //3.������Ϊ��ʱ��������ֱ���滻s���ɡ�����ʱ�ض�������p->key != bt->key,ƽ�����֮��õ�����
		}                                                                      //4.��p->key < bt->keyʱ���ݹ����������ɾ����Ȼ��Ƚ�bt�����������߶ȣ������е���
		else if(!(*bt)->rchild){//������Ϊ��                                   //5.����ʱ��Ҫ��t = bt->lchild, �Ƚ�t�����������߶�(�����Ƚ�����),��ȷ�������ṹ��ѡ�������ʽ
			q = *bt;                                                           //6.��p->key > bt->keyʱ��ͬ��
			*bt = (*bt)->lchild;                                               //7.ɾ���ڵ��Ҫ�ǵø��½ڵ�ĸ߶ȣ���Ϊ4-6���Ĳ����п���û�о���
			free(q);
		}
		else{//������������Ϊ�� ����Ҫһֱ������������s���Ƚ����������ĸ߶ȣ��ӽϸߵ���������s��Ȼ���Ƹ�bt���ٰ�sɾ�� 
			if(HEIGHT((*bt)->lchild) > HEIGHT((*bt)->rchild)){//�������ĺô��ǣ�ɾ��s�󣬲���Ҫ���������Ա���ƽ�� ��������ɾ������Ҫ�ݹ�һ�� 
				q = *bt;
				s = (*bt)->lchild;
			
				while(s->rchild){
					q = s;
					s = s->rchild;
				}
				(*bt)->key = s->key;//��s��ֵ����bt�� 
				delnode(&(*bt)->lchild, &s);	//Ȼ��ɾ����s 
			}
			else{
				q = *bt;
				s = (*bt)->rchild;
				
				while(s->lchild){
					q = s;
					s = s->lchild;
				}
				(*bt)->key = s->key;//��s��ֵ����bt�� 
				delnode(&(*bt)->rchild, &s);	
			}
			
			(*bt)->height = MAX(HEIGHT((*bt)->lchild), HEIGHT((*bt)->rchild));//��ɾ���ڵ�󣬲�Ҫ���˸��½��ĸ߶ȣ���Ϊ����������֧����û�о���			
		}
		
	}
	else if((*p)->key < (*bt)->key){ //Ҫɾ���Ľڵ��������� ,ɾ����Ҫ����ƽ�� 
		delnode(&(*bt)->lchild, p);//�������õݹ����ɾ��
		(*bt)->height = MAX(HEIGHT((*bt)->lchild), HEIGHT((*bt)->rchild)) + 1; //Ҫ�ǵø��½ڵ�ĸ߶� 
		if(HEIGHT((*bt)->rchild) - HEIGHT((*bt)->lchild) == 2){
			t = (*bt)->rchild;
			if(HEIGHT(t->lchild) < HEIGHT(t->rchild)){//ע�⣬Ҫ�ж���������������߶Ȳ� ���Ա�ȷ�������ת 
				(*bt) = RR_rotation(*bt);
				printf("RR_rotation\n");
			}	
			else{
				(*bt) = RL_rotation(*bt);
				printf("RL_rotation\n");
			}		
		}
	}		
	else{//Ҫɾ���Ľڵ���������
		delnode(&(*bt)->rchild, p);
		(*bt)->height = MAX(HEIGHT((*bt)->lchild), HEIGHT((*bt)->rchild)) + 1; //Ҫ�ǵø��½ڵ�ĸ߶�
		if(HEIGHT((*bt)->lchild) - HEIGHT((*bt)->rchild) == 2){
			t = (*bt)->lchild;
			if(HEIGHT(t->lchild) > HEIGHT(t->rchild)){ //�ж����� 
				(*bt) = LL_rotation(*bt);
				printf("LL_rotation\n");
			}	
			else{
				(*bt) = LR_rotation(*bt);
				printf("LR_rotation\n");
			}		
		}
	} 	
	return 1;
}

//deltree
int deltree(AVL **bt, Type key){
	AVL *p;
	p = search((*bt), key);
	if(p){    //��ȷ��key���ڣ���ִ��ɾ�� 
		printf("p->key = %d\n", p->key);
		if(delnode(&(*bt), &p)){
			printf("��ɾ��:%d\n", key);
			return 1;
		}
	}
	else
		return 0;
}

//destroy
int destroy(AVL **bt){
	while(*bt){
		deltree(&(*bt), (*bt)->key);
		inorder(*bt);
	}
	if(*bt == NULL){
		printf("���ѿգ�\n");
		return 1;
	}
	return 0;
}

//inorder
void inorder(AVL *bt){
	if(bt){
		inorder(bt->lchild);
		printf("%d\n", bt->key);
		inorder(bt->rchild);
	}
}
