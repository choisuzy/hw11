#include<stdio.h>
#include<stdlib.h>

#define MAX_VERTEX 10 /* 최대 Vertex의 수를 10으로 정의함 */
#define FALSE 0 /* FALSE를 0으로 정의함 */
#define TRUE 1 /* TRUE를 1로 정의함 */

typedef struct graphnode {  /* struct graphnode에 타입이 다른 데이터들을 그룹화 */
	int vertex;	/* vertex를 int형으로 선언, vertex는 정점임, 데이터 필드 */
	struct graphnode* link;	/* 구조체 graphnode포인터 link를 선언, 링크 필드 */
}graphnode; /* 구조체 호출용 이름 */

typedef struct graphtype { /* struct graphtype에 타입이 다른 데이터들을 그룹화 */
	int n;	/* n을 int형으로 선언, 그래프정점의 갯수 */
	graphnode* adjpointer[MAX_VERTEX]; /* 인접하는 헤드포인터들의 배열을 graphnode포인터로 선언 */
    int visited[MAX_VERTEX];  /* 방문 플래그 표시를 위한 배열을 정수형으로 선언*/
}graphtype; /* 구조체 호출용 이름 */

typedef struct stacknode{ /* struct stacknode에 타입이 다른 데이터들을 그룹화 */
   int data; /* data를 int형으로 선언*/
   struct stacknode* link; /* 구조체 stacknode포인터 link를 선언, 링크 필드 */
} stacknode; /* 구조체 호출용 이름 */

stacknode* top; /* stacknode포인터 top 선언 */

typedef struct queuenode{ /* struct queuenode에 타입이 다른 데이터들을 그룹화 */
   int data; /* data를 int형으로 선언*/
   struct queuenode* link; /* 구조체 queuenode포인터 link를 선언, 링크 필드 */
} queuenode; /* 구조체 호출용 이름 */

typedef struct queuetype { /* struct queuetype에 타입이 다른 데이터들을 그룹화 */
   struct queuenode* front,* rear; /* struct queuenode포인터 front와 rear 선언 */
} queuetype; /* 구조체 호출용 이름 */

void InitializeGraph(graphtype* g); /* 그래프를 초기화하는 함수 선언 */
void InsertVertex(graphtype* g, int h); /* 그래프에 정점을 삽입하는 함수 선언 */
void InsertEdge(graphtype* g, int t, int h); /* 그래프에 간선을 삽입하는 함수 선언 */
int isEmpty(); /* 스택이 비었는지 확인하는 함수 선언 */
void push(int e); /* 스택에 push하는 함수 선언 */
int pop(); /* 스택에 pop하는 함수 선언 */
void DepthFirstSearch(graphtype* g, int h); /* 깊이우선탐색을 하는 함수 선언 */
queuetype* initQueue(); /* queue를 초기화하는 함수 선언 */
int isQueueEmpty(); /* 큐가 비었는지 확인하는 함수 선언 */
void enQueue(queuetype* q, int e);  /* Queue에 데이터를 넣는 함수 선언 */
int deQueue(queuetype* q); /* Queue에 데이터를 빼는 함수 선언 */
void BreathFirstSearch(graphtype* g, int h); /* 넓이우선탐색을 하는 함수 선언 */
void PrintGraph(graphtype* g); /*인접리스트의 포인터배열의 첫번째부터 인접한 정점들을 출력하는 함수 선언 */
void FreeGraph(graphtype* g); /* 그래프에 할당된 메모리를 free시키는 함수 선언 */

