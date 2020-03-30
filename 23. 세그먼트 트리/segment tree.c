//트리 구조로 구간 합 구하기 
//- 구간 합 트리 생성하기 [특정 범위 인덱스의 값을 저장]
#include <stdio.h>
#define NUMBER 7

int a[] = {7 1 9 5 6 4 1};
int tree[4*NUMBER]; //4를 곱하면 모든 범위를 커버할 수 있습니다.

//start : 시작 인덱스, end : 끝 인덱스
int init(int start, int end, int node)
{
    if(start == end)    //리프노드
        return tree[node] = a[start];
    int mide = (start + end) / 2;   //리프노드가 아닌 경우
        return tree[node] = init(start, mid, node * 2) + init(mide + 1, end, node * 2 + 1);
        //재귀적으로 두 부분으로 나눈 뒤에 그 합을 자기 자신으로 합니다.
}

//- 구간 합 계산하기
//start : 시작 인덱스, end : 끝 인덱스
//left, right : 구간 합을 구하고자 하는 범위
int sum(int start, int end, int node, int left, int right)
{
    if(left > end || right < start) //범위 밖에 있는 경우
        return 0;
    if(left <= start && end <= right) //범위 안에 있는 경우
        return tree[node];
    
    int mide = (start + end) / 2;   //그렇지 않다면 두 부분으로 나누어 합을 구하기

    return sum(start, mid, node*2, left, right) + sum(mid+1, end, node*2+1, left, right);
}

//-구간 합 수정하기
//start : 시작 인덱스, end : 끝 인덱스
//index : 구간 합을 수정하고자 하는 노드
//dif : 수정할 값
void update(int start, int end, int node, int index, int dif)
{
    if(index < start || index > end)    //범위 밖에 있는 경우
        return;
    
    tree[node] += dif;  //범위 안에 있으면 내려가며 다른 원소도 갱신

    if(start == end )
        return;
    
    int mid = (start + end) / 2;
    update(start, mid, node*2, index, dif);
    update(mid+1, end, node*2+1, index, dif);
}

//-세그먼트 트리 사용해보기
int main(void)
{
    //구간 합 트리의 인덱스를 제외하고는 모두 인덱스 0부터 시작합니다.
    init(0, NUMBER-1, 1);   //구간 합 트리 생성하기

    printf("0부터 6까지의 구간 합 : %d\n", sum(0, NUMBER-1, 1, 0, 6));  //구간 합 구하기

    printf("인덱스 5의 원소를 +3 만큼 수정\n"); //구간 합 갱신하기

    update(0, NUMBER-1, 1, 5, 3);

    printf("3부터 6까지의 구간 합 : %d\n", sum(0, NUMBER-1, 1, 3, 6));  //구간 합 다시 구하기

    system("pause");
}