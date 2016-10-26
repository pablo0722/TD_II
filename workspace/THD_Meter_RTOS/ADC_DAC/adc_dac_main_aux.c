/*
 * adc_dac_main.c
 *
 *  Created on: 20 de oct. de 2016
 *      Author: Pablo
 */




#include "header.h"


#define DMACIntStat			((*((volatile const uint32_t *) 0x50004000)) & 0xFF)
#define DMACRawIntTCStat 	((*((volatile const uint32_t *) 0x50004004)) & 0xFF)
#define DMACRawIntErrStat 	((*((volatile const uint32_t *) 0x5000400C)) & 0xFF)
#define DMACEnbldChns 		((*((volatile const uint32_t *) 0x5000401C)) & 0xFF)
#define DMACSoftBReq 		((*((volatile const uint32_t *) 0x50004020)) & 0xFFFF)
#define DMACSoftSReq 		((*((volatile const uint32_t *) 0x50004024)) & 0xFFFF)
#define DMACConfig 			((*((volatile const uint32_t *) 0x50004030)) & 0x03)
#define DMACSync 			((*((volatile const uint32_t *) 0x50004030)) & 0xFFFF)
#define DMACC0SrcAddr 		((*((volatile const uint32_t *) 0x50004100)) & 0xFFFFFFFF)
#define DMACC0DestAddr 		((*((volatile const uint32_t *) 0x50004104)) & 0xFFFFFFFF)
#define DMACC0LLI	 		((*((volatile const uint32_t *) 0x50004108)) & 0xFFFFFFFC)
#define DMACC0Control	 	((*((volatile const uint32_t *) 0x5000410C)) & 0xFFFFFFFF)
#define DMACC0Config	 	((*((volatile const uint32_t *) 0x50004110)) & 0x0007FFFF)
#define DMACC1SrcAddr 		((*((volatile const uint32_t *) 0x50004120)) & 0xFFFFFFFF)
#define DMACC1DestAddr 		((*((volatile const uint32_t *) 0x50004124)) & 0xFFFFFFFF)
#define DMACC1LLI	 		((*((volatile const uint32_t *) 0x50004128)) & 0xFFFFFFFC)
#define DMACC1Control	 	((*((volatile const uint32_t *) 0x5000412C)) & 0xFFFFFFFF)
#define DMACC1Config	 	((*((volatile const uint32_t *) 0x50004130)) & 0x0007FFFF)


#define BYTE_TO_BINARY_2(byte)  \
  (byte & 0x02 ? 1 : 0), \
  (byte & 0x01 ? 1 : 0)


#define BYTE_TO_BINARY_8(byte)  \
  (byte & 0x80 ? 1 : 0), \
  (byte & 0x40 ? 1 : 0), \
  (byte & 0x20 ? 1 : 0), \
  (byte & 0x10 ? 1 : 0), \
  (byte & 0x08 ? 1 : 0), \
  (byte & 0x04 ? 1 : 0), \
  (byte & 0x02 ? 1 : 0), \
  (byte & 0x01 ? 1 : 0)


#define BYTE_TO_BINARY_16(byte)  \
  (byte & 0x8000 ? 1 : 0), \
  (byte & 0x4000 ? 1 : 0), \
  (byte & 0x2000 ? 1 : 0), \
  (byte & 0x1000 ? 1 : 0), \
  (byte & 0x0800 ? 1 : 0), \
  (byte & 0x0400 ? 1 : 0), \
  (byte & 0x0200 ? 1 : 0), \
  (byte & 0x0100 ? 1 : 0), \
  (byte & 0x0080 ? 1 : 0), \
  (byte & 0x0040 ? 1 : 0), \
  (byte & 0x0020 ? 1 : 0), \
  (byte & 0x0010 ? 1 : 0), \
  (byte & 0x0008 ? 1 : 0), \
  (byte & 0x0004 ? 1 : 0), \
  (byte & 0x0002 ? 1 : 0), \
  (byte & 0x0001 ? 1 : 0)


#define BYTE_TO_BINARY_32(byte)  \
  (byte & 0x80000000 ? 1 : 0), \
  (byte & 0x40000000 ? 1 : 0), \
  (byte & 0x20000000 ? 1 : 0), \
  (byte & 0x10000000 ? 1 : 0), \
  (byte & 0x08000000 ? 1 : 0), \
  (byte & 0x04000000 ? 1 : 0), \
  (byte & 0x02000000 ? 1 : 0), \
  (byte & 0x01000000 ? 1 : 0), \
  (byte & 0x00800000 ? 1 : 0), \
  (byte & 0x00400000 ? 1 : 0), \
  (byte & 0x00200000 ? 1 : 0), \
  (byte & 0x00100000 ? 1 : 0), \
  (byte & 0x00080000 ? 1 : 0), \
  (byte & 0x00040000 ? 1 : 0), \
  (byte & 0x00020000 ? 1 : 0), \
  (byte & 0x00010000 ? 1 : 0), \
  (byte & 0x00008000 ? 1 : 0), \
  (byte & 0x00004000 ? 1 : 0), \
  (byte & 0x00002000 ? 1 : 0), \
  (byte & 0x00001000 ? 1 : 0), \
  (byte & 0x00000800 ? 1 : 0), \
  (byte & 0x00000400 ? 1 : 0), \
  (byte & 0x00000200 ? 1 : 0), \
  (byte & 0x00000100 ? 1 : 0), \
  (byte & 0x00000080 ? 1 : 0), \
  (byte & 0x00000040 ? 1 : 0), \
  (byte & 0x00000020 ? 1 : 0), \
  (byte & 0x00000010 ? 1 : 0), \
  (byte & 0x00000008 ? 1 : 0), \
  (byte & 0x00000004 ? 1 : 0), \
  (byte & 0x00000002 ? 1 : 0), \
  (byte & 0x00000001 ? 1 : 0)


