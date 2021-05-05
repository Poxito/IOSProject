#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>

void ls(const char *dir,int op_l)
{

        struct dirent *d;
        DIR *dh = opendir(dir);
        if (!dh)
        {
        printf("An error has occurred.");
                exit(EXIT_FAILURE);
        }
        printf("\n");
        while ((d = readdir(dh)) != NULL)
        {
                if (d->d_name[0] == '.')
                        continue;
                printf("%s  ", d->d_name);
                if(op_l) {

            struct stat st;
            int sterror = stat(d->d_name,&st);
            if(sterror==0){
                printf("%d",st.st_size);
                printf("\t");
                printf("%d",st.st_ctime);
                printf("\t");
            }
            printf("\n");
        }
        }
        if(!op_l)
        printf("\n");
}
int main(int argc, const char *argv[])
{
        if (argc == 1)
        {
                ls(".",0);
        }
        else if (argc == 2)
        {
                if (argv[1][0] == '-')
                {
                        int op_l = 0;
                        char *p = (char*)(argv[1] + 1);
                        while(*p){
                                if(*p == 'l') op_l = 1;
                                else{
                                        perror("Option not available");
                                        exit(EXIT_FAILURE);
                                }
                                p++;
                        }
                        ls(".",op_l);
                }
        }
        return 0;
}