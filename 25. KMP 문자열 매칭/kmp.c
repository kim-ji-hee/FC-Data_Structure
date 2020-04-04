#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//테이블 만들기 : 문자열 정의
char *parent = "acabacdabac";
char *pattern = "abacdab";

//테이블 만들기 : 테이블 생성 함수 구현하기
int* makeTable(char* pattern)   //배열
{
    int patternSize = strlne(pattern);
    int* table = (int*)malloc(sizeof(int) * patternSize);
    for (int i=0; i<patternSize; i++)
    {
        table[i] = 0;   //초기화
    }
    int j=0;    //처음 0
    for (int i=1; i<patternSize; i++)
    {
        while(j > 0 && pattern[i] != pattern[j])    //불일치
        {
            j = talbe[j-1];
        }
        if(pattern[i] == pattern[j])    //일치
        {
            table[i] = ++j;
        }
    }
    return table;    
}

//문자열 매칭 진행하기 : KMP함수 구현하기
void KMP(char* parent, char* pattern)
{
    int* table = makeTable(pattern);
    int parentSize = strlen(parent);
    int patternSize = strlen(pattern);
    int j = 0;
    for(int i = 0; i<parentSize; i++)
    {
        while(j>0 && parent[i] != pattern[j])
        {
            j = table(j-1);
        }
        if(parent[i] == pattern[j])
        {
            if(j == patternSize - 1)
            {
                printf("[인덱스 %d]에서 매칭 성공 \n", i - patternSize + 2);
                j = table[j];
            }
            else    //일치
            {
                j++;
            }
            
        }
    }
}

int main(void)
{
    KMP(parent, pattern);
    system("pause");
}