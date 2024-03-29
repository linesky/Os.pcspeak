// need file libdos.c to be compile in directory
//bcc -x -i -L -Md hello.c -o HELLO.COM
#define varn 0x0080
#define seconds 18

int getptr();
void putsn(x,y,s,color,size);
void locate(x,y);
int gettimer();
void sleep(i);
void backs(address,count,color);

int main(){
	int n;
	int x=10;
	int y=10;
	int x1=200;
	int y1=150;
	int color=2;
	char c[80];
	backs(0xb800,4000,0x11);
	beep();


		asm	"db 0xb4,0,0xcd,0x21";
		
	return 0;
}



int getptr()
{
	int *c;
	c = (int * ) varn;

	asm	"db 0x8C,0xC8,0x2E,0xA3,0x80,0x0";
	return *(c + 0);
}

void putsn(x,y,s,color,size)
int x;
int y;
char *s;
int color;
int size;
{
	int *c;
	c = (int * ) varn;
	*(c + 0) = x;
	*(c + 1) = y;
	*(c + 2) = s;
	*(c + 3) = color;
	*(c + 4) = size;


	asm	"db 0x1E,0x06,0x50,0x53,0x51,0x52,0x56,0x57,0x0E,0x07,0x2E,0x8A,0x16,0x80,0x00,0x2E,0x8A,0x36,0x82,0x00,0x2E,0x8B,0x36,0x84,0x00,0x2E,0x8A,0x1E,0x86,0x00,0x2E,0x8B,0x0E,0x88,0x00,0xB7,0x00,0xB0,0x01,0xB4,0x13,0x55,0x89,0xF5,0xCD,0x10,0x5D,0x90,0x5F,0x5E,0x5A,0x59,0x5B,0x58,0x07,0x1F";
}

void backs(address,count,color)
int address;
int count;
int color;
{
	int *c;
	c = (int * ) varn;
	*(c + 0)=address;
	*(c + 1)=count;
	*(c + 2)=color;
	asm	"db 0x1E,0x06,0x0E,0x1F,0x8B,0x0E,0x82,0x00,0x8B,0x16,0x84,0x00,0xA1,0x80,0x00,0x50,0x07,0x88,0xD0,0x31,0xD2,0x89,0xD7,0x90,0xFC,0xF3,0xAA,0x07,0x1F";
	
}

void locate(x,y)
int x;
int y;
{
	int *c;
	c = (int * ) varn;
	*(c + 0) = x;
	*(c + 1) = y;


	asm	"db 0x1E,0x06,0x2E,0x8A,0x16,0x80,0x00,0x2E,0x8A,0x36,0x82,0x00,0xB7,0x00,0xB4,0x02,0xCD,0x10,0x90,0x07,0x1F";
}


int gettimer()
{
	int *c;
	c = (int * ) varn;

		asm	"db 0x1E,0x06,0x50,0x53,0x51,0x52,0x56,0x57,0xB4,0x00,0xCD,0x1A,0x2E,0x89,0x16,0x80,0x00,0x5F,0x5E,0x5A,0x59,0x5B,0x58,0x07,0x1F";
	return *(c + 0) & 0x7fff;	
}

void sleep(i)
int i;
{
	int t1;
	int t2;
	t1=gettimer();
	t1=t1+i;
	t2=gettimer();
	while(t1<t2){
		t2=gettimer();
	}
	while(t1>t2){
		t2=gettimer();
	}
}



int sound(freq)
int freq;
{
	int f1=freq;
	int f2=f1;
	int i2;
	int i1;
	int i;
	int *c;
	c = (int * ) varn;
	f1=f1;
	i1=f1;
	*(c + 0)=f1;
	*(c + 1)=0;
	*(c + 2)=0x61;
	*(c + 3)=0x43;
	*(c + 4)=0xb6;
	*(c + 5)=0x3;
	*(c + 6)=0xfc;

		asm	"db 0x1E,0x06,0x50,0x53,0x51,0x52,0x56,0x57,0x2E,0x8B,0x16,0x84,0x00,0x2E,0x8A,0x26,0x8A,0x00,0xEC,0x08,0xE0,0xEE,0x2E,0x8B,0x16,0x86,0x00,0x2E,0xA0,0x88,0x00,0xEE,0x4A,0x2E,0xA1,0x80,0x00,0xEE,0x88,0xE0,0xEE,0x5F,0x5E,0x5A,0x59,0x5B,0x58,0x07,0x1F";
	
}

int nosound()
{
	int *c;
	c = (int * ) varn;
	*(c + 0)=0x61;
	*(c + 1)=0xfc;
		asm	"db 0x1E,0x06,0x50,0x53,0x51,0x52,0x56,0x57,0x2E,0x8B,0x16,0x80,0x00,0xEC,0x22,0x06,0x82,0x00,0xEE,0x5F,0x5E,0x5A,0x59,0x5B,0x58,0x07,0x1F";
	
}


int beep(){
	sound(1800);
	sleep(seconds *1 );
	nosound();
}
