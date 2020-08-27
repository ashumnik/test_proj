#include <ctime>
#include <climits>
#include <pthread.h>

#include "list.hpp" 

#define NUMOFT 2 //количество потоков

static int num_zeroes = 0;
static int num_ones = 0;
 
void rand_list(size_t const& n, List &lst) { //генерация списка со случайными значениями
	
	for (int i = 0; i != n; i++)
		lst.Add(rand());

}

void* Count_bits(void* args) { //функция считает количесво 1/0 битов


	if (((Args*)args)->b) { //если b = true, то выполняется поиск 0 битов с начала списка
		Node *temp = ((Args*)args)->lst->Head;
		size_t size_of_value = CHAR_BIT * sizeof temp->x;
		while (temp != NULL) {
            int zeroes = 0;
            printf("counting zeroes in element %p\n", temp);
			for(size_t i = 0; i < size_of_value; ++i)
				if ((temp->x & (1 << i)) == 0)
					++zeroes;
            printf("got %d zeroes\n", zeroes);
            num_zeroes += zeroes;
			temp = ((Args*)args)->lst->New_Head();
		}
	} else { //если b = false, то выполняется поиск 1 битов с конца списка
		Node *temp = ((Args*)args)->lst->Tail;
		size_t size_of_value = CHAR_BIT * sizeof temp->x;
		while (temp != NULL) {
            int ones = 0;
            printf("counting ones in element %p\n", temp);
			for(size_t i = 0; i < size_of_value; ++i)	
				if (temp->x & (1 << i))
                    ones++;
            printf("got %d ones\n", ones);
            num_ones += ones;
			temp = ((Args*)args)->lst->New_Tail();
		}
	}

	return 0;
}




int main () {
	srand( time(0) );
	List lst;

	int size = 0;
	cout << "List size: " << endl;
	cin >> size;

	rand_list(size, lst);
	
	Args args[NUMOFT];
	pthread_t threads[NUMOFT];

	for(int i = 0; i < NUMOFT; i++){
		args[i].lst = &lst;
		if (i == 0) {
			args[i].b = 1;
		} else {
			args[i].b = 0;
		}
	}
	
	for (uint32_t i = 0; i < NUMOFT; i++) {
		if (pthread_create(&threads[i], NULL, Count_bits, (void *)&args[i])) {
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
	cout << "0 bits: " << num_zeroes << endl;
	cout << "1 bits: " << num_ones << endl;

	return 0;
}
