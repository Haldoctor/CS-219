#include <stdio.h>
typedef struct {
    int id;
    char description[1024];
} Stu;

void disp_struct(Stu& stud) {  
    printf("Student_id:%d\tinfo:%s\n", stud.id, stud.description);
}

int main() {
    Stu stum = {3, "NAZHA"};
    disp_struct(stum);  
    return 0;
}
