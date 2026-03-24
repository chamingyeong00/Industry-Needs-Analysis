#include <stdio.h>
#include <unistd.h>

extern void get_school_position(int school_index, int* posX, int* posY);
extern void get_student_position(int student_index, int* posX, int* posY);
extern void set_student_school(int student_index, int school_index);
static int total = 0;

typedef struct stduent {
    int index;
    int posX;
    int posY;
    int distant[3];
    int order[3];
    int diff[2];
} t_student;

int get_distant(int student_posX, int student_posY, int school_posX, int school_posY)
{
    int dx = student_posX - school_posX;
    int dy = student_posY - school_posY;
    return dx * dx + dy * dy;
}

int check_school_max(int min_school_index, int school_count[3]) {
    if (school_count[min_school_index] >= 3500)
        return 0;
    return 1;
}

void set_diff(t_student *student){
    student->diff[0] = student->distant[student->order[1]]
                     - student->distant[student->order[0]];

    student->diff[1] = student->distant[student->order[2]]
                     - student->distant[student->order[1]];
}

int get_min_diff(int student_diff[3])
{
    int min = 21474836;
    for (int i = 0; i < 3; i++)
    {
        if (min > student_diff[i])
            min = student_diff[i];
    }
    return min;
}

void swap(t_student *student1, t_student *student2)
{
    t_student temp;
    temp = *student1;
    *student1 = *student2;
    *student2 = temp;
}

void select_sort(t_student student[10000])
{
    int MAX = 0;
    for (int i = 0; i < 9999; i++)
    {
        for (int j = i+1; j < 10000; j++)
        {
            if (student[i].diff[0] < student[j].diff[0] ||
            (student[i].diff[0] == student[j].diff[0] &&
                student[i].diff[1] < student[j].diff[1]))
            {
                swap(&student[i], &student[j]);
            }
        }
    }
}

int choose_school(t_student *student, int school_count[3])
{
    int school;

    school = student->order[0];
    if (school_count[school] < 3500)
    {
        school_count[school]++;
        return school;
    }

    school = student->order[1];
    if (school_count[school] < 3500)
    {
        school_count[school]++;
        return school;
    }

    school = student->order[2];
    school_count[school]++;
    return school;
}

void set_order(t_student *student)
{
    int temp;

    student->order[0] = 0;
    student->order[1] = 1;
    student->order[2] = 2;

    if (student->distant[student->order[0]] > student->distant[student->order[1]])
    {
        temp = student->order[0];
        student->order[0] = student->order[1];
        student->order[1] = temp;
    }
    if (student->distant[student->order[1]] > student->distant[student->order[2]])
    {
        temp = student->order[1];
        student->order[1] = student->order[2];
        student->order[2] = temp;
    }
    if (student->distant[student->order[0]] > student->distant[student->order[1]])
    {
        temp = student->order[0];
        student->order[0] = student->order[1];
        student->order[1] = temp;
    }
}

void run_contest(void)
{
    int school_posX[3], school_posY[3];
    t_student student[10000];
    int school_count[3] = { 0, 0, 0 };
    int min_school_index = 0;
    total = 0;

    for (int school_index = 0; school_index < 3; school_index++)
    {
        get_school_position(school_index, &school_posX[school_index], &school_posY[school_index]);
    }


    for (int people_index = 0; people_index < 10000; people_index++)
    {
        student[people_index].index = people_index;
        get_student_position(people_index, &student[people_index].posX, &student[people_index].posY);
        for (int school_index = 0; school_index < 3; school_index++)
        {
            student[people_index].distant[school_index] = get_distant(student[people_index].posX,student[people_index].posY, school_posX[school_index], school_posY[school_index]);
        }
        set_order(&student[people_index]);
        set_diff(&student[people_index]);

        }
    }
    select_sort(student);


    for (int people_index = 0; people_index < 10000; people_index++)
    {
        min_school_index = get_min_student_school(student[people_index].distant, school_count);
        set_student_school(student[people_index].index, min_school_index);
    }

    printf("total : %d\n", total);
    printf("school 0 : %d\n", school_count[0]);
    printf("school 1 : %d\n", school_count[1]);
    printf("school 2 : %d\n", school_count[2]);

}