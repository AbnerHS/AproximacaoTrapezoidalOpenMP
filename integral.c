#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>

double f(double x){
	return sqrt(pow(1000,2)-pow(x,2));	//função f(x)
}

int main(int argc, char* argv[]){
	int qtdThreads = strtol(argv[1],NULL,10); //recebe a quantidade de threads por parametro, converte pra int
	double h = strtod(argv[2],NULL); //recebe o intervalo de discretização, converte para double
	int i,n = 0;	//variaveis de iteração
	const double a = 0.0, b = 100.0;	//intervalo da integral
	double resultado = 0.0, x = 0.0;	//variavel de resultado e x da função
	n = (b-a)/h;	//calcula a quantidade de trapézios
	#pragma omp parallel for num_threads(qtdThreads) private(x) reduction(+:resultado) schedule(static,10)
	for(i = 1; i < n; i++){
		x = a+i*h;
		resultado += f(x);	//incrementa o resultado de cada ponto
	}
	resultado = (resultado+(f(a)+f(b))/2.0)*h;	//calcula a área do trapézio
	printf("Integral: %f\n",resultado);	//mostra o resultado
	return 0;
}

