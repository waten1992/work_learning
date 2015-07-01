#if !defined(__HEADERS_H__FAST_)
#define __HEADERS_H__FAST_

//libc libstdc++ headers
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <strings.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <errno.h>
#include <assert.h>
#include <stdarg.h>
//mFAST  from GitHub
#include <mfast/mfast.h>
#include <mfast/mfast/coder/mfast_coder_export.h>
#include <mfast/mfast/coder/fast_encoder.h>
#include <mfast/mfast/coder/fast_decoder.h>
#include <mfast/mfast/coder/fast_decoder_v2.h>
#include <mfast/mfast/coder/fast_encoder_v2.h>

#include <zmq/zmq.h>
#include <zmq/zmq_utils.h>

#include "../bridge.h"


//  MACROS
#define FAILURE (-1)
#define ARRAY_SIZE(a)   (sizeof(a)/sizeof(a[0]))

extern int debug_output;

#endif
