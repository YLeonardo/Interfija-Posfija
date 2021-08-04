#include <stdio.h>
#include "pila.h"

int main (){
	char cadena[TAMMAX],cadenapost[TAMMAX]; //declaramos una cadena para la expresion interfija
	int i;
	pila p;//declaramos una pila
	DATO eltope;//una variable para el tope

	printf("\n***********************************************");
	printf("\n        EXPRESI%cN INTERFIJA A POSFIJA ",224);
	printf("\n***********************************************\n");
	printf("\n\n La expresi%cn en forma interfija: ",162);
	gets(cadena);
	printf("%s",cadena);
	inic_pil(&p);//damos valores iniciales a la pila
	crea_pil(&p);//asignamos memoria a la pila declarada
/********************************************************************************************************/
/*									EVALUAR PARENTESIS 												    */
/********************************************************************************************************/
	if(parentesis(&p,&cadena[0])==1){
		return 1;
	}
/***************************************************************************************************/
/*										EVALUAR OPERADORES										   */
/***************************************************************************************************/
	operador(&p,&cadena[0],&cadenapost[0]);

	for(i=0;cadenapost[i]!='\0';i++){
		printf("%c",cadenapost[i]);
	}

	printf("\n");
	elim_pil(&p);//libera la memoria usada por la pila
	return 0;
}

/***************************************************************************************/
/*	                                EVALUAR PARENTESIS
/***************************************************************************************/
int parentesis(pila* p, char* cadena){
	int i;
	DATO eltope;

	for(i=0;cadena[i]!='\0';i++){//recorre la expresion

		if(cadena[i]=='('||cadena[i]=='['||cadena[i]=='{'){
			push_pil(p,cadena[i]);//si encuentra un operador que abre
			tope_pil(&eltope,p);//retorna el dato que hay en el tope de la pila
		}
		
		if(cadena[i]==')'){
			if(p->tope==0){//verifica si la pila esta vacia
				printf("\n\n cadena inv%clida",160);//cierra el programa diciendo que es invalida la expresion
				return 1;
			}else{
				if(eltope=='('){
					pop_pil(p);// elimina el tope de la pila si se casa el parentesis de cierre
				}else{
					printf("\n\n cadena inv%clida",160);//si no imprime cadena invalida y cierra el programa
					return 1;
				}
				tope_pil(&eltope,p);//asigna un nuevo tope de la pila despues de haber eliminado
			}
		}
	
		if(cadena[i]==']'){
			if(p->tope==0){
			    printf("\n\n cadena inv%clida",160);
				return 1;
			}else{
				if(eltope=='['){
					pop_pil(p);
				}else{
					printf("\n\n cadena inv%clida",160);
					return 1;
				}
				tope_pil(&eltope,p);
			}
		}

		if(cadena[i]=='}'){
			if(p->tope==0){
				printf("\n\n cadena inv%clida",160);
				return 1;
			}else{
				if(eltope=='{'){
					pop_pil(p);
				}else{
					printf("\n\n cadena inv%clida",160);
					return 1;
				}
				tope_pil(&eltope,p);
			}
		}
	}
	
	if(p->tope!=0){//si la pila esta vacia despues de haber recorrido la expresion la cadena es valida
		printf("\n\n cadena inv%clida",160);
		return 1;
	}
	return OK;
}

