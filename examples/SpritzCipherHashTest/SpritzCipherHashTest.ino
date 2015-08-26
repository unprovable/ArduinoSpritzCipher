/**
 * Spritz Cipher Hash Test
 *
 * This example code test SpritzCipher library hash output
 * using test vectors from "RS14.pdf" Page 30:
 * <https://people.csail.mit.edu/rivest/pubs/RS14.pdf>
 *
 * The circuit:  No external hardware needed.
 *
 * Created 25 Aug. 2015
 * by Abderraouf Adjal <abderraouf.adjal@gmail.com>
 *
 * This example code is in the public domain.
 */


#include <SpritzCipher.h>

/* Data to input */
const unsigned char testData1[3] = { 'A', 'B', 'C' };
const unsigned char testData2[4] = { 's', 'p', 'a', 'm' };
const unsigned char testData3[7] = { 'a', 'r', 'c', 'f', 'o', 'u', 'r' };

/* Test vectors */
/* Data 'ABC' hash test vectors */
const unsigned char testVector1[32] =
{ 0x02, 0x8f, 0xa2, 0xb4, 0x8b, 0x93, 0x4a, 0x18,
  0x62, 0xb8, 0x69, 0x10, 0x51, 0x3a, 0x47, 0x67,
  0x7c, 0x1c, 0x2d, 0x95, 0xec, 0x3e, 0x75, 0x70,
  0x78, 0x6f, 0x1c, 0x32, 0x8b, 0xbd, 0x4a, 0x47
};
/* Data 'spam' hash test vectors */
const unsigned char testVector2[32] =
{ 0xac, 0xbb, 0xa0, 0x81, 0x3f, 0x30, 0x0d, 0x3a,
  0x30, 0x41, 0x0d, 0x14, 0x65, 0x74, 0x21, 0xc1,
  0x5b, 0x55, 0xe3, 0xa1, 0x4e, 0x32, 0x36, 0xb0,
  0x39, 0x89, 0xe7, 0x97, 0xc7, 0xaf, 0x47, 0x89
};
/* Data 'arcfour' hash test vectors */
const unsigned char testVector3[32] =
{ 0xff, 0x8c, 0xf2, 0x68, 0x09, 0x4c, 0x87, 0xb9,
  0x5f, 0x74, 0xce, 0x6f, 0xee, 0x9d, 0x30, 0x03,
  0xa5, 0xf9, 0xfe, 0x69, 0x44, 0x65, 0x3c, 0xd5,
  0x0e, 0x66, 0xbf, 0x18, 0x9c, 0x63, 0xf6, 0x99
};

unsigned char digest[32]; /* Output buffer */
unsigned char hashLen = 32;

SpritzCipher sc;


void setup() {
  /* Initialize serial (4800 bps) and wait for port to open */
  Serial.begin(4800);
  while (!Serial) {
    ; /* Wait for serial port to connect. Needed for Leonardo only */
  }
}

void loop() {
  /* Data: ABC */
  Serial.println("hash('ABC'):");
  sc.hash(digest, hashLen, testData1, sizeof(testData1));
  for (unsigned int i = 0; i < sizeof(digest); i++) {
    if (digest[i] < 0x10) {
      Serial.write('0');
    }
    Serial.print(digest[i], HEX);
  }
  Serial.println();
  /* Check the output */
  for (size_t i = 0; i < sizeof(digest); i++) {
    /* If the output is wrong */
    if (digest[i] != testVector1[i]) {
      Serial.println("** WARNING: Output_1 != Test_Vector **");
    }
  }

  /* Data: spam */
  Serial.println("hash('spam'):");
  sc.hash(digest, hashLen, testData2, sizeof(testData2));
  for (unsigned int i = 0; i < sizeof(digest); i++) {
    if (digest[i] < 0x10) {
      Serial.write('0');
    }
    Serial.print(digest[i], HEX);
  }
  Serial.println();
  /* Check the output */
  for (size_t i = 0; i < sizeof(digest); i++) {
    /* If the output is wrong */
    if (digest[i] != testVector2[i]) {
      Serial.println("** WARNING: Output_2 != Test_Vector **");
    }
  }

  /* Data: arcfour */
  Serial.println("hash('arcfour'):");
  sc.hash(digest, hashLen, testData3, sizeof(testData3));
  for (unsigned int i = 0; i < sizeof(digest); i++) {
    if (digest[i] < 0x10) {
      Serial.write('0');
    }
    Serial.print(digest[i], HEX);
  }
  Serial.println();
  /* Check the output */
  for (size_t i = 0; i < sizeof(digest); i++) {
    /* If the output is wrong */
    if (digest[i] != testVector3[i]) {
      Serial.println("** WARNING: Output_3 != Test_Vector **");
    }
  }


  delay(5000); /* Wait 5s */
}
