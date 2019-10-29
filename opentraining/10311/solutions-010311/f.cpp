#include <cstdio>
// precalc solution by Snark; precalc was written in Java
int main()
{
int a,b;
scanf ("%d %d",&a,&b);
if ((a==1)&&(b==1)) printf ("0\n");
else if ((a==1)&&(b==2)) printf ("17\n");
else if ((a==1)&&(b==4)) printf ("10\n");
else if ((a==1)&&(b==6)) printf ("4\n");
else if ((a==1)&&(b==8)) printf ("7\n");
else if ((a==2)&&(b==2)) printf ("1\n");
else if ((a==2)&&(b==4)) printf ("18\n");
else if ((a==2)&&(b==6)) printf ("8\n");
else if ((a==2)&&(b==8)) printf ("11\n");
else if ((a==3)&&(b==2)) printf ("5\n");
else if ((a==3)&&(b==4)) printf ("78\n");
else if ((a==3)&&(b==6)) printf ("88\n");
else if ((a==3)&&(b==8)) printf ("15\n");
else if ((a==4)&&(b==2)) printf ("105\n");
else if ((a==4)&&(b==4)) printf ("2\n");
else if ((a==4)&&(b==6)) printf ("12\n");
else if ((a==4)&&(b==8)) printf ("115\n");
else if ((a==5)&&(b==2)) printf ("9\n");
else if ((a==5)&&(b==4)) printf ("102\n");
else if ((a==5)&&(b==6)) printf ("112\n");
else if ((a==5)&&(b==8)) printf ("19\n");
else if ((a==6)&&(b==2)) printf ("89\n");
else if ((a==6)&&(b==4)) printf ("6\n");
else if ((a==6)&&(b==6)) printf ("16\n");
else if ((a==6)&&(b==8)) printf ("79\n");
else if ((a==7)&&(b==2)) printf ("149\n");
else if ((a==7)&&(b==4)) printf ("46\n");
else if ((a==7)&&(b==6)) printf ("56\n");
else if ((a==7)&&(b==8)) printf ("159\n");
else if ((a==8)&&(b==2)) printf ("13\n");
else if ((a==8)&&(b==4)) printf ("106\n");
else if ((a==8)&&(b==6)) printf ("116\n");
else if ((a==8)&&(b==8)) printf ("3\n");
else if ((a==9)&&(b==2)) printf ("53\n");
else if ((a==9)&&(b==4)) printf ("166\n");
else if ((a==9)&&(b==6)) printf ("156\n");
else if ((a==9)&&(b==8)) printf ("63\n");
else printf ("-1\n");
return (0);
}
