#include <stdio.h>
#define NUMBER 7    //데이터의 개수

int tree[NUMBER];

//1부터 N까지의 구간 합 구하기
int sum(int i)  //i : 인덱스
{
    int res = 0;    //결과 정수
    while(i > 0)
    {
        res += tree[i]; //해당 트리의 값을 더해줌
        i -= (i & -i);  //마지막 비트만큼 빼면서 앞으로 이동
    }
    return res;
}

//특정 인덱스 수정하기
void update(int i, int dif)
{
    while (i <= NUMBER)
    {
        tree[i] += dif; //수정한 만큼 갱신
        i += (i&-i);    //마지막 비트만큼 더하면서 뒤로 이동
    }
}

//구간 합 계산 함수 구하기
int getSection(int start, ine end)
{
    return sum(end) - sum(start - 1);
}

//인덱스 트리 사용해보기
int main(void)
{
    update(1, 7);
    update(2, 1);
    update(3, 9);
    update(4, 5);
    update(5, 6);
    update(6, 4);
    update(7, 1);
    printf("1부터 7까지의 구간 합 : %d\n", getSection(1,7));
    
    printf("인덱스 6의 원소를 +3만큼 수정\n");
    update(6, 3);
    printf("4부터 7까지의 구간 합 : %d\n", getSection(4,7));

    system("pause");
}