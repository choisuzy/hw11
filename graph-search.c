#include<stdio.h>
#include<stdlib.h>

#define MAX_VERTEX 10 /* 최대 Vertex의 수를 10으로 정의함 */
#define FALSE 0
#define TRUE 1

typedef struct graphnode {  /* struct graphnode에 타입이 다른 데이터들을 그룹화 */
	int vertex;	/* vertex를 int형으로 선언, vertex는 정점임, 데이터 필드 */
	struct graphnode* link;	/* 구조체 graphnode포인터 link를 선언, 링크 필드 */
}graphnode; /* 구조체 호출용 이름 */

typedef struct graphtype { /* struct graphtype에 타입이 다른 데이터들을 그룹화 */
	int n;	/* n을 int형으로 선언, 그래프정점의 갯수 */
	graphnode* adjpointer[MAX_VERTEX]; /* 인접하는 헤드포인터들의 배열 */
    int visited[MAX_VERTEX];  /* 방문 플래그 표시를 위한 배열*/
}graphtype; /* 구조체 호출용 이름 */

typedef struct stacknode{ /* struct stacknode에 타입이 다른 데이터들을 그룹화 */
   int data; /* data를 int형으로 선언*/
   struct stacknode* link; /* 구조체 stacknode포인터 link를 선언, 링크 필드 */
} stacknode; /* 구조체 호출용 이름 */

stacknode* top;

typedef struct queuenode{
   int data;
   struct queuenode* link;
} queuenode; /* 구조체 호출용 이름 */

typedef struct queuetype {
   struct queuenode* front,* rear;
} queuetype; /* 구조체 호출용 이름 */

void InitializeGraph(graphtype* g); /* 그래프를 초기화하는 함수 선언 */
void InsertVertex(graphtype* g, int h); /* 그래프에 정점을 삽입하는 함수 선언 */
void InsertEdge(graphtype* g, int t, int h); /* 그래프에 간선을 삽입하는 함수 선언 */
int isEmpty(); /* 스택이 비었는지 확인하는 함수 선언 */
void push(int e); /* 스택에 push하는 함수 선언 */
int pop(); /* 스택에 pop하는 함수 선언 */
void DepthFirstSearch(graphtype* g, int h); /* 깊이우선탐색을 하는 함수 선언 */
queuetype* initQueue();
int isQueueEmpty();
void enQueue(queuetype* q, int item);
int deQueue(queuetype* q);
void BreathFirstSearch(graphtype* g, int h); /* 넓이우선탐색을 하는 함수 선언 */
void PrintGraph(graphtype* g); /*인접리스트의 포인터배열의 첫번째부터 인접한 정점들을 출력하는 함수 선언 */
void FreeGraph(graphtype* g); /* 그래프에 할당된 메모리를 free시키는 함수 선언 */

int main(){

    printf("[----- [Choi Suzy]  [2021024135] -----]\n");
    
    char command; /* command 선언 */
    graphtype* g = (graphtype*)malloc(sizeof(graphtype)); /* graphtype크기만큼을 동적할당한 graphtype포인터를 graphtype포인터 G에 넣음 */

    do{
        printf("\n");
		printf("----------------------------------------------------------------\n"); /* print */
		printf("                       Graph Searches                           \n"); /* print */
		printf("----------------------------------------------------------------\n"); /* print */
		printf(" Initialize Graph      = z                     \n"); /* print */
		printf(" Insert Vertex         = v       Insert Edge           = e \n"); /* print */
		printf(" Depth First Search    = d       Breath First Search   = b\n"); /* print */
		printf(" Print Graph           = p       Quit                  = q\n"); /* print */
		printf("----------------------------------------------------------------\n"); /* print */

		printf("Command = "); /* print */
		scanf(" %c", &command); /* char형 command를 입력자에게 입력받음 */

		switch(command) { /* command가 ~이면 조건문 */ 
		case 'z': case 'Z': /* command가 z나 Z면 */
			InitializeGraph(g); /* InitializeGraph 함수 호출 */
			break; /* 조건식을 빠져나옴 */
		case 'v': case 'V': /* command가 v나 V이면 */
			for (int data = 0; data < MAX_VERTEX; data++) /* for문을 MAX_VERTEX만큼 돌며 해당 데이터의 정점을 삽입*/
            InsertVertex(g, data);
			break; /* 조건식을 빠져나옴 */
		case 'e': case 'E': /* command가 e나 E면 */
            int num;
            printf("input edge num : ");
            scanf("%d", &num);

            if (num > MAX_VERTEX*(MAX_VERTEX-1)/2)  /* 간선의 개수가 최대간선수보다 큰 경우에는 break */
            break;

            for (int i = 0; i < num; i++) { /*for문을 Num만큼 돌며 무방향 그래프의 간선을 해당 정점에 부속시킴*/
                int x, y; // 꼬리정점 x, 머리정점 y
                printf("input vertex(x,y) : ");
                scanf("%d %d", &x, &y);

                // 무방향 그래프 간선 삽입
                InsertEdge(g, x, y);
                InsertEdge(g, y, x);
            }
			break; /* 조건식을 빠져나옴 */
		case 'd': case 'D': /* command가 d나 D이면 */
            int dv; // 탐색을 시작할 정점
            printf("input vertex: ");
            scanf("%d", &dv);
			DepthFirstSearch(g, dv);
            printf("\n");
			break; /* 조건식을 빠져나옴 */
		case 'b': case 'B': /* command가 b나 B이면 */
            int bv; // 탐색을 시작할 정점
            printf("input vertex: ");
            scanf("%d", &bv);
			BreathFirstSearch(g, bv);
			break; /* 조건식을 빠져나옴 */
		case 'p': case 'P': /* command가 p나 P이면 */
			PrintGraph(g);
			break; /* 조건식을 빠져나옴 */
		case 'q': case 'Q': /* command가 q나 Q이면 */
			FreeGraph(g); /* FreeGraph함수 호출 */ 
			break; /* 조건식을 빠져나옴 */
		default: /* 위의 알파벳이 다 아니면 */
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); /* print */
			break; /* 조건식을 빠져나옴 */
		}

	}while(command != 'q' && command != 'Q'); /* command가 q가 아니고 Q가 아니라면 do루프 계속 돎 */

	return 1; /* 1을 반환함 */
}

