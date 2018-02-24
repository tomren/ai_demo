#include <stdio.h>
#include <inttypes.h>
#include "frame/game_server.hpp"
#include "msgpack.h"

void test()
{
    /* msgpack::sbuffer is a simple buffer implementation. */
    msgpack_sbuffer sbuf;
    msgpack_sbuffer_init(&sbuf);

    /* serialize values into the buffer using msgpack_sbuffer_write callback function. */
    msgpack_packer pk;
    msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

    msgpack_pack_array(&pk, 3);
    msgpack_pack_int(&pk, 123456);
    msgpack_pack_true(&pk);
    msgpack_pack_str(&pk, 7);
    msgpack_pack_str_body(&pk, "example", 7);

    /* deserialize the buffer into msgpack_object instance. */
    /* deserialized object is valid during the msgpack_zone instance alive. */
    msgpack_unpacked upk;
    msgpack_unpacked_init(&upk);

    //msgpack_zone mempool;
    //msgpack_zone_init(&mempool, 2048);

    //msgpack_object deserialized;
    //msgpack_unpack(sbuf.data, sbuf.size, NULL, &mempool, &deserialized);

    if (msgpack_unpack_next(&upk, sbuf.data, sbuf.size, NULL))
    {
        msgpack_object obj = upk.data;
        if (obj.type == MSGPACK_OBJECT_ARRAY)
        {
            printf("%u\n", obj.via.array.size);
            printf("%" PRId64 "\n", obj.via.array.ptr[0].via.i64);
            printf("%d\n", (int32_t)obj.via.array.ptr[1].via.boolean);
            char buff[32];
            memcpy(buff, obj.via.array.ptr[2].via.str.ptr, obj.via.array.ptr[2].via.str.size);
            buff[obj.via.array.ptr[2].via.str.size] = '\0';
            printf("%s\n", buff);
        }
    }

    /* print the deserialized object. */
    //msgpack_object_print(stdout, deserialized);
    //puts("");

    //msgpack_zone_destroy(&mempool);
    msgpack_sbuffer_destroy(&sbuf);
}

int main(int argc, char **argv)
{
    int32_t ret = 0;

    MeatBall::GameServer gameSvr;

    test();

    ret = gameSvr.Init();
    if (0 != ret)
        return ret;

    return ret;
}
