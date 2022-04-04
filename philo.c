#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>

pthread_mutex_t chops[5];
int ready;
int is_full[5];
int philo_id[5] = {0, 1, 2, 3, 4};

void* philo(void* data);
void think(int id);
void eat(int id);

int main(){
	int i;
	pthread_t philosopher[5];
	for(i = 0; i < 5; i++){
		pthread_mutex_init(&chops[i], NULL);
		printf("chop %d init over\n", i);
		// unknown order of main and philo threads, use global variable philo_id[] to set orders
		pthread_create(&philosopher[i], NULL, philo, philo_id+i);
		printf("philo %d is on table\n", i);
	}
	ready = 1;
	for(i = 0; i < 5; i++){
		pthread_join(philosopher[i], NULL);
		pthread_mutex_destroy(&chops[i]);
	}
	return 0;
}

void* philo(void* data){
	int i = 0;
	int id = *((int*)data);
	// wait other philo on table
	while(!ready);
	printf("philo %d ready to eat\n", id);
	while(i <= 10){
		think(id);
		eat(id);
		if(is_full[id] > 6){
			printf("philo %d is full\n" ,id);
			break;
		}
		i++;
	}
	return NULL;
}

void think(int id){
	printf("philo %d is thinking\n", id);
	sleep(1);
}

void eat(int id){
	int ret1, ret2;
	while(1){
		// only eaten can the loop over, or keep waiting
		ret1 = pthread_mutex_trylock(&chops[id]);
		ret2 = pthread_mutex_trylock(&chops[(id+1)%5]);
		if(ret1 != EBUSY && ret2 != EBUSY){
			printf("philo %d is eating\n", id);
			is_full[id]++;
			sleep(1);
			pthread_mutex_unlock(&chops[id]);
			pthread_mutex_unlock(&chops[(id+1)%5]);
			break;
		}
		else{
			if(ret1 != EBUSY){
				pthread_mutex_unlock(&chops[id]);
			}
			if(ret2 != EBUSY){
				pthread_mutex_unlock(&chops[(id+1)%5]);
			}
			printf("philo %d is waiting to eat\n", id);
			sleep(1);
		}
	}
}
