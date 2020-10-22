#include <stdio.h>
#include <stdlib.h>


 int main(int argc, char *argv[])
{
    printf("Wartość %.0f do kwadratu to %.0f.\n", atof(argv[1]), atof(argv[1])*atof(argv[1]));
    return 0;
}

