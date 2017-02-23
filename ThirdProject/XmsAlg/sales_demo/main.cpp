#include "imp_algopc.h"
int main(int argc, char *argv[])
{
    IMP_AlgoPC ap;
    ap.setIPAddressPort("192.168.0.1",3334,3335);
    ap.start();
    ap.wait();
    return 0;
}
