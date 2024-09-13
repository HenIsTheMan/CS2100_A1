// Name: LING GUAN YU
// Student ID: A0308292A
// Tutorial group: T36

int func(int a0){
	int count = (a0 >= 0);

	for(int i = 31; i > 0; --i){
		if((a0 <<= 1) >= 0){
			++count;
		}
	}

	return count;
}