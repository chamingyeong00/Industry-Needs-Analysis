extern void my_push(int s);
extern int my_pop(int s);
extern void enqueue(void);

int check_sort_all_stack(int array[10000])
{
	for (int i = 0; i < 9999; i++)
	{
		for (int j = i + 1; j < 10000; j++)
		{
			if (array[i] < array[j])
				return 0;
		}
	}
	return 1;
}

void test_main(void)
{
	int sort_sp[10];
	int array[10000];

	sort_sp[0] = 10000;
	for (int i = 1; i < 10; i++)
		sort_sp[i] = 0;

	for (int move = 0; move < 4; move++)
	{
		int array_count = 0;
		for (int i = 0; i < 10000; i++)
			array[i] = 0;

		for (int size = 0; size < 10000; size++)
		{
			int stack_content_10num = my_pop(0);
			sort_sp[0]--;
			int stack_content_8num = (stack_content_10num >> move * 3) & 7;

			my_push(stack_content_8num + 1);
			sort_sp[stack_content_8num + 1]++;
		}

		for (int stack_8 = 8; stack_8 > 0; stack_8--)
		{
			for (int sp = sort_sp[stack_8]; sp > 0; sp--)
			{
				int stack_content_10num = my_pop(stack_8);
				sort_sp[stack_8]--;
				array[array_count++] = stack_content_10num;
				my_push(0);
				sort_sp[0]++;
			}
		}

		if (check_sort_all_stack(array) == 1)
			break;
	}

	for (int stack_8 = 8; stack_8 >= 0; stack_8--)
	{
		for (int sp = sort_sp[stack_8]; sp > 0; sp--)
		{
			int check = my_pop(stack_8);
			enqueue();
		}
	}
}
