#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "base64.h"
#include "hmac.h"
#include "sha.h"

using namespace CryptoPP;

int getCode() {
    std::string shared_secret = "oMld9ZU0MbBpXzf8ReeASI4w+W8=";
    //std::string ret = base64_encode((const unsigned char*)shared_secret.data(), shared_secret.length());


    std::string ret;
    CryptoPP::StringSource(shared_secret, true,
        new CryptoPP::Base64Decoder(new CryptoPP::StringSink(ret)));

    //std::cout << shared_secret << std::endl;
    //std::cout << ret << std::endl;

    for (;;) {
        //ret = b64decode(ret.data(), ret.length());
        //std::cout << ret << std::endl;
        time_t ltime;
        time(&ltime);
        //ltime -= 9000*30;

        printf("%li : ", ltime);
        char ntc[sizeof(time_t)] = { 0 };
        uint32_t part = (ltime / 30);
        char* cpart = (char*)&part;

        for (int i = 3; i >= 0; i--)
            ntc[4 + i] = cpart[3 - i];

        CryptoPP::HMAC<CryptoPP::SHA1> hmac((byte*)ret.data(), ret.length());
        char res[HMAC<SHA1>::DIGESTSIZE] = { 0 };
        hmac.Update((byte*)ntc, 8);
        hmac.Final((byte*)res);
        //std::cout << res << std::endl;
        int start = res[19] & 0x0f;

        byte slice[4];

        for (int i = 0; i < 4; i++) {
            slice[3 - i] = res[start + i];
        }

        uint32_t* fullcodep = (uint32_t*)slice;
        uint32_t fullcode = *fullcodep;
        fullcode = fullcode & 0x7FFFFFFF;

        char chars[] = "23456789BCDFGHJKMNPQRTVWXY";

        char code[6] = { 0 };
        for (int i = 0; i < 5; i++) {
            code[i] = chars[fullcode % 26];
            fullcode /= 26;
        }

        //struct tm* timeinfo = gmtime(&ltime); /* Convert to UTC */
        //ltime = mktime(timeinfo); /* Store as unix timestamp */
        //printf("Current UTC time as unix timestamp: %li\n", ltime);
        std::cout << code << std::endl;
        std::cout.flush();
        Sleep(10000);
        //ltime += 30;
    }
    return 0;
}