void InitializeGraph(graphtype* g){ /* 그래프를 초기화하는 함수 정의 */
    int h; /* h를 정수형으로 선언 */
    g->n = 0; /* 그래프의 정점 수를 0으로 초기화시킴 */
    for(h =0; h<MAX_VERTEX; h++){ /* MAX_VERTEX번 for문 돎 */
        g->adjpointer[h] = NULL; /* 인접하는 그래프 배열을 빈공간으로 초기화시킴 */
    }
}

void InsertVertex(graphtype* g, int h){ /* 그래프에 정점을 삽입하는 함수 정의 */
    if (g->n + 1 > MAX_VERTEX) { /* 그래프가 정점개수를 초과하였을 때 */
		return; /* 0 반환함 */
	}
	g->n++; /* 그래프 정점의 개수 하나 증가시킴 */
}

void InsertEdge(graphtype* g, int t, int h){ /* 그래프에 간선을 삽입하는 함수 정의 */
    if(t >= g->n || h>= g->n){ /* 정점 t가 그래프 정점의 개수이상이거나 정점 h가 그래프 정점의 개수 이상일 때*/
        printf("error \n"); /* print */
        return; /* 0을 반환함 */
    }

    graphnode* node = (graphnode*)malloc (sizeof(graphnode)); /* 삽입할 노드를 동적할당으로 생성함 */
    node -> vertex = h; /* node의 vertex부분에 h를 넣음 */
    node -> link = NULL; /* node의 link부분을 빈공간으로 만듦 */

    if(g -> adjpointer[h] == NULL){ /* g의 adjpointer가 빈공간이라면 */
        g -> adjpointer[h] = node; /* g의 adjpointer에 node를 넣음 */
        return; /* 0을 반환함 */
    }

    graphnode* c = g -> adjpointer[h]; /* graphnode포인터 c에 g의 adjpointer를 넣음 */
    graphnode* p = g -> adjpointer[h]; /* graphnode포인터 p에 g의 adjpointer를 넣음 */

    while(c != NULL){ /* c가 빈공간이 아니라면 while문 계속 돎 */
        if(c->vertex > t){ /* c의 vertex가 t보다 크다면 */
            if (c == g->adjpointer[h]){ /* 처음 노드앞에 삽입해야 할 경우 */
                node->link = g->adjpointer[h]; /* node의 link에 g의 adjpointer를 넣음 */
                g->adjpointer[h] = node; /* g의 adjpointer에 node를 넣음 */
            }
            else {  /* 중간이거나 마지막에 삽입해야 할 경우 */
            node->link = c; /* node의 link에 c를 넣음 */
            p->link = node; /* p의 link에 node를 넣음 */
            }
        return; /* 0을 반환함 */
        }
        p = c; /* p에 c를 넣음 */
        c = c->link; /* c에 c의 link를 넣음 */
    }
}

int isEmpty() { /* 스택이 비었는지 확인하는 함수 정의 */
	if (top == NULL) { /* top이 빈공간이라면 */
		return 1; /* 1을 반환함 */
	}
	else return 0; /* top이 빈공간이 아니라면 0을 반환함 */
}

