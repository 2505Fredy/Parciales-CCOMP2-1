#include <iostream>
#include <cstring> // strlen()
using namespace std;

//variables y constantes globales
char der[5]{'N', 'E', 'S', 'O', 'N'};
char izq[5]{'N', 'O', 'S', 'E', 'N'};
const int filaTab = 9;
const int columnaTab = 9;
//NOTA: ES IMPERATIVO DECLARAR EL NUMERO DE FILAS Y COLUMNAS EN LAS 2 FILAS ANTERIORES, PUESTO QUE SE TRABAJA CON MATRICES Y NO SE PUEDE TRABAJAR CON VARIABLES AL PASAR COMO PARÁMETRO A UNA FUNCIÓN UNA MATRIZ, EL NUMERO DEBE SER CONSTANTE. RECOMIENDO QUE SE TRABAJE CON NÚMEROS DEL 0 AL 9, PUESTO QUE, DESPUÉS DE 2 DÍGITOS LA IMAGEN SE DEFORMA.


// Las posiciones (i,j) del robot las manejaré dentro de un arreglo de 2 enteros. Pensaba hacerlo todo con "struct" pero no se nos enseñó aún, entonces lo hice con un arreglo de enteros. 
// La inicializo con los valores que recibo del usuario o valores ya predeterminados. No inicialicé la dirección porque es tipo char, y si declaro mi matriz como char, no puede contener números mayores al 9. En tal sentido inicialicé la dirección dentro de main().
void inicializarPosicion(int punto[2], int x, int y){ 
  punto[0]=x;
  punto[1]=y;
}


// Función booleana que verifica que la posición del robot esté dentro de los límites del tablero. Es decir, si está fuera del tablero devuelve "true"; caso contrario, "false".
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

void printTablero(int fila, int col, char matriz[filaTab+1][columnaTab+1]){  
  cout << "  ";
  int filas= ((fila+1)*2)+1, columnas= ((col+1)*2)+1, filIndex=0;
  for (int i=0; i<col+1; i++) cout << i << ' ';
  cout << endl;
  for (int j=0; j< filas; j++){
    if (j%2==0){
      cout << ' ';
      for (int k=0; k<columnas; k++) cout << '-';
      cout << endl;
    }
    else if (j%2==1){
      cout << filIndex;
      int colIndex=0;
      for (int l=0; l<columnas; l++){
        if (l%2==0) cout << '|';
        else{ 
          cout << matriz[filIndex][colIndex];
          colIndex++;
          }
      }
      filIndex++;
      cout << endl;
    }
  }
}

// Marca la posición final del robot en el tablero y le asigna la letra que corresponde a su dirección final.
void marcadoTab(int filRob, int colRob, char direction, char matrix[][columnaTab+1]){
  for (int i=0; i < filaTab+1; i++){
    for (int j=0; j < columnaTab+1; j++){
      if (i==filRob && j==colRob) matrix[i][j]= direction;
      else matrix[i][j]=' ';
    }
  }
}

int main() {
  int filRob, colRob; // Inicializo las variables de fila y columna del robot, al igual que el número de filas y columnas del tablero(mapa).
  char direction='N'; // Declaro la dirección del robot mediante un carácter, inicializandola en "N" norte.
  cout << "Ingrese la fila del robot: ";
  cin >> filRob;
  cout << "Ingrese la columna del robot: ";
  cin >> colRob;
  validacion(filaTab, columnaTab);
  cout << "Ingrese la dirección del robot: \n(N=norte; S=sur; E= este; O= oeste)\n";
  cin >> direction;
  char matrix[filaTab+1][columnaTab+1]; //Creo una matriz[tablero] con constantes definidas al principio, ya que al pasar como argumento a una función no se puede pasar con variables
  int posicion[2]{0,0}; // Declaro la posición del robot en el tablero, en las posiciones (0,0)inicialmente.
  inicializarPosicion(posicion, filRob, colRob); // Inicializo la posición del robot, con los valores ingresados.
  char movimientos[41]; // El número máximo de movimientos es 40. Trabajé con un valor constante. 
  cout << "Ingrese los movimientos a ejecutar: ";
  cin >> movimientos;
  if (movimiento(movimientos, posicion, direction, filaTab+1, columnaTab+1)) cout << "No salió del mapa.\n";
  else{
    cout << "Salió del mapa.\n";
    exit(-1);
  }
  marcadoTab(posicion[0], posicion[1], direction, matrix);
  printTablero(filaTab, columnaTab, matrix);
}
