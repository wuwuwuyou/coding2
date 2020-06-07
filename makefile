ALL:encoder decoder 
encoder: encoder.c fun.h timing.h LU3.h LU4.h
	g++ -o encoder encoder.c
decoder: decoder.c fun.h timing.h LU3.h LU4.h
	g++ -o decoder encoder.c
