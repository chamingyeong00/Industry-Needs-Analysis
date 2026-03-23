#include <stdio.h>

extern void get_school_position(int school_index, int* posX, int* posY);
extern void get_student_position(int student_index, int* posX, int* posY);
extern void set_student_school(int student_index, int school_index);
static int total = 0;

int get_distant(int student_posX, int student_posY, int school_posX, int school_posY)
{
    int distant = 0;

    distant = (student_posX - school_posX >= 0 ? student_posX - school_posX : school_posX - student_posX)
        + (student_posY - school_posY >= 0 ? student_posY - school_posY : school_posY - student_posY);

    return distant;
}

int check_school_max(int min_school_index, int school_count[3]) {
    if (school_count[min_school_index] >= 3500)
        return 0;
    return 1;
}

int get_min_student_school(int distant[3], int school_count[3])
{
    int min_distant = 2147483647;
    int shelter_index = 0;

    for (int i = 0; i < 3; i++)
    {
        if (min_distant == distant[i])
            continue;

        if (min_distant > distant[i] && check_school_max(i, school_count))
        {
            min_distant = distant[i];
            shelter_index = i;
        }
    }
    total += min_distant;
	school_count[shelter_index]++;
    return shelter_index;
}


void run_contest(void)
{
    int school_posX, school_posY;
    int people_posX, people_posY;
    int school_count[3] = { 0, 0, 0 };
    int distant[3] = { 0, 0, 0 };
    int min_school_index = 0;

    for (int people_index = 0; people_index < 10000; people_index++)
    {
        get_student_position(people_index, &people_posX, &people_posY);
        for (int school_index = 0; school_index < 3; school_index++)
        {
            get_school_position(school_index, &school_posX, &school_posY);
            distant[school_index] = get_distant(people_posX, people_posY, school_posX, school_posY);
        }
        min_school_index = get_min_student_school(distant, school_count);
        set_student_school(people_index, min_school_index);
    }

    printf_s("total : %d\n", total);
    printf_s("school 0 : %d\n", school_count[0]);
    printf_s("school 1 : %d\n", school_count[1]);
    printf_s("school 2 : %d\n", school_count[2]);

}