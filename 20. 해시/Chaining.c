#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define TABLE_SIZE 10007    //서수로 설정
#define INPUT_SIZE 5000     //5000개의 데이터 들어갑

//체이닝 구조체 정의
typedef struct {
    int id;
    char name[20];
} Student;

typedef struct {
    Student* data;
    struct Bucket* next;    //연결리스트
} Bucket;   //하나의 키에 해당하는 데이터가 여러개 들어갈 수 있음

//체이닝 해시 테이블 초기화 함수
void init(Bucket** hashTable)
{
    for(int i=0; i<TABLE_SIZE; i++)
    {
        hashTable[i] = NULL;
    }
}

//해시 테이블의 메모리를 반환
void destructor(Bucket** hashTable)
{
    for(int i=0; i<TABLE_SIZE; i++)
    {
        if(hashTable[i] != NULL)
            free(hashTable[i]);
    }
}

//체이닝 데이터 탐색 함수
int isExist(Bucket** hashTable, int id) //id에 해당하는 데이터가 존재하는지 확인
{
    int i = id % TABLE_SIZE;
    if (hashTable[i] == NULL)
        return 0;
    else {  //데이터가 존재하면
        Bucket *cur = hashTable[i];
        while(cur != NULL)  //모든 데이터를 검사
        {
            if(cur->data->id == id) //인덱스 일치
                return 1;
            cur = cur->next;
        }
    }
    return 0;
}

//특정한 키 인덱스에 데이터를 삽입함
void add(Bucket** hashTable, Student* input)
{
    int i = input->id % TABLE_SIZE;
    if(hashTable[i] == NULL)    //비어있다면
    {
        hashTable[i] = (Bucket*)malloc(sizeof(Bucket));
        hashTable[i]->data = input; //데이터 입력
        hashTable[i]->next = NULL;
    }
    else    //비어있지 않으면
    {
        Bucket *cur = (Bucket*)malloc(sizeof(Bucket));
        cur->data = input;  //앞부분에 데이터 삽입
        cur->next = hashTable[i];
        hashTable[i] = cur;
    }    
}

//해시 테이블에 존재하는 모든 데이터를 출력
void show(Bucket** hashTable)
{
    for (int i=0; i<TABLE_SIZE; i++)
    {
        if(hashTable[i]!=NULL)
        {
            Bucket *cur = hashTable[i];
            while(cur!=NULL)
            {
                printf("키 : [%d] 이름 : [%d]\n", i, cur->data->name);
                cur  = cur -> next;
            }
        }
    }
}

int main(void)
{
    Bucket **hashTable;
    hashTable = (Bucket**)malloc(sizeof(Bucket) * TABLE_SIZE);
    init(hashTable);

    for(int i=0; i<INPUT_SIZE; i++)
    {
        Student* student = (Student*)malloc(sizeof(Student));
        student->id = rand % 1000000;
        sprintf(student->name, "사람%d", student->id);
        if(!isExist(hashTable, student->id)) //중복되는 ID는 존재하지 않도록 함
            add(hashTable, student);
    }

    show(hashTable);
    destructor(hashTable);
    system("pause");
    return 0;
}