/*************************************************************************************************************/
/*								             EVALUAR OPERADORES
/************************************************************************************************************/
void operador(pila* p,char* cadena,char* cadenapost){
	int i,n=0;
	DATO eltope;

	printf("\n\n POSFIJA: ");
	for(i=0;cadena[i]!='\0';i++){
		
		if(cadena[i]=='('||cadena[i]=='['||cadena[i]=='{'){
			push_pil(p,cadena[i]);
		}

		if(cadena[i]==')'){
			tope_pil(&eltope,p);

			while(eltope!='('){
				cadenapost[n]=eltope;
				n++;
				pop_pil(p);
				tope_pil(&eltope,p);
			}
			pop_pil(p);
		}
		
		if(cadena[i]==']'){
			tope_pil(&eltope,p);

			while(eltope!='['){
				cadenapost[n]=eltope;
				n++;
				pop_pil(p);
				tope_pil(&eltope,p);
			}
			pop_pil(p);
		}

		if(cadena[i]=='}'){
			tope_pil(&eltope,p);

			while(eltope!='{'){
				cadenapost[n]=eltope;
				n++;
				pop_pil(p);
				tope_pil(&eltope,p);
			}
			pop_pil(p);
		}

		if(cadena[i]=='+'||cadena[i]=='-'){
			if(p->tope==0){
				push_pil(p,cadena[i]);
			}else{
				tope_pil(&eltope,p);
				if(eltope=='+'||eltope=='-'||eltope=='^'||eltope=='*'||eltope=='/'){
					cadenapost[n]=eltope;
					n++;
					pop_pil(p);
					push_pil(p,cadena[i]);
				}else{
					push_pil(p,cadena[i]);
				}	
			}
		}

		if(cadena[i]=='*'||cadena[i]=='/'){
			if(p->tope==0){
				push_pil(p,cadena[i]);	
			}else{
				tope_pil(&eltope,p);
				
				if(eltope=='^'||eltope=='*'||eltope=='/'){
					cadenapost[n]=eltope;
					n++;
					pop_pil(p);
					push_pil(p,cadena[i]);
				}else{
					push_pil(p,cadena[i]);
				}
			}
		}

		if(cadena[i]=='^'){
			if(p->tope==0){
				push_pil(p,cadena[i]);	
			}else{
				tope_pil(&eltope,p);
				
				if(eltope=='^'){
					cadenapost[n]=eltope;
					n++;
					pop_pil(p);
					push_pil(p,cadena[i]);
				}else{
					push_pil(p,cadena[i]);
				}
			}
		}

		if(cadena[i]!='('&&cadena[i]!=')'&&cadena[i]!='['&&cadena[i]!=']'&&cadena[i]!='{'&&cadena[i]!='}'&&cadena[i]!='+'&&cadena[i]!='-'&&cadena[i]!='*'&&cadena[i]!='/'&&cadena[i]!='^'){
			cadenapost[n]=cadena[i];
			n++;
		}
	}

	while(p->tope!=0){
		tope_pil(&eltope,p);
		cadenapost[n]=eltope;
		n++;
		pop_pil(p);	
	}
	cadenapost[n]='\0';
}

/*********************************************************
Definir las funciones que se utilizan para el control
  de las pilas.
**********************************************************/

/* Función interna que hace crecer el arreglo 
   dentro de la pila
RECIBE: Apuntador a la pila que ya está llena
REGRESA: La misma pila con espacio adicional
     o código de error en caso que ya no haya memoria
NOTAS: El arreglo crece en TAMCRE espacios de memoria
*/
int crece(pila* p){
  /*Apuntador a arreglo más grande*/
  DATO* nuevo;
  int i;
  
  nuevo = (DATO*)malloc(sizeof(DATO)*(p->tam+TAMCRE));
  if(!AP_VAL(nuevo))
    return OVERFLOW;
  /*Copiar datos al arreglo nuevo*/
  for(i=0;i<p->tam;i++)
    nuevo[i] = p->dato[i];
  
  if (AP_VAL(p->dato))
    free(p->dato); 
  
  p->dato = nuevo;
  p->tam+=TAMCRE;
  return OK;
}

/**********************************************************
                C O N S T R U C T O R E S
/*********************************************************/
/* Inicializar la pila.
Objetivo: Dar valores iniciales. Se debe invocar después
   de declarar una variable tipo pila.
RECIBE:
   Apuntador a pila a ser inicializada
REGRESA:
   Código de error. 
REQUIERE: 
   Que el apuntador que recibie no sea NULL
*/
int inic_pil(pila* p){
  if(!AP_VAL(p))
    return AP_INV;
  
  p->dato = NULL;
  p->tope = 0;
  p->tam  = 0;
  return OK;
}

