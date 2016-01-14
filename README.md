# Spritz Library for Arduino

Spritz - a spongy RC4-like stream cipher and hash function.

This library contains cryptographic pseudo-random number generator,
Cryptographic hash function, Message Authentication Code (MAC) function,
Data encryption/decryption using Key and Nonce/Salt/IV, General purpose
functions such as timing-safe comparison and data wiping from memory.

This C Spritz library can be used to:
  - Hash data
  - Data encryption
  - Authenticated encryption
  - Generate random numbers from entropy/seed

**Spritz paper:** https://people.csail.mit.edu/rivest/pubs/RS14.pdf

**GitHub repository:** https://github.com/abderraouf-adjal/ArduinoSpritzCipher


## Library Content

See the source code and header files for the details.

### Constants
**SPRITZ_TIMING_SAFE_CRUSH**

If defined, equal time **crush()** will be used.  Defined by default.

**SPRITZ_WIPE_TRACES**

If defined, sensitive data like ```spritz_ctx``` will be wiped when they are 
no longer needed in the functions:
   * spritz_hash
   * spritz_mac
   * spritz_hash_final
   * spritz_mac_final
   
  Defined by default.

**SPRITZ_WIPE_TRACES_PARANOID**

If defined, any variable will be wiped if it contains a bit or more of 
spritz state such as temporary variables in a swap function or user data. 
Internal variables that contain data length will not be wiped. If 
defined, ```SPRITZ_WIPE_TRACES``` and ```SPRITZ_TIMING_SAFE_CRUSH``` will 
be defined automatically. Defined by default.

**SPRITZ_N 256**

Present the value of N in this spritz implementation.

**SPRITZ_LIBRARY_VERSION_STRING "0.5.1"**

Present the version of this spritz library (MAJOR . MINOR . PATCH)
using [Semantic Versioning](semver.org).

**SPRITZ_LIBRARY_VERSION_MAJOR 0**

The MAJOR version of the library.

**SPRITZ_LIBRARY_VERSION_MINOR 5**

The MINOR version of the library.

**SPRITZ_LIBRARY_VERSION_PATCH 1**

The PATCH version of the library.

### Types

**spritz_ctx** - The context/ctx (contain the state). The state consists of byte registers
                 {i, j, k, z, w, a}, And an array {s} containing a permutation
                 of {0, 1, ... , SPRITZ_N-1}.

**uint8_t** - unsigned integer type with width of 8-bit, MAX=255.

**uint16_t** - unsigned integer type with width of 16-bit, MAX=65,535.

**uint32_t** - unsigned integer type with width of 32-bit, MAX=4,294,967,295.


