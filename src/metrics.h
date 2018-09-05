// Copyright (c) 2016 The Zcash developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "uint256.h"

#include <atomic>
#include <mutex>
#include <string>

struct AtomicCounter {
    std::atomic<uint64_t> value;

    AtomicCounter() : value {0} { }

    void increment(){
        ++value;
    }

    void decrement(){
        --value;
    }

    int get() const {
        return value.load();
    }
};

class AtomicTimer {
private:
    std::mutex mtx;
    uint64_t threads;
    int64_t start_time;
    int64_t total_time;

public:
    AtomicTimer() : threads(0), start_time(0), total_time(0) {}

    /**
     * Starts timing on first call, and counts the number of calls.
     */
    void start();

    /**
     * Counts number of calls, and stops timing after it has been called as
     * many times as start().
     */
    void stop();

    bool running();

    uint64_t threadCount();

    double rate(const AtomicCounter& count);
};

extern AtomicCounter transactionsValidated;
extern AtomicCounter ehSolverRuns;
extern AtomicCounter solutionTargetChecks;
extern AtomicTimer miningTimer;

void TrackMinedBlock(uint256 hash);

void MarkStartTime();
double GetLocalSolPS();
int EstimateNetHeightInner(int height, int64_t tipmediantime,
                           int heightLastCheckpoint, int64_t timeLastCheckpoint,
                           int64_t genesisTime, int64_t targetSpacing);

void TriggerRefresh();

void ConnectMetricsScreen();
void ThreadShowMetricsScreen();

/**
 * bitcoin image: https://upload.wikimedia.org/wikipedia/commons/thumb/4/46/Bitcoin.svg/200px-Bitcoin.svg.png
 * License: CC BY-SA 3.0
 *
 * Rendering options:
 * Logo: img2txt -W 90 -H 20 -f utf8 -d none -g design.png >> design.ansi
 */
const std::string METRICS_ART =
" [0;37;5;47;107m .    ....  .  .                        [0m\n"
"[0;37;5;47;107m  :@[0;1;33;93;47m@[0;37;5;43;103m88[0;1;33;93;47mS[0;37;5;43;103m8[0;1;33;93;47m@8[0;1;37;97;47m;[0;37;5;47;107mS.   ::@[0;33;5;40;100m [0;30;5;40;100mS[0;1;30;90;47m;[0;37;5;47;107m.:. .8[0;1;37;97;47m:[0;37;5;47;107m8[0;1;37;97;47m [0;37;5;47;107m88[0;1;37;97;47mt[0;37;5;47;107m8[0;1;37;97;47m.[0;37;5;47;107m88:[0m\n"
"[0;37;5;47;107m.8[0;33;5;43;103m [0;33;5;41;101m [0;37;5;43;103m8[0;37;5;47;107m88888[0;37;5;43;103m8[0;1;31;91;5;43;103m88[0;37;5;43;103m8[0;37;5;47;107m8.:[0;33;5;40;100m.[0;1;30;90;40m@S[0;31;40m.[0;32;40m :[0;1;30;90;40m@X[0;1;30;90;47mX[0;37;5;47;107m [0;1;30;90;47m8[0;32;5;42;102m  [0;37;5;42;102m8[0;32;5;42;102m    [0;37;5;42;102m8[0;32;5;42;102m  ;[0;1;37;97;47m%[0m\n"
"[0;37;5;47;107mS[0;1;31;91;5;43;103m8[0;33;5;43;103m [0;1;33;93;5;41;101m8[0;1;31;91;5;43;103m8[0;37;5;43;103m8[0;37;5;47;107m.8[0;1;31;91;5;43;103m8[0;1;37;97;5;43;103m8[0;37;5;47;107m  [0;37;5;43;103m8[0;1;33;93;5;41;101m@[0;37;5;43;103m8[0;37;5;47;107mX.[0;1;37;97;47m;[0;1;30;90;47mt;t[0;30;5;40;100mS[0;34;40m.[0;31;40m.[0;30;5;40;100m@[0;37;5;47;107m8.[0;33;5;40;100m [0;32;5;42;102m          S[0;1;30;90;47m8[0m\n"
"[0;1;37;97;47m8[0;1;33;93;5;41;101m8[0;33;5;41;101m [0;37;5;43;103m8[0;1;31;91;5;43;103m8[0;37;5;47;107m8X8[0;1;37;97;5;43;103m8[0;37;5;47;107m888[0;1;33;93;5;41;101m8[0;1;31;91;5;43;103m88[0;37;5;47;107mX   [0;1;37;97;47m8[0;33;5;40;100m [0;31;40m:[0;34;40m;[0;37;5;40;100mX[0;37;5;47;107mX  8[0;32;5;42;102m%.       .[0;33;5;40;100m.[0;37;5;47;107m8[0m\n"
"[0;37;5;47;107m@[0;33;5;43;103m [0;37;5;43;103m8[0;1;33;93;5;41;101m8[0;1;37;97;47m:[0;37;5;47;107m@;[0;1;31;91;5;43;103m@[0;1;33;93;5;41;101m8[0;37;5;43;103m8[0;37;5;47;107mt:[0;1;37;97;5;43;103m8[0;1;33;93;5;41;101m8[0;1;33;93;47mX[0;37;5;47;107mX @[0;37;5;40;100mS[0;31;40mt[0;32;40m:[0;36;5;40;100m:[0;1;37;97;47mX[0;37;5;47;107mtt;:.;[0;1;30;90;47mX[0;32;5;42;102m :   .[0;33;5;42;102mX[0;1;37;97;47mX[0;37;5;47;107m;.[0m\n"
"[0;37;5;47;107m.[0;1;37;97;47m [0;1;33;93;5;41;101m8[0;37;5;43;103m8[0;37;5;47;107m8[0;1;33;93;5;47;107mX[0;37;5;47;107m%. :X8[0;1;33;93;5;41;101m8[0;1;31;91;5;43;103m8[0;37;5;47;107m8.X[0;31;5;40;100m@[0;31;40m:[0;34;40m.[0;31;40m.[0;1;30;90;40m@@@X[0;37;5;40;100mS[0;37;5;47;107m    t[0;33;5;40;100m.[0;32;5;42;102m .X[0;1;30;90;47m@[0;37;5;47;107m    [0m\n"
"[0;37;5;47;107m  8[0;37;5;43;103m8[0;1;33;93;5;41;101m8[0;1;37;97;5;43;103m8[0;37;5;43;103m8[0;37;5;47;107m8[0;1;37;97;5;43;103m8[0;1;33;93;5;41;101m@[0;1;31;91;5;43;103m88[0;37;5;47;107m88: @[0;37;5;40;100mS[0;33;5;40;100m  [0;31;40m;[0;32;40m.[0;30;5;40;100m@[0;33;5;40;100m  [0;1;30;90;47m:[0;37;5;47;107m .   t[0;1;37;97;47m [0;32;5;42;102m8[0;1;37;97;47m%[0;37;5;47;107m:  . [0m\n"
"[0;37;5;47;107m  ;  S8888; t      .[0;1;30;90;47m.S[0;1;37;97;47m8[0;37;5;47;107m        :. .     [0m";