/* Asignar memoria dinámica.
Objetivo: Dar valores iniciales. Y solicitar memoria para
   El arreglo que almacenará los datos. Crea una pila vacia.
RECIBE:
   Apuntador a pila a ser creada
REGRESA:
   Código de error. 
REQUIERE: 
   Que el apuntador que recibie no sea NULL y que 
   se invoque a la función eliminar cuando ya no se use
   la pila.
*/
int crea_pil(pila* p){
  if(!AP_VAL(p))
    return AP_INV;
  
  if(AP_VAL(p->dato))
    elim_pil(p); 
  p->dato = (DATO*)malloc(sizeof(DATO)*TAMMAX);
  if(!AP_VAL(p->dato))
    return OVERFLOW;
  
  p->tope = 0;
  p->tam = TAMMAX;
  return OK;
}

/* Regresa la memoria dinÃ¡mica.
Objetivo: Destruir la pila y regresar la memoria dinÃ¡mica.
RECIBE:
   Apuntador a pila a ser creada
REGRESA:
   Código de error. 
REQUIERE: 
   Que la pila haya sido creada. 
*/
int elim_pil(pila* p){
  if(!AP_VAL(p))
    return AP_INV;
  
  if(p->dato)
    free(p->dato); 
  inic_pil(p);
  return OK;
}

/**********************************************************
                M O D I F I C A D O R E S
/*********************************************************/

/* Inserta un dato en la pila.
Objetivo: Insertar un dato en la pila. En caso de que la
  pila está llena busca hacer crecer el arreglo. Si no hay
  memoria regresará OVERFLOW
RECIBE:
   Apuntador a pila a ser creada
   Dato a ser insertado en la pila
REGRESA:
   Código de error. 
REQUIERE: 
   Que la pila haya sido creada y un apuntador no NULL
*/
int push_pil(pila* p,DATO d){
  int err;
  if(!AP_VAL(p))
    return AP_INV;
  if(!TIE_ESP(p))
	  if(err = crece(p))
      return err;
  
  p->dato[p->tope++]= d;
  return OK;
}

/* Eliminar un dato en la pila.
Objetivo: Eliminar un dato de la pila. En caso de que
   la pila está vacia regresa UNDERFLOW.
RECIBE:
   Apuntador a pila de que se sacará el dato
REGRESA:
   Código de error. 
REQUIERE: 
   Que haya datos en la pila, apuntador no NULL
*/
int pop_pil(pila* p){
  if(!AP_VAL(p))
    return AP_INV;
  if(!TIE_DAT(p))
    return UNDERFLOW;
  
  p->tope--;
  return OK;
}

/* Tope de la pila
Objetivo: Regresa dato en el tope de la pila.
RECIBE:
   Apuntador a pila de que se sacará el dato
   Apuntador a dato en que se regresará el valor
      que está en el tope de la pila
REGRESA:
   Código de error. 
REQUIERE: 
   Que haya datos en la pila, apuntadores no NULL
*/
int tope_pil(DATO* d, const pila* p){
  if(!(AP_VAL(p) && AP_VAL(d)) )
    return AP_INV;
  if(!TIE_DAT(p))
    return UNDERFLOW;
  
  *d = p->dato[p->tope-1];  
  return OK;
}

/* A cadena
Objetivo: Generar una representación de la pila 
   Como cadena. Usa la constante FORMATO para 
   convertir cada dato de la pila a cadena.
   Debe garantizar la cadena de salida tiene espacio
     para almcenar la representación completa.
RECIBE:
   Apuntador a cadena que tendrá la representación
   Apuntador pila que será convertida a cadena.
REGRESA:
   El mismo apuntador que regresa. En caso de error
   Agrega a la cadena el valor "NULL"   
REQUIERE: 
   Apuntadores no NULL
*/
char* tostr_pil(char* s, const pila* p){
  char dato[TAMDAT];
  int i;
  if(!(AP_VAL(s)&&AP_VAL(p)))
    return s;
  
  strcpy(s,"[");
  for(i=0;i<p->tope;i++){
    sprintf(dato,FORMATO,p->dato[i]);
	  strcat(s,dato);
  }
  strcat(s,"]\n");
  return s;
}