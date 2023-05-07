#import <cmath>
#import <cstring>
#import <ctime>
#import <cstdlib>
#import <stdio.h>
#import <iostream>

int n, e = 0, d;
 
 // Двоичное преобразование
int BinaryTransform(int num, int bin_num[]) {
	int i = 0,  mod = 0; 
	while(num != 0) { // Преобразуется в двоичный, обратный временно сохраняется в массиве temp []
		mod = num % 2;
		bin_num[i] = mod;
		num = num / 2;
		i++;
	}
	return i; // Возвращает количество цифр в двоичных числах
}
long long Modular_Exponentiation(long long a, int b, int n) { // Повторное возведение в квадрат в степень
	int c = 0, bin_num[1000];
	long long d = 1;
	int k = BinaryTransform(b, bin_num)-1;
	for(int i = k; i >= 0; i--) {
		c = 2 * c;
		d = (d * d) % n;
		if(bin_num[i] == 1) {
			c = c + 1;
			d = (d * a) % n;
		}
	}
	return d;
}
int ProducePrimeNumber(int prime[]) {  // Генерация простых чисел в пределах 1000
	int c = 0, vis[1001];
	memset(vis, 0, sizeof(vis));
	for(int i = 2; i <= 1000; i++) if(!vis[i]) {
		prime[c++] = i;
		for(int j = i * i; j <= 1000; j+=i) vis[j] = 1;
	}
	return c;
}
int Exgcd(int m, int n, int &x) { // Расширенный алгоритм Евклида
	int x1, y1, x0, y0, y;
	x0 = 1; y0 = 0;
	x1 = 0; y1 = 1;
	x = 0; y = 1;
	int r = m % n;
	int q = (m - r) / n;
	while(r) {
		x = x0 - q * x1; y = y0 - q * y1;
		x0 = x1; y0 = y1;
		x1 = x; y1 = y;
		m = n; n = r; r = m % n;
		q = (m - r) / n;
	}
	return n;
}
void RSA_Initialization() { // Инициализация RSA
	int prime[5000]; // Вынимаем простые числа в пределах 1000 и сохраняем их в массиве prime []
	int count_Prime = ProducePrimeNumber(prime);
 	srand((unsigned)time(NULL)); // Случайно возьмем два простых числа p, q

	int ranNum1 = 32; //rand() % count_Prime;
	int ranNum2 = 152; //rand() % count_Prime;

    int p = prime[ranNum1], q = prime[ranNum2];
 
	n = p * q;
 
	int On = (p - 1) * (q - 1);

	 // Используем расширенный алгоритм Евклида, чтобы найти e, d
	for(int j = 3; j < On; j+=1331) {
		int gcd = Exgcd(j, On, d);
		if(gcd == 1 && d > 0) {
			e = j;
			break;
		}
	}
    std::cout << "RSA e: " << e << std::endl
              << "RSA d: " << d << std::endl
              << "RSA ranNum1: " << ranNum1 << std::endl
              << "RSA ranNum2: " << ranNum2 << std::endl;
}
// шифрование RSA
void RSA_Encrypt(long long *Ciphertext, char *text, size_t size) {
	int buffer[1024];

	for (int i = 0; i < strlen(text); i++)
        buffer[i] = (int)text[i];

	for(int i = 0; i < sizeof(buffer) / sizeof(int); i++)
        Ciphertext[i] = Modular_Exponentiation(buffer[i], e, n);
}
// Расшифровка RSA
void RSA_Decrypt(long long *Ciphertext, size_t size) {
	for(int i = 0; i < size; i++) Ciphertext[i] = Modular_Exponentiation(Ciphertext[i], d, n);
}

