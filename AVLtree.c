/*
AVL树，自平衡二叉树
一颗排序二叉树，满足左右子树的|高度差| <= 1 
与排序二叉树不同的是，在插入，删除操作后，多了平衡调整的步骤
重新调整平衡是AVL的重点，共有4种情况：LL，RR，LR，RL. 
*/
#include <stdio.h>
#include <stdlib.h>
#define Type int 
#define MAX(a, b)  ((a) > (b) ? (a) : (b))        //求最大值 
#define HEIGHT(p)  ((p==NULL) ? 0 : (p->height))  //节点高度 

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

//树的高度 
int tree_height(AVL *bt){
	return HEIGHT(bt);
}

//旋转
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

//main测试 
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
	AVL *avltree = NULL;
	create(&avltree, key, n); 
	inorder(avltree);
	//查找
	printf("输入要查找的元素:");
	scanf("%d", &search_key);
	AVL *search_result = NULL;
	search_result = search(avltree, search_key); 
	if(search_result)
		printf("找到了元素%d,其节点高度为：%d\n", search_result->key, search_result->height);
	//插入 
	printf("输入要插入的元素:\n");
	scanf("%d", &num);
	insert(&avltree, num);
	inorder(avltree); 
	printf("树的高度为:%d\n", tree_height(avltree));
	//删除
	printf("输入要删除的元素:\n");
	scanf("%d", &del_key); 
	deltree(&avltree, del_key);	
	printf("中序遍历：\n");
	inorder(avltree);
	printf("树的高度为:%d\n", tree_height(avltree));
	//摧毁 
	printf("摧毁树\n");
	destroy(&avltree);
}

//create
void create(AVL **bt, Type *key, int n){//二级指针 
	int i = 0;
	for(i; i<n; i++)
		insert(bt, key[i]);
}

//insert
int insert(AVL **bt, Type key){
	if(*bt == NULL){
		*bt = (AVL*)malloc(sizeof(AVL));
		if(*bt == NULL){
			printf("分配内存失败！\n");
			return 0;
		}
		(*bt)->key = key;
		printf("*bt->key = %d\n", (*bt)->key);
		(*bt)->lchild = (*bt)->rchild =NULL;
		(*bt)->height = 1;
	}
	else if(key < (*bt)->key){
		insert(&(*bt)->lchild, key);//递归插入，插入后调整平衡 

		if(HEIGHT((*bt)->lchild) - HEIGHT((*bt)->rchild) == 2){//同样要判断两层 
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
		printf("%d已存在，无法插入！\n", key);
		return 0; 
	}
	//更新节点高度放在最后 
	(*bt)->height = MAX(HEIGHT((*bt)->lchild), HEIGHT((*bt)->rchild)) + 1;
	return 1;	
}
//search
AVLtree search(AVL *bt, Type key){//递归搜索，返回指针 
	if(bt){
		if(key == bt->key){
			return bt;
		}
		else if(key < bt->key)
			return search(bt->lchild, key);
		else
			return search(bt->rchild, key);
	}
	printf("未找到%d!\n", key);
	return NULL;
}

//delnode
int delnode(AVL **bt, AVL **p){   //最复杂的操作仍是删除 
	AVL *q, *s, *t;
	
	if(!(*bt) || !(*p)){
		printf("删除失败!\n");
		return 0;
	} 
	//这里一系列的操作仍然要用(*bt)不能用(*p)!!! 因为p只是search返回的指针,内容操作还是要用bt                       
	else if((*p)->key == (*bt)->key){ //找到待删除节点后,删除操作和BST基本相同                
		if(!(*bt)->lchild && !(*bt)->rchild){//左右子树都为空                            
			*bt = NULL;                                                                  
		}                                                                                
		else if(!(*bt)->lchild){//左子树为空                                             
			q = *bt;                                                           //1.删除节点，p->key = bt->key时，分为左右子树都不为空，和子树为空两种情况    
			*bt = (*bt)->rchild;                                               //2.左右子树都不空时，从左右子树中找到s,赋值给bt，然后delete s.树保持平衡不需调整
			free(q);		                                                   //3.子树不为空时，将子树直接替换s即可。而此时必定经过了p->key != bt->key,平衡会在之后得到调整
		}                                                                      //4.当p->key < bt->key时，递归从左子树中删除，然后比较bt的左右子树高度，并进行调整
		else if(!(*bt)->rchild){//右子树为空                                   //5.调整时，要另t = bt->lchild, 比较t的左右子树高度(即共比较两层),以确定子树结构，选择调整方式
			q = *bt;                                                           //6.当p->key > bt->key时，同理
			*bt = (*bt)->lchild;                                               //7.删除节点后，要记得更新节点的高度，因为4-6步的操作有可能没有经过
			free(q);
		}
		else{//左右子树都不为空 ，不要一直从左子树中找s，比较两个子树的高度，从较高的子树中找s，然后复制给bt，再把s删掉 
			if(HEIGHT((*bt)->lchild) > HEIGHT((*bt)->rchild)){//这样做的好处是，删除s后，不需要调整，树仍保持平衡 ，代价是删除操作要递归一次 
				q = *bt;
				s = (*bt)->lchild;
			
				while(s->rchild){
					q = s;
					s = s->rchild;
				}
				(*bt)->key = s->key;//将s的值赋给bt， 
				delnode(&(*bt)->lchild, &s);	//然后删除掉s 
			}
			else{
				q = *bt;
				s = (*bt)->rchild;
				
				while(s->lchild){
					q = s;
					s = s->lchild;
				}
				(*bt)->key = s->key;//将s的值赋给bt， 
				delnode(&(*bt)->rchild, &s);	
			}
			
			(*bt)->height = MAX(HEIGHT((*bt)->lchild), HEIGHT((*bt)->rchild));//在删除节点后，不要忘了更新结点的高度，因为下面两个分支可能没有经过			
		}
		
	}
	else if((*p)->key < (*bt)->key){ //要删除的节点在左子树 ,删除后要重新平衡 
		delnode(&(*bt)->lchild, p);//这里利用递归进行删除
		(*bt)->height = MAX(HEIGHT((*bt)->lchild), HEIGHT((*bt)->rchild)) + 1; //要记得更新节点的高度 
		if(HEIGHT((*bt)->rchild) - HEIGHT((*bt)->lchild) == 2){
			t = (*bt)->rchild;
			if(HEIGHT(t->lchild) < HEIGHT(t->rchild)){//注意，要判断两层的左右子树高度差 ，以便确定如何旋转 
				(*bt) = RR_rotation(*bt);
				printf("RR_rotation\n");
			}	
			else{
				(*bt) = RL_rotation(*bt);
				printf("RL_rotation\n");
			}		
		}
	}		
	else{//要删除的节点在右子树
		delnode(&(*bt)->rchild, p);
		(*bt)->height = MAX(HEIGHT((*bt)->lchild), HEIGHT((*bt)->rchild)) + 1; //要记得更新节点的高度
		if(HEIGHT((*bt)->lchild) - HEIGHT((*bt)->rchild) == 2){
			t = (*bt)->lchild;
			if(HEIGHT(t->lchild) > HEIGHT(t->rchild)){ //判断两层 
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
	if(p){    //先确定key存在，再执行删除 
		printf("p->key = %d\n", p->key);
		if(delnode(&(*bt), &p)){
			printf("已删除:%d\n", key);
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
		printf("树已空！\n");
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
