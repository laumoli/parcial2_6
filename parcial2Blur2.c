
#include <stdio.h>
#include <time.h>
#include <omp.h>


void kernel();

int main()
{


	kernel();
}


void kernel(){

  FILE *image = fopen("lena_color.bmp","rb");			
	FILE *outputImage = fopen("image_blur7.bmp","wb");		    	

	int i,j,y, x;

	unsigned char xx[54]; 

      for(int i=0; i<54; i++){
        xx[i] = getc(image);
        putc(xx[i], outputImage);
    }

	int height = *(int*)&xx[18];
	int width = *(int*)&xx[22];
	int bitDepth = *(int*)&xx[28];

	printf("width: %d\n",width);
	printf("height: %d\n",height );

	int size = height*width;					

	unsigned char in[size][3];				
	unsigned char out[size][3];					

	for(i=0;i<size;i++)						
	{
		in[i][2]=getc(image);					// blue
		in[i][1]=getc(image);					// green
		in[i][0]=getc(image);					// red
	}
float v=1.0 / 9.0;						// blurring kernel
	float kernel[15][15]={{v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
					           {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v}};

	for(x=1;x<height-14;x++)
	{					
		for(y=1;y<width-14;y++)
		{
			float sum0= 0.0;

			for(i=-1;i<=8;++i)
			{
				for(j=-1;j<=8;++j)
				{	
					sum0=sum0+(float)kernel[i+1][j+1]*in[(x+i)*width+(y+j)][0];
				}
			}
			out[(x)*width+(y)][0]=sum0;
		}
	}

	float kernel1[23][23]={{v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
					           {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v}};
	for(x=1;x<height-22;x++)
	{					
		for(y=1;y<width-22;y++)
		{
			float sum0= 0.0;

			for(i=-1;i<=8;++i)
			{
				for(j=-1;j<=8;++j)
				{	
					sum0=sum0+(float)kernel1[i+1][j+1]*in[(x+i)*width+(y+j)][2];
				}
			}
			out[(x)*width+(y)][2]=sum0;
		}
	}
  
  float kernel2[35][35]={{v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
						         {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
					           {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
					           {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
					           {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
					           {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
					           {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
					            {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
					             {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
					              {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
					               {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
					                {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
					                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
					           {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v}};
	
	for(x=1;x<height-34;x++)
	{					
		for(y=1;y<width-34;y++)
		{
			float sum0= 0.0;

			for(i=-1;i<=8;++i)
			{
				for(j=-1;j<=8;++j)
				{	
					sum0=sum0+(float)kernel2[i+1][j+1]*in[(x+i)*width+(y+j)][1];
				}
			}
			out[(x)*width+(y)][1]=sum0;
		}
	}
  
	
	
	for(i=0;i<size;i++)						
	{
		putc(out[i][2],outputImage);
		putc(out[i][1],outputImage);
		putc(out[i][0],outputImage);
	}
		
	fclose(outputImage);
	fclose(image);


}


