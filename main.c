#include <stdint.h>
#include <stdio.h>
uint32_t add(uint32_t x,uint32_t y);
uint32_t sub(uint32_t x,uint32_t y);
int main(void)
{
    /* Loop forever */
	uint32_t res;
	res=add(40,-90);
	printf("sum=%ld",res);
	res=sub(90,50);
	printf("diff=%ld",res);
	for(;;);
}
uint32_t add(uint32_t x,uint32_t y)
{
	uint32_t res;
	__asm("SVC #36");
	__asm("MOV %0,R0":"=r"(res)::);
	return res;
}
uint32_t sub(uint32_t x,uint32_t y)
{
	uint32_t res;
	__asm("SVC #37");
	__asm("MOV %0,R0":"=r"(res)::);
	return res;
}
__attribute__((naked)) SVC_Handler(void)
{
	__asm("MRS R0,MSP");
	__asm("B SVC_Handler_c");
}
void SVC_Handler_c(uint32_t *pBase)
{
	uint32_t val1,val2,res;
	uint32_t *pRet_add=(uint32_t *)pBase[6];
	pRet_add-=2;
	uint8_t SVC_no=*pRet_add;
	printf("svc_no=%d",SVC_no);

	val1=pBase[0];
	val2=pBase[1];
	switch(SVC_no)
	{
	case 36:
		res=val1+val2;
		break;
	case 37:
		res=val1-val2;
		break;
	default:
		printf("inv");
		break;
	}
	pBase[0]=res;
	printf("in SVC");
}