### Functions
  * **uint8_t spritz_compare(const uint8_t \*data_a, const uint8_t \*data_b, uint16_t len)**

    Timing-safe comparison for ```data_a``` and ```data_b``` equality.
    This function compares passwords hash safely.
    Return zero (0x00) if ```data_a``` equals ```data_b``` or ```len``` is zero,
    non-zero value if they are not equal.

  * **void spritz_memzero(uint8_t \*buf, uint16_t len)**

    Wipe ```buf``` data by replacing it with ```len``` zeros (0x00).
  
  * **void spritz_ctx_memzero(spritz_ctx \*ctx)**

    Wipe ```spritz_ctx``` data by replacing its data with zeros (0x00).
    If ```SPRITZ_WIPE_TRACES_PARANOID``` is defined, This function will
    wipe the "sensitive" temporary variables in ```spritz_ctx```.

  * **void spritz_setup(spritz_ctx \*ctx, const uint8_t \*key, uint8_t keyLen)**

    Setup spritz state ```spritz_ctx``` with a ```key``` of length ```keyLen```.

  * **void spritz_setupWithIV(spritz_ctx \*ctx,
                        const uint8_t \*key, uint8_t keyLen,
                        const uint8_t \*nonce, uint8_t nonceLen)**

    Setup spritz state ```spritz_ctx``` with a ```key``` and ```nonce```/Salt/IV.

  * **uint8_t spritz_random_byte(spritz_ctx \*ctx)**

    Generates a random byte of keystream from spritz state ```spritz_ctx```.
    spritz_random_byte() usable after spritz_setup() or spritz_setupWithIV().

  * **uint32_t spritz_random_u32(spritz_ctx \*ctx)**

    Generates a random 32-bit (4 bytes) of keystream from spritz state ```spritz_ctx```.
    spritz_random_u32() usable after spritz_setup() or spritz_setupWithIV().

  * **uint32_t spritz_random_uniform(spritz_ctx \*ctx, uint32_t upper_bound)**
    
    Calculate a uniformly distributed random number less than ```upper_bound```
    avoiding "modulo bias".
    Uniformity is achieved by generating new random numbers until the one
    returned is outside the range [0, 2\*\*32 % ```upper_bound```).
    This guarantees the selected random number will be inside
    [2\*\*32 % ```upper_bound```, 2\*\*32) which maps back to [0, ```upper_bound```)
    after reduction modulo ```upper_bound```.
    So use "spritz_random_uniform(ctx, m)", Not "spritz_random_u32(ctx) % m".
    spritz_random_uniform() usable after spritz_setup() or spritz_setupWithIV().

  * **void spritz_add_entropy(spritz_ctx \*ctx,
                        const uint8_t \*entropy, uint16_t len)**
    
    Add ```entropy``` to spritz state ```spritz_ctx``` using absorb().
    spritz_add_entropy() usable after spritz_setup() or spritz_setupWithIV().

  * **void spritz_crypt(spritz_ctx \*ctx,
                  const uint8_t \*data, uint16_t dataLen,
                  uint8_t \*dataOut)**
    
    Encrypt or decrypt ```data``` chunk by XOR-ing it with spritz keystream.
    spritz_crypt() usable after spritz_setup() or spritz_setupWithIV().

  * **void spritz_hash(uint8_t \*digest, uint8_t digestLen,
                 const uint8_t \*data, uint16_t dataLen)**
  
    Spritz cryptographic hash function.

  * **void spritz_mac(uint8_t \*digest, uint8_t digestLen,
                const uint8_t \*msg, uint16_t msgLen,
                const uint8_t \*key, uint16_t keyLen)**

    Spritz Message Authentication Code (MAC) function.

  * **void spritz_hash_setup(spritz_ctx \*hash_ctx)**
  
    Setup spritz hash state.

  * **void spritz_hash_update(spritz_ctx \*hash_ctx,
                        const uint8_t \*data, uint16_t dataLen)**
  
    Add ```data``` chunk to hash.

  * **void spritz_hash_final(spritz_ctx \*hash_ctx,
                       uint8_t \*digest, uint8_t digestLen)**
  
    Output hash digest.

  * **void spritz_mac_setup(spritz_ctx \*mac_ctx,
                      const uint8_t \*key, uint16_t keyLen)**
  
    Setup spritz MAC state.

  * **void spritz_mac_update(spritz_ctx \*mac_ctx,
                       const uint8_t \*msg, uint16_t msgLen)**
  
    Add message/data chunk to MAC.

  * **void spritz_mac_final(spritz_ctx \*mac_ctx,
                      uint8_t \*digest, uint8_t digestLen)**
  
    Output MAC digest.


## Examples

* [Hash 32 KB of Spritz stream](examples/SpritzBestPractice/SpritzBestPractice.ino) 
  (pseudo-random number generator output) then print the result.
  This code show what can ArduinoSpritzCipher library do (ShowOff API).
  An embedded entropy/seed for the pseudo-random number generator is used.

* [Make strong Alphanumeric passwords then print it](examples/SpritzBestPracticePassword/SpritzBestPracticePassword.ino).
  This code show what can ArduinoSpritzCipher library do (ShowOff API).
  An embedded entropy/seed for the pseudo-random number generator is used.

* [Test the library encryption/decryption function](examples/SpritzCryptTest/SpritzCryptTest.ino)

* [Generate random bytes (Spritz stream) test](examples/SpritzStreamTest/SpritzStreamTest.ino)

* [Hash test](examples/SpritzHashTest/SpritzHashTest.ino)

* [MAC test](examples/SpritzMACTest/SpritzMACTest.ino)


## Installation Guide

https://www.arduino.cc/en/Guide/Libraries

Compiling this library with GCC or Clang will guarantee zero optimization
for functions that should be compiled with zero optimization.


## Reporting bugs

[Create an issue on GitHub](https://github.com/abderraouf-adjal/ArduinoSpritzCipher/issues)


## Copyright

Copyright (c) 2015-2016 Abderraouf Adjal

## License

The MIT License.