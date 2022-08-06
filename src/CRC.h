/* crc.h -- header for CCITT CRC-32 function.
   This file is in the Public Domain.
*/

extern void CALLTYPE crc32done(void); // Frees up 1024 bytes of RAM.
extern unsigned long int *Ccitt32Table;
extern int CALLTYPE BuildCRCTable(void);
// Allocates a 1024-byte table and fills it.
// Make sure that the following macro is called after BuildCRCTable() but before crc32done().

#define crc32(crc, c)(((crc>>8)&0x00FFFFFFL)^(Ccitt32Table[(int)((int)crc^c)&0xFF]))

/* crc.cpp -- contains table based CCITT 32 bit CRC function.
   This file is in the Public Domain.
*/

#define CRC_MASK           0xFFFFFFFFL
#define CRC32_POLYNOMIAL   0xEDB88320L

unsigned long  *Ccitt32Table = (unsigned long *)NULL;

/*
   This routine simply builds the coefficient table used to calculate
   32 bit CRC values throughout this program. The 256 long word table
   has to be set up once when the program starts. Alternatively, the
   values could be hard coded in, which would offer a miniscule improvement
   in overall performance of the program.
*/

int CALLTYPE BuildCRCTable(void) {
  int i;
  int j;
  unsigned long value;
  if (Ccitt32Table) return 0;
  Ccitt32Table = new unsigned long int[256];
  if (Ccitt32Table == NULL) {
    return 1;
  }
  for (i = 0; i <= 255 ; i++) {
    value = i;
    for (j = 8 ; j > 0; j--) {
      if (value & 1) value = (value >> 1) ^ CRC32_POLYNOMIAL;
      else value >>= 1;
    }
    Ccitt32Table[ i ] = value;
  }
  return 0;
}

void CALLTYPE crc32done(void) {
  if (Ccitt32Table) {
    delete Ccitt32Table;
    Ccitt32Table = (unsigned long*)NULL;
  }
}
