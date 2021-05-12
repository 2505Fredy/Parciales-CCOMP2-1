#include <iostream>
#include <cstring> // strlen()
using namespace std;

//variables globales
char der[5]{'N', 'E', 'S', 'O', 'N'};
char izq[5]{'N', 'O', 'S', 'E', 'N'};

// Las posiciones (i,j) del robot las manejaré dentro de un arreglo de 2 enteros. Pensaba hacerlo todo con "struct" pero no se nos enseñó aún, entonces lo hice con un arreglo de enteros. 
// La inicializo con los valores que recibo del usuario o valores ya predeterminados
void inicializarPosicion(int punto[2], int x, int y){
  punto[0]=x;
  punto[1]=y;
}


// Función booleana que veerifica que la posición del robot esté dentro de los límites del tablero. Es decir si está fuera del tablero devuelve "true"; caso contrario, "false".
bool salioMapa(int fila, int col, int robot[2]){
  if (robot[0]<0 || robot[0]>fila){
    return true;
  }
  if (robot[1]<0 || robot[1]>col-1){
    return true;
  }
  return false;
}

//Cambia el valor char de la variable direccion. Es decir si está en N cambia al valor E.
void giraDerecha(char &direccion){
  for (int i=0; i<5; i++){
    if (der[i] == direccion){
      direccion= der[i+1];
      return;
    }
  }
}

// Cambia el valor char de la variable direccion. Es decir si está en O cambia al valor S.
void giraIzquierda(char &direccion){
  for (int i=0; i<5; i++){
    if (izq[i] == direccion){
      direccion= izq[i+1];
      return;
    }
  }
}

// Avanza una posición hacia la dirección que está apuntando
void avanza(char direccion, int posicion[2]){
  if (direccion=='N') posicion[0]-=1;
  if (direccion=='S') posicion[0]+=1;
  if (direccion=='O') posicion[1]-=1;
  if (direccion=='E') posicion[1]+=1;
}

// Función booleana que ejecuta los movimientos y devuelve "false" si el robot salió del tablero y no ejecuta los movimientos siguientes. Devuelve "true" si el robot no sale del tablero y termina todos los movimientos.
bool movimiento(char *movs, int posicion[2], char &direccion, int fila, int col){
  int longitud = strlen(movs);
  for (int i = 0; i<longitud; i++){
    if (movs[i] == 'A'){
      avanza(direccion, posicion);
    }
    else if (movs[i] == 'D'){
      giraDerecha(direccion);
    }
    else if (movs[i] == 'I'){
      giraIzquierda(direccion);
    }
    if (salioMapa(fila, col, posicion)) return false;
  }
  return true;
}

//Validación del tamaño máximo del mapa
void validacion(int fila, int col){
  if (fila>50 || col>50){
    cout << "Excedió el límite del tamaño máximo(del mapa) admitido." << endl;
    exit(-1); // Puse ésto porque si no se cumple que las filas y/o columnas sean menor o igual que 50, no tiene caso seguir ejecutándolo.
  }
}

int main() {
  int filRob, colRob, filTab, colTab; // Inicializo las variables de fila y columna del robot, al igual que el número de filas y columnas del tablero(mapa).
  char direction='N'; // Declaro la dirección del robot mediante un carácter, inicializandola en "N" norte.
  cout << "Ingrese la fila del robot: ";
  cin >> filRob;
  cout << "Ingrese la columna del robot: ";
  cin >> colRob;
  cout << "Ingrese número de filas del mapa: ";
  cin >> filTab;
  cout << "Ingrese número de columnas del mapa: ";
  cin >> colTab;
  validacion(filTab, colTab);
  cout << "Ingrese la dirección del robot: \n(N=norte; S=sur; E= este; O= oeste)\n";
  cin >> direction;
  filTab++; // Le sumé +1 porque en la imagen se cuenta desde cero incluyendo el límite de filas. Osea si se pone 5, el número de filas es 0,1,2,3,4,5= 6 filas.
  colTab++; // Le sumé +1 porque en la imagen se cuenta desde cero incluyendo el límite de columnas.
  int posicion[2]{0,0}; // Declaro la posición del robot en el tablero, en las posiciones (0,0)inicialmente.
  inicializarPosicion(posicion, filRob, colRob); // Inicializo la posición del robot, con los valores ingresados.
  char movimientos[41]; // El número máximo de movimientos es 40. Trabajé con un valor constante. 
  cout << "Ingrese los movimientos a ejecutar: ";
  cin >> movimientos;
  if (movimiento(movimientos, posicion, direction, filTab, colTab)) cout << "No se salió del mapa.";
  else cout << "Salió del mapa.";
  cout << endl << "Posición: " << posicion[0] << ";" << posicion[1] << endl << "Dirección: " << direction << endl;
}
