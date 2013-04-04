// ’’ ”€‰‹ ‘„…†ˆ’ ‚€†…‰˜ˆ… •€€Š’…ˆ‘’ˆŠˆ ‚€˜…ƒ –…‘‘€
#define _PII	0x2
#define _PIII	0x3
#define _P4		0x4
#define _P2DUOE8400 0x5
#define _Athlon	0x015


#ifndef _CPU
	#define _CPU _P2DUOE8400
#endif


#if (_CPU==_P4)
	#define CPU_NAME		"P4"
	#define L1_CACHE_SIZE		8*K
	#define L2_CACHE_SIZE		256*K
	#define L1_CACHE_LINE_SIZE	64
	#define L1_PREFETCH_SIZE	128
	#define L2_PREFETCH_SIZE	128
#endif

#if (_CPU==_P2DUOE8400)
	#define CPU_NAME		"P-Core 2 Duo E8400"
	#define L1_CACHE_SIZE		32*K //64Kb indeed 32 for data, 32 for instructions
	#define L2_CACHE_SIZE		6*M
	#define L1_CACHE_LINE_SIZE	64
	#define L2_CACHE_LINE_SIZE	64
	#define L1_PREFETCH_SIZE	32 // unknown
	#define L2_PREFETCH_SIZE	32 // unknown
	#define L2_BUS_WIDE			256 
	#define PAGE_SIZE			64*K
	#define BANK_COUNT			8      // SDDR3
	#define PACKET_SIZE			32	   //
#endif

#if (_CPU==_PIII)
	#define CPU_NAME		"P-III"
	#define L1_CACHE_SIZE		16*K
	#define L2_CACHE_SIZE		256*K
	#define L1_CACHE_LINE_SIZE	32
	#define L2_CACHE_LINE_SIZE	32
	#define L1_PREFETCH_SIZE	32
	#define L2_PREFETCH_SIZE	32
	#define L2_BUS_WIDE			256
#endif

#if (_CPU==_PII)
	#define CPU_NAME		"P-II"
	#define L1_CACHE_SIZE		16*K
	#define L2_CACHE_SIZE		128*K
	#define L1_CACHE_LINE_SIZE	32
#endif

#if (_CPU==_Athlon)
	#define CPU_NAME		"AMD-Athlon"
	#define L1_CACHE_SIZE		64*K
	#define L2_CACHE_SIZE		256*K
	#define L1_CACHE_LINE_SIZE	64
	#define L2_CACHE_LINE_SIZE	64
	#define _NORDTSC 
#endif

// CPU LEVEL

