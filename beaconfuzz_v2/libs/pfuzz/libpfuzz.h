/* Code generated by cmd/cgo; DO NOT EDIT. */

/* package command-line-arguments */


#line 1 "cgo-builtin-export-prolog"

#include <stddef.h> /* for ptrdiff_t below */

#ifndef GO_CGO_EXPORT_PROLOGUE_H
#define GO_CGO_EXPORT_PROLOGUE_H

#ifndef GO_CGO_GOSTRING_TYPEDEF
typedef struct { const char *p; ptrdiff_t n; } _GoString_;
#endif

#endif

/* Start of preamble from import "C" comments.  */




/* End of preamble from import "C" comments.  */


/* Start of boilerplate cgo prologue.  */
#line 1 "cgo-gcc-export-header-prolog"

#ifndef GO_CGO_PROLOGUE_H
#define GO_CGO_PROLOGUE_H

typedef signed char GoInt8;
typedef unsigned char GoUint8;
typedef short GoInt16;
typedef unsigned short GoUint16;
typedef int GoInt32;
typedef unsigned int GoUint32;
typedef long long GoInt64;
typedef unsigned long long GoUint64;
typedef GoInt64 GoInt;
typedef GoUint64 GoUint;
typedef __SIZE_TYPE__ GoUintptr;
typedef float GoFloat32;
typedef double GoFloat64;
typedef float _Complex GoComplex64;
typedef double _Complex GoComplex128;

/*
  static assertion to make sure the file is being used on architecture
  at least with matching size of GoInt.
*/
typedef char _check_for_64_bit_pointer_matching_GoInt[sizeof(void*)==64/8 ? 1:-1];

#ifndef GO_CGO_GOSTRING_TYPEDEF
typedef _GoString_ GoString;
#endif
typedef void *GoMap;
typedef void *GoChan;
typedef struct { void *t; void *v; } GoInterface;
typedef struct { void *data; GoInt len; GoInt cap; } GoSlice;

#endif

/* End of boilerplate cgo prologue.  */

#ifdef __cplusplus
extern "C" {
#endif


extern void PrysmMain(GoUint8 p0);

extern GoUint8 pfuzz_ssz_attestation(void* p0, GoInt p1);

extern GoUint8 pfuzz_ssz_attester_slashing(void* p0, GoInt p1);

extern GoUint8 pfuzz_ssz_block(void* p0, GoInt p1);

extern GoUint8 pfuzz_ssz_block_header(void* p0, GoInt p1);

extern GoUint8 pfuzz_ssz_deposit(void* p0, GoInt p1);

extern GoUint8 pfuzz_ssz_proposer_slashing(void* p0, GoInt p1);

extern GoUint8 pfuzz_ssz_voluntary_exit(void* p0, GoInt p1);

// BeaconFuzzAttestation implements libfuzzer and beacon fuzz interface.

extern GoUint8 pfuzz_attestation(void* p0, GoInt p1, void* p2, GoInt p3, void* p4, GoInt p5);

extern GoUint8 pfuzz_attester_slashing(void* p0, GoInt p1, void* p2, GoInt p3, void* p4, GoInt p5);

extern GoUint8 pfuzz_block(void* p0, GoInt p1, void* p2, GoInt p3, void* p4, GoInt p5);

extern GoUint8 pfuzz_block_header(void* p0, GoInt p1, void* p2, GoInt p3, void* p4, GoInt p5);

extern GoUint8 pfuzz_deposit(void* p0, GoInt p1, void* p2, GoInt p3, void* p4, GoInt p5);

extern GoUint8 pfuzz_proposer_slashing(void* p0, GoInt p1, void* p2, GoInt p3, void* p4, GoInt p5);

extern GoUint8 pfuzz_voluntary_exit(void* p0, GoInt p1, void* p2, GoInt p3, void* p4, GoInt p5);

#ifdef __cplusplus
}
#endif
