typedef struct crs
{
    char courseName[25];
    long courseId;
    float grade;
} course;
struct std
{
    char firstName[20];
    char lastName[20];
    long studentNumber;
    course course1;
};
typedef struct std student;