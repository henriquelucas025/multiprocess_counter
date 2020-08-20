#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

void multiprocessos(int num_proc, int *v, int tamanho) {
	pid_t p1,p2,p3;
	int j,k;
	int i=0;
	int resultado=0;
    int protection = PROT_READ | PROT_WRITE;
    int visibility = MAP_SHARED | MAP_ANON;
    int *b;
    b = (int*) mmap(NULL, sizeof(int)*100, protection, visibility, 0, 0);
    (*b) = 0;
	
	
	if (num_proc == 4) {
		int aux = 0;
		for(k=0;k<=tamanho;k=k+4) {
			if (aux != 1) {
				p1 = fork();
				if(p1==0) {	 for (j = 2; j < v[k]; j++) {
								if (v[k] % j == 0) {	resultado=1;
											break; } }
						 if (resultado == 0 && v[k] != 0 && v[k] != 1) { (*b) = (*b)+1; }
						 exit(0); } 

				if(aux != 3) {
					p2 = fork();
					if(p2==0) {	 for (j = 2; j < v[k+1]; j++) {
									if (v[k+1] % j == 0) {  resultado=1;
												break; } }
							 if (resultado == 0 && v[k+1] != 0 && v[k+1] != 1) { (*b) = (*b)+1; }
							 exit(0); } 

							
					if(aux != 2) {
						p3 = fork();	
						if(p3==0) {	 for (j = 2; j < v[k+2]; j++) {
										if (v[k+2] % j == 0) {	resultado=1;
													break; } }
								 if (resultado == 0 && v[k+2] != 0 && v[k+2] != 1) { (*b) = (*b)+1; }
							         exit(0); }

						} } } 
					
					 for (j = 2; j < v[k+3]; j++) {
							 if (v[k+3] % j == 0) {	  resultado=1;
										  break; } }
				waitpid(p1, NULL, 0);
				waitpid(p2, NULL, 0);		
				waitpid(p3, NULL, 0); 
				if (resultado == 0 && v[k+3] != 0 && v[k+3] != 1) { (*b) = (*b)+1; } } 
				
				if (tamanho - k == 3) { aux = 3; }
				if (tamanho - k == 2) { aux = 2;}
				if (tamanho - k == 1) { aux = 1;}
				}
 

    if (num_proc == 1) {

         for (j = 2; j < v[0]; j++) {
                if (v[0] % j == 0) {
                                resultado=1;
                                break; } }
         if (resultado == 0 && v[0] != 0 && v[0] != 1) {
                            (*b) = (*b) + 1;
                            printf("%d\n",*b); }
         else printf("%d\n",*b); }



    if (num_proc == 2) {

        p1 = fork();
        if(p1==0) {
                 for (j = 2; j < v[0]; j++) {
                        if (v[0] % j == 0) {
                                        resultado=1;
                                        break; } }
                 if (resultado == 0 && v[0] != 0 && v[0] != 1) { (*b) = (*b)+1; }
                 exit(0); }
				 
         waitpid(p1, NULL, 0);
         for (j = 2; j < v[1]; j++) {
                 if (v[1] % j == 0) {
                                      resultado=1;
                                      break; } }
                 if (resultado == 0 && v[1] != 0 && v[1] != 1) { *b = *b+1; } }

 
    

   if (num_proc == 3) {

        p1 = fork();
	p2 = fork();
        if(p1==0) {
                 for (j = 2; j < v[0]; j++) {
                        if (v[0] % j == 0) {
                                        resultado=1;
                                        break; } }
                 if (resultado == 0 && v[0] != 0 && v[0] != 1) { (*b) = (*b)+1; }
                 exit(0); }
        if(p2==0) {
                 for (j = 2; j < v[1]; j++) {
                        if (v[1] % j == 0) {
                                        resultado=1;
                                        break; } }
                 if (resultado == 0 && v[1] != 0 && v[1] != 1) { (*b) = (*b)+1; }
                 exit(0); }
				 
         waitpid(p1, NULL, 0);
	 waitpid(p2, NULL, 0);
         for (j = 2; j < v[2]; j++) {
                 if (v[2] % j == 0) {
                                      resultado=1;
                                      break; } }
                 if (resultado == 0 && v[2] != 0 && v[2] != 1) { *b = *b+1; } }   
         printf("%d\n",*b); }




int main() {
    char entrada_dados[100];
    int v[100];
    int primos=0;
    int i=0;
    scanf("%[^\n]s",&entrada_dados);
    int tamanho = strlen(entrada_dados);
    char* pointer = strtok(entrada_dados," ");

    while(pointer) {
        v[i] = atoi(pointer);
        pointer = strtok(NULL," ");
        i++; }

    int num_proc = i;
    if (num_proc>4) {num_proc=4;}

    multiprocessos(num_proc, v, i);

    return 0;
}
