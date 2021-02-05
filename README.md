# SPUF2
Implementation of so called Strong PUF. Second design


### Notes on design 
* Architecture consists of 3 stages: 
* First 2 stages consist of 5 unique different secret Sboxes, with 5bits in, 5 bits out, 
3th stage has 5 Sboxes with 5bits in, 1 bit out
* Each SBOX is unique and completely random  (assume so)
* Phase 1: Input is 25 bits of challenge (plaintext)
* Phase 2: 3 rounds, every round 25 new plaintext bits are added
* Total input challenge is 100 bits
* Output is 1 bit
* Paper claims that 20M plaintext/ciphertext pairs in combination with machine learning are not sufficient to predict better than 50%.


![alt text](https://github.com/mahzoun/SPUF2/blob/master/media/design.png)
### Run

```
x@y:~/SPUF1$ cmake . #code directory
x@y:~/SPUF1$ make
x@y:~/SPUF1$ ./SPUF1
```

### Notes on the Implementation
See `main.cpp` for an example. Each step of the authentication process is also available publicly. 

### Usage
```
Puf puf; // Initialize the circuits with fresh randomness
```

### Resources
Unpublished. 

