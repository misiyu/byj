//
// Created by mingj on 18-12-18.
//
#include "./helper/NDNHelper.h"
#include "./helper/JSONCPPHelper.h"
#include "./helper/LibPcapHelper.h"

using namespace std;

void dealNDN1(void *arg) {
    auto *ndnHelper = (NDNHelper *) arg;
    //cout<<"dealNDN1 success"<<endl;
    ndnHelper->start1();
}

void dealNDN2(void *arg) {
    auto *ndnHelper = (NDNHelper *) arg;
    //cout<<"dealNDN2 success"<<endl;
    ndnHelper->start2();
}

void process(void *arg) {
    auto *ndnHelper = (NDNHelper *) arg;
    //cout<<"dealNDN2 success"<<endl;
    ndnHelper->process();
}

int main(int argc, char *argv[]) {

    NDNHelper ndnHelper;
    CacheHelper cacheHelper;
    LibPcapHelper libPcapHelper;

    ndnHelper.bindCacheHelper(&cacheHelper);
    libPcapHelper.bindCacheHelper(&cacheHelper);
    libPcapHelper.bindNDNHelper(&ndnHelper);


    ndnHelper.initNDN(argv[1]);

    boost::thread t(bind(&dealNDN1, &ndnHelper));
    boost::thread y(bind(&dealNDN2, &ndnHelper));
    boost::thread u(bind(&process, &ndnHelper));

    libPcapHelper.initLibPcap(argv[1]);

    t.join();
    y.join();
    u.join();
    libPcapHelper.join();
    ndnHelper.join();
    libPcapHelper.close();


    return 0;
}

