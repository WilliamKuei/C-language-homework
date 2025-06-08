#include <stdio.h>
#include <string.h>
typedef union{
	struct{
		unsigned F:23;
		unsigned E:8;
		unsigned S:1;
	};
	float f;
} Float;
int S2I(char *s, int *i,int *digit);
unsigned long I2Fragment(unsigned long vt, unsigned long digit,int *n);
float S2Float(char * s);
int pEncoder(unsigned long vt);
int main()
{
	Float v;
	char s[100]="1234567890";
	double df;

	while(1){
		printf("=============================\n");
		gets_s(s, sizeof(s));
		if(strstr(s,"end")!=NULL)break;
		v.f= S2Float(s);
		printf(">> [%f][%02X][%08lX]\n",v.f,v.E,v.F);
		sscanf(s,"%f",&(v.f));
		printf("[%f][%02X][%08lX]\n",v.f,v.E,v.F);
	}

	return 0;
}

float S2Float(char * s)
{
	unsigned long vt,ft=0,BM,ftf,ftft;
	int n,i,t,nn;
	Float v;

	i = 0;
	vt = S2I(s,&i, &t);
	n= pEncoder(vt);

	v.S=0;
	v.E= (n == -1)?0:127+n;

	if(n >=0){
		if(n < 24 ){
			ft= (vt << (23-n));
		}else{
			v.F= (vt >> (n-23))+1;
			return v.f;
		}
	}
	if(s[i]!='.'){
		v.F=ft;
		return v.f;
	}
	i++;
	vt = S2I(s, &i, &t);
	ftft = I2Fragment(vt, (unsigned long) t, &nn);

	if(v.E==0){
	    v.E= (ftft==0)?0:(127-nn-1);
		ft= ftft;
	}
	else {		
		ftf = ftft >> (nn+1);
		ft |= (n > 0) ? (ftf >> n) : ftf;
	}

	v.F=ft&0x7FFFFF;

	return v.f;
}

unsigned long I2Fragment(unsigned long vt,  unsigned long digit, int *n)
{
	unsigned long BM = 0x0800000,ft;
	unsigned char flag = 0;
	ft = 0UL;*n = 0;
//	printf("[%08lX] <%d>", vt, vt);
	while (BM > 0 && vt > 0) {
		vt <<= 1; // vt*2
		if (vt < digit && flag == 0) {
			(*n)++;
			continue;
		}
		else {
			flag = 1;
		}
		ft = (vt >= digit) ? (vt -= digit, (ft | BM)) : (ft & (~BM));
		BM >>= 1;
	}
	printf("[%08lX] <%d>\n", ft, *n);
	return ft;
}

int S2I(char *s, int *ii, int *digit)
{
	int vt,i;
	*digit = 1;vt = 0;
	for (i= *ii;s[i] && (s[i] >= '0' && s[i] <= '9');i++) {
		vt = vt * 10 + (s[i] - '0');
		*digit = (*digit) * 10;
	}
	*ii = i;
//	printf("[%s]=<%08lX> %d %d\n", s, vt, *ii, *digit);
	return vt;
}

int pEncoder(unsigned long vt)
{
	union {
		unsigned long n;
		unsigned char b[4];
	}v;
	int i,k;
	unsigned char B,BM=0x80;

	v.n=vt;
	for(i=3;i> 0;i--){
		if(v.b[i] != 0 ) break;
	}
	B=v.b[i];
	k= i * 8;

	for(i=7;i >= 0 && !(BM&B);i--, BM >>= 1);
	k=k+i;
	return k;
}