void push(int e) { /* 스택에 push하는 함수 정의 */
	stacknode* temp = (stacknode*)malloc(sizeof(stacknode)); /* stacknode크기만큼을 동적할당한 stacknode포인터를 stacknode포인터 temp에 넣음 */

	temp->data = e; /* temp의 data에 e를 넣음 */
	temp->link = top; /* temp의 link에 top을 넣음 */
	top = temp; /* top에 temp를 넣음 */
}

int pop() { /* 스택에 pop하는 함수 정의 */
	int e; /* e를 정수형으로 선언 */
	stacknode* temp = top; /* stacknode포인터 temp에 top을 넣음 */

	if (top == NULL) { /* top이 빈공간이라면 */
		return 0; /* 0을 반홤함 */
	}
	else {  /* top이 빈공간이 아니라면 */
		e = temp->data; /* e에 temp의 data를 넣음 */
        top = temp->link; /* top에 temp의 link를 넣음 */
		free(temp); /* temp를 free시킴 */
		return e; /* e를 반환함 */
	}
}

void DepthFirstSearch(graphtype* g, int h){
    graphnode* b;  
    top = NULL;
    push(h);

    g->visited[h] = TRUE;
    printf(" %d", h);

    while(!isEmpty()) {
        b = g->adjpointer[h];
        while(b) {
        if (!g->visited[b->vertex]) {
            push(b->vertex);
            g->visited[b->vertex] = TRUE;
            printf(" %d", b->vertex);
            h = b->vertex;
            b = g->adjpointer[h];
         }
         else b = b->link;
      }
      h = pop();
   }
}

queuetype* initQueue(){ /* queue를 초기화하는 함수 정의 */
   queuetype* q; /* queuetype 포인터 q선언 */
   q = (queuetype*)malloc(sizeof(queuetype)); /* queuetype크기만큼을 동적할당한 queuetype포인터를 queuetype포인터 q에 넣음 */
  
   q->front = NULL; /* q의 front부분에 빈공간을 넣음 */
   q->rear = NULL; /* q의 rear부분에 빈공간을 넣음 */
   return q; /* q를 초기화함 */
}

int isQueueEmpty(queuetype* q) { /* Queue가 비었는지 확인하는 함수 정의 */
   if (q->front == NULL) return 1; /* q의 front부분이 빈공간이라면 1을 반환함 */
   else return 0; /* q의 front부분이 빈공간이 아니라면 0을 반환함 */
}

void enQueue(queuetype* q, int e) { /* Queue에 새로운 것을 입력하는 함수 정의 */
   queuenode* newnode = (queuenode*)malloc(sizeof(queuenode));
   newnode->data = e;
   newnode->link = NULL;

   if (q->front == NULL) {
      q->front = newnode;
      q->rear = newnode;
   }
   else {
      q->rear->link = newnode;
      q->rear = newnode;
   }
}

int deQueue(queuetype* q) {
   queuenode* a = q->front;
   int e;
   if (isQueueEmpty(q)) return 0;
   else {
       e = a->data;
       q->front = q->front->link;
       if (q->front == NULL)
       q->rear = NULL;
       free(a);

    return e;
   }
}


void BreathFirstSearch(graphtype* g, int h){
    graphnode* b;
    queuetype* q;
    q = initQueue();
    g->visited[h] =  TRUE;
    printf("%d ", h);
    enQueue(q, h);
   
    while(!isQueueEmpty(q)) {
        h = deQueue(q);
        for (b = g->adjpointer[h]; b; b = b->link){
        if (!g->visited[b->vertex]){
            g->visited[b->vertex] = TRUE;
            printf("%d ", b->vertex);
            enQueue(q, b->vertex);
        }
      }
   }
}

void PrintGraph(graphtype* g){ /*인접리스트의 포인터배열의 첫번째부터 인접한 정점들을 출력하는 함수 정의 */
    for (int i = 0; i < g->n; i++) { /* for문을 정점의 수만큼 돎 */
        graphnode* p = g->adjpointer[i]; /* graphnode포인터 p에 g의 adjpointer를 넣음 */
        printf(" %d ",i); /* i 출력 */
        
        while (p != NULL) { /* p가 빈공간이 아니라면 while문 돎 */
        printf("-> %d ", p->vertex); /* 출력 */
        p = p->link; /* p에 p의 link를 넣음 */
        }
    printf("\n");
    }
}

void FreeGraph(graphtype* g){
     if(g->adjpointer != NULL){
      free(g->adjpointer);
   }
   if(g->visited != NULL){
      free(g->visited);
   }

}