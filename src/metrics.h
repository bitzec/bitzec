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
* Bitcoin image: https://upload.wikimedia.org/wikipedia/commons/thumb/4/46/Bitcoin.svg/2000px-Bitcoin.svg.png
* License:
*
* Rendering options:
* Zcash: img2txt -W 40 -H 20 -f utf8 -d none -g 0.7 Z-yellow.orange-logo.png
* Bitcoin: img2txt -W 40 -H 20 -f utf8 -d none 2000px-Bitcoin.svg.png
 */
const std::string METRICS_ART =
NNNNNNNNNNNNNNhds++++o++o+oooo//+sdmm/:-/:/-.:+/:/:/syy+yyo/s+/://:syshms//::+++//+o+sdmNNNNNNNNmmNN
NNNNNNNMMMMNNNhho//o+oo/++++/oo///yyo/ooossyhdddddmNNNNNNmmmmdyoo+/hNNh/+:/::-+/----/sydmNNNNNNNmmmm
NNNNNNNNMMNNNNy++++++s+///++o+:/osyhdNNNNNNNNmmmNNNNNNNNNNNMMMMMMMmdho/::y+//--:++--::/yNNNmhhdhmdyy
NmNNNNNmdNNNNNdhs++++s++osy+syhmMMNNNNNNNNNNhsdmNNNNNNNNNNNNNNNNNNNNNNMNddo:-:/:-.---:+shmNNdydhsh+.
mNNmmyohNmmNNmyhyo+//s//+sdmNMNNNNNNNNNNNNNMMMMMMMNNNNNNNNNNNNmNmmNNNNNNNNMNNyo:---/osymNmNMmyo://--
NNNNNmymNmdmdysoooso++odNNNNNNNNNNNNNNNMm/s+o+MMMMdyhhsdMMMMNNNmmNNNNNNNNNNNNMMNmh+-`.`-ddNNds+o/:::
NNNNdhoshydhhss+++/+smNNNNNNNNNNNNNNNNMMN://-:MMMMyshhymMMMMMMMNNNNNNNNNNNNNNNMMMMMmy/-:/osoo/+o////
NNmmmNmdhyysysoo//ymNNNNNNNNNNNNNNNNNNNNm:-:.:NNNMhshhyNMMNMMMMMNNNNNNNNNNNNNNNNMMMMMmh+/+/os+o::::/
mmNNmmmhsyoyysoosmNNNNNNNNNMMh+++/sso++/oo//::+//syhhss++/-+soomNMNNNNNNNNNNNMMMNMMMMMMNdo+ss:+hds--
mmmdmdhssssys+ohNNNNNNNNNMNMMs/+ooo++/+oys++o/-:/ssys+o+/------../smNNNNNNNNNNNNMMMMMMMMNmyyy/ssmhh.
oo++/o+++sosoyhNNNNMNNNNNNNNNMMMMMMMddMmss++//hddddhhhhho--:.`...:./+mNNNNNNNNNNNNMMMMMMMNydsso+++//
soo////+++osohNNMMMMNNNNNMNNNNNMMMMMhyyydyoo/oMMMMMMMMMMMNo.```.-/-y:.NNNNNNNNNNNNNNNNMNMMdyhysooooo
sss+//////++oNNMMMMNMMNNNNNNNNNMMMMMysNyhsso+oNMMMMMNNMMMMh````:/:-yo:mNNNNNNNNNNNNMMMMMMMN+ydhysssh
+o+:::://ooyNMMMMMMMMMNMMNNMMNNNMMMMsyhsyysoo+mNNNNNNNNNmo-`-.```-.syNMNNNNNNNNNNNNMMMMMMMNyydyhyhdd
/+/+/::+/++dMMMMNMNMMNMMNMNNNMMNMMMMsss/+ysoo/o/o+sydhhyy-:--```.:sdNMMMMMNNNNNMMMNNNNMMNNNhhddy::+y
o+oo+//oossNMMNhyNMMMMMMMMMMMMMNMMMMy+s/:+:///+/ooydmddhy/-.-....---:/dMMMMNNNMMMMNMMNMMNNNyhdy+:/-o
+oso/++++//sMNhNsmMMMMMMMMNNNNMNMMMMy/+oo+/-::dMMMMMMMMMMNmho/:-.---:.:/mMMMNMMMMMNMMNMMMMNsho:/-:./
hyysooys+ooomsyNdMMNMMMMMMNNNNNNMMMMhs/:.//:/:hMMMMMMMMMMNMMMd------/-:/oMMMNNNNNMNMMMMMMMds/--:./--
mmdyyydNsssoyhmMMNNMMMMMMNNNNNNNMMMMmdyso/+//+yMMMMMMMMMMMMMMh..`.--:.-+oMMMNNNNNNNNMMMMMNyyo++///:-
hNNmhyhsysssyhddmhmMMMMMNNNNdhdNNNNMdhmNdoo+::hMMMMMMMMMMNdd+-.-.---:`-/mNMMMMNNNNNNMMMMNhsssyyyyo+:
mNNNhyyhmdhdddmNNNNNNNMNNNNMNmosyhysshdNds/o+./+o+shyosso/:--`...`.:/-oNMMNNNNNNNNNMMMMmhyoosyoo++:-
NNmhhyshdNNNNNNmmmhNNNNNNNMMMMooos++shdyd+oho--:/++s+osos+/::+yooohydNmNMMNNNNNNNNNMMNy:-:-++syyyyyy
NNmmmdmmdNNMNNNmddmNNNNNNNNMMMmdNNNNNNMNMm+ys/hmdmhossysNNNNNNNMMMNdNNmNNNNNNNNNNMMmy/--:/sdssyhyyhd
MMNmddmNNNNMMNmhdhdyhdNNNNNNMMmNNMMMMMMMMNhhsomMMMhsosssNNNNNNNmhdNh++smmmmmNNNMMmysoohhhhhdyhddddhh
MMNmmmmmmNNNNNmdhyy+oosmMMMMMMMMMMMMMMMMMm++ysmMMMy+ooyyMMNmmmhmhsoyhdmmmdNNMMNyoosshddddddhyydmmdhy
MMMNdmmdhmmNNmmdhhyoosoodMMMMMMMMMMMMMMMMMMMMMMMMNNmMMMMMNNmNms:+dddddmmdmmmho///:ooyddddhmddmmmmmmm
MMMMNNddhhhmmddmddhyyso++ohmmNMMMMMMMMMMMMMMMMMMMMMMMMMMNNNmdssohdhhdddddyyo+/////+/+syyhhdmmmNmmmNN
MMMNNMNmmdmdmmdmmmdddyyo+osyyyyyddNNMMMMMMMMMMMMMMMMMMMMMNNNmddmmmmhyhyssshs/:/++os++ohhhyhdmNNNNNNN
MMMMMMMNNNmmmmdhdddddyhyysssyhyoyssoyyhdmNNNMMMMMMMMMMMMMNmmddhyhddhsssssoo+//ooysso++hhhmmmmmNNNNNN
MMMMMMMMMMMNddyyhmmmmdyssssosssyssssyyydsyhhyyyyssohdmdddhdy+syNmshsssyhhso+o+/yyssyhdmhhmmmmNNNNNNN
";
