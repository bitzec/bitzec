// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "key_io.h"
#include "main.h"
#include "crypto/equihash.h"

#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "chainparamsseeds.h"

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, const uint256& nNonce, const std::vector<unsigned char>& nSolution, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    // To create a genesis block for a new chain which is Overwintered:
    //   txNew.nVersion = OVERWINTER_TX_VERSION
    //   txNew.fOverwintered = true
    //   txNew.nVersionGroupId = OVERWINTER_VERSION_GROUP_ID
    //   txNew.nExpiryHeight = <default value>
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 520617983 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nSolution = nSolution;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = genesis.BuildMerkleTree();
    return genesis;
}


 /* Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database (and is in any case of zero value).
 */

 /**
 *  >>> from hashlib import blake2s
 *  >>> Bitzec ("the binary digit zero knowledge electronic currency')
 *
 * CBlock(hash=00040fe8, ver=4, hashPrevBlock=00000000000000, hashMerkleRoot=c4eaa5, nTime=1536721921, nBits=1f07ffff, nNonce=4695, vtx=1)
 *   CTransaction(hash=c4eaa5, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff071f0104455a6361736830623963346565663862376363343137656535303031653335303039383462366665613335363833613763616331343161303433633432303634383335643334)
 *     CTxOut(nValue=0.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: c4eaa5
 */

