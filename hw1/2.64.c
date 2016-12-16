//#include <stdio.h>
//#include <assert.h>

int any_odd_one(unsigned x){
  if (!(x & 0xAAAAAAAA))
    return 0;
  return 1;
}

/*
int main(){
  int x = any_odd_one(1); //0
  int y = any_odd_one(2); //1
  int z = any_odd_one(0x55555555); //0
  int a = any_odd_one(0x55565555); //1
  printf("%u\n",x);
  printf("%u\n",y);
  printf("%u\n", z);
  printf("%u\n", a);
  return 0;
}
*/
/*
int main(){
    unsigned a = 21;	//010101
    assert(any_odd_one(a)==0);
    a = 29;	//011101
    assert(any_odd_one(a)==1);
    a = 229;//11100101
    assert(any_odd_one(a)==1);
    a = 22;//00010110
    assert(any_odd_one(a)==1);
    a = 340;//101010100
    assert(any_odd_one(a)==0);
    a = 101;//01100101
    assert(any_odd_one(a)==1);
    a = -1;	//1111...11
    assert(any_odd_one(a)==1);
    a = 68;//001000100
    assert(any_odd_one(a)==0);
    return 0;
}
*/
