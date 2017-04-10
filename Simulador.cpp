#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{
    char nombre[20];
    char apellido[20];
    int cedula;
    int activo;
    int edad;
}registro;

#define TAMANO_REGISTRO sizeof(registro)
#define NOMBRE_ARCHIVO "archi.txt"

void v_inicializar(FILE *fp, char *c_archivo) 
{
    fp=fopen(c_archivo,"rb+");
    if(fp==NULL)
        printf("\n Error: Al abrir el archivo ");
        
    fclose(fp);
    fp=fopen(c_archivo,"wb+");
    if(fp==NULL)
        printf("\n Error: Al abrir el archivo ");
        
    printf("\n Archivo Abierto ");
}

int i_buscar (FILE *fp, int i_clave, registro *r_registro)
{

    registro r_reg;
    if(fp==NULL)
              return -1;
    
 
    fseek(fp,0,SEEK_SET);
    while (fread(&r_reg,TAMANO_REGISTRO,1,fp))
    {   
    
        if(i_clave==r_reg.cedula && r_reg.activo==1)
        {
                                 
           strcpy(r_registro->nombre,r_reg.nombre);
           strcpy(r_registro->apellido,r_reg.apellido);
           //r_registro->edad=r_reg.edad;
           r_registro->cedula=r_reg.cedula;            
           r_registro->activo=r_reg.activo;
           fseek(fp,-TAMANO_REGISTRO,SEEK_CUR);                                         
           return 1;
        }
    }
    return 0;       
}

void v_agregar(FILE *fp)                  
{
    if(fp==NULL)    
        printf("\n Error: ");
        
    int n;
    int i_clave;
    char nombre[30];
    char apellido[30];
    int cedula;
    //int edad; 
    
    registro r_registro;
      
    printf("\n Cedula : ");
    scanf("%d",&i_clave);
    
    n=i_buscar(fp,i_clave,&r_registro);
    printf(" %d ",n);
    
    if(n==0)
    {
       
        printf("\n\n Nombre: ");
        scanf("%s",nombre);
        printf(" Apellido: ");
        scanf("%s",apellido);
        //printf(" Edad: ");
        //scanf("%d",&edad);
        
        strcpy(r_registro.nombre,nombre);
        strcpy(r_registro.apellido,apellido);
        //r_registro.edad = edad;
        r_registro.cedula = i_clave;
        r_registro.activo = 1;
        fseek(fp,0,SEEK_END);
        fwrite(&r_registro,TAMANO_REGISTRO,1,fp);
        
        printf(" Activo: %d ",r_registro.activo);
        printf("\n Registro agregado");
    }
    if(n==1)
    {
        printf("\n\n Error: Cedula Registrada ");
    }
}

void v_imprimir(FILE *fp)            
{
    if(fp==NULL)    
        printf("\n Error: ");
        
    registro r_registro;
    printf("\nActivo \t\t Cedula \t\tApellido \t\t Nombre ");//\tEdad");
    fseek(fp,0,SEEK_SET);
    while(fread(&r_registro,TAMANO_REGISTRO,1,fp))
    {   
        if(r_registro.activo == 1)
        {
            printf("\n %d",r_registro.activo);
            printf("\t\t%d",r_registro.cedula);
            printf("\t\t%s",r_registro.apellido);
            printf("\t\t%s",r_registro.nombre);
            //printf("\t\t%d",r_registro.edad);
        }
    }
}

int i_modificar(FILE *fp, int i_clave)       
{
    if(fp==NULL)    
        printf("\n Error: ");
        
    int n;
    registro r_registro;
    n=i_buscar(fp,i_clave,&r_registro);
    printf(" %d ",n);
    
    if(n==0)
    {
        printf("\n\n Registro No Encontrado ");
        return 0;
    }   
    if(n==1)
    {
        
        printf("\n\n Nombre: ");
        scanf("%s",r_registro.nombre);
        printf(" Apellido: ");
        scanf("%s",r_registro.apellido);
        /*printf(" Edad: ");
        scanf("%d",&r_registro.edad);
        strcpy(r_registro.nombre,"X");
        strcpy(r_registro.apellido,"X");*/
        r_registro.activo = 1;
        fwrite(&r_registro,TAMANO_REGISTRO,1,fp);
        
        printf(" Activo: %d ",r_registro.activo);
        printf("\n Registro Modificado ");
        return 1;
    }
    if(n==-1)
    {
        printf("\n Error: Registro No Modificado ");
        return -1;
    }
    fseek(fp,-TAMANO_REGISTRO,SEEK_CUR);
}

int i_eliminar(FILE *fp, int i_clave)   
{ 
    if(fp==NULL)    
        printf("\n Error: ");
    
    int n;
    registro r_registro;
   
    n=i_buscar(fp,i_clave,&r_registro);
    printf(" %d ",n);
    
    if(n==0)
    {
        printf("\n\n Registro No Encontrado ");
        return 0;
    }
       
    if(n==1)
    {  
        //strcpy(r_registro.nombre,"Xooo");
        //strcpy(r_registro.apellido,"Xooo");
        r_registro.activo = 0;
        fwrite(&r_registro,TAMANO_REGISTRO,1,fp);
        printf("\n\n Registro Eliminado ");
        return 1;
    }
    if(n==-1)
    {
        printf("\n Error: Registro No Borrado ");
        return -1;
    }
    fseek(fp,TAMANO_REGISTRO,SEEK_SET);
}

void v_menu()
{
    printf("\n\n\n\n\n\n\n\n\t\t\t     1. Inicializar ");
    printf("\n\t\t\t     2. Imprimir Registro ");
    printf("\n\t\t\t     3. Agregar Registro ");
    printf("\n\t\t\t     4. Buscar Registro ");
    printf("\n\t\t\t     5. Modificar Registro ");
    printf("\n\t\t\t     6. Eliminar Registro ");
    printf("\n\t\t\t     0. Salir "); 
    printf("\n\t\t\t     Selecione su opcion: ");
}

int main()
{
    int n;
    int i_clave;
    registro r_registro;
    
    FILE *fp=fopen(NOMBRE_ARCHIVO,"rb+");
    if(fp==NULL)
    {
        fp=fopen(NOMBRE_ARCHIVO,"wb+");
        if(fp==NULL)
        {
                printf("\nError al abrir el archivo");
        }
    }
  
    else
    {
        system("cls");
        int opc;
    
        do
        {
            v_menu();
            scanf("%d",&opc);
            system("cls");   
            switch(opc)
            {
                case 1: v_inicializar(fp,NOMBRE_ARCHIVO);break;
                case 2: v_imprimir(fp);break;
                case 3: v_agregar(fp);break;
                case 4: i_buscar(fp,i_clave, &r_registro);break;
                case 5: 
                    { 
                        printf("\n Cedula: ");
                        scanf("%d",&i_clave);
                        n=i_modificar(fp,i_clave);
                        printf("\n %d ",n);
                        break;
                    }
            
                case 6: 
                    {
                        printf("\n Cedula: ");
                        scanf("%d",&i_clave);
                        n=i_eliminar(fp,i_clave);
                        printf("\n %d ",n);
                        break;
                    }
            }
        }while(opc!=0);
    }
    fclose(fp);
    getch();
}
