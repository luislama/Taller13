#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

pthread_mutex_t mutex;
pthread_cond_t condicionConsumidor;
pthread_cond_t condicionProductor;

int tam_cola = 0;

void mostrarinfo(int nhilos_prod, int nhilos_cons, double tiempo_cons, double tiempo_prod, int total_items);

int main(int argc, char** argv)
{
  if (argc!=7){
  	printf("Uso del programa <num_hilos_prod> <tiempo_prod> <num_hilos_cons> <tiempo_cons> <tam_cola> <total_items>\n");
  	return -1;
  }
  
  int nhilos_prod = atoi(argv[1]);
  double tiempo_prod = atof(argv[2]);
  int nhilos_cons = atoi(argv[3]);
  double tiempo_cons = atof(argv[4]);
  tam_cola = atoi(argv[5]);
  int total_items = atoi(argv[6]);

  mostrarinfo(nhilos_prod, nhilos_cons, tiempo_cons, tiempo_prod, total_items);

  condicionConsumidor = PTHREAD_COND_INITIALIZER;
  condicionProductor = PTHREAD_COND_INITIALIZER;


  return 0;
}

void mostrarinfo(int nhilos_prod, int nhilos_cons, double tiempo_cons, double tiempo_prod, int total_items){
	printf("Número de productores: %d\n", nhilos_prod);
	printf("Número de consumidores: %d\n", nhilos_cons);
	printf("Tiempo de consumo: %.2f segundos", tiempo_cons);
	printf("Tiempo de producción: %.2f segundos", tiempo_prod);
	printf("Total de ítems a producir: %d elementos.\n", total_items);
}