static CBlock CreateGenesisBlock(uint32_t nTime, const uint256& nNonce, const std::vector<unsigned char>& nSolution, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp ="Bitzec" ;
    const CScript genesisOutputScript = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nSolution, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

const arith_uint256 maxUint = UintToArith256(uint256S("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"));

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        strCurrencyUnits = "BZC";
        bip44CoinType = 133; // As registered in https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        consensus.fCoinbaseMustBeProtected = true;
        consensus.nSubsidySlowStartInterval = 5000;
        consensus.nSubsidyHalvingInterval = 2628000;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 4000;
        consensus.powLimit = uint256S("0007ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowAveragingWindow = 17;
        assert(maxUint/UintToArith256(consensus.powLimit) >= consensus.nPowAveragingWindow);
        consensus.nPowMaxAdjustDown = 32; // 32% adjustment down
        consensus.nPowMaxAdjustUp = 16; // 16% adjustment up
        consensus.nPowTargetSpacing = 2.5 * 60;
        //consensus.vUpgrades[Consensus::BASE_SPROUT].nProtocolVersion = 1;
        //consensus.vUpgrades[Consensus::BASE_SPROUT].nActivationHeight =
            Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        //consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nProtocolVersion = 1;
        //consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
            Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        //consensus.vUpgrades[Consensus::UPGRADE_OVERWINTER].nProtocolVersion = 1;
        //consensus.vUpgrades[Consensus::UPGRADE_OVERWINTER].nActivationHeight = 1;
        //consensus.vUpgrades[Consensus::UPGRADE_SAPLING].nProtocolVersion = 1;
        //consensus.vUpgrades[Consensus::UPGRADE_SAPLING].nActivationHeight = 0;

        consensus.fPowNoRetargeting=false;
        consensus.nLWMAHeight=10000;
        consensus.nPowLwmaTargetSpacing = 1 * 60;
        consensus.nZawyLwmaAveragingWindow = 75;
        consensus.nZawyLwmaAdjustedWeight = 2280;
        consensus.nZawyLwmaMinDenominator = 10;
        consensus.fZawyLwmaSolvetimeLimitation = true;
        consensus.ZCnPowTargetSpacing = 2.5 * 60; //legacy spacing.

	// The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00000000000000000000000000000000000000000000000000281b32ff3198a1");

        /**
         * The message start string should be awesome! Bⓩ❤
         */
        pchMessageStart[0] = 0x21;
        pchMessageStart[1] = 0xe8;
        pchMessageStart[2] = 0x27;
        pchMessageStart[3] = 0x61;
        vAlertPubKey = ParseHex("04b7ecf0baa90495ceb4e4090f6b2fd37eec1e9c85fac68a487f3ce11589692e4a317479316ee814e066638e1db54e37a10689b70286e6315b1087b6615d179264");
        nDefaultPort = 8733;
        nPruneAfterHeight = 100000;
        newTimeRule = 25000;
        eh_epoch_1 = eh200_9;
        eh_epoch_2 = eh144_5;
        eh_epoch_1_endblock = 25000;
        eh_epoch_2_startblock = 25000;

        genesis = CreateGenesisBlock(
            1536721921,
            uint256S("0x0000000000000000000000000000000000000000000000000000000000000c94"),
            ParseHex("00e92dbc6a43824326a1919ebc43d4b09be655a9342239dd0f79d0d74dfd63c3066d6d840d46543ed84c2fbde79e190d216c8b0078b50d6923f6c876b70e3350dd04f3ddf1eb6df9c50613333596c6dae9ff7003034ca2415dc439899318683a8e7013c330d11f20db40f4d67d3a9499d31510a4976369f94e60f6133a3a128edc99ed9c6db9caa9c44996dd5e6da5bebc2fc01d575fd6e68a588db3eeb36c89efee810e7c898120014b83e2a5c33a9bc184e3a275a231fa36343acd1a3722a36f85d894dd4e81b8445fd4e47a363e522d1e0293b1daa90c5c5dc022a08ec33d7ca8ef34686e3506d966eb51d160257041c14661e700e954cbf380331742ea45f85ae6db16e516d26decb00dc6c58eafd52795628704145d0d793a560961c0260618195ba6042cfe01e521a79b3b74ff3549b0596c4a34723242262da97b27c01505a1c7bed8c35b467e6384a2bd79e8072f245fea5ed1fd7e5d030b5db9ba25a8e77d08310c31b75aa7c358f504c335c2416b6a8e80affe8f7e091691a0b4030741c67054e723ec91396af011a7a727f3a619b0a565cf5822f33456537238e96b4e8b0323a9c4f9c614a0a0c1cc13b02e363e2547b15d9594284c341c45537ea9068028a979d4cd4311e859c06125aced9ab4eeee4b825fa27696d61c85ba7f5e9c6a2cfb6cf0d5e339dd26cdb63187bca2fe0be97c979b08568941aa5bbe3d00fc57f8a76cf25e5a293b47cd146cea1da5136c05d8cd2957cf5a1fb682e91927491531c4b4f70eed3ad8a453381043580b321abf1999189e2e5aae4c624deb5802e4eb52e5d54a54583b83144d4ce46b08c51cd08f7178bfcc6a3d98b17eb00e284cdbf99d357b55b65412c2fbf6d8fccdc6f04bb219e57389dd2d52857e8e4277c8d5b312c93b5f492020330c002bd3e56d7cb3d4abe6ac7ea13f1e5f87ed02043cecc9adaa1576486475956b72225c3dd346c417c390e138cf51dcc2c5d5496166da874130fac28b0c8e169da2162bb9c928f307709ab29a7fe31dfd1a228862b6e3d358453bf74cbeae76d8cfaa76df5a0703e735dac3c85c1263685043db272fcc9727b35901059ca7c8cf81dbef8e2fd067f4dce2964ca4bb53bc0a8706235d570be3f709e15bc6da4cb0ae1cf5751e1f2074daf6a67b71b2fa345a1c41bcbd7e22d3d14c03ca2a26fb0d67b6760ba49e274cbec52b3d335a0e1eb6f789cf5bba953672036f3b639f9654703cd7640839a2aa49c396dea8a0452e503461155dc959ff8f15bcc8e31b8bda6ab7c0f3395c724160daecd3a8142a8cf9aea79b5ad9d0c9f8280758514e75c7347710350689f3a5d3de22bd09f458d5dd905e7fc2b63b192f1b8f74c61c76899345d56ff7afb29624f47ad78546b62720ab2119ddbad0b767b05fe503a627dde2a80237c07e5565c1333cf082044896fb3efdcc7f306e14c4f7c2219014d74e6cf1dba6479e2623829166e3078a3636bcd7cbc7fcb633c5d8d8f0f9f58bd7d01020c172080d5bbe13b8e952545be7c3dcc6215617900ac922041246522fc8ef07a00dd4a5cb38f73fcef61f4d172577988f8be05364b7e3dcdd42e9627d401611e3f09b1ee7f1e3efa28330ac29938557a45e9785135fcf1e15e97ff9d7b6762c2fd6cb9e8ce99abf00092322f89f6b9123c9701a017af47573f7081fe6a327a6577f5d541d98cc0ee407d538f1597532d12efc10db27d871317d7fbab2e22a3ddb632dc9a71fbea012e2a5db298f8b24ab6d44528e44190db33ab9526b0d0fb2d8e4c9527258db51774f7c9a58aea153ba7b127963e57b483985912f43928efc9f090959989ef818fe58dc308ae5f9141056d9f5d35f720cb015102f21928b948b5c4dd139f642398c55eb089c791438a0"),
            0x1f07ffff, 4, 0);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00027f370c78f3866b3f90794c4daf6770fa62a6e1cd93ea4f160bcb3e7cc88c"));
        assert(genesis.hashMerkleRoot == uint256S("0x51d02c5b0782c1166d49ae4293d3461f2923ce5fecdcb3f7c5d1f47618479bfd"));

        vFixedSeeds.clear();
        vSeeds.clear();
        //vSeeds.push_back(CDNSSeedData("z.cash", "dnsseed.z.cash")); // Zcash
        //vSeeds.push_back(CDNSSeedData("str4d.xyz", "dnsseed.str4d.xyz")); // @str4d
        //vSeeds.push_back(CDNSSeedData("znodes.org", "dnsseed.znodes.org")); // @bitcartel

        // guarantees the first 2 characters, when base58 encoded, are "t1"
        base58Prefixes[PUBKEY_ADDRESS]     = {0x1C,0xB8};
        // guarantees the first 2 characters, when base58 encoded, are "t3"
        base58Prefixes[SCRIPT_ADDRESS]     = {0x1C,0xBD};
        // the first character, when base58 encoded, is "5" or "K" or "L" (as in Bitcoin)
        base58Prefixes[SECRET_KEY]         = {0x80};
        // do not rely on these BIP32 prefixes; they are not specified and may change
        base58Prefixes[EXT_PUBLIC_KEY]     = {0x04,0x88,0xB2,0x1E};
        base58Prefixes[EXT_SECRET_KEY]     = {0x04,0x88,0xAD,0xE4};
        // guarantees the first 2 characters, when base58 encoded, are "zc"
        base58Prefixes[ZCPAYMENT_ADDRRESS] = {0x16,0x9A};
        // guarantees the first 4 characters, when base58 encoded, are "ZiVK"
        base58Prefixes[ZCVIEWING_KEY]      = {0xA8,0xAB,0xD3};
        // guarantees the first 2 characters, when base58 encoded, are "SK"
        base58Prefixes[ZCSPENDING_KEY]     = {0xAB,0x36};

        bech32HRPs[SAPLING_PAYMENT_ADDRESS]      = "zs";
        bech32HRPs[SAPLING_FULL_VIEWING_KEY]     = "zviews";
        bech32HRPs[SAPLING_INCOMING_VIEWING_KEY] = "zivks";
        bech32HRPs[SAPLING_SPENDING_KEY]         = "secret-spending-key-main";

        //vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        checkpointData = (Checkpoints::CCheckpointData) {
            boost::assign::map_list_of
            (0, consensus.hashGenesisBlock)
            //(2500, uint256S("0x00000006dc968f600be11a86cbfbf7feb61c7577f45caced2e82b6d261d19744")),
            //(15000, uint256S("0x00000000b6bc56656812a5b8dcad69d6ad4446dec23b5ec456c18641fb5381ba"))
            //(67500, uint256S("0x000000006b366d2c1649a6ebb4787ac2b39c422f451880bc922e3a6fbd723616"))
            //(100000, uint256S("0x000000001c5c82cd6baccfc0879e3830fd50d5ede17fa2c37a9a253c610eb285"))
            //(133337, uint256S("0x0000000002776ccfaf06cc19857accf3e20c01965282f916b8a886e3e4a05be9"))
            //(180000, uint256S("0x000000001205b742eac4a1b3959635bdf8aeada078d6a996df89740f7b54351d"))
            //(222222, uint256S("0x000000000cafb9e56445a6cabc8057b57ee6fcc709e7adbfa195e5c7fac61343"))
            //(270000, uint256S("0x00000000025c1cfa0258e33ab050aaa9338a3d4aaa3eb41defefc887779a9729"))
            //(304600, uint256S("0x00000000028324e022a45014c4a4dc51e95d41e6bceb6ad554c5b65d5cea3ea5")),
            //1477973071,     // * UNIX timestamp of last checkpoint block
            //22063,        // * total number of transactions between genesis and last checkpoint
                            //   (the tx=... number in the SetBestChain debug.log lines)
            //5083            // * estimated number of transactions per day after checkpoint
                            //   total number of tx / (checkpoint block height / (24 * 24))
        };

        // Founders reward script expects a vector of 2-of-3 multisig addresses
        vFoundersRewardAddress = {
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 0*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 1*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 2*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 3*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 4*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 5*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 6*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 7*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 8*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 9*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 10*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 11*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 12*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 13*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 14*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 15*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 16*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 17*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 18*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 19*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 20*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 21*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 22*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 23*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 24*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 25*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 26*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 27*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 28*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 29*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 30*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 31*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 32*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 33*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 34*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 35*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 36*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 37*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 38*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 39*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 40*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 41*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 42*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 43*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 44*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 45*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 46*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 47*/
//            "t3PZ9PPcLzgL57XRSG5ND4WNBC9UTFb8DXv", /* main-index: 48*/
//            "t3L1WgcyQ95vtpSgjHfgANHyVYvffJZ9iGb", /* main-index: 49*/
//            "t3JtoXqsv3FuS7SznYCd5pZJGU9di15mdd7", /* main-index: 50*/
//            "t3hLJHrHs3ytDgExxr1mD8DYSrk1TowGV25", /* main-index: 51*/
//            "t3fmYHU2DnVaQgPhDs6TMFVmyC3qbWEWgXN", /* main-index: 52*/
//            "t3T4WmAp6nrLkJ24iPpGeCe1fSWTPv47ASG", /* main-index: 53*/
//            "t3fP6GrDM4QVwdjFhmCxGNbe7jXXXSDQ5dv", /* main-index: 54*/
};
        assert(vFoundersRewardAddress.size() <= consensus.GetLastFoundersRewardBlockHeight());
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        strCurrencyUnits = "TBZC";
        bip44CoinType = 1;
        consensus.fCoinbaseMustBeProtected = true;
        consensus.nSubsidySlowStartInterval = 3;
        consensus.nSubsidyHalvingInterval = 840000;
        consensus.nMajorityEnforceBlockUpgrade = 51;
        consensus.nMajorityRejectBlockOutdated = 75;
        consensus.nMajorityWindow = 400;
        consensus.powLimit = uint256S("07ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowAveragingWindow = 17;
        assert(maxUint/UintToArith256(consensus.powLimit) >= consensus.nPowAveragingWindow);
        consensus.nPowMaxAdjustDown = 32; // 32% adjustment down
        consensus.nPowMaxAdjustUp = 16; // 16% adjustment up
        consensus.nPowTargetSpacing = 2.5 * 60;
        //consensus.vUpgrades[Consensus::BASE_SPROUT].nProtocolVersion = 1;
        //consensus.vUpgrades[Consensus::BASE_SPROUT].nActivationHeight =
            Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        //consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nProtocolVersion = 1;
        //consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
            Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        //consensus.vUpgrades[Consensus::UPGRADE_OVERWINTER].nProtocolVersion = 1;
        //consensus.vUpgrades[Consensus::UPGRADE_OVERWINTER].nActivationHeight = 1;
        //consensus.vUpgrades[Consensus::UPGRADE_SAPLING].nProtocolVersion = 1;
        //consensus.vUpgrades[Consensus::UPGRADE_SAPLING].nActivationHeight = 0;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00000000000000000000000000000000000000000000000000000001d0c4d9cd");

        pchMessageStart[0] = 0xfb;
        pchMessageStart[1] = 0x1a;
        pchMessageStart[2] = 0xf7;
        pchMessageStart[3] = 0xbf;
        vAlertPubKey = ParseHex("044e7a1553392325c871c5ace5d6ad73501c66f4c185d6b0453cf45dec5a1322e705c672ac1a27ef7cdaf588c10effdf50ed5f95f85f2f54a5f6159fca394ed0c6");
        nDefaultPort = 18733;
        nPruneAfterHeight = 1000;
        const size_t N = 200, K = 9;
        BOOST_STATIC_ASSERT(equihash_parameters_acceptable(N, K));
        nEquihashN = N;
        nEquihashK = K;

        genesis = CreateGenesisBlock(
            1536721921,
            uint256S("0x0000000000000000000000000000000000000000000000000000000000000004"),
            ParseHex("01a9b6d750a8051d900f533a0e9ffdcd7894d3a9621e97e4f25464f75fd15186ac706d8c4eafdab84fba2579ba9334164c5d87c8f61d6836cf49c33ffb95d25ad5a31d7465ff31a92d55cf60b1020a432755cf4510ddd715e122dacf6836e4f490cbd0de5457de84ed1bf15998cb87285b8a4dc31eb7d16db8eeff2bad8c364eda32ba5200b30e6046635de24e360744da3ad74c77ae9908d69959893065f5f65840ce2080bbc3b30277bc820db87ca9ee45c2f171fc02dcc61c50e8d5028c9f70486da0cbf0320151c4de71fc94f654f46d1b27e5341b9ff3198e6056029dfe24fb027c5a2b5728d9cafe3e52040ab847254de24ba71a13da52272112c4f3a2818e08efcaf8e739dec0e2a65727189f3f1d734d98125781193a0ba77dc348f85e5e68b93b6d1f065425482cbdd7bdc2c7e38decdad774f37d70cc2c89e531aa31d083dd2e381d53d1cc770db2df36f402811711e507c17fe60db09df605332066c913ac961a42edbd8ea4390b891701e183afe748ba8f9fa29405d15571ec2579b16dab02074a9ff3f89b4d3fab1f122ade01b1114e2591b475498879d1ca4aac9d3c04067e276910242b6f370c1169cafa3af8b49f5f525825976fa5363c765dfc4314eb9463ba56ad211636ed1636270af1490a9ee7b28166aa0bd1f0af707ca6d0829b369175e70cd1e687c9d04ff754fe9aff9704bf04926ed922241f595f7911c796f9a9c60815f2d9250e250b2824077812d4c190ed6d57b37dc148d19d4c0929a1909235fa5fc9f472d541e0f05508edf8636f298c83f95827abcba2013324c6c088156b262dc2011286221843561555949162dc9bc9d7892140576cfd4463628729e8a9d14ba785f17c4bb3edb194ee52bf22787d1d9ce64579a63b63ab245cf69237fadb8c643e53c7be7e6051f5b40817542ebd50765b7959fc6d01bdc96eb682e0d9525a90cc587f62c284429c71d907042797a9dc08f96c4cb36a267eb7d527c2787e9a131423a81d4a4bb67a81d1a4491de8f5b56adf1b733473cf3d7dadfb97974ca39611f706f93edf5397320731b937b60b57a538df1181e4cb5f8d028cf631cf1598b0f2a4b20c85f024e7078c72fe89c89c7b7fd114ce6f557b05432be6a042133619a7a1c29a8e3906314569b2545aca63b554d5d59d6f0275b7aaf584280564f82f49472f1cfc5953eb8d238d936e16bd3443072351c679d9e1854e9723f18ebe77e186c8971b230cf2ebc31b91b6954a9ac182d547c2e59162bd0de13d4fbd4a36df2febc4766727bbdb20827903f863bd0d3056e95fe01601c93222de17e637e0bd0e28e1101983f4da6f1b18a33b9b57c14a5a765e675cfb0e8c3494fa3948d9864d96cbb74075de9072a60895fe5744b836df65db7c696340a899df5c2feb3048faffe302caa27d2c2bd53ffffde3abf0a4955a4374d9e8c01475cb0e068c91247c1b098bdacdb34f68b81e98b51049b4eba2891f26adcb659e8b7a3cd1ad8fb987441a41750e0a48700d1249a3ea0b37086bcfe81f372c185ddc1f4c327fe59ca724abab56782db38ad3ad171977fbbb1ea6872d9159f4f437e975add749387d66203e42e6178b655f8112723599fa3320bd210fc8aea19057e3567876a3d9a1ea935b7f28f35f743d5251071e36d49dc7f0377fb03264ec47ebc7d2863f3b4e08d03b0ed5df252920fc6270a29981d56076b35c9b1abcf7d9fb4c6f5ee43032e93e7d30e210de957eb2264a63b68be024a196a2e573c7433f11f02c5fada50ee1b53979c815c8d777a2a5086ea6ed699fb3153d3dac8f786dab0d35f754f50f0b32bee763829c6d0f20bd86e10dd25941e2807792be67a64251313f7b1f2590fed9f6897233764af37b3e63d4d729281c39c6"),
            0x2007ffff, 4, 0);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x02d8377b5ae8870c318f19b8c6be8ca7fd32fa2b9306dbcf13098be69e6600e8"));
        assert(genesis.hashMerkleRoot == uint256S("0x51d02c5b0782c1166d49ae4293d3461f2923ce5fecdcb3f7c5d1f47618479bfd"));

        //vFixedSeeds.clear();
        //vSeeds.clear();
        //vSeeds.push_back(CDNSSeedData("z.cash", "dnsseed.testnet.z.cash")); // Zcash

        // guarantees the first 2 characters, when base58 encoded, are "tm"
        base58Prefixes[PUBKEY_ADDRESS]     = {0x1D,0x25};
        // guarantees the first 2 characters, when base58 encoded, are "t2"
        base58Prefixes[SCRIPT_ADDRESS]     = {0x1C,0xBA};
        // the first character, when base58 encoded, is "9" or "c" (as in Bitcoin)
        base58Prefixes[SECRET_KEY]         = {0xEF};
        // do not rely on these BIP32 prefixes; they are not specified and may change
        base58Prefixes[EXT_PUBLIC_KEY]     = {0x04,0x35,0x87,0xCF};
        base58Prefixes[EXT_SECRET_KEY]     = {0x04,0x35,0x83,0x94};
        // guarantees the first 2 characters, when base58 encoded, are "zt"
        base58Prefixes[ZCPAYMENT_ADDRRESS] = {0x16,0xB6};
        // guarantees the first 4 characters, when base58 encoded, are "ZiVt"
        base58Prefixes[ZCVIEWING_KEY]      = {0xA8,0xAC,0x0C};
        // guarantees the first 2 characters, when base58 encoded, are "ST"
        base58Prefixes[ZCSPENDING_KEY]     = {0xAC,0x08};

        bech32HRPs[SAPLING_PAYMENT_ADDRESS]      = "ztestsapling";
        bech32HRPs[SAPLING_FULL_VIEWING_KEY]     = "zviewtestsapling";
        bech32HRPs[SAPLING_INCOMING_VIEWING_KEY] = "zivktestsapling";
        bech32HRPs[SAPLING_SPENDING_KEY]         = "secret-spending-key-test";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;
	checkpointData = (Checkpoints::CCheckpointData) {
            boost::assign::map_list_of
            (0, consensus.hashGenesisBlock)
            //(38000, uint256S("0x001e9a2d2e2892b88e9998cf7b079b41d59dd085423a921fe8386cecc42287b8")),
            //1486897419,  // * UNIX timestamp of last checkpoint block
            //47163,       // * total number of transactions between genesis and last checkpoint
                         //   (the tx=... number in the SetBestChain debug.log lines)
            //715          //   total number of tx / (checkpoint block height / (24 * 24))
        };

        // Founders reward script expects a vector of 2-of-3 multisig addresses
        vFoundersRewardAddress = {
            "t2UNzUUx8mWBCRYPRezvA363EYXyEpHokyi", "t2N9PH9Wk9xjqYg9iin1Ua3aekJqfAtE543", "t2NGQjYMQhFndDHguvUw4wZdNdsssA6K7x2", "t2ENg7hHVqqs9JwU5cgjvSbxnT2a9USNfhy",
            "t2BkYdVCHzvTJJUTx4yZB8qeegD8QsPx8bo", "t2J8q1xH1EuigJ52MfExyyjYtN3VgvshKDf", "t2Crq9mydTm37kZokC68HzT6yez3t2FBnFj", "t2EaMPUiQ1kthqcP5UEkF42CAFKJqXCkXC9",
            "t2F9dtQc63JDDyrhnfpzvVYTJcr57MkqA12", "t2LPirmnfYSZc481GgZBa6xUGcoovfytBnC", "t26xfxoSw2UV9Pe5o3C8V4YybQD4SESfxtp", "t2D3k4fNdErd66YxtvXEdft9xuLoKD7CcVo",
            "t2DWYBkxKNivdmsMiivNJzutaQGqmoRjRnL", "t2C3kFF9iQRxfc4B9zgbWo4dQLLqzqjpuGQ", "t2MnT5tzu9HSKcppRyUNwoTp8MUueuSGNaB", "t2AREsWdoW1F8EQYsScsjkgqobmgrkKeUkK",
            "t2Vf4wKcJ3ZFtLj4jezUUKkwYR92BLHn5UT", "t2K3fdViH6R5tRuXLphKyoYXyZhyWGghDNY", "t2VEn3KiKyHSGyzd3nDw6ESWtaCQHwuv9WC", "t2F8XouqdNMq6zzEvxQXHV1TjwZRHwRg8gC",
            "t2BS7Mrbaef3fA4xrmkvDisFVXVrRBnZ6Qj", "t2FuSwoLCdBVPwdZuYoHrEzxAb9qy4qjbnL", "t2SX3U8NtrT6gz5Db1AtQCSGjrpptr8JC6h", "t2V51gZNSoJ5kRL74bf9YTtbZuv8Fcqx2FH",
            "t2FyTsLjjdm4jeVwir4xzj7FAkUidbr1b4R", "t2EYbGLekmpqHyn8UBF6kqpahrYm7D6N1Le", "t2NQTrStZHtJECNFT3dUBLYA9AErxPCmkka", "t2GSWZZJzoesYxfPTWXkFn5UaxjiYxGBU2a",
            "t2RpffkzyLRevGM3w9aWdqMX6bd8uuAK3vn", "t2JzjoQqnuXtTGSN7k7yk5keURBGvYofh1d", "t2AEefc72ieTnsXKmgK2bZNckiwvZe3oPNL", "t2NNs3ZGZFsNj2wvmVd8BSwSfvETgiLrD8J",
            "t2ECCQPVcxUCSSQopdNquguEPE14HsVfcUn", "t2JabDUkG8TaqVKYfqDJ3rqkVdHKp6hwXvG", "t2FGzW5Zdc8Cy98ZKmRygsVGi6oKcmYir9n", "t2DUD8a21FtEFn42oVLp5NGbogY13uyjy9t",
            "t2UjVSd3zheHPgAkuX8WQW2CiC9xHQ8EvWp", "t2TBUAhELyHUn8i6SXYsXz5Lmy7kDzA1uT5", "t2Tz3uCyhP6eizUWDc3bGH7XUC9GQsEyQNc", "t2NysJSZtLwMLWEJ6MH3BsxRh6h27mNcsSy",
            "t2KXJVVyyrjVxxSeazbY9ksGyft4qsXUNm9", "t2J9YYtH31cveiLZzjaE4AcuwVho6qjTNzp", "t2QgvW4sP9zaGpPMH1GRzy7cpydmuRfB4AZ", "t2NDTJP9MosKpyFPHJmfjc5pGCvAU58XGa4",
            "t29pHDBWq7qN4EjwSEHg8wEqYe9pkmVrtRP", "t2Ez9KM8VJLuArcxuEkNRAkhNvidKkzXcjJ", "t2D5y7J5fpXajLbGrMBQkFg2mFN8fo3n8cX", "t2UV2wr1PTaUiybpkV3FdSdGxUJeZdZztyt",
            };
        assert(vFoundersRewardAddress.size() <= consensus.GetLastFoundersRewardBlockHeight());
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        strCurrencyUnits = "REG";
        bip44CoinType = 1;
        consensus.fCoinbaseMustBeProtected = false;
        consensus.nSubsidySlowStartInterval = 0;
        consensus.nSubsidyHalvingInterval = 150;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.powLimit = uint256S("0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f");
        consensus.nPowAveragingWindow = 17;
        assert(maxUint/UintToArith256(consensus.powLimit) >= consensus.nPowAveragingWindow);
        consensus.nPowMaxAdjustDown = 0; // Turn off adjustment down
        consensus.nPowMaxAdjustUp = 0; // Turn off adjustment up
        consensus.nPowTargetSpacing = 2.5 * 60;
        //consensus.vUpgrades[Consensus::BASE_SPROUT].nProtocolVersion = 1;
        //consensus.vUpgrades[Consensus::BASE_SPROUT].nActivationHeight =
            Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        //consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nProtocolVersion = 1;
        //consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
            Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        //consensus.vUpgrades[Consensus::UPGRADE_OVERWINTER].nProtocolVersion = 1;
        //consensus.vUpgrades[Consensus::UPGRADE_OVERWINTER].nActivationHeight =
            Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        //consensus.vUpgrades[Consensus::UPGRADE_SAPLING].nProtocolVersion = 1;
        //consensus.vUpgrades[Consensus::UPGRADE_SAPLING].nActivationHeight =
            Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        pchMessageStart[0] = 0xaa;
        pchMessageStart[1] = 0xe7;
        pchMessageStart[2] = 0x3f;
        pchMessageStart[3] = 0x5f;
        nDefaultPort = 18734;
        nPruneAfterHeight = 1000;
        const size_t N = 48, K = 5;
        BOOST_STATIC_ASSERT(equihash_parameters_acceptable(N, K));
        nEquihashN = N;
        nEquihashK = K;

        genesis = CreateGenesisBlock(
            1536721921,
            uint256S("0x0000000000000000000000000000000000000000000000000000000000000000"),
            ParseHex("08a983bf9263def7cb2ca7d35c94dd5d934f0b8b8cc9917974deee1593c90904bf0969c7"),
            0x200f0f0f, 4, 0);
        consensus.hashGenesisBlock = genesis.GetHash();
        //assert(consensus.hashGenesisBlock == uint256S("0x0be024573a7bf8665bafe6e69efd52cefa68eafd3c13957335186889bc80f48e"));
        assert(genesis.hashMerkleRoot == uint256S("0x51d02c5b0782c1166d49ae4293d3461f2923ce5fecdcb3f7c5d1f47618479bfd"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        checkpointData = (Checkpoints::CCheckpointData){
            boost::assign::map_list_of
            ( 0, uint256S("0x0be024573a7bf8665bafe6e69efd52cefa68eafd3c13957335186889bc80f48e"),
            0,
            0,
            0
        };
        // These prefixes are the same as the testnet prefixes
        base58Prefixes[PUBKEY_ADDRESS]     = {0x1D,0x25};
        base58Prefixes[SCRIPT_ADDRESS]     = {0x1C,0xBA};
        base58Prefixes[SECRET_KEY]         = {0xEF};
        // do not rely on these BIP32 prefixes; they are not specified and may change
        base58Prefixes[EXT_PUBLIC_KEY]     = {0x04,0x35,0x87,0xCF};
        base58Prefixes[EXT_SECRET_KEY]     = {0x04,0x35,0x83,0x94};
        base58Prefixes[ZCPAYMENT_ADDRRESS] = {0x16,0xB6};
        base58Prefixes[ZCVIEWING_KEY]      = {0xA8,0xAC,0x0C};
        base58Prefixes[ZCSPENDING_KEY]     = {0xAC,0x08};

        bech32HRPs[SAPLING_PAYMENT_ADDRESS]      = "zregtestsapling";
        bech32HRPs[SAPLING_FULL_VIEWING_KEY]     = "zviewregtestsapling";
        bech32HRPs[SAPLING_INCOMING_VIEWING_KEY] = "zivkregtestsapling";
        bech32HRPs[SAPLING_SPENDING_KEY]         = "secret-spending-key-regtest";

        // Founders reward script expects a vector of 2-of-3 multisig addresses
        vFoundersRewardAddress = { "t2FwcEhFdNXuFMv1tcYwaBJtYVtMj8b1uTg" };
        assert(vFoundersRewardAddress.size() <= consensus.GetLastFoundersRewardBlockHeight());
    }

    void UpdateNetworkUpgradeParameters(Consensus::UpgradeIndex idx, int nActivationHeight)
    {
        assert(idx > Consensus::BASE_SPROUT && idx < Consensus::MAX_NETWORK_UPGRADES);
        consensus.vUpgrades[idx].nActivationHeight = nActivationHeight;
    }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams &Params(CBaseChainParams::Network network) {
    switch (network) {
        case CBaseChainParams::MAIN:
            return mainParams;
        case CBaseChainParams::TESTNET:
            return testNetParams;
        case CBaseChainParams::REGTEST:
            return regTestParams;
        default:
            assert(false && "Unimplemented network");
            return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network) {
    SelectBaseParams(network);
    pCurrentParams = &Params(network);

    // Some python qa rpc tests need to enforce the coinbase consensus rule
    if (network == CBaseChainParams::REGTEST && mapArgs.count("-regtestprotectcoinbase")) {
        regTestParams.SetRegTestCoinbaseMustBeProtected();
    }
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}


// Block height must be >0 and <=last founders reward block height
// Index variable i ranges from 0 - (vFoundersRewardAddress.size()-1)
std::string CChainParams::GetFoundersRewardAddressAtHeight(int nHeight) const {
    int maxHeight = consensus.GetLastFoundersRewardBlockHeight();
    assert(nHeight > 0 && nHeight <= maxHeight);

    size_t addressChangeInterval = (maxHeight + vFoundersRewardAddress.size()) / vFoundersRewardAddress.size();
    size_t i = nHeight / addressChangeInterval;
    return vFoundersRewardAddress[i];
}

// Block height must be >0 and <=last founders reward block height
// The founders reward address is expected to be a multisig (P2SH) address
CScript CChainParams::GetFoundersRewardScriptAtHeight(int nHeight) const {
    assert(nHeight > 0 && nHeight <= consensus.GetLastFoundersRewardBlockHeight());

    CTxDestination address = DecodeDestination(GetFoundersRewardAddressAtHeight(nHeight).c_str());
    assert(IsValidDestination(address));
    assert(boost::get<CScriptID>(&address) != nullptr);
    CScriptID scriptID = boost::get<CScriptID>(address); // address is a boost variant
    CScript script = CScript() << OP_HASH160 << ToByteVector(scriptID) << OP_EQUAL;
    return script;
}

std::string CChainParams::GetFoundersRewardAddressAtIndex(int i) const {
    assert(i >= 0 && i < vFoundersRewardAddress.size());
    return vFoundersRewardAddress[i];
}


int validEHparameterList(EHparameters *ehparams, unsigned long blockheight, const CChainParams& params){
    //if in overlap period, there will be two valid solutions, else 1.
    //The upcoming version of EH is preferred so will always be first element
    //returns number of elements in list
    if(blockheight>=params.eh_epoch_2_start() && blockheight>params.eh_epoch_1_end()){
        ehparams[0]=params.eh_epoch_2_params();
        return 1;
    }
    if(blockheight<params.eh_epoch_2_start()){
        ehparams[0]=params.eh_epoch_1_params();
        return 1;
    }
    ehparams[0]=params.eh_epoch_2_params();
    ehparams[1]=params.eh_epoch_1_params();
    return 2;
}
void UpdateNetworkUpgradeParameters(Consensus::UpgradeIndex idx, int nActivationHeight)
{
    regTestParams.UpdateNetworkUpgradeParameters(idx, nActivationHeight);
}
