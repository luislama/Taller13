#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex;
pthread_cond_t condicionConsumidor = PTHREAD_COND_INITIALIZER;
pthread_cond_t condicionProductor = PTHREAD_COND_INITIALIZER;

int total_items = 0;
int tam_cola = 0;
int cola = 0;

int producidos = 0;

double tiempo_prod = 0;
double tiempo_cons = 0;

void mostrarinfo(int nhilos_prod, int nhilos_cons, double tiempo_cons, double tiempo_prod, int total_items);

void* productor(void * arg){
  
  pthread_mutex_lock(&mutex);
    int myid = (*((int *)arg)); 
  pthread_mutex_unlock(&mutex);

  int c = 0;
  int p = 0;
  int debeProducir = 1;
  while(debeProducir == 1){
    pthread_mutex_lock(&mutex);

    while( cola == tam_cola )
      pthread_cond_wait(&condicionProductor,&mutex);
    if( producidos == total_items )
      debeProducir = 0;
    else {    
      usleep(tiempo_prod);
      cola++;
      producidos++;
      c = cola;
      p = producidos;
      printf("Productor  %d ha producido 1 item, tamaño cola = %d\n",myid,c);
      printf("producidos: %d de %d\n",p,total_items);
    }
    
    if(producidos == total_items)
        pthread_cond_broadcast(&condicionConsumidor);
    else
        pthread_cond_signal(&condicionConsumidor);
    pthread_mutex_unlock(&mutex);
    
  }
  pthread_mutex_lock(&mutex);
    printf("termino hilo productor %d\n",myid);
  pthread_mutex_unlock(&mutex);
  return (void*)1;
}

void* consumidor(void * arg){ 

  pthread_mutex_lock(&mutex);
    int myid = (*((int *)arg)); 
  pthread_mutex_unlock(&mutex);

  int c = 0;
  int puedeConsumir = 1;
  while(puedeConsumir == 1)
  {  
    pthread_mutex_lock(&mutex);

      while( cola == 0 && producidos < total_items)
        pthread_cond_wait(&condicionConsumidor,&mutex);

      if( producidos == total_items && cola == 0)
        puedeConsumir = 0;
      else if(cola>=1){
        usleep(tiempo_cons);
        cola--;
        c=cola;
        printf("Consumidor %d ha consumido 1 item, tamaño cola = %d\n",myid,c);
    
      }
    pthread_cond_signal(&condicionProductor);
    pthread_mutex_unlock(&mutex);      
  }
  printf("termino hilo consumidor %d\n",myid);
  return (void*)1;  
}


int main(int argc, char** argv)
{
  if (argc!=7)
  {
  	printf("Uso del programa <num_hilos_prod> <tiempo_prod> <num_hilos_cons> <tiempo_cons> <tam_cola> <total_items>\n");
  	return -1;
  }
  else{
    int nhilos_prod = atoi(argv[1]);
    tiempo_prod = atof(argv[2])*1000000;
    int nhilos_cons = atoi(argv[3]);
    tiempo_cons = atof(argv[4])*1000000;
    tam_cola = atoi(argv[5]);
    total_items = atoi(argv[6]);

    mostrarinfo(nhilos_prod, nhilos_cons, tiempo_cons, tiempo_prod,total_items);
 
    int maxHilos = 0;
    if(nhilos_cons > nhilos_prod)
      maxHilos = nhilos_cons;
    else
      maxHilos = nhilos_prod;
  
    pthread_t *listProd = (pthread_t *)malloc(sizeof(pthread_t)*nhilos_prod);  
    pthread_t *listCons = (pthread_t *)malloc(sizeof(pthread_t)*nhilos_cons);

    pthread_mutex_init(&mutex, NULL);
    
    //ME RESULTO IMPOSIBLE ENVIAR LOS INDEX A PARTIR DE "i" DEL FOR QUE 
    //CREABA LOS HILOS Y QUE SE IMPRIMAN BIEN
    int *ids =(int *)malloc(sizeof(int)*maxHilos);
    for(int i = 0; i<maxHilos; i++)
      *(ids+i)=i+1;

    producidos=0;
    for(int i = 0; i<maxHilos ; i++ )
    {
      //int c = i;
      //int p = i;
      if(i<nhilos_prod)     
        //pthread_create(&(listProd[i]),NULL,productor,&(ids[i]));  -->FALLA
        //pthread_create(&(listProd[i]),NULL,productor,&p);         -->FALLA
        pthread_create(&(listProd[i]),NULL,productor,ids+i);
      if(i<nhilos_cons)
        //pthread_create(&(listCons[i]),NULL,consumidor,&(ids[i])); -->FALLA
        //pthread_create(&(listCons[i]),NULL,consumidor,&c);        -->FALLA
        pthread_create(&(listCons[i]),NULL,consumidor,ids+i); 
    }

    for(int i = 0; i<maxHilos ; i++ )
    {
      if(i<nhilos_prod)     
        pthread_join(listProd[i],NULL);
      if(i<nhilos_cons)
        pthread_join(listCons[i],NULL); 
    }
  
  return 0;
  }
}

void mostrarinfo(int nhilos_prod, int nhilos_cons, double tiempo_cons, double tiempo_prod, int total_items){
	printf("Número de productores: %d\n", nhilos_prod);
	printf("Número de consumidores: %d\n", nhilos_cons);
	printf("Tiempo de consumo: %.2f segundos\n", tiempo_cons/1000000);
	printf("Tiempo de producción: %.2f segundos\n", tiempo_prod/1000000);
	printf("Total de ítems a producir: %d elementos.\n\n", total_items);
}
