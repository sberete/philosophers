/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:51:33 by sberete           #+#    #+#             */
/*   Updated: 2025/05/16 16:51:34 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	*thread_routine(void *arg)
// {
// 	(void)arg;
// 	pthread_t tid;

// 	tid = pthread_self();
//  	printf("%sThread [%ld]: Le plus grand ennui c'est d'exister sans vivre.%s\n",
// 		YELLOW, tid, NC);
//  	return (NULL); // 
// }
// int main(void)
// {
//  pthread_t tid1; // Identifiant du premier thread
//  pthread_t tid2; // Identifiant du second thread

//  // Création du premier thread qui va directement aller
//  // exécuter sa fonction thread_routine.
//  pthread_create(&tid1, NULL, thread_routine, NULL);
//  printf("Main: Creation du premier thread [%ld]\n", tid1);
//  // Création du second thread qui va aussi exécuter thread_routine.
//  pthread_create(&tid2, NULL, thread_routine, NULL);
//  printf("Main: Creation du second thread [%ld]\n", tid2);
//  // Le main thread attend que le nouveau thread
//  // se termine avec pthread_join.
//  pthread_join(tid1, NULL);
//  printf("Main: Union du premier thread [%ld]\n", tid1);
//  pthread_join(tid2, NULL);
//  printf("Main: Union du second thread [%ld]\n", tid2);
//  return (0);
// }
/*
Erreurs de synchronisation -> data race
void *thread_routine(void *data)
{
	// Chaque thread commence ici
	pthread_t tid;
	unsigned int *count; // pointeur vers la variable dans le main
	unsigned int i;

	tid = pthread_self();
	count = (unsigned int *)data;
	// On imprime le compte avant que ce thread commence
	// a itérer
	printf("%sThread [%ld]: compte au depart = %u.%s\n",
	YELLOW, tid, *count, NC);
	i = 0;
	while (i < TIMES_TO_COUNT)
	{
		// On itere TIMES_TO_COUNT fois
		// On incremente le compte a chaque iteration
		(*count)++;
		i++;
 	}
	// On imprime le compte final au moment ou ce thread
	// a termine son propre compte
	printf("%sThread [%ld]: Compte final = %u.%s\n",
	BYELLOW, tid, *count, NC);
	return (NULL); // Thread termine ici.
}
int main(void)
{
 pthread_t tid1;
 pthread_t tid2;
 // Variable pour contenir le compte des deux threads :
 unsigned int count;

 count = 0;
 // Vu que chaque thread va compter TIMES_TO_COUNT fois et qu'on va
 // avoir 2 threads, on s'attend a ce que le compte final soit
 // 2 * TIMES_TO_COUNT :
 printf("Main: Le compte attendu est de %s%u%s\n", GREEN,
     2 * TIMES_TO_COUNT, NC);
 // Creation des threads :
 pthread_create(&tid1, NULL, thread_routine, &count);
 printf("Main: Creation du premier thread [%ld]\n", tid1);
 pthread_create(&tid2, NULL, thread_routine, &count);
 printf("Main: Creation du second thread [%ld]\n", tid2);
 // Recuperation des threads :
 pthread_join(tid1, NULL);
 printf("Main: Union du premier thread [%ld]\n", tid1);
 pthread_join(tid2, NULL);
 printf("Main: Union du second thread [%ld]\n", tid2);
 // Evaluation du compte final :
 if (count != (2 * TIMES_TO_COUNT))
  printf("%sMain: ERREUR ! Le compte est de %u%s\n", RED, count, NC);
 else
  printf("%sMain: OK. Le compte est de %u%s\n", GREEN, count, NC);
 return (0);
}
*/
/*
typedef struct s_counter
{
 pthread_mutex_t count_mutex;
 unsigned int count;
} t_counter;

void *thread_routine(void *data)
{
 // Chaque thread commence ici
 pthread_t tid;
 t_counter *counter; // pointeur vers la structure dans le main
 unsigned int i;

 tid = pthread_self();
 counter = (t_counter *)data;
 // On imprime le compte avant que ce thread commence
 // a itérer. Pour lire la valeur de count, on verrouille le
 // mutex.
 pthread_mutex_lock(&counter->count_mutex);
 printf("%sThread [%ld]: compte au depart = %u.%s\n",
  YELLOW, tid, counter->count, NC);
 pthread_mutex_unlock(&counter->count_mutex);
 i = 0;
 while (i < TIMES_TO_COUNT)
 {
  // On itere TIMES_TO_COUNT fois
  // On verouille le mutex le temps
  // d'incrementer le compte
  pthread_mutex_lock(&counter->count_mutex);
  counter->count++;
  pthread_mutex_unlock(&counter->count_mutex);
  i++;
 }
 // On imprime le compte final au moment ou ce thread
 // a termine son propre compte en verouillant le mutex
 pthread_mutex_lock(&counter->count_mutex);
 printf("%sThread [%ld]: Compte final = %u.%s\n",
  BYELLOW, tid, counter->count, NC);
 pthread_mutex_unlock(&counter->count_mutex);
 return (NULL); // Thread termine ici.
}
 int main(void)
{
 pthread_t tid1;
 pthread_t tid2;
 // Structure pour contenir le compte des deux threads :
 t_counter counter;

 // Il n'y a ici qu'un seul thread, on peut donc initialiser
 // le compte sans mutex.
 counter.count = 0;
 // Initialisation du mutex :
 pthread_mutex_init(&counter.count_mutex, NULL);
 // Vu que chaque thread va compter TIMES_TO_COUNT fois et qu'on va
 // avoir 2 threads, on s'attend a ce que le compte final soit
 // 2 * TIMES_TO_COUNT :
 printf("Main: Le compte attendu est de %s%u%s\n", GREEN,
     2 * TIMES_TO_COUNT, NC);
 // Creation des threads :
 pthread_create(&tid1, NULL, thread_routine, &counter);
 printf("Main: Creation du premier thread [%ld]\n", tid1);
 pthread_create(&tid2, NULL, thread_routine, &counter);
 printf("Main: Creation du second thread [%ld]\n", tid2);
 // Recuperation des threads :
 pthread_join(tid1, NULL);
 printf("Main: Union du premier thread [%ld]\n", tid1);
 pthread_join(tid2, NULL);
 printf("Main: Union du second thread [%ld]\n", tid2);
 // Evaluation du compte final :
 // (Ici on peut lire le compte sans s'occuper du mutex
 // car tous les threads sont unis et on a la garantie
 // qu'un seul un thread va y acceder.)
 if (counter.count != (2 * TIMES_TO_COUNT))
  printf("%sMain: ERREUR ! Le compte est de %u%s\n",
     RED, counter.count, NC);
 else
  printf("%sMain: OK. Le compte est de %u%s\n",
     GREEN, counter.count, NC);
 // On detruit le mutex à la fin du programme :
 pthread_mutex_destroy(&counter.count_mutex);
 return (0);
}
 */
