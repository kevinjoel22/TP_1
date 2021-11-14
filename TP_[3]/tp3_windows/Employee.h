#ifndef employee_H_INCLUDED
#define employee_H_INCLUDED
#define NOMBRELEN 128
typedef struct
{
    int id;
    char nombre[NOMBRELEN];
    int horasTrabajadas;
    int sueldo;
}Employee;

Employee* employee_new(void);
Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldoStr);

Employee* employee_newParametrosAdd(int idStr,char* nombreStr,int horasTrabajadasStr, int sueldoStr);

void employee_delete();

int employee_setId(Employee* this,int id);
int employee_getId(Employee* this,int* id);

int employee_setNombre(Employee* this,char* nombre);
int employee_getNombre(Employee* this,char* nombre);

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas);
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas);

int employee_setSueldo(Employee* this,int sueldo);
int employee_getSueldo(Employee* this,int* sueldo);

int employee_imprimir(Employee* auxEmpleado, int indice);

#endif // employee_H_INCLUDED
