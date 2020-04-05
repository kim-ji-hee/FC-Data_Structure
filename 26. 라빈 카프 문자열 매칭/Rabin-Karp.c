#include <stdio.h>
#include <string.h>

//문자열 선언 및 확인 함수 구현하기
char *parent = "acabacdabac";
char *pattern = "abacdab";

//start: 해시값이 일치하기 시작한 인덱스
//부모문자열에서 패턴문자열이 일치하는지 확인 수행
void check(char *parent, char *pattern, int start)  
{
    int found = 1;
    int patternSize = strlen(pattern);
    for(int i=0; i<patternSize; i++)
    {
        if(parent[start+i] != pattern[i])
        {
            found = 0;
            break;
        }
    }
    if(found)
    {
        printf("[인덱스 %d에서 매칭 발생]\n", start+1);
    }
}

//라빈 카프 알고리즘 구현하기
void rabinKarp(char *parent, char *pattern)
{
    int parentSize = strlen(parent);
    int patternSize = strlen(pattern);
    int parentHash = 0, patternHash = 0, power = 1; //제곱승
    for(int i=0; i<=parentSize - patternSize; i++)
    {
        if(i==0)    //해시 값 구하기
        {
            for(int j=0; j<patternSize; j++)
            {
                //가장 뒤에 있는 문자부터 아스키 값에 power를 곱함
                parentHash = parentHash + parent[patternSize - 1 - j] * power;
                patternHash = patternHash + pattern[patternSize - 1 - j] * power;
                if(j < patternSize - 1)
                    power = power * 2;
            }
        }
        else    //i가 증가 할 때마다 수행, 다음 해시 값 구함
        {
            parentHash = 2 * (parentHash - parent[i-1]*power) + parent[patternSize - 1 + i];]
        }
        if(parentHash == patternHash)
        {
            check(parent, pattern, i);
        }        
    }
}

//라빈 카프 알고리즘 사용해보기
int main(void)
{
    rabinKarp(parent, pattern);
    system("pause");
}