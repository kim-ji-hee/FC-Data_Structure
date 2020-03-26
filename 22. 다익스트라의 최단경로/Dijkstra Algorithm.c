#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define NODE_MAX 20001
#define EDGE_MAX 600001 //양방향 간선이므로 300,000개

//다익스트라 알고리즘 간선 구조체 정의 [최대 노드 20,000개 / 최대 간선 300,000개]
typedef struct {   
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

//다익스트라 알고리즘 우선순위 큐 정의 및 삽입 함수 구현 - 프림 알고리즘과 동일
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

//다익스트라 알고리즘 우선순위 큐 추출 함수 구현 - 프림 알고리즘과 동일 
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

//다익스트라 알고리즘 간선 연결 리스트 구현 - 프림 알고리즘과 동일
typedef struct Node {
    Edge *data;
    struct Node *next;
} Node;

Node ** adj;
int ans[NODE_MAX];  //특정 노드까지의 최단 거리 값

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

//다익스트라 알고리즘 사용해보기
int main(void)
{
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k); // n 정점의 개수, m 간선의 개수
    adj = (Node**)malloc(sizeof(Node*) * (n+1));    //노드의 개수만큼 동적 할당
    for (int i=1; i<=n; i++)
    {
        adj[i] = NULL;  //연결리스트 초기화
        ans[i] = INT_MAX;   //처음 모든 노드에 갈 수 있는 비용은 무한이라고 가정
    }
    priorityQueue *pq;  //우선순위 큐
    pq = (priorityQueue*)malloc(sizeof(priorityQueue));
    pq->count = 0;
    for (int i=0; i<m; i++) //모든 간선에 대한 입력을 받음
    {
        int a, b, c;    //a에서 b까지 가는데 c(가중치)가 소요된다 (방향그래프)
        scanf("%d %d %d", &a, &b, &c);  //무방향 그래프 (양쪽에서 갈 수 있음)
        Edge *edge = (Edge*)malloc(sizeof(Edge));
        edge->node = b; //원소 b
        edge->cost = c;
        addNode(adj, a, edge);
    }
    
    //다익스트라 알고리즘을 시작합니다.
    ans[k] = 0; //출발하고자 하는 노드 k
    Edge *start = (Edge*)malloc(sizeof(Edge));
    start->cost = 0;    //처음 비용은 0
    start->node = k;    //출발 노드에 대한 간선 정보를 큐에 넣음
    push(pq,start);

    while(1)  //큐에서 pop을 하면서 알고리즘 수행 (원소가 바닥날 때 까지 모든 원소를 큐에 담고 뺌)
    {
        Edge* now = pop(pq);    //원소를 꺼냄
        if(now == NULL)
            break;
        int curNode = now->node;
        int curCost = now->cost;
        if (ans[curNode] < curCost) //현재 비용이 테이블에 담은 비용보다 크다면
            continue;               //무시
        Node *cur = adj[curNode];   //그렇지 않다면 노드추가

        while (cur != NULL)         //연결된 노드들 다 확인
        {
            Edge* temp = cur->data;
            temp->cost += curCost;  //해당 노드로 건너가는 비용을 cost에 담음
            if(temp->cost < ans[temp->node]) //현재 담겨있던 최단거리 비용이 현재 보고 있는 비용보다 크다면
            {
                ans[temp->node] = temp->cost;//더 작은 값으로 갱신
                push(pq, temp);     //해당 간선을 큐에 담아서 다시 간선 데이터를 확인할 수 있게 함
            }
            cur = cur->next;
        }
    }

    for(int i=1; i<=n; i++)
    {
        if(ans[i] == INT_MAX) printf("INF\n");  //해당 노드로 도착할 수 없는 경우
        else printf("%d\n", ans[i]);
    }
    system("pause");
}