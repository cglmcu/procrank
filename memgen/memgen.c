#include <stdio.h>
#include <stdlib.h> // rand()함수 포함 라이브러리
#include <time.h> // time()함수 포함 라이브러리
#include <unistd.h>

int main()
{
    srand(time(NULL)); // 매번 다른 시드값 생성
    int random = 0; // 정수형 변수 선언
    char* m[BUFSIZ];
    int msize[BUFSIZ];
    int mcnt = 0;
    int sum = 0;

    while(1){
        for (int i = 0; i < 10; i++) { // 10번 반복
            random = rand()%50000; // 난수 생성
            // printf("%d\n",random);
            m[mcnt] = malloc(random);
            msize[mcnt] = random;
            sum += random;
            if(mcnt+1 >= BUFSIZ){
                break;
            }
            mcnt++;
        }
        for (int i = 0; i < 9; i++) { // 10번 반복
            mcnt--;
            free(m[mcnt]);
            sum -= msize[mcnt];
        }
        (void) usleep(1000000);
        printf("wait : %d\n",sum);
    }
}
