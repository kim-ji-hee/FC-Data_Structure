#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define NODE_MAX 1001
#define EDGE_MAX 200001 //양방향 간선이므로 100,000개

//프림 알고리즘 간선 구조체 정의 [최대 노드 1,000개 / 최대 간선 100,000개]
typedef struct {    //각 간선에 대한 정보
    int cost;
    int node;
} Edge;

void swap(Edge *a, Edge *b)     //간선 교체 (우선순위 큐)
{
    Edge temp;
    temp.cost = a->cost;
    temp.node = a->node;
    a->cost = b->cost;
    a->node = b->node;
    b->cost = temp.cost;
    b->node = temp.node;
}

//프림 알고리즘 우선순위 큐 정의 및 삽입 함수 구현
typedef struct {
    Edge *heap[EDGE_MAX];   //간선이 들어가는 배열
    int count;
} priorityQueue;

void push(priorityQueue *pq, Edge *edge)
{
    if(pq->count >= EDGE_MAX)   //데이터를 넣을 때 간선의 크기를 벗어나면 리턴
        return;
    
    pq->heap[pq->count] = edge; //마지막 인덱스에 새로운 원소를 넣음
    int now = pq->count;
    int now pq->count;
    int parent = (pq->count - 1) / 2;
    //새 원소를 삽입한 이후에 상향식으로 힙을 구성합니다.
    while(now > 0 && pq->heap[now]->cost < pq->heap[parent]->cost)
    {
        swap(pq->heap[now], pq->heap[parent]);
        now = parent;
        parent = (parent - 1) / 2;
    }
    pq->count++;
}

//프림 알고리즘 우선순위 큐 추출 함수 구현
Edge* pop(priorityQueue *pq)
{
    if (pq->count <=0)
        return NULL;
    
    Edge *res = pq->heap[0];
    pq->count--;
    pq->heap[0] = pq->heap[pq->count];
    int now = 0, leftChild = 1, rightChild = 2;
    int target = now;
    //새 원소를 추출한 이후에 하향식으로 힙을 구성합니다.
    while(leftChild < pq->count)
    {
        if(pq->heap[target]->cost > pq->heap[leftChild]->cost)
            target = leftChild;
        if(pq->heap[target]->cost > pq->heap[rightChild]->cost && rightChild < pq->count)
            target = rightChild;
        if(target == now)
            break;  //더 이상 내려가지 않아도 될 때 종료
        else {
            swap(pq->heap[now], pq->heap[target]);
            now = target;
            leftChild = now * 2 + 1;
            rightChild = now * 2 + 2;
        }
    }
    return res;
}

//프림 알고리즘 간선 연결 리스트 구현
typedef struct Node {
    Edge *data;
    struct Node *next;
} Node;

Node ** adj;
int d[NODE_MAX];

void addNode(Node** target, int index, Edge* edge)  //인덱스의 정점에 간선 추가
{
    if (target[index] == NULL)  //연결된 간선이 없다면
    {
        target[index] = (Node*)malloc(sizeof(Node));
        target[index]->data = edge;
        target[index]->next = NULL;
    }
    else    //그렇지 않으면 새로 추가
    {
        Node* node = (Node*)malloc(sizeof(Node));
        node->data = edge;
        node->next = target[index];
        target[index] = node;
    }
    
}

//프림 알고리즘 사용해보기
int main(void)
{
    int n, m;
    scanf("%d %d", &n, &m); // n 정점의 개수, m 간선의 개수
    adj = (Node**)malloc(sizeof(Node*) * (n+1));    //정점의 개수만큼 동적 할당
    for (int i=1; i<=n; i++)
    {
        adj[i] = NULL;  //연결리스트 초기화
    }
    priorityQueue *pq;  //우선순위 큐
    pq = (priorityQueue*)malloc(sizeof(priorityQueue));
    pq->count = 0;
    for (int i=0; i<m; i++) //모든 간선에 대한 입력을 받음
    {
        int a, b, c;    //a에서 b까지 가는데 c(가중치)가 소요된다
        scanf("%d %d %d", &a, &b, &c);  //무방향 그래프 (양쪽에서 갈 수 있음)
        Edge *edge1 = (Edge*)malloc(sizeof(Edge));
        edge1->node = b;
        edge1->cost = c;
        addNode(adj, a, edge1);

        Edge *edge2 = (Edge*)malloc(sizeof(Edge));
        edge2->node = a;
        edge2->cost = c;
        addNode(adj, b, edge2) ;
    }
    
    //프림 알고리즘을 시작합니다.
    long long res = 0;
    Edge *start = (Edge*)malloc(sizeof(Edge));
    start->cost = 0;    //처음 비용은 0
    start->node = 1;    //시작 노드를 1로 설정
    push(pq,start);

    for(int i = 1; i <= n; i++) //n개의 정점 만큼 반복
    {
        int nextNode = -1, nextCost = INT_MAX;  //다음으로 나아갈 노드와 그 비용을 담는 변수
        while(1)    //방문하지 않은 노드들 중에서 (가장 비용이 적은 노드를) 우선순위 큐에서 꺼냄
        {
            Edge* now = pop(pq);
            if(now == NULL)
                break;
            nextNode = now->node;
            if(!d[nextNode])
            {
                nextCost = now->cost;
                break;
            }
        }
        if (nextCost == INT_MAX)
            printf("연결 그래프가 아닙니다.\n");
        res+= nextCost;
        d[nextNode] = 1;    //방문처리
        Node *cur = adj[nextNode];
        while(cur!=NULL)    //노드의 인접한 노드를 확인하면서 우선순위 큐에 넣음
        {
            push(pq, cur->data);
            cur = cur->next;
        }
    }
    printf("%lld\n", res);
    system("pause");
}