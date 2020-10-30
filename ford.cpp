#include <stdio.h>
#include <vector>
#include <stdlib.h>
using namespace std;
#define maxi 50  //Numero maximo de vertices(porseaca)
#define infin 1<<30 //Defino valor infinito
#define Node pair<int,int>

int anter[maxi];
int dist[maxi];
int numVert;
vector<Node>seguidos[maxi];//lista

void init(){
    for(int i=0; i<=numVert; ++i){
        anter[i]=-1;
        dist[i]=infin;
    }
}

bool pasoRelaj(int n_actual, int n_junto, int peso){
    if(dist[n_actual]+peso< dist[n_junto]){
        dist[n_junto]= dist[n_actual]+peso;
        anter[n_junto]=n_actual;
        return true;
    }
    return false;
}

void print(int n_destino){
    if(anter[n_destino] !=-1){
        print(anter[n_destino]);
        }
    printf("%d ",n_destino);
}

void algBellFord(int n_inicio ){
    init();
    dist[n_inicio]= 0;

    for(int i=1; i<=numVert-1; ++i){
        for(int n_actual=1; n_actual<=numVert; ++n_actual){
            for(int j=0; j<seguidos[n_actual].size();++j){
                int n_junto= seguidos[n_actual][j].first;
                int peso = seguidos[n_actual][j].second;
                pasoRelaj(n_actual,n_junto,peso);
            }
        }
    }

    for(int n_actual=1; n_actual<=numVert; ++n_actual){
        for(int j=0; j<seguidos[n_actual].size(); ++j){
            int n_junto= seguidos[n_actual][j].first;
            int peso=seguidos[n_actual][j].second;
            if(pasoRelaj(n_actual, n_junto, peso)){
                puts("Hay ciclo negativo!");
                return;
            }
        }
    }

    puts("No hay ciclo negativo :)");
    printf("Recorrido mas corto iniciando en el vertice %d\n",n_inicio);
    for(int i= 1; i<=numVert; ++i){
        printf("Distancia mas corta al vertice %d = %d\n" ,i, dist[i]);
    }
}

int main(){
    int numArist, v_orig, v_dest, peso, n_inicio;
    printf("Ingrese el numero de vertices y aristas respectivamente\n");
    printf("(Proximamente con archivo)\n");
    scanf("%d %d" ,&numVert , &numArist);
    printf("\n");

    printf("Ingrese origen destino y peso de cada arista\n");
    while(numArist--){
        scanf("%d %d %d", &v_orig, &v_dest, &peso);
        seguidos[v_orig].push_back(Node(v_dest, peso));
    }
    printf("Ingrese el vertice de origen: ");
    scanf("%d", &n_inicio);
    algBellFord(n_inicio);
    return 0;
}
