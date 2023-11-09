#include <stdio.h>
#include <stdlib.h>

#define VOLUME L*L
#define DIM 2
#define VUOTO -1
#define DESTRA 0
#define SOPRA 1
#define SINISTRA 2
#define SOTTO 3
#define QUADRATO(arg) ((arg)*(arg))

void inizializzazione_variabili(char **argv);
void inizializzazione_generatore(void);
void inizializzazione_array(void);
void inizializzazione_reticolo(double prob);
void aggiornamento_reticolo(void);
double misura(void);

unsigned int seme, L, num_passi, num_misure, num_storie, periodo_misure, N;
double prob, random_num;
int **pos_particella;
int **reticolo;
int **pos_vera_particella;
int **pos_zero_particella;
int *vicino_pos;
int *vicino_neg;
double **med_distanza_quadra;
double **err_distanza_quadra;
double coeff_diffusione;
FILE *pf;

int main(int argc, char **argv){

  unsigned int i, j;
  if(argc != 6){
    fprintf(stderr,"sintassi: ./gas <L> <prob> <num_passi> <num_storie> <num_misure>\n");
    exit(EXIT_FAILURE);
  }
  inizializzazione_variabili(argv);
  inizializzazione_generatore();
  inizializzazione_array();
  
  for(i = 0; i < num_storie; i++){
    inizializzazione_reticolo(prob);
    for(j = 1; j <= num_passi; j++){
      aggiornamento_reticolo();
      if((j%periodo_misure) == 0){
	med_distanza_quadra[i][(int)j/periodo_misure - 1] = misura();
      }
    }
  }
  if((pf = fopen("coeff_diffusione.dat","w")) == NULL){
    fprintf(stderr,"errore nell'apertura del file \"coeff_diffuzione.dat\"");
  }
  
  for(i = 0; i < num_misure; i++){
    coeff_diffusione = 0;
    for(j = 0; j < num_storie; j++){
      coeff_diffusione += med_distanza_quadra[j][i];
    }
    coeff_diffusione /= (double)(2*DIM*(i + 1)*periodo_misure*num_storie);
    fprintf(pf,"%u %f\n", (i + 1)*periodo_misure, coeff_diffusione);
  }
  fclose(pf);
  /*for(i = 0; i < N; i++){
    printf("(%d,%d) (%d,%d)\n",pos_particella[i][0],pos_particella[i][1],pos_vera_particella[i][0],pos_vera_particella[i][1]);
    }*/
  system("gnuplot -p 'script.gpl'");
  return 0;
}

void inizializzazione_variabili(char **argv){
  L = atoi(argv[1]);
  prob = atof(argv[2]);
  num_passi = atoi(argv[3]);
  num_storie = atoi(argv[4]);
  num_misure = atoi(argv[5]);
  if(num_passi%num_misure){
    fprintf(stderr,"attenzione: num_passi non multiplo di num_misure");
  }
  periodo_misure = num_passi/num_misure;
  printf("periodo misure: %d\n", periodo_misure);
}

void inizializzazione_generatore(){
pf = fopen("/dev/random","r");
  fread(&seme, sizeof(unsigned int), 1, pf);
  printf("seme: %u\n", seme);
  srand(seme);
  fclose(pf);
}

void inizializzazione_array(void){
  unsigned int i;
  reticolo = (int**)malloc(L*sizeof(int*));
  for(i = 0; i < L; i++){
    reticolo[i] = (int*)malloc(L*sizeof(int));
  }
  pos_particella = (int**)malloc(VOLUME*sizeof(int*));
  pos_vera_particella = (int**)malloc(VOLUME*sizeof(int*));
  pos_zero_particella = (int**)malloc(VOLUME*sizeof(int*));
  for(i = 0; i < (VOLUME); i++){
    pos_particella[i] = (int*)calloc(DIM,sizeof(int));
    pos_vera_particella[i] = (int*)calloc(DIM,sizeof(int));
    pos_zero_particella[i] = (int*)calloc(DIM,sizeof(int));
  }

  med_distanza_quadra = (double**)malloc(num_storie*sizeof(double*));
  err_distanza_quadra = (double**)malloc(num_storie*sizeof(double*));
  for(i = 0; i < num_storie; i++){
    med_distanza_quadra[i] = (double*)calloc(num_misure,sizeof(double));
    err_distanza_quadra[i] = (double*)calloc(num_misure,sizeof(double));
  }
  
  vicino_pos = (int*)malloc(L*sizeof(int));
  vicino_neg = (int*)malloc(L*sizeof(int));
  
  for(i = 0; i < L; i++){
    vicino_pos[i] = i + 1;
    vicino_neg[i] = i - 1;
  }
  vicino_pos[L - 1] = 0;
  vicino_neg[0] = L - 1;
}

void inizializzazione_reticolo(double prob){
  unsigned int x, y;
  N = 0;
  for(x = 0; x < L; x++){
    for(y = 0; y < L; y++){
      random_num = (double)rand()/RAND_MAX;
      if(random_num < prob){
	reticolo[x][y] = N;
	pos_particella[N][0] = x;
	pos_particella[N][1] = y;
	pos_vera_particella[N][0] = 0;
	pos_vera_particella[N][1] = 0;
	pos_zero_particella[N][0] = x;
	pos_zero_particella[N][1] = y;
	N++;
      } else {
	reticolo[x][y] = VUOTO;
      }
    }
  }
}

void aggiornamento_reticolo(void){
  unsigned int i, x, y, direzione;
  for(i = 0; i < N; i++){
    x = pos_particella[i][0];
    y = pos_particella[i][1];
    direzione = rand()%4;
    if(direzione == DESTRA){
      if(reticolo[vicino_pos[x]][y] == VUOTO){
	reticolo[vicino_pos[x]][y] = reticolo[x][y];
	reticolo[x][y] = VUOTO;
	pos_particella[i][0] = vicino_pos[x];
	pos_vera_particella[i][0]++;
      }
    } else if(direzione == SOPRA){
      if(reticolo[x][vicino_pos[y]] == VUOTO){
	reticolo[x][vicino_pos[y]] = reticolo[x][y];
	reticolo[x][y] = VUOTO;
	pos_particella[i][1] = vicino_pos[y];
	pos_vera_particella[i][1]++;
      }
    } else if(direzione == SINISTRA){
      if(reticolo[vicino_neg[x]][y] == VUOTO){
	reticolo[vicino_pos[x]][y] = reticolo[x][y];
	reticolo[x][y] = VUOTO;
	pos_particella[i][0] = vicino_neg[x];
	pos_vera_particella[i][0]--;
      }
    } else if(direzione == SOTTO){
      if(reticolo[x][vicino_neg[y]] == VUOTO){
	reticolo[vicino_pos[x]][y] = reticolo[x][y];
	reticolo[x][y] = VUOTO;
	pos_particella[i][1] = vicino_neg[y];
	pos_vera_particella[i][1]--;
      }
    }
  }
}

double misura(void){
  unsigned int i;
  unsigned long long int sum_distanze_quadre = 0;
  for(i = 0; i < N; i++){
    sum_distanze_quadre += QUADRATO(pos_vera_particella[i][0]) + QUADRATO(pos_vera_particella[i][0]);
  }
  return (double)sum_distanze_quadre/N;
}
