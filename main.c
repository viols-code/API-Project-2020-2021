#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct{
    unsigned int dist;
    int visited;
} Nodo;

typedef struct class{
    unsigned int costo;
    unsigned int ins;
    struct class * prec;
    struct class * next;
} Class;


unsigned int AggiungiGrafo(unsigned int d){
    unsigned int i, j, minv, minp, count, costo;
    char s[1000000];
    unsigned int A[d][d];
    char * ns;

    for(i = 0; i < d; i++){
        if(!fgets(s, 1000000, stdin)){
            printf("Errore\n");
        }

        A[i][0] = strtol(s, &ns, 10);

        for(j = 1; j < d; j++){
            A[i][j] = strtol(ns + 1, &ns, 10);
        }
    }

    Nodo P[d - 1];

    minv = 0;
    minp = 1;
    count = 0;
    costo = 0;

    for(i = 0; i < d - 1; i++){
        P[i].dist = A[0][i + 1];
        P[i].visited = 0;
        if(minv == 0){
            if(A[0][i + 1] != 0){
                minv = A[0][i + 1];
                minp = i + 1;
            }
        } else {
            if(minv > A[0][i + 1] && A[0][i + 1] != 0){
                minp = i + 1;
                minv = A[0][i + 1];
            }
        }
    }

    if(minv == 0){
        return costo;
    }

    costo += minv;

    P[minp - 1].visited = 1;
    count ++;

    while(count < d - 1){
        minv = 0;
        j = minp;
        for(i = 0; i < d - 1; i++){
            if(P[i].visited == 0){
                if(P[i].dist == 0){
                    if(A[j][i + 1] != 0){
                        P[i].dist = A[j][i + 1] + P[j - 1].dist;
                    }
                } else {
                    if(A[j][i + 1] != 0){
                        if(P[j - 1].dist + A[j][i + 1] < P[i].dist){
                            P[i].dist = P[j - 1].dist + A[j][i + 1];
                        }
                    }
                }

                if(minv == 0){
                    minv = P[i].dist;
                    minp = i + 1;
                } else {
                    if(minv > P[i].dist && P[i].dist != 0){
                        minv = P[i].dist;
                        minp = i + 1;
                    }

                }

            }
        }

        P[minp - 1].visited = 1;
        costo += minv;
        count ++;
    }

    return costo;
}


int main() {
    unsigned int d, k, costo, num;
    char s1[1000000];
    char s2[] = "AggiungiGrafo\n";
    Class * head = NULL;
    Class * last = NULL;
    Class * new = NULL;
    Class * visita = NULL;
    Class * prima = NULL;

    if(!scanf("%u %u\n", &d, &k)){
        printf("Errore\n");
    }

    num = 0;

    while(fgets(s1, 1000000, stdin) != NULL){
        if(!strcmp(s1, s2)){
            costo = AggiungiGrafo(d);
            if(num < k){
                if(num == 0){
                    head = malloc(sizeof(Class));
                    head->ins = 0;
                    head->costo = costo;
                    head->next = NULL;
                    head->prec = NULL;
                    last = head;
                } else {
                    new = malloc(sizeof(Class));
                    new->ins = num;
                    new->costo = costo;
                    if(costo < head->costo){
                        new->next = head;
                        new->prec = NULL;
                        head->prec = new;
                        head = new;
                    } else {
                        if(costo >= last->costo){
                            new->next = NULL;
                            new->prec = last;
                            last->next = new;
                            last = new;
                        } else {
                            prima = head;
                            while(prima->costo <= new->costo){
                                prima = prima->next;
                            }

                            new->next = prima;
                            new->prec = prima->prec;
                            prima->prec = new;
                            (new->prec)->next = new;

                        }
                    }

                }
            } else {
                if(costo < last->costo){
                    if(costo < head->costo){
                        (last->prec)->next = NULL;
                        visita = last->prec;

                        last->ins = num;
                        last->costo = costo;

                        last->next = head;
                        last->prec = NULL;
                        head->prec = last;
                        head = last;

                        last = visita;
                        visita = NULL;
                    } else{
                        prima = head;
                        while(prima->costo <= costo){
                            prima = prima->next;
                        }

                        if(prima != last){
                            (last->prec)->next = NULL;
                            visita = last->prec;

                            last->ins = num;
                            last->costo = costo;

                            last->next = prima;
                            last->prec = prima->prec;
                            prima->prec = last;
                            (last->prec)->next = last;

                            last = visita;

                        } else {
                            last->ins = num;
                            last->costo = costo;
                        }

                    }
                }

            }

            num++;

        } else {
            visita = head;

            while(visita != NULL){
                if(visita->next == NULL){
                    printf("%u", visita->ins);
                } else {
                    printf("%u ", visita->ins);
                }
                visita = visita->next;
            }

            printf("\n");

        }
    }

    return 0;
}
