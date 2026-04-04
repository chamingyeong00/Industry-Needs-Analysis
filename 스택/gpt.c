// DO NOT ANY INCLUDE
#define SIZE 10000

// main.cpp에 정의된 전역 함수들을 가져옵니다.
extern void my_push(int s);
extern int my_pop(int s);
extern void enqueue(void);

void test_main(void)
{
    int counts[10];

    // 난수의 범위가 0 ~ 1023 (10비트) 이므로, 8진수(3비트 단위)를 사용합니다.
    // 1023은 8진수로 최대 4자리(1777)이므로, 총 4번의 pass만 수행하면 됩니다.
    for (int pass = 0; pass < 4; pass++)
    {
        // 각 버킷(스택 1~8)에 들어간 데이터의 개수를 초기화합니다.
        for (int i = 0; i < 10; i++)
        {
            counts[i] = 0;
        }

        // 1. Distribution (분배 단계)
        // stack[0]에서 하나씩 꺼내어, 현재 자릿수의 값(0~7)에 따라 8개의 보조 스택에 분배합니다.
        for (int i = 0; i < SIZE; i++)
        {
            int val = my_pop(0);
            
            // 8진법 기준 현재 자리의 숫자(0~7) 추출
            // pass 0: 비트 0~2, pass 1: 비트 3~5, pass 2: 비트 6~8, pass 3: 비트 9
            int bucket = (val >> (pass * 3)) & 7;
            
            // bucket(0~7) 값을 스택 1~8에 나누어 저장합니다.
            my_push(bucket + 1);
            counts[bucket + 1]++;
        }

        // 2. Merge (병합 단계)
        // 큰 값을 가진 버킷부터 작은 버킷 순서로 다시 stack[0]으로 옮깁니다.
        // 스택은 LIFO(후입선출) 구조이므로 큰 번호(8)의 버킷부터 먼저 넣어야,
        // 다음 pass에서 작은 숫자가 stack[0]의 상단(Top)에 위치하게 되어 안정 정렬(Stable Sort)이 유지됩니다.
        for (int b = 8; b >= 1; b--)
        {
            for (int i = 0; i < counts[b]; i++)
            {
                my_pop(b);
                my_push(0);
            }
        }
    }

    // 4번의 Pass가 끝나면 stack[0]에는 가장 작은 수가 상단(Top)에 위치하도록 완벽히 오름차순 정렬되어 있습니다.
    // 이를 하나씩 Pop하여 큐(Queue)로 옮겨줍니다.
    for (int i = 0; i < SIZE; i++)
    {
        my_pop(0);
        enqueue();
    }
}