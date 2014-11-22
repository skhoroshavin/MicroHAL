
#pragma once

#define _CAT(a,b) a##b
#define CAT(a,b)  _CAT(a,b)

#define STATIC_ASSERT(pred,name) typedef char CAT(assertion_failed_##name##_,__LINE__)[2*(pred)-1]

#define ARRAY_SIZE(a) (sizeof(a)/sizeof((a)[0]))
