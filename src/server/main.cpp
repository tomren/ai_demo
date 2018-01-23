#include "frame/gamesvr.hpp"

int main(int argc, char **argv)
{
    int32_t ret = 0;

    printf("hello\n");
    MeatBall::GameServer gameSvr;

    printf("main()\n");

   ret = gameSvr.Init();
   if (0 != ret)
       return ret;

    return ret;
}
