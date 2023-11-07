
//4脚 5.0V
//3脚	GND

#include<reg51.h>
#include<intrins.h>


sbit SCLPIN=P1^4;
sbit SDAPIN=P1^3;


bit l_cx;
#define  time_1	6000    //8字速度
#define  time_2	6000


unsigned char code Mask[]={0xaf,0xa0,0xcb,0xe9,0xe4,0x6d,0x6f,0xa8,0xef,0xed};
unsigned char code Mask2[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

unsigned char data l_data[25];

unsigned char code z_addr1[]={
 1,4, 3,4, 0,4, 2,4, 4,4,11,4, 5,4,13,4,15,4,
18,3,18,2,18,1,18,0, 7,4,18,7,18,6,18,5,18,4, 6,4,
19,7,19,3,19,2,19,1,19,0, 8,4, 9,4,10,4,12,4,14,4,16,4,17,4,
21,2,21,1,21,3,20,7,20,3,21,0,20,4,20,6,20,5,
20,2,20,0,19,4,20,1,19,5,19,6
};




void f_start()
{  SDAPIN=1;
   _nop_();
   SCLPIN=1;
   _nop_();
   SDAPIN=0;
   _nop_();
   SCLPIN=0;
}

void f_stop()
{  SDAPIN=0;
   _nop_();
   SCLPIN=1;
   _nop_();
   SDAPIN=1;
   _nop_();
   SCLPIN=0;
}

bit IICCACK()
{  bit l_bit;
   SDAPIN=1;
   _nop_();
   SCLPIN=1;
   _nop_();
   l_bit=SDAPIN;
   _nop_();
   _nop_();
   SCLPIN=0;
   return l_bit;
}

void f_bit(bit l_bit)
{  SDAPIN=l_bit;
   _nop_();
   _nop_();
   SCLPIN=1;
   _nop_();
   SCLPIN=0;
   _nop_();
   SDAPIN=0;
}

void f_byte_rrc(unsigned char l_byte)
{  unsigned char i;
   for (i=0;i<8;i++)
   {  if((l_byte&0x1)==0x1)
         f_bit(1);
      else
         f_bit(0);
      l_byte>>=1;
   }
}

void f_byte(unsigned char l_byte)
{  unsigned char i;
   for (i=0;i<8;i++)
   {  if((l_byte&0x80)==0x80)
         f_bit(1);
      else
         f_bit(0);
      l_byte<<=1;
   }
}

void f_wc(unsigned char l_ICCS)
{  f_start();
   f_byte(0x7e);
   if(IICCACK()==0)
      f_byte(l_ICCS);
   f_stop();
}


void f_wd1(unsigned char l_ICADDR,unsigned char l_ICDATA)
{  l_data[l_ICADDR]=l_ICDATA;
   f_start();
   f_byte(0x7e);
   if(IICCACK()==0)
      f_byte(l_ICADDR);
   if(IICCACK()==0)
      f_byte(l_ICDATA);
   f_stop();
}

void f_fill(unsigned char h)
{  unsigned char i;
   for(i=0;i<22;i++)
   {
      f_wd1(i,h);
      }
}


void lcdreset()
{
   f_wc(0x8c);     //开显示，设偏压等
   f_wc(0xc0);     //光标关
   f_wc(0x71);     //VLCD电压调整
}

void delay(unsigned int t)
{  unsigned int i,j;
   lcdreset();
   for(i=0;i<t;i++)
      for(j=0;j<10;j++)
         ;
   lcdreset();
   
}


void f_dd()
{  unsigned char i,k,h;
   for(k=0;k<9;k++)
   {

   for(i=0;i<18;i++)
      f_wd1(i,Mask[k]);

   delay(time_1);
   }
}

void f_hhx1(unsigned char t)
{  unsigned char i,k;

   for(i=0;i<18;i++)
      l_data[i]=Mask[8];

   for(i=0;i<t+1;i+=2)
   {  l_data[z_addr1[i]]|=Mask2[z_addr1[i+1]];
   }
   for(i=0;i<22;i++)
   { f_wd1(i,l_data[i]);
   }
}

void f_hh()
{  unsigned char i;
   for(i=0;i<92;i+=2)
   {
   f_hhx1(i);
   delay(time_2);
   }
}

main()
{
   delay(100);
   while(1)
   {
   lcdreset();
   lcdreset();
   f_fill(0xff);
   delay(time_1);
   f_fill(0xff);
   delay(time_1);
   lcdreset();
   f_fill(0x00);
   lcdreset();
   f_dd();
   lcdreset();
   f_hh();
   }
}


