//for 264
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

//for 273
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