#if USE_DAC_INTERNO
	void main_dac_aux()
	{
		#if (DEBUG_MODE)
/*
			static uint32_t IntStat = -1;
			if(IntStat != DMACIntStat)
			{
				IntStat = DMACIntStat;
				printf("DMACIntStat: %d%d%d%d %d%d%d%d \r\n", BYTE_TO_BINARY_8(IntStat));
			}

			static uint32_t RawIntTCStat = -1;
			if(RawIntTCStat != DMACRawIntTCStat)
			{
				RawIntTCStat = DMACRawIntTCStat;
				printf("DMACRawIntTCStat: %d%d%d%d %d%d%d%d \r\n", BYTE_TO_BINARY_8(RawIntTCStat));
			}

			static uint32_t RawIntErrStat = -1;
			if(RawIntErrStat != DMACRawIntErrStat)
			{
				RawIntErrStat = DMACRawIntErrStat;
				printf("DMACRawIntErrStat: %d%d%d%d %d%d%d%d \r\n", BYTE_TO_BINARY_8(RawIntErrStat));
			}

			static uint32_t EnbldChns = -1;
			if(EnbldChns != DMACEnbldChns)
			{
				EnbldChns = DMACEnbldChns;
				printf("DMACEnbldChns: %d%d%d%d %d%d%d%d \r\n", BYTE_TO_BINARY_8(EnbldChns));
			}

			static uint32_t SoftBReq = -1;
			if(SoftBReq != DMACSoftBReq)
			{
				SoftBReq = DMACSoftBReq;
				printf("DMACSoftBReq: %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d \r\n", BYTE_TO_BINARY_16(SoftBReq));
			}

			static uint32_t SoftSReq = -1;
			if(SoftSReq != DMACSoftSReq)
			{
				SoftSReq = DMACSoftSReq;
				printf("DMACSoftSReq: %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d \r\n", BYTE_TO_BINARY_16(SoftSReq));
			}

			static uint32_t Config = -1;
			if(Config != DMACConfig)
			{
				Config = DMACConfig;
				printf("DMACConfig: %d%d \r\n", BYTE_TO_BINARY_2(Config));
			}

			static uint32_t Sync = -1;
			if(Sync != DMACSync)
			{
				Sync = DMACSync;
				printf("DMACSync: %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d \r\n", BYTE_TO_BINARY_16(Sync));
			}

			static uint32_t C0SrcAddr = -1;
			if(C0SrcAddr != DMACC0SrcAddr)
			{
				C0SrcAddr = DMACC0SrcAddr;
				printf("DMACC0SrcAddr: %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d \r\n", BYTE_TO_BINARY_32(C0SrcAddr));
			}

			static uint32_t C0DestAddr = -1;
			if(C0DestAddr != DMACC0DestAddr)
			{
				C0DestAddr = DMACC0DestAddr;
				printf("DMACC0DestAddr: %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d \r\n", BYTE_TO_BINARY_32(C0DestAddr));
			}

			static uint32_t C0LLI = -1;
			if(C0LLI != DMACC0LLI)
			{
				C0LLI = DMACC0LLI;
				printf("DMACC0LLI: %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d \r\n", BYTE_TO_BINARY_32(C0LLI));
			}

			static uint32_t C0Control = -1;
			if(C0Control != DMACC0Control)
			{
				C0Control = DMACC0Control;
				printf("DMACC0Control: %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d \r\n", BYTE_TO_BINARY_32(C0Control));
			}

			static uint32_t C0Config = -1;
			if(C0Config != DMACC0Config)
			{
				C0Config = DMACC0Config;
				printf("DMACC0Config: %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d \r\n", BYTE_TO_BINARY_32(C0Config));
			}

			static uint32_t C1SrcAddr = -1;
			if(C1SrcAddr != DMACC1SrcAddr)
			{
				C1SrcAddr = DMACC1SrcAddr;
				printf("DMACC1SrcAddr: %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d \r\n", BYTE_TO_BINARY_32(C1SrcAddr));
			}

			static uint32_t C1DestAddr = -1;
			if(C1DestAddr != DMACC1DestAddr)
			{
				C1DestAddr = DMACC1DestAddr;
				printf("DMACC1DestAddr: %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d \r\n", BYTE_TO_BINARY_32(C1DestAddr));
			}

			static uint32_t C1LLI = -1;
			if(C1LLI != DMACC1LLI)
			{
				C1LLI = DMACC1LLI;
				printf("DMACC1LLI: %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d \r\n", BYTE_TO_BINARY_32(C1LLI));
			}

			static uint32_t C1Control = -1;
			if(C1Control != DMACC1Control)
			{
				C1Control = DMACC1Control;
				printf("DMACC1Control: %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d \r\n", BYTE_TO_BINARY_32(C1Control));
			}

			static uint32_t C1Config = -1;
			if(C1Config != DMACC1Config)
			{
				C1Config = DMACC1Config;
				printf("DMACC1Config: %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d \r\n", BYTE_TO_BINARY_32(C1Config));
			}
*/
		#endif
	}
#endif

