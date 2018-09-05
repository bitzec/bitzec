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
 *
 */
const std::string METRICS_ART =
"            [0;5;37;47m....ttSXStt .... . @[0;1;37;47m@[0;5;37;47m8... ...::.. ::... [0m\n"
"            [0;5;37;47m %[0;1;33;47m8X[0;5;37;47m888SXX[0;5;37;43m8[0;1;33;47mS[0;1;37;47m8[0;5;37;47mt. [0;1;37;47m@[0;5;33;40m [0;5;37;40mX[0;5;33;40m%[0;34;40mS[0;5;33;40mX[0;5;36;40m  [0;1;30;47mX[0;5;37;47m X[0;1;30;47m8[0;1;32;47mS[0;1;37;47m   [0;1;32;47mX[0;1;36;47m%[0;1;33;47mS[0;1;37;47m  [0;5;37;42m8[0;5;37;47m8.[0m\n"
"            [0;5;37;47m;[0;5;37;43m8[0;1;37;47m.[0;5;37;43m8[0;5;37;47m8X t%t8[0;5;37;43m88[0;1;37;47m;[0;5;37;47m: [0;1;37;47m:[0;5;30;40m8888[0;34;40mS[0;5;30;40m@[0;1;30;40m8[0;5;33;40m [0;5;37;47m [0;1;37;47m:[0;5;36;42m [0;1;37;47m [0;5;1;36;42m@[0;5;1;37;43m8[0;5;1;36;42m8[0;5;1;32;43m8[0;5;1;32;46m8[0;5;37;43m8[0;5;1;36;42m8[0;5;37;43m8[0;5;1;36;42m8[0;1;37;47m [0;5;37;47m:[0m\n"
"            [0;1;37;47m8[0;5;37;43m88[0;5;37;47m8[0;5;1;31;43mX[0;5;37;47m;.[0;5;37;43m88[0;5;37;47m8;X[0;5;37;43m88[0;5;37;47m8:;%%:[0;1;30;47m.[0;1;30;40m88[0;5;32;40m%[0;5;37;47m@ [0;1;37;47mt[0;5;37;42m8[0;1;33;47mX[0;5;1;36;42m8[0;5;1;32;43m8[0;5;1;37;46m8[0;5;1;32;43m8[0;5;37;46m8[0;5;1;33;42m8[0;5;1;37;46m8[0;5;1;33;42m@[0;5;37;42m8[0;1;37;47m [0;5;37;47m;[0m\n"
"            [0;1;37;47m8[0;5;37;43m8[0;1;37;47m [0;5;1;31;43m@[0;5;37;47m8S:8[0;5;1;33;47m8[0;5;37;47m8:8[0;5;1;37;43m8[0;1;33;47mS[0;5;37;47m8; . [0;1;37;47mX[0;5;31;40mS[0;1;30;40m@8[0;1;37;47m:[0;5;37;47m  @[0;5;36;42m.[0;1;37;47m [0;5;1;33;42m8[0;5;1;37;46m8[0;5;1;33;42m8[0;5;37;46m8[0;5;1;32;43m8[0;5;37;46m8[0;5;1;32;43m8[0;5;1;37;46m8[0;5;1;33;42mS[0;5;37;47m8;[0m\n"
"            [0;1;37;47m@[0;5;37;43m8[0;5;1;33;47m8[0;1;33;47m%[0;5;1;37;43m8[0;5;37;47m.@[0;5;1;37;43m8[0;5;37;47m8@ [0;5;1;33;47m@[0;5;37;41m8[0;5;1;37;43m8[0;5;37;47m8%. [0;1;30;47mt[0;1;30;40m8X[0;5;36;40mS[0;1;37;47m@[0;5;37;47m .  X[0;5;37;42m8[0;5;37;46m8[0;5;1;33;42m8[0;5;37;46m8[0;5;1;32;43m8[0;5;1;37;46m8[0;5;1;33;42m8[0;5;1;32;46m8[0;5;1;33;42m8[0;1;37;47m8[0;5;37;47m:.[0m\n"
"            [0;5;37;47m8[0;1;33;47m@S[0;5;37;47m88%8[0;5;1;37;43m8[0;5;1;33;47m8[0;5;37;47m8S%[0;5;1;37;43m8[0;5;37;43m8[0;5;37;47m8;;[0;1;30;47mX[0;5;31;40m8[0;1;30;40mX[0;5;36;40m:[0;1;37;47mt[0;5;37;47m%%t   X[0;1;33;47m8[0;5;1;36;42mX[0;5;37;43m8[0;5;1;36;42m8[0;5;1;32;43m8[0;5;37;46m8[0;5;37;43m8[0;1;37;47m8[0;5;37;47m   [0m\n"
"            [0;5;37;47m%[0;1;33;47m%[0;5;37;43m8[0;5;37;47m8%:t;X%.8[0;5;37;43m8[0;5;1;35;47m8[0;5;37;47mX.[0;1;37;47m.[0;1;30;41mX[0;1;30;40m@@[0;5;30;40m8[0;5;31;40m@[0;5;30;40mX8[0;5;33;40m;[0;5;37;47mX ...[0;1;32;47m@[0;5;1;36;42mX[0;1;37;47m [0;5;1;33;42m@[0;5;37;42m8[0;5;37;47m% . .[0m\n"
"            [0;5;37;47m.88[0;5;1;31;43m@[0;5;37;47m8%8@8[0;5;1;33;47m@8[0;5;37;43m8[0;5;37;47m88; [0;1;30;47m8[0;31;40m@[0;5;30;40m8[0;1;30;40m8@88X[0;5;30;40m8[0;5;37;47mt .  %[0;1;33;47mX[0;5;1;36;42mS[0;1;36;47mS[0;5;37;47m8t .  [0m\n"
"            [0;5;37;47m ;X8[0;5;1;37;43m@88[0;5;37;47m8[0;5;37;43m8[0;5;1;37;43m8[0;1;37;47m [0;5;37;47m88% :XSX[0;5;37;40mS[0;32;40m;[0;5;36;40m:[0;5;37;47m8@X.  .. ;[0;33;47m@[0;5;37;47m8%.  . [0m\n"
"            [0;5;37;47m ..t::@8St@S; . .. [0;1;37;47mX[0;1;30;47m:[0;1;37;47m;[0;5;37;47m. .  .  . t;. ..  [0m";
