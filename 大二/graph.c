#include <stdio.h>
#include <stdlib.h>

struct Edge{
	char AdjV;
	double Weight;
	struct Edge* Next;
};

struct Node{
	char Vertex;
    struct Edge* FirstEdge;
};

struct Graph{
	int n,e;
	struct Node* head;
};

void creatGraph(struct Graph* ggg){
	int i=0;
	char temp;
	struct Edge* eee=NULL,*pe=NULL;
	struct Node* p=NULL;
	
	printf("Please input the num of node and edge:");
	scanf("%d%d",&ggg->n,&ggg->e);
	ggg->head=(Node*)malloc(ggg->n*sizeof(Node));
	printf("Please input the name of node:\n");
	for (;i<ggg->n;i++){
		getchar();
		scanf("%c",&(ggg->head[i].Vertex));
		ggg->head[i].FirstEdge=NULL;
	}
	printf("Please input the tail/head/weight of edge:\n");
	for (i=0;i<ggg->e;i++){
		eee=(Edge*)malloc(sizeof(Edge));
		eee->Next=NULL;
		getchar();
		scanf("%c,%c,%lf",&temp,&eee->AdjV,&eee->Weight);
		for(p=ggg->head;p->Vertex!=temp;p++);
		if(p->FirstEdge==NULL)p->FirstEdge=eee;
		else{
			for(pe=p->FirstEdge;pe->Next!=NULL;pe=pe->Next);
			pe->Next=eee;
		}
	}
}
void printGraph(struct Graph* ggg){
	int i=0;
	struct Edge *pe=NULL;
	for (;i<ggg->n;i++){
		printf("%c",ggg->head[i].Vertex);
		for(pe=ggg->head[i].FirstEdge;pe!=NULL;pe=pe->Next)
			printf("->%c,%lf",pe->AdjV,pe->Weight);
		printf("\n");
	}
}

int main(){
	struct Graph ggg;
	creatGraph(&ggg);
	printGraph(&ggg);
	return 0;
}