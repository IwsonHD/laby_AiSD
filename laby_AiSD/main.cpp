#include <iostream>
#include <cmath>
using namespace std;


void copy(char* from, char* into,int lenght,int from_ind) {
	into[lenght+from_ind] = from[lenght];
	if (lenght != 0) return copy(from, into, lenght - 1,from_ind);
}




void d_t_b_r(char* out,int dec,int bits,int ind) {
	if (pow(2, bits-1) <= dec) {
		dec = dec - pow(2, bits-1);
		out[ind] = '1';
	}
	else {
		out[ind] = '0';
	}
	if (bits > 0) return d_t_b_r(out, dec, bits - 1, ind + 1);

}

char* dec_to_bin_rec(int dec, int bits) {
	char* out = new char[bits+1];
	d_t_b_r(out, dec, bits, 0);
	out[bits] = '\0';
	return out;
}




char* g_m_in(char* in,char* out, int cur_pos,int lenght) {
	out[cur_pos] = in[lenght];
	if (lenght == 0) {
		return out;
	}
	else {
		return g_m_in(in, out, cur_pos + 1, lenght - 1);
	}
}

char* generate_mirr(char* string, int lenght) {
	char* out = new char[lenght];
	return g_m_in(string, out,0, lenght-1);
}


void g_p_in_0(char* out, int curr_bin, int lenght,int curr_pos) {
	char* tmp = dec_to_bin_rec(curr_bin, lenght);
	char* tmp_rev = generate_mirr(tmp, lenght);
	copy(tmp, out, lenght, curr_pos);
	copy(tmp_rev, out, lenght, curr_pos + lenght);
	if (curr_bin > 0) return g_p_in_0(out, curr_bin - 1, lenght, curr_pos + (lenght * 2));

}

void g_p_in_1(char* out, int curr_bin, int lenght, int curr_pos) {
	char* tmp = dec_to_bin_rec(curr_bin, lenght);
	char* tmp_rev = generate_mirr(tmp, lenght);
	copy(tmp, out, lenght, curr_pos);
	out[curr_pos + lenght] = '1';
	copy(tmp_rev, out, lenght, curr_pos + lenght + 1);
	copy(tmp, out, lenght, curr_pos + 2*lenght + 1);
	out[curr_pos + 3*lenght + 1] = '0';
	copy(tmp_rev, out, lenght, curr_pos + 3*lenght + 2);
	if (curr_bin > 0) return g_p_in_1(out, curr_bin - 1, lenght, curr_pos + (lenght * 4) + 2);
	
}







char* generate_palins(int n) {
	int half = n / 2;
	int max = pow(2, half) - 1;
	char* out;
	if (n % 2 == 0) {
		out = new char[(max+1)*n+1];
		g_p_in_0(out, max, half,0);
		out[(max + 1) * n] = '\0';
		return out;
	}
	else {
		out = new char[2*((max + 1) * n) + 1];
		g_p_in_1(out, max, half, 0);
		out[2 * ((max + 1) * n)] = '\0';
		return out;


	}
	
}








int main() {
	/*while (n != '\n') {
		cin >> n;
		//generate_palins(n);
		cout << '\n';
	}
	
	*/

	cout << generate_palins(3);


	return 0;

}
