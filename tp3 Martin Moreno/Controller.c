#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"
#include "Controller.h"

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
    int todoOk = -1;
    FILE* pFile;

    if(path != NULL && pArrayListEmployee != NULL)
    {
        pFile = fopen(path, "r");

        if(pFile != NULL)
        {
            if(parser_EmployeeFromText(pFile, pArrayListEmployee))
            {
                todoOk = 1;
            }
            fclose(pFile);
        }
    }

    return todoOk;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
    int todoOk = -1;
    FILE* pFile;

    if(path != NULL && pArrayListEmployee != NULL)
    {
        pFile = fopen(path, "rb");

        if(pFile != NULL)
        {
            if(parser_EmployeeFromBinary(pFile, pArrayListEmployee))
            {
                todoOk = 1;
            }
            fclose(pFile);
        }
    }

    return todoOk;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{

    Employee* auxEmployee=newEmployee();
    int todoOk=0;
    int id=1001;
    int *indice;

    char newName[128];
    int newHours=0;
    int newSalary=0;

    int statusNombre=0;
    int statusHoras=0;
    int statusSueldo=0;

    if(pArrayListEmployee!=NULL)
    {
        indice = ll_get(pArrayListEmployee, id);
        auxEmployee = (Employee*) ll_get(pArrayListEmployee, *indice);
        while( auxEmployee != NULL)
        {
            id++;
            indice = ll_get(pArrayListEmployee, id);
            auxEmployee = (Employee*) ll_get(pArrayListEmployee, *indice);
        }


        if(id!=0)
        {
            fflush(stdin);
            printf("introdusca el nuevo Nombre\n");
            statusNombre=scanf("%s", newName);
            while(statusNombre!=1)
            {
                fflush(stdin);
                printf("introdusca el nuevo Nombre\n");
                statusNombre=scanf("%s", newName);
            }

            fflush(stdin);
            printf("introdusca las nuevas Horas\n");
            statusHoras=scanf("%d", &newHours);
            while(statusHoras!=1)
            {
                fflush(stdin);
                printf("introdusca las nuevas Horas\n");
                statusHoras=scanf("%d", &newHours);
            }

            fflush(stdin);
            printf("introdusca el nuevo Sueldo\n");
            statusSueldo=scanf("%d", &newSalary);
            while(statusSueldo!=1)
            {
                fflush(stdin);
                printf("introdusca el nuevo Sueldo\n");
                statusSueldo=scanf("%d", &newSalary);
            }
            auxEmployee = newEmployeeParam(id, newName, newHours, newSalary);
            if(auxEmployee!=NULL)
            {
                ll_add(pArrayListEmployee , auxEmployee);
                todoOk=1;
            }
        }


    }

    return todoOk;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
    char confirma = 's';
    int opcion=0;
    int valorInvalido =0;

    Employee* auxEmployee;

    char newName[128];
    int newHours=0;
    int newSalary=0;
    int auxId=0;

    int statusNombre=0;
    int statusHoras=0;
    int statusSueldo=0;

    int todoOk=1;
    int id;
    int* indice;

    system("cls");
    //controller_ListEmployee(pArrayListEmployee);
    printf("ingrese id del empleado a modificar: ");
    scanf("%4d",&id);

    indice = ll_get(pArrayListEmployee, (id-2));


    if( *indice == -1)
    {
        printf("no existe una persona con ese id\n\n");
    }
    else
    {
        auxEmployee = (Employee*) ll_get(pArrayListEmployee, *indice);
        if(auxEmployee==NULL)
        {
            printf("no existe un empleado con esa id\n\n");
        }
        else
        {

            auxId = auxEmployee->id;
            strcpy(newName, (auxEmployee->nombre));
            newHours = auxEmployee->horasTrabajadas;
            newSalary = auxEmployee->sueldo;

            printf("Seleccione que dato modificar\n");
            printf("1 Nombre\n");
            printf("2 Horas de trabajo\n");
            printf("3 Salario\n");
            fflush(stdin);
            scanf("%d", &opcion);

                        switch(opcion)
            {
            case 1:
                fflush(stdin);
                printf("introdusca el nuevo Nombre\n");
                statusNombre=scanf("%s", newName);
                while(statusNombre!=1)
                {
                    fflush(stdin);
                    printf("introdusca el nuevo Nombre\n");
                    statusNombre=scanf("%s", newName);
                }
                break;

            case 2:
                fflush(stdin);
                printf("introdusca la nueva cantidad de horas\n");
                statusHoras=scanf("%d", &newHours);
                while(statusHoras!=1)
                {
                    fflush(stdin);
                    printf("el valor debe ser numeros enteros,\n introdusca la nueva cantidad de horas\n");
                    statusHoras=scanf("%d", &newHours);
                }
                break;

            case 3:
                fflush(stdin);
                printf("introdusca el nuevo sueldo\n");
                statusSueldo=scanf("%d", &newSalary);
                while(statusSueldo!=1)
                {
                    fflush(stdin);
                    printf("el valor debe ser numeros enteros,\n introdusca el nuevo sueldo\n");
                    statusSueldo=scanf("%d", &newSalary);
                }
                break;

            default:
                printf("valor invalido\n");
                valorInvalido=1;
                break;
            }

            if(valorInvalido!=1)
            {
                printf("\nConfirma modificacion: ");
                fflush(stdin);
                scanf("%c", &confirma);
                if(confirma=='s')
                {
                    auxEmployee->id = auxId;
                    strcpy((auxEmployee->nombre), newName);
                    auxEmployee->horasTrabajadas = newHours;
                    auxEmployee->sueldo = newSalary;
                    /*
                    //intente con esto pero no funciono
                    ll_remove(pArrayListEmployee, *indice);
                    auxEmployee = newEmployeeParam(auxId, newName, newHours, newSalary);
                    ll_add(pArrayListEmployee, auxEmployee);
                    */
                    todoOk=0;
                }
                else
                {
                    todoOk=2;
                }
            }
        }
    }
    return todoOk;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
    int todoOk=0;
    //int tam = ll_len(pArrayListEmployee);
    int auxId;
    //int indice;
    char confirma;
    Employee* auxEmp;
    if(pArrayListEmployee!=NULL)
    {
        system("cls");
        printf("      Baja de Empleado     \n\n");
        controller_ListEmployee(pArrayListEmployee);
        printf("ingrese id: ");
        scanf("%d", &auxId);

        auxEmp = (Employee*) ll_get(pArrayListEmployee, auxId);

        if( auxEmp == NULL)
        {
            printf("no existe un empleado con esa id\n\n");
        }
        else
        {
            mostratEmployee(auxEmp);
            printf("Confirma borrado: ");
            fflush(stdin);
            scanf("%c", &confirma);
            if(confirma == 's')
            {
                ll_remove(pArrayListEmployee, auxId);
                todoOk=1;
            }
            else
            {
                todoOk = 2;
            }
        }

    }
    return todoOk;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
    int todoOk=0;
    int tam = ll_len(pArrayListEmployee);
    Employee* auxEmp;
    if(pArrayListEmployee != NULL)
    {
        todoOk=1;
        printf("  id     Nombre   Horas Trabajadas   sueldo\n");
        for(int i=0; i<tam; i++)
        {
            auxEmp=(Employee*) ll_get(pArrayListEmployee, i);
            if(auxEmp!= NULL)
            {
                mostratEmployee(auxEmp);
            }
        }
    }
    return todoOk;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
    int error=0;
    int opcion;
    printf("*** Ordenar ***\n\n");
    printf("1. Ordenar datos por id\n");
    printf("2. Ordenar datos por nombres\n");
    printf("3. Ordenar datos por horas trabajadas\n");
    printf("4. Ordenar datos por sueldo\n");
    printf("Ingrese opcion: ");
    fflush(stdin);
    scanf("%d",&opcion);
    if (opcion>4 || opcion <0)
    {
        error=0;
    }
    else
    {
        error=1;
        switch(opcion)
        {
        case 1:
            ll_sort(pArrayListEmployee, employeeSortById, 1);
            break;

        case 2:
            ll_sort(pArrayListEmployee, employeeSortByName, 1);
            break;

        case 3:
            ll_sort(pArrayListEmployee, employeeSortByHours, 1);
            break;

        case 4:
            ll_sort(pArrayListEmployee, employeeSortBySalary, 1);
            break;
        default:
            printf("opcion invalida");
            break;
        }

    }

    return error;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
    int len = ll_len(pArrayListEmployee);
    int error = 0;
    if(path != NULL && pArrayListEmployee != NULL)
    {
        FILE* fp=fopen(path,"w");
        Employee* auxEmployee = newEmployee();
        if(fp!=NULL)
        {
            for(int i=0; i<len; i++)
            {
                auxEmployee = (Employee*) ll_get(pArrayListEmployee,i);
                if(auxEmployee!=NULL)
                {
                    fprintf(fp,"%d,%s,%d,%d\n", auxEmployee->id, auxEmployee->nombre, auxEmployee->horasTrabajadas, auxEmployee->sueldo);
                    error =1;
                }
            }
        }
        else
        {
            printf("no se pudo leer el archivo\n");
            exit(EXIT_FAILURE);
        }
        fclose(fp);
    }


    return error;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
    /*
    verificar que la lista no este vacia
    abrir archivo para escritura si la lista no esta vacia
    si pudo abrir el archivo llamo a la funcion que guarda los datos en el archivo
    paso

    lograr guardar en archivo binario los datos de un linkedlist
    */
    int len = ll_len(pArrayListEmployee);
    int error = -1;
    Employee* auxEmployee;

    if(path != NULL && pArrayListEmployee != NULL)
    {
        FILE* fp=fopen(path,"wb");
        auxEmployee= newEmployee();
        if(fp!=NULL)
        {
            for(int i=0; i<len; i++)
            {
                auxEmployee = (Employee*) ll_get(pArrayListEmployee,i);
                if(auxEmployee!=NULL)
                {
                    fwrite(auxEmployee, sizeof(Employee), 1, fp);
                    error =1;
                }
            }
        }
        else
        {
            printf("no se pudo leer el archivo\n");
            exit(EXIT_FAILURE);
        }
        fclose(fp);
    }


    return error;
}

/*int obtenerIdMasAlto(LinkedList* pArrayListEmployee)
{
    int len = ll_len(pArrayListEmployee);
    int idMayor=-1;
    int idMayorFlag=1;
    if(pArrayListEmployee != NULL)
    {
        Employee* auxEmployee;
            for(int i=0; i<len; i++)
            {
                auxEmployee = (Employee*) ll_get(pArrayListEmployee,i);
                if(idMayorFlag==1)
                {
                 idMayor=auxEmployee->id;
                }
                else if(auxEmployee->id >idMayor)
                {
                    idMayor=auxEmployee->id;
                }

            }
    }


    return idMayor;
}*/
//falta ll_deleteLinkedList


