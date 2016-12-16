#include <limits.h>
//#include <stdio.h>
//#include <assert.h>

int saturating_add(int x, int y){
  if (x >= 0 && y >=0 && x+y < 0)
    return INT_MAX;
  else if (x < 0 && y < 0 && x+y >= 0)
    return INT_MIN;
  return x+y;
}

/*
int main(){
	// positive overflow
  printf("*positive overflow*\n%i\n", saturating_add(1, INT_MAX));
  // negative overflow
  printf("*negative overflow*\n%i\n", saturating_add(-3, -INT_MAX));
  printf("%i\n", saturating_add(-1, INT_MIN));
	// no overflow
  printf("*no overflow*\nreturn INT_MAX-1: %i\n", saturating_add(-1, INT_MAX));
  printf("return INT_MIN: %i\n", saturating_add(0, INT_MIN));
  printf("return 5: %i\n", saturating_add(2, 3));
  printf("return 5: %i\n", saturating_add(-2, 7));
  printf("return -5: %i\n", saturating_add(-2, -3));
}
*/
/*
int main(){
    assert(saturating_add(INT_MAX,0)==INT_MAX);
    assert(saturating_add(INT_MAX,1)==INT_MAX);
    assert(saturating_add(INT_MIN, -1)==INT_MIN);
    assert(saturating_add(10, 20)==30);
    assert(saturating_add(INT_MAX-5,300)==INT_MAX);
    assert(saturating_add(-12345,-9999)==(-12345-9999));
    assert(saturating_add(INT_MIN,0)==INT_MIN);
    assert(saturating_add(INT_MIN+12345,-5809500)==INT_MIN);
    assert(saturating_add(-1,1)==0);
    assert(saturating_add(INT_MAX,INT_MIN)==-1);
    return 0;
}
*/
