#include <iostream>
using namespace std;
#define n 3
void ProdusVectorial(int x1,int y1,int z1,int x2,int y2,int z2, int *x3,int *y3,int *z3){
    *x3= y1 * z2 - y2 * z1;
    *y3= x2 * z1 - x1 * z2;
    *z3= x1 * y2 - x2 * y1;

}
int main() {
   int v_A[] = { 1, 0, 0 };
   int v_B[] = { 0, 1, 0 };
   int c_P[n];
   cout << "Produs vectorial:";
   ProdusVectorial(v_A[0],v_A[1],v_A[2], v_B[0],v_B[1],v_B[2], &c_P[0],&c_P[1],&c_P[2]);
   for (int i = 0; i < n; i++)
      cout << c_P[i] << " ";
   return 0;
}
