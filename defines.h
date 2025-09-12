// Set a specific bit in a word
#define SETBIT(WORD, BIT)           (WORD |= (1 << BIT))     

// Clear a specific bit in a word
#define CLRBIT(WORD, BIT)           (WORD &= ~(1 << BIT))    

// Complement (toggle) a specific bit in a word
#define CLPBIT(WORD, BIT)           (WORD ^= (1 << BIT))     

// Read a specific bit (returns 0 or 1)
#define READBIT(WORD, BIT)          (((WORD) >> (BIT)) & 1)  

// Write a single bit (0 or 1) to a specific bit position
#define WRITEBIT(WORD, BITPOS, BIT) \
    (WORD = ((WORD & ~(1 << BITPOS)) | ((BIT) << BITPOS)))

// Read a 4-bit nibble starting at BITSTARTPOS
#define READNIBBLE(WORD, BITSTARTPOS) \
    (((WORD) >> (BITSTARTPOS)) & 0x0F)  // 0x0F = 15

// Write a 4-bit nibble to a specific position
#define WRITENIBBLE(WORD, BITSTARTPOS, NIBBLE) \
    (WORD = ((WORD & ~(0x0F << BITSTARTPOS)) | ((NIBBLE & 0x0F) << BITSTARTPOS)))

// Read 8-bit byte starting from BITSTARTPOS
#define READBYTE(WORD, BITSTARTPOS) \
    (((WORD) >> (BITSTARTPOS)) & 0xFF)

// Write 8-bit byte at BITSTARTPOS
#define WRITEBYTE(WORD, BITSTARTPOS, BYTE) \
    (WORD = ((WORD & ~(0xFF << BITSTARTPOS)) | ((BYTE & 0xFF) << BITSTARTPOS)))

// Copy a bit from one source to a destination bit position in another word
#define READWRITEBIT(DWORD, DBIT, SWORD, SBIT) \
    (DWORD = ((DWORD & ~(1 << DBIT)) | (((SWORD >> SBIT) & 1) << DBIT)))

