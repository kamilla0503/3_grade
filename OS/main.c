#include <stdio.h>
#include <sys/file.h>
#include <stdlib.h>
#include<sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include<signal.h>
#include <setjmp.h>
#include <string.h>
//#include<dos.h>

sigjmp_buf obl;
int counter=0;
char name_for_copy[] = "Test";
char name_of_original[BUFSIZ];
//char *name_of_original;
void for_signals(){
    int q, n, f1;
    char buf[BUFSIZ];
    counter = counter +1;
    printf("\n Interaption! \n");
    signal (SIGINT, for_signals);
    if(counter ==1){
        printf("\n It was first signal \n");
        q= link(name_for_copy, name_of_original);
        if(q!=0){
            printf("Mistake with rename \n");
        }
        unlink(name_for_copy);
        f1=open(name_of_original, O_RDONLY);

        while ((n = read(f1, buf, BUFSIZ)) > 0) {
            buf[n]=0;
            printf("%s", buf);
            printf("\n");
        }
        close(f1);







    }

    if(counter>5){
        printf("finish \n");
        exit(1);
    }

    siglongjmp (obl, 1);



}

int main(int argc, char *argv[]) {
    void for_signals();



    int f1, f2, fd[2], s, status;
    struct stat buff;
    char buf[BUFSIZ], command[BUFSIZ]="cmp -s ";
    int n, k, n1;
    struct sigaction mm;
    //signal(SIGINT, for_signals);

    mm.sa_handler = for_signals;
    mm.sa_flags = 0;
    sigprocmask(0, 0, &mm.sa_mask);

    sigaction(SIGINT, &mm, 0);

    sigsetjmp(obl, 1);
    printf("Enter the name of file \n");
    n = scanf("%s", &name_of_original[0]);
    //name_of_original[n]=0;
    //printf("see it \n");
    //printf("%s \n", name_of_original);

       //name_of_original=argv[1];
       sigsetjmp(obl, 1);
        f1 = open(name_of_original, O_RDONLY, 0);
        if (f1 == -1) {
            printf("Something related to file is wrong! \n");
            return -1;
        }
        stat(name_of_original, &buff);
        f2 = creat(name_for_copy, buff.st_mode);
        if (f2 == -1) {
            printf("Problems related to creating file! \n");
            return -1;
        }

        sleep(3);
        //printf("%d", buff.st_mode);
        while ((n = read(f1, buf, BUFSIZ)) > 0) {
            if (write(f2, buf, n) != n) {
                printf("Copy process was wrong! \n");
                return -1;
            }
        }
       close(f1);
       close(f2);
       printf("copy finished \n");



        sleep(2);
        printf("before pipe  \n");
        pipe(fd);
        printf("after pipe \n");

    strcat(command, name_of_original);
    strcat(command, " ");
    strcat(command, name_for_copy);
    strcat(command, "; echo $?\n");
    //system(command);
    printf("see it \n");
    printf("%s\n", command);
    if (fork() == 0) {
            k = 0;
            close(1);
            //printf("fork \n");
            close(fd[0]);
            dup(fd[1]);
            close(fd[1]);
            //execl("/bin/echo", "echo", "Start", 0);

            //execl("/usr/bin/cmp", "/usr/bin/cmp", "-s", "CPP_version/conformations.cpp", "Copy", 0);
            //execl("/usr/bin/cmp", "cmp", "-l", name_of_original, name_for_copy, 0);

            //execl("/bin/echo", "echo", "Start", 0);

            system(command);





            exit(0);
        } else {
            //printf("parent \n ");

            wait(0);
            sigsetjmp(obl, 1);
        printf("problems or not *** \n");
        //close(fd[1]);
            //buf[0]=0;
            //
            n=read(fd[0], buf,10);
        printf("problems or not %d \n", n);
        printf("problems or not \n");
        printf("it is buf %s \n", buf);
            //buf[n]=0;
            sleep(2);
                if (buf[0]=='0') {
                    printf("Files are the same, original file will be removed \n");
                    sleep(5);
                    unlink(name_of_original);

                    printf("deleted \n ");
                    sigsetjmp(obl, 1);

                    sleep(5);

                } else {
                    printf("files are different! \n");
                }






            //printf(buf);

        }


       //free(fd);


        //printf("descriptions is %d %d \n", f1, f2);











    printf("Hello, World!\n");
    return 0;

}






/**while ((n = read(f1, buf, BUFSIZ)) > 0 && (n1= read(f2, buf1, BUFSIZ))>0) {
                //n1= read(f2, buf1, BUFSIZ);
                if (buf != buf1){
                    printf("Files are different! \n");
                    k=-1;

                    break;
                }
            }
            if(k==0){
                printf("Files are the same, original file will be removed \n");
                unlink(argv[1]);

            }**/