int main(){

    printf("[----- [Choi Suzy]  [2021024135] -----]\n");
    
    int num; /* num을 정수형으로 선언 */
    int dv; /* dv를 정수형으로 선언 */
    int bv; /* bv를 정수형으로 선언 */
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
            int num; /* num을 정수형으로 선언 */
            printf("input edge num : "); /* 출력 */
            scanf("%d", &num); /* 사용자에게 간선의 개수 num을 입력받음 */

            if (num > MAX_VERTEX*(MAX_VERTEX-1)/2)  /* 간선의 개수가 최대간선수보다 큰 경우 */
            break; /* 조건문을 빠져나옴 */

            for (int i = 0; i < num; i++) { /* num만큼 for문을 돎 (방향이 없는 일반 그래프의 edge를 해당 vertex에 부속) */
                int x, y; /* x와 y를 정수형으로 선언 */
                printf("input vertex(x,y) : "); /* 출력 */
                scanf("%d %d", &x, &y); /* 사용자에게 x와 y를 입력받음 */

                InsertEdge(g, x, y); /* InsertEdge함수 호출 */
                InsertEdge(g, y, x); /* InsertEdge함수 호출 */
            }
			break; /* 조건식을 빠져나옴 */
		case 'd': case 'D': /* command가 d나 D이면 */
            int dv; // 탐색을 시작할 정점
            printf("input vertex: "); /* 출력 */
            scanf("%d", &dv); /* 사용자에게 vertex를 입력받음 */
			DepthFirstSearch(g, dv); /* DepthFirstSearch함수 호출 */
            printf("\n"); /* 출력 */
			break; /* 조건식을 빠져나옴 */
		case 'b': case 'B': /* command가 b나 B이면 */
            int bv; // 탐색을 시작할 정점
            printf("input vertex: "); /* 출력 */
            scanf("%d", &bv); /* 사용자에게 vertex를 입력받음 */
			BreathFirstSearch(g, bv); /* BreathFirstSearch함수 호출 */
			break; /* 조건식을 빠져나옴 */
		case 'p': case 'P': /* command가 p나 P이면 */
			PrintGraph(g); /* PrintGraph함수 호출 */
			break; /* 조건식을 빠져나옴 */
		case 'q': case 'Q': /* command가 q나 Q이면 */
			FreeGraph(g); /* FreeGraph함수 호출 */ 
			break; /* 조건식을 빠져나옴 */
		default: /* 위의 알파벳이 다 아니면 */
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); /* 출력 */
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
        g->visited[v] = FALSE; /* g의 visited부분을 FALSE로 함 */
    }
}

void InsertVertex(graphtype* g, int h){ /* 그래프에 정점을 삽입하는 함수 정의 */
    if (g->n + 1 > MAX_VERTEX) { /* 그래프가 정점개수를 초과하였을 때 */
		return; /* 반환함 */
	}
	g->n++; /* 그래프 정점의 개수 하나 증가시킴 */
}

void InsertEdge(graphtype* g, int t, int h){ /* 그래프에 간선을 삽입하는 함수 정의 */
    if(t >= g->n || h>= g->n){ /* 정점 t가 그래프 정점의 개수이상이거나 정점 h가 그래프 정점의 개수 이상일 때*/
        printf("error \n"); /* print */
        return; /* 반환함 */
    }

    graphnode* node = (graphnode*)malloc (sizeof(graphnode)); /* graphnode크기만큼을 동적할당한 graphnode포인터를 graphnode포인터 node에 넣음 */
    node -> vertex = h; /* node의 vertex부분에 h를 넣음 */
    node -> link = NULL; /* node의 link부분을 빈공간으로 만듦 */

    if(g -> adjpointer[h] == NULL){ /* g의 adjpointer가 빈공간이라면 */
        g -> adjpointer[h] = node; /* g의 adjpointer에 node를 넣음 */
        return; /* 반환함 */
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
        return; /* 반환함 */
        }
        p = c; /* p에 c를 넣음 */
        c = c->link; /* c에 c의 link를 넣음 */
    }
    p->link = node; /* p의 link부분에 node를 넣음 */ /* 마지막노드까지 찾아봤을 때 찾지 못했으면 마지막에 삽입함 */
    return; /* 반환함 */
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

void DepthFirstSearch(graphtype* g, int h){ /* 깊이우선탐색을 하는 함수 정의 */
    graphnode* b;  /* graphnode포인터 b 선언 */
    top = NULL; /* top을 빈공간으로 만듦 */
    push(h); /* h를 push함 */

    g->visited[h] = TRUE; /* g의 visited를 TRUE로 함 */
    printf(" %d", h); /* 출력 */

    while(!isEmpty()) { /* isempty함수가 아니라면 */
        b = g->adjpointer[h]; /* b에 g의 adjpointer배열을 넣음 */
        while(b) { /* b이면 while문을 돎 */
            if (!g->visited[b->vertex]) { /* g의 visited부분이 아니라면 */
                push(b->vertex); /* b의 vertex부분을 push함 */
                g->visited[b->vertex] = TRUE; /* g의 visited부분을 TRUE로 함 */
                printf(" %d", b->vertex); /* 출력 */
                h = b->vertex; /* h에 b의 vertex부분을 넣음 */
                b = g->adjpointer[h]; /* b에 g의 adjpointer배열을 넣음 */
         }
         else b = b->link; /* g의 visited부분이면 b에 b의 link부분을 넣음 */
      }
      h = pop(); /* h에 pop함수 넣음 */
   }
   for(int i = 0; i<MAX_VERTEX; i++){ /* MAX_VERTEX번 만큼 for문을 돎 */
       g->visited[i]=FALSE; /* g의 visited배열을 FALSE로 함 */
   }
}

