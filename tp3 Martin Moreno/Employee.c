#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Employee.h"
/*
int employee_getNombre(Employee* this,char* nombre)
{
    int error=0;
    return error;
}
*/

int employee_setId(Employee* this,int id)
{
    int todoOk = 0;
    if(this!=NULL && id > 0)
    {
        this ->id= id;
        todoOk= 1;
    }
    return todoOk;
}
int employee_getId(Employee* this,int* id)
{
    int todoOk = 0;
    if(this!=NULL && id != NULL)
    {
        *id = this->id;
        todoOk= 1;
    }
    return todoOk;
}

int employee_setNombre(Employee* this,char* nombre)
{
    int todoOk = 0;
    if(this!=NULL && nombre != NULL && strlen(nombre) > 1)
    {
        strcpy(this->nombre, nombre);
        todoOk=1;
    }
    return todoOk;
}
int employee_getNombre(Employee* this,char* nombre)
{
    int todoOk = 0;
    if(this!=NULL && nombre != NULL)
    {
        strcpy(nombre, this->nombre);
        todoOk= 1;
    }
    return todoOk;
}

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas)
{
    int todoOk = 0;
    if(this!=NULL && horasTrabajadas > 0)
    {
        this ->horasTrabajadas= horasTrabajadas;
        todoOk= 1;
    }
    return todoOk;
}
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas)
{
    int todoOk = 0;
    if(this!=NULL && horasTrabajadas != NULL)
    {
        *horasTrabajadas = this->horasTrabajadas;
        todoOk= 1;
    }
    return todoOk;
}

int employee_setSueldo(Employee* this,int sueldo)
{
    int todoOk = 0;
    if(this!=NULL && sueldo > 0)
    {
        this ->sueldo= sueldo;
        todoOk= 1;
    }
    return todoOk;
}
int employee_getSueldo(Employee* this,int* sueldo)
{
    int todoOk = 0;
    if(this!=NULL && sueldo != NULL)
    {
        *sueldo = this->sueldo;
        todoOk= 1;
    }
    return todoOk;
}

int employeeSortByName(void* empleadoA, void* empleadoB)
{
    int retorno = 0;
    char nombresA[20];
    char nombresB[20];

    if(employee_getNombre((Employee*)empleadoA, nombresA) &&
        employee_getNombre((Employee*)empleadoA, nombresB))
    {
        retorno = strcmp(nombresA, nombresB);
    }

    return retorno;
}

int employeeSortById(void* empleadoA, void* empleadoB)
{
    int retorno = 0;
    int idA;
    int idB;

    if(employee_getId((Employee*)empleadoA, &idA) &&
        employee_getId((Employee*)empleadoA, &idB))
    {
        retorno = idA - idB;
    }

    return retorno;
}

int employeeSortByHours(void* empleadoA, void* empleadoB)
{
    int retorno = 0;
    int horasA;
    int horasB;

    if(employee_getHorasTrabajadas((Employee*)empleadoA, &horasA) &&
        employee_getHorasTrabajadas((Employee*)empleadoA, &horasB))
    {
        retorno = horasA - horasB;
    }

    return retorno;
}

int employeeSortBySalary(void* empleadoA, void* empleadoB)
{
    int retorno = 0;
    int salarioA;
    int salarioB;

    if(employee_getSueldo((Employee*)empleadoA, &salarioA) &&
        employee_getSueldo((Employee*)empleadoA, &salarioB))
    {
        retorno = salarioA - salarioB;
    }

    return retorno;
}

Employee* newEmployee()
{
    Employee* nuevoEmpleado = (Employee*) malloc(sizeof(Employee));
    if(nuevoEmpleado!=NULL)
    {
        nuevoEmpleado->id = 0;
        strcpy(nuevoEmpleado->nombre, "nombre apellido");
        nuevoEmpleado->horasTrabajadas = 0;
        nuevoEmpleado->sueldo = 0;
    }
    return nuevoEmpleado;
}

Employee* newEmployeeParam(int id, char* nombre, int horasTrabajadas, int sueldo)
{
    Employee* nuevoEmpleado = newEmployee();
    if(nuevoEmpleado!=NULL)
    {
        if(!(employee_setId(nuevoEmpleado, id)
        && employee_setNombre(nuevoEmpleado, nombre)
        && employee_setHorasTrabajadas(nuevoEmpleado, horasTrabajadas)
        && employee_setSueldo(nuevoEmpleado, sueldo)))
        {
            free(nuevoEmpleado);
            nuevoEmpleado = NULL;
        }
    }
    return nuevoEmpleado;
}

void mostratEmployee(Employee* empleado)
{
    printf("%4d %10s      %4d           %6d\n", empleado->id, empleado->nombre, empleado->horasTrabajadas, empleado->sueldo);
}
