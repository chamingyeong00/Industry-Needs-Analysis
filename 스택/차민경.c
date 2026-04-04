#define SIZE 10000

extern void my_push(int s);
extern int my_pop(int s);
extern void enqueue(void);

void test_main(void)
{
    int count[10];

    for (int i = 0; i < 10; i++)
        count[i] = 0;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            int val = my_pop(0);

            int bucket = (val >> (i* 3)) & 7;

            my_push(bucket+1);
            count[bucket+1]++;
        }

        for (int k = 8; k > 0; k--)
        {
            for (int l = 0; l < count[k]; l++)
            {
                int val = my_pop(k);
                my_push(0);
            }
            count[k] = 0;
        }
    }

    for (int i = 0; i < SIZE; i++)
    {
        int val = my_pop(0);
        enqueue();
    }
}