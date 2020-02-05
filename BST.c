#include <stdio.h>
#include <stdlib.h>
/*
BST 二叉排序树
a. 结点k的所有左子树结点，都小于等于结点k
b. 结点k的所有右子树结点，都大于等于结点k
c. k的子树也都是二叉排序树（递归）

BST的中序遍历即为有序递增序列
博客详解：https://editor.csdn.net/md/?articleId=101167476 
*/ 
/*
将指针传递给函数，并在函数中修改指针的值
要将函数中的指针定义为二级指针
调用函数时， 指针前加取址符&
函数中的*p， 即为调用前的bt,
函数中的**p, 即为调用前的*bt. 
*/ 
typedef struct BST{
	int key;
	struct BST *lchild;
	struct BST *rchild;
}BST;

void create(BST **bst, int *key, int n);
int insert(BST **bt, int key);
void inorder(BST *bt);
BST *search(BST *bt, int key);  //search需要一级指针就够了，不需要对最外层的指针内容进行修改 
int delnode(BST **p);
int del(BST **bt, int key);
int destroy(BST *bst); 

int main(void){
	int *key;
	
	int n, i=0;
	int num, search_key, del_key;
	printf("输入n：\n");
	scanf("%d", &n);
	key = (int *)malloc(sizeof(int)*n);
	printf("输入数字:\n");
	for(i=0; i<n; i++){
		scanf("%d", &key[i]);
	}
	//创建 
	BST *bst = NULL;
	create(&bst, key, n);//这个数组传入指针即可
	//中序遍历 
	printf("中序遍历：\n");
	inorder(bst);
	//插入元素 
	printf("输入插入元素:\n");
	scanf("%d", &num);
	insert(&bst, num);
	printf("中序遍历：\n");
	inorder(bst);
	//查找元素 
	printf("输入查找元素：\n");
	scanf("%d", &search_key);
	BST *result = NULL;
	result = search(bst, search_key); //返回值是bt指针 
	if(result)
		printf("查找元素的指针是：result->key = %d\n", result->key); //这里的result即为BST指针 
	//删除元素
	printf("输入要删除的元素：\n");
	scanf("%d", &del_key); 
	del(&bst, del_key);
	printf("中序遍历：\n");
	inorder(bst);
	//摧毁,摧毁后要想使用必须重建bst 
	printf("摧毁树\n");
	destroy(bst);
	//printf("*bst = %d\n", *bst);
	
	return 0;
}

//创建 
void create(BST **bst, int *key, int n){
	int i=0;
	for(i=0; i<n; i++){
		insert(bst, key[i]);	
	}
}

//插入 
int insert(BST **bt, int key){
	if(*bt == NULL){
		*bt = (BST*)malloc(sizeof(BST));
		if(*bt == NULL){
			printf("分配内存失败\n");
			return 0;
		}
		(*bt)->key = key;
		(*bt)->lchild = (*bt)->rchild = NULL;
		//printf("(*bt)->key=%d\n",(*bt)->key);
		return 1;
	}
	if(key == (*bt)->key){//如果已存在，则插入失败 
		printf("%d已存在！\n", key);
		return 0;
	}
	else if(key < (*bt)->key)
		insert(&(*bt)->lchild, key);
	else
		insert(&(*bt)->rchild, key);	
	return 0;
}

//查找   函数指针，返回值是BST指针 
BST *search(BST *bt, int key){
	if(bt == NULL){
		printf("查找失败！\n");
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

//删除节点 
int delnode(BST **p){
	//删除节点有4种情况
	BST *s, *q;
		
	if((*p)->lchild == NULL && (*p)->rchild == NULL){ //左右子树都为空!!!!!!!!
		*p = NULL;  //二级指针下，可以直接令*p = NULL 
		return 1; 	
	}
	else if(!(*p)->lchild){//左子树为空 
		q = *p;  //让q指向p的右子树，然后把p的右子树挪到p的位置 
		*p = (*p)->rchild; //这个地方要用指针把右子树整体放到p的地址内 
		free(q); //最后这个q要free掉 
		return 1;
	}
	else if(!(*p)->rchild){//右子树为空 
		q = *p;
		*p = (*p)->lchild;
		free(q);
		return 1;	
	}
	else{   //左右子树都不为空 
		s = (*p)->lchild;
		q = *p;
		while(s->rchild){ //找到中序遍历中p的直接前驱 
			q = s;
			s = s->rchild;
		}
		(*p)->key = s->key;  //把前驱的值赋值给p
	
		if(q != (*p))//如果q = *p，则while没执行，即p->lchild = s 
			q->rchild = s->lchild; //叶子节点置空，必须使其父节点指向空，不能直接对叶子结点操作 
		else //如果q = s 
			q->lchild = s->lchild;//q不存在，p->lchild即为s 
			
		free(s);			
	} 
	return 1;
} 

//删除
int del(BST **bt, int key){
	if(*bt == NULL){
		printf("未找到%d\n", key);
		return 0;
	}	
	if((*bt)->key == key){
		if(delnode(&(*bt)))
			printf("已删除%d\n", key);
		return 1;
	}
	else if((*bt)->key > key)
		return del(&(*bt)->lchild, key);//因为bt中的值要改变，所以这里必须传入实值，定义为二级指针 
	else
		return del(&(*bt)->rchild, key);
	
}
 
//摧毁树
int destroy(BST *bst){
	if(bst == NULL){
		printf("树为空！\n");
		return 0;
	}
	while(bst){
		del(&bst, bst->key);	
	}
	free(bst);
	printf("树已摧毁！\n");
	return 1;
}

//中序遍历
void inorder(BST *bt){
	if(bt!=NULL){
		inorder(bt->lchild);
		printf("%d\n",bt->key);
		inorder(bt->rchild);
	}
}
