#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define MAXSIZE 512

int number = 10;

int n = 0;

int args = 0;

void more_see(FILE *fp);
void usage(void);

int main(int argc, char *argv[])
{
    FILE *fp;
    int numarg = 1, c;
    
    if(argc == 1)
    {
        args = 1;
        more_see(stdin);
    }
    else
    {
        if(argc == 2)
        {
            if((fp = fopen(argv[1], "r")) == NULL)
            {
                usage();
                fclose(fp);
		exit(1);
            }
            more_see(fp);
        }
        if(argc > 2)
        {
            while(numarg != argc)
            {
                while((c = getopt(argc, argv, "n: ")) != -1)
                {
                    switch(c)
                    {
                        case 'n':
                            number = atoi(optarg);
                            numarg = optind;
                            break;
                        default:
                            usage();
                            exit(1);
                            break;
                    }
                }
                if((fp = fopen(argv[numarg], "r")) == NULL)
                {
                    usage();
                    exit(1);
                }
                if(number == 10)
                {
                    printf("==>%s<==\n", argv[numarg]);
                }
                if(argc > 4 && (number != 10))
                {
                    printf("==>%s<==\n", argv[numarg]);
                }
                more_see(fp);
                fclose(fp);
                numarg++;
                if(numarg != argc)
                {
                    printf("\n");
                }
            }
        }
    }
    return 0;
}

void more_see(FILE *fp)
{
    char eat[MAXSIZE] = {0};
    long z, y;
    
    if(args != 1)
    {
        fseek(fp, 0, SEEK_SET);
        
        z = ftell(fp);
        
        fseek(fp, -2, SEEK_END);
        
        y = ftell(fp);
        
        while(n != number && z < y)
        {
            if(fgetc(fp) == '\n')
            {
                n++;
            }
            if(n != number && z < y)
            {
                fseek(fp, -2, SEEK_CUR);
                y = ftell(fp);
            }
        }
    }
    if(number != 0)
    {
        while((fgets(eat, MAXSIZE, fp)) != '\0')
        {
            if(fputs(eat, stdout))
            {
            }
        }
        n = 0;
    }
}

void usage(void)
{
    printf("./tail1 -n numberlines file\n");
    printf("./tail1 file\n");
}
