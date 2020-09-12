#include <ctime>
#include <climits>
#include <pthread.h>

#include "list.h" 

#define NUMOFT 2 //количество потоков

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

static int NumZeroes = 0;
static int NumOnes = 0;

void* CountZeroes (List* lst) {
	int x = 0;
	size_t size_of_value = CHAR_BIT * sizeof x;
	do {
		if (x) {
			for(size_t i = 0; i < size_of_value; ++i)
				if ((x & (1 << i)) == 0)
					++NumZeroes;
		}
		pthread_mutex_lock(&mut);
		x = lst->NewHead();
		pthread_mutex_unlock(&mut);
	} while (x) ;
	return 0;
}

void* CountOnes (List* lst) {
	int x = 0;	
	size_t size_of_value = CHAR_BIT * sizeof x;	
	do {
		if (x) {
			for(size_t i = 0; i < size_of_value; ++i)	
				if (x & (1 << i))
					++NumOnes;
		}	
		pthread_mutex_lock(&mut);
		x = lst->NewTail();
		pthread_mutex_unlock(&mut);		
	} while (x);
	return 0;
}

void* CountBits(void* args) {
	((Args*)args)->fcnPtr(((Args*)args)->lst);
	return 0;
}

int main () {
	srand( time(0) );
	List lst;

	int size = 0;
	cout << "List size: " << endl;
	cin >> size;

	lst.Add(size);

	Args args[NUMOFT];
	pthread_t threads[NUMOFT];

	for(int i = 0; i < NUMOFT; i++){
		args[i].lst = &lst;
		if (i == 0) {
			args[i].fcnPtr = CountZeroes;
		} else {
			args[i].fcnPtr = CountOnes;
		}
	}
	
	for (uint32_t i = 0; i < NUMOFT; i++) {
		if (pthread_create(&threads[i], NULL, CountBits, (void *)&args[i])) {
			printf("Error: pthread_create failed!\n");
			return 1;
		}
	}

	for (uint32_t i = 0; i < NUMOFT; i++) {
		if (pthread_join(threads[i], NULL) != 0) {
			perror("pthread_join");
			exit(1);
		}
	}

	cout << "0 bits: " << NumZeroes << endl;
	cout << "1 bits: " << NumOnes << endl;

	return 0;
}
