#include<stdio.h>
int main(){
			  int i,j,d,k,l,frst,f,s,last_ele,last,a[10],c[10],d2[10],prev,frst_ele,b[10],final[10][10],result[10],pad[10];
	      int rslt,sum;
				for(i=0;i<10;i++)
			 {
			 	 c[i]=0;
			 	 d2[i]=0;
			 }
			 printf("Enter the length of the first matrix : ");
			 scanf("%d",&f);
			 printf("\nEnter the elements of the first matrix : ");
			 for(i=0;i<f;i++)
			 {
			 	 scanf("%d",&c[i]);
			 }
			 printf("Enter the length of the Second matrix : ");
			 scanf("%d",&s);
			 printf("\nEnter the elements of the first matrix : ");
			 for(i=0;i<s;i++)
			 {
			 	 scanf("%d",&d2[i]);
			 }
		   printf("\n First matrix before padding: ");
		   printf("\n[ ");
			 for(i=0;i<f;i++)
			 {
			 	 printf("%d\t",c[i]);
			 }
			 printf("]\n");
		   printf("\n Second matrix before padding: ");
		   printf("\n[ ");
			 for(i=0;i<s;i++)
			 {
			 	 printf("%d\t",d2[i]);
			 }
			 printf("]\n");
			if(f>s)
			{
			 		  for(i=0;i<f;i++)
			 			{
			 			 a[i]=c[i];
			 		  }	 
		        frst=f;
		          for(i=0;i<frst;i++)
			 			{
			 			 pad[i]=d2[i];
			 		  }	 
		  }
		  else
		  {
	 		    for(i=0;i<s;i++)
			 	 {
			 	   a[i]=d2[i];
				 }
			   frst=s;
	       for(i=0;i<frst;i++)
	 			{
	 			 pad[i]=c[i];
	 		  }	 
	 		}
			 printf("\n Both the Matrix After padding : \n\t1st Matrix\t 2nd Matrix ");
			 for(i=0;i<frst;i++)
			 {
			 	 printf("\n\t     %d\t\t     ",c[i]);
			 	 printf("%d",d2[i]);
			 }
			 for(j=0;j<frst;j++)
			 {
				  
			 		last=frst-1;
			 		frst_ele=a[0];
					last_ele=a[last];
				  if(j>0)
					{
						 for(k=0;k<frst;k++)
						 {
								if(k>0 && k<frst)
								{
			 			      prev=k-1;
			 			      b[k]=a[prev];
		 			        final[k][j]=b[k];
							}
								else 
								{
								 	b[0]=last_ele;
								 	final[k][j]=b[k];
							
								}				
						}
			       for(d=0;d<frst;d++)
			        {
								a[d]=b[d];
							}	
					}
					else
					{
					 		 for(k=0;k<frst;k++)
			        {
					      final[k][j]=a[k];
								
							}
		 		  }
		}
       printf("\n\n ******* Final Matrix *****\n");
       	for(i=0;i<frst;i++)
				{
				 
					for(j=0;j<frst;j++)
						{
							printf("\t%d",final[i][j]);
						}	
				printf("\n");
				}
				 printf("\n ******* Circular Convulated Matrix *****\n");
				 printf("\n[ ");
       	for(i=0;i<frst;i++)
				{
			     sum=0;
					for(j=0;j<frst;j++)
						{
					    rslt=final[i][j]*pad[j];
							sum=sum+rslt;
						}	
						result[j]=sum;
						printf("%d\t",result[j]);
				}
					printf("]\n");
       return 0;
}