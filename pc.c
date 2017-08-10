#include <stdio.h>
#include <pthread.h>
#include <cstdlib>

pthread_mutex_t mutex;
pthread_cond_t condicionConsumidor;
pthread_cond_t condicionProductor;
int tam_cola = 0;
int cola=0;
int total_items = 0;
int producidos = 0;


void* productor(void * arg)
{ 
  int salir=0;
  while(salir==0)
  {
    pthread_mutex_lock(&mutex);
    while(cola == tam_cola)
      pthread_cond_wait(&condicionProductor,&mutex)
    cola++;
    producidos++;
    if(producidos == total_items)
      salir = 1;
    pthread_mutex_unlock(&mutex);
    pthread_cond_broadcast(&condicionConsumidor);
  } 

  return (void*)1;
}

void* consumidor(void * arg)
{ 
  int salir=0;
  while(salir==0)
  {  
    pthread_mutex_lock(&mutex);
    while(cola == 0)
      pthread_condition_wait(&condicionCOnsumidor,&mutex)
    cola--;  
    if(producidos == total_items && cola == 0)
      salir = 1;
    pthread_mutex_unlock(&mutex);
    pthread_cond_broadcast(&condicionProductor);
  }
  return (void*)1;  
}

int main(int argc, char** argv)
{
  if (argc!=7){
  	printf("Uso del programa <num_hilos_prod> <tiempo_prod> <num_hilos_cons> <tiempo_cons> <tam_cola>
		<total_items>\n");
  	return -1;
  }
  
  int nhilos_prod = atoi(argv[1]);
  int tiempo_prod = atof(argv[2]);
  int nhilos_cons = atoi(argv[3]);
  int tiempo_cons = atof(argv[4]);
  tam_cola = atoi(argv[5]);
  cola = tam_cola;
  total_items = atoi(argv[6]);

  int maxHilos = 0;
  if(nhilos_cons > nhilos_pro)
    maxhilos = nhilos_cons
  else
    maxhilos = nhilos_prod
  
  pthread_t *listProd = (pthread_t *)malloc(sifeof(pthread_t)*nhilos_prod);  
  pthread_t *listCons = (pthread_t *)malloc(sifeof(pthread_t)*nhilos_cons);

  for(int i = 0; i<maxHilos ; i++ )
  {
    if(i<nhilos_cons)
      pthread_create(&(listCons[i]),NULL,productor,null); 
    if(i<nhilos_prod)     
      pthread_create(&(listProd[i]),NULL,productor,null);
  }

  return 0;
}