queuetype* initQueue(){ /* queue를 초기화하는 함수 정의 */
   queuetype* q; /* queuetype 포인터 q선언 */
   q = (queuetype*)malloc(sizeof(queuetype)); /* queuetype크기만큼을 동적할당한 queuetype포인터를 queuetype포인터 q에 넣음 */
  
   q->front = NULL; /* q의 front부분을 빈공간으로 만듦 */
   q->rear = NULL; /* q의 rear부분을 빈공간으로 만듦 */
   return q; /* q를 초기화함 */
}

int isQueueEmpty(queuetype* q) { /* Queue가 비었는지 확인하는 함수 정의 */
   if (q->front == NULL) return 1; /* q의 front부분이 빈공간이라면 1을 반환함 */
   else return 0; /* q의 front부분이 빈공간이 아니라면 0을 반환함 */
}

void enQueue(queuetype* q, int e) { /* Queue에 데어터를 넣는 함수 정의 */
   queuenode* newnode = (queuenode*)malloc(sizeof(queuenode)); /* queuenode크기만큼을 동적할당한 queuenode포인터를 queuenode포인터 newnode에 넣음 */
   newnode->data = e; /* newnode의 data에 e를 넣음 */
   newnode->link = NULL; /* newnode의 link를 빈공간으로 만듦*/

   if (q->front == NULL) { /* q의 front부분이 빈공간이라면 */
      q->front = newnode; /* q의 front부분에 newnode를 넣음 */
      q->rear = newnode; /* q의 rear부분에 newnode를 넣음 */
   }
   else { /* q의 front부분이 빈공간이 아니라면 */
      q->rear->link = newnode; /* q의 rear의 link부분에 newnode를 넣음 */
      q->rear = newnode; /* q의 rear부분에 newnode를 넣음 */
   }
}

int deQueue(queuetype* q) { /* Queue에 데이터를 빼는 함수 정의 */
   queuenode* a = q->front; /* queuenode포인터 a에 q의 front부분을 넣음 */
   int e; /* e를 정수형으로 선언 */

   if (isQueueEmpty(q)) return 0; /* Queue가 비었는지 확인하는 함수를 실행해서 해당하면 0을 반환함 */
   else { /* isQueueEmpty함수에 성립하지 않으면 */
       e = a->data; /* e에 a의 data부분을 넣음 */
       q->front = q->front->link; /* q의 front부분에 q의 front부분의 link를 넣음 */
       if (q->front == NULL) /* q의 front부분이 빈공간이라면 */
       q->rear = NULL; /* q의 rear부분을 빈공간으로 만듦 */
       free(a); /* a를 free시킴 */

    return e; /* e를 반환함 */
   }
}


void BreathFirstSearch(graphtype* g, int h){  /* 넓이우선탐색을 하는 함수 정의 */
    graphnode* b; /* graphnode포인터 b를 선언 */
    queuetype* q; /* queuetype포인터 q를 선언 */
    q = initQueue(); /* q에 initQueue함수를 넣음 */
    g->visited[h] =  TRUE; /* g의 visited배열은 TRUE */
    printf("%d ", h); /* 출력 */
    enQueue(q, h); /* enQueue함수 실행 */
   
    while(!isQueueEmpty(q)) { /* isQueueEmpty함수가 아닌 동안 while문을 돎 */
        h = deQueue(q); /* h에 deQueue함수를 넣음 */
        for (b = g->adjpointer[h]; b; b = b->link){ /* b번동안 for문을 돎 */
            if (!g->visited[b->vertex]){ /* g의 visited부분이 아니면 */
                g->visited[b->vertex] = TRUE; /* g의 visited부분을 TRUE로 함 */
                printf("%d ", b->vertex); /* 출력 */
                enQueue(q, b->vertex); /* enQueue함수 실행 */
            }
        }
    }
    for(int i = 0; i<MAX_VERTEX; i++){ /* MAX_VERTEX번만큼 for문을 돎 */
        g->visited[i] = FALSE; /* g의 visited배열을 FALSE로 함 */
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

void FreeGraph(graphtype* g){ /* graph를 freet시키는 함수 정의 */
     if(g->adjpointer != NULL){ /* g의 adjpointer가 빈공간이 아니라면 */
      free(g->adjpointer); /* g의 adjpointer를 free시킴 */
   }
   if(g->visited != NULL){ /* g의 visited가 빈공간이 아니라면 */
      free(g->visited); /* g의 visited를 free시킴 */
   }
}