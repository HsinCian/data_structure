#include <stdio.h>
#include <math.h>

int main(){
	//read the data p, m and n
	unsigned int p, m, n;
	scanf ("%u %u %u", &p, &m, &n);
	
	unsigned int user; //user_id
	unsigned int hash; //store the value hash of user_id 
	unsigned int size = m/8; //compute the size of the array x
	char x[size+1]; //an array of length m to store the value true(1) or false(0)
	
	//initialize the array x to 0(false)
	for (int i = 0; i < size; i++) x[i] = 0;
	
	//consider the user can be choose or not
	for (int i = 0; i < n; i++){
		scanf ("%u", &user);
		hash = user * user % p % m; //use hash function to compute the value
		unsigned int num_char = hash/8; //compute which char the hash is
		char tmp = x[num_char]; //use a char to store the value 
		unsigned int num_bit = hash%8; //compute which bit the hash is
		tmp = tmp << num_bit; //shift left for num_bit bit
		tmp = tmp >> 7; //shifr right for 7 bit

		//if tmp equal to 0, the user can be choose, otherwise, the user can't be choose
		if (tmp == 0){
			printf ("%u 1\n", user);
			x[num_char] += pow(2,(7-num_bit)); //if the user be choose, renew the array x
		}else{
			printf ("%u 0\n", user);
		}
	}
		
}


