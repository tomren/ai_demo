#include <cstdint>

#define BEGIN_MEATBALL_NAMESPC namespace MeatBall {
#define END_MEATBALL_NAMESPC };

#define GET_FIELD(ptr, type, field) \
    ((type *) ((char *) (ptr) - ((char *) &((type *) 0)->field)))
    