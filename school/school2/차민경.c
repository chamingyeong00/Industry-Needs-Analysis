#include <stdio.h>

extern void get_school_position(int school_index, int* posX, int* posY);
extern void get_student_position(int student_index, int* posX, int* posY);
extern void set_student_school(int student_index, int school_index);
static int total = 0;

typedef struct student {
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

int check_school_max(int school_index, int school_count[3]) {
    if (school_count[school_index] >= 3500)
        return 0;
    return 1;
}

void set_diff(t_student *student){
    student->diff[0] = student->distant[student->order[1]]
                     - student->distant[student->order[0]];

    student->diff[1] = student->distant[student->order[2]]
                     - student->distant[student->order[1]];
}

void swap(t_student *student1, t_student *student2)
{
    t_student temp;
    temp = *student1;
    *student1 = *student2;
    *student2 = temp;
}

void sort_by_diff(t_student student[10000])
{
    for (int i = 0; i < 9999; i++)
    {
        for (int j = i+1; j < 10000; j++)
        {
            if (student[i].diff[0] < student[j].diff[0] ||
            (student[i].diff[0] == student[j].diff[0] && student[i].diff[1] < student[j].diff[1]))
            {
                swap(&student[i], &student[j]);
            }
        }
    }
}

int choose_school(t_student *student, int school_count[3])
{
    int school_index;

    school_index = student->order[0];
    if (check_school_max(school_index, school_count))
    {
        school_count[school_index]++;
        return school_index;
    }

    school_index = student->order[1];
    if (check_school_max(school_index, school_count))
    {
        school_count[school_index]++;
        return school_index;
    }

    school_index = student->order[2];
    school_count[school_index]++;
    return school_index;
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
    int assigned_school = 0;
    total = 0;

    for (int school_index = 0; school_index < 3; school_index++)
    {
        get_school_position(school_index, &school_posX[school_index], &school_posY[school_index]);
    }

    for (int student_index = 0; student_index < 10000; student_index++)
    {
        student[student_index].index = student_index;
        get_student_position(student_index, &student[student_index].posX, &student[student_index].posY);
        for (int school_index = 0; school_index < 3; school_index++)
        {
            student[student_index].distant[school_index] = get_distant(
            student[student_index].posX,
            student[student_index].posY,
            school_posX[school_index],
            school_posY[school_index]
            );
        }
        set_order(&student[student_index]);
        set_diff(&student[student_index]);
    }
    sort_by_diff(student);
    for (int student_index = 0; student_index < 10000; student_index++)
    {
        assigned_school = choose_school(&student[student_index], school_count);
        total += student[student_index].distant[assigned_school];
        set_student_school(student[student_index].index, assigned_school);
    }

//    printf("total : %d\n", total);
//    printf("school 0 : %d\n", school_count[0]);
//    printf("school 1 : %d\n", school_count[1]);
//    printf("school 2 : %d\n", school_count[2]);

}