/*
Les interblocages -> deadlock
 typedef struct s_locks
{
 pthread_mutex_t lock_1;
 pthread_mutex_t lock_2;
 unsigned int count;
} t_locks;

// Le premier thread invoque cette routine :
void *thread_1_routine(void *data)
{
 pthread_t tid;
 t_locks  *locks;

 tid = pthread_self();
 locks = (t_locks *)data;
 printf("%sThread [%ld]: veut verrouiller lock 1%s\n", YELLOW, tid, NC);
 pthread_mutex_lock(&locks->lock_1);
 printf("%sThread [%ld]: possede lock 1%s\n", BYELLOW, tid, NC);
 printf("%sThread [%ld]: veut verrouiller lock 2%s\n", YELLOW, tid, NC);
 pthread_mutex_lock(&locks->lock_2);
 printf("%sThread [%ld]: possede lock 2%s\n", BYELLOW, tid, NC);
 locks->count += 1;
 printf("%sThread [%ld]: deverouille lock 2%s\n", BYELLOW, tid, NC);
 pthread_mutex_unlock(&locks->lock_2);
 printf("%sThread [%ld]: deverouille lock 1%s\n", BYELLOW, tid, NC);
 pthread_mutex_unlock(&locks->lock_1);
 printf("%sThread [%ld]: termine%s\n", YELLOW, tid, NC);
 return (NULL); // Le thread termine ici.
}

// Le deuxieme thread invoque cette routine :
void *thread_2_routine(void *data)
{
 pthread_t tid;
 t_locks  *locks;

 tid = pthread_self();
 locks = (t_locks *)data;
 printf("%sThread [%ld]: veut verrouiller lock 2%s\n", YELLOW, tid, NC);
 pthread_mutex_lock(&locks->lock_2);
 printf("%sThread [%ld]: possede lock 2%s\n", BYELLOW, tid, NC);
 printf("%sThread [%ld]: veut verrouiller lock 1%s\n", YELLOW, tid, NC);
 pthread_mutex_lock(&locks->lock_1);
 printf("%sThread [%ld]: possede lock 1%s\n", BYELLOW, tid, NC);
 locks->count += 1;
 printf("%sThread [%ld]: deverouille lock 1%s\n", BYELLOW, tid, NC);
 pthread_mutex_unlock(&locks->lock_1);
 printf("%sThread [%ld]: deverouille lock 2%s\n", BYELLOW, tid, NC);
 pthread_mutex_unlock(&locks->lock_2);
 printf("%sThread [%ld]: termine%s\n", YELLOW, tid, NC);
 return (NULL); // Le thread termine ici.
}

int main(void)
{
 pthread_t tid1; // Identifiant du premier thread
 pthread_t tid2; // Identifiant du second thread
 t_locks  locks; // Structure contenant 2 mutex

 locks.count = 0;
 // Initialisation des deux mutex :
 pthread_mutex_init(&locks.lock_1, NULL);
 pthread_mutex_init(&locks.lock_2, NULL);
 // Création des threads :
 pthread_create(&tid1, NULL, thread_1_routine, &locks);
 printf("Main: Creation du premier thread [%ld]\n", tid1);
 pthread_create(&tid2, NULL, thread_2_routine, &locks);
 printf("Main: Creation du second thread [%ld]\n", tid2);
 // Union des threads :
 pthread_join(tid1, NULL);
 printf("Main: Union du premier thread [%ld]\n", tid1);
 pthread_join(tid2, NULL);
 printf("Main: Union du second thread [%ld]\n", tid2);
 // Évaluation du résultat :
 if (locks.count == 2)
  printf("%sMain: OK: Le compte est %d\n", GREEN, locks.count);
 else
  printf("%sMain: ERREUR: Le compte est%u\n", RED, locks.count);
 // Destruction des mutex :
 pthread_mutex_destroy(&locks.lock_1);
 pthread_mutex_destroy(&locks.lock_2);
 return (0);
}
 */