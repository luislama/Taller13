#include <stdio.h>
#include <pthread.h>
#include <cstdlib>

pthread_mutex_t mutex;
pthread_cond_t condicionConsumidor;
pthread_cond_t condicionProductor;

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
  int nhilos_cons = atof(argv[4]);
  int tam_cola = atoi(argv[5]);
  int total_items = atoi(argv[6]);


  return 0;
}
