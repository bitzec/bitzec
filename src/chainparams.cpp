// Bismilah


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
 *
 *  >>> 'Bitzec' (b'the binary digit zero knowledge electronic currency')
 *
 * CBlock(hash=00040fe8, ver=4, hashPrevBlock=00000000000000, hashMerkleRoot=c4eaa5, nTime=1536721921, nBits=1f07ffff, nNonce=4695, vtx=1)
 *   CTransaction(hash=c4eaa5, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff071f0104455a6361736830623963346565663862376363343137656535303031653335303039383462366665613335363833613763616331343161303433633432303634383335643334)
 *     CTxOut(nValue=0.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: c4eaa5
 */

static CBlock CreateGenesisBlock(uint32_t nTime, const uint256& nNonce, const std::vector<unsigned char>& nSolution, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp ="Bitzec6028c7b3ef33e2e036027f241fa0a396ed17ed90e7c7e264132ee59a34035baf" ;
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
        strCurrencyUnits = "BZC"; // the binary digit zero knowledge electronic currency
        bip44CoinType = 133; // As registered in https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        consensus.fCoinbaseMustBeProtected = true;
        consensus.nSubsidySlowStartInterval = 7;
        consensus.nSubsidyHalvingInterval = 13000001;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 4000;
        consensus.powLimit = uint256S("0007ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowAveragingWindow = 17;
        assert(maxUint/UintToArith256(consensus.powLimit) >= consensus.nPowAveragingWindow);
        consensus.nPowMaxAdjustDown = 32; // 32% adjustment down
        consensus.nPowMaxAdjustUp = 16; // 16% adjustment up
        consensus.nPowTargetSpacing = 2.5 * 60;
        consensus.nPowAllowMinDifficultyBlocksAfterHeight = boost::none;
        consensus.vUpgrades[Consensus::BASE_SPROUT].nProtocolVersion = 170002;
        consensus.vUpgrades[Consensus::BASE_SPROUT].nActivationHeight =
            Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nProtocolVersion = 170002;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
            Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_OVERWINTER].nProtocolVersion = 175001;
        consensus.vUpgrades[Consensus::UPGRADE_OVERWINTER].nActivationHeight = 3;
        consensus.vUpgrades[Consensus::UPGRADE_SAPLING].nProtocolVersion = 175001;
        consensus.vUpgrades[Consensus::UPGRADE_SAPLING].nActivationHeight = 5;

  // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        /**
         * The message start string should be awesome! Bⓩ❤
         */
        pchMessageStart[0] = 0x21;
        pchMessageStart[1] = 0xe7;
        pchMessageStart[2] = 0x27;
        pchMessageStart[3] = 0x61;
        vAlertPubKey = ParseHex("04b7ecf0baa90495ceb4e4090f6b2fd37eec1e9c85fac68a487f3ce11589692e4a317479316ee814e066638e1db54e37a10689b70286e6315b1087b6615d179264");
        nDefaultPort = 8733;
        nPruneAfterHeight = 100000;

        const size_t N = 200, K = 9;
        BOOST_STATIC_ASSERT(equihash_parameters_acceptable(N, K));
        nEquihashN = N;
        nEquihashK = K;

        genesis = CreateGenesisBlock(
            1536721921,
            uint256S("0x000000000000000000000000000000000000000000000000000000000000051b"),
            ParseHex("00083769919f4cdd7c1723ce2fd6b4b10a95ef0b842cf40de1a2aae29973d214486e3b1a8af0b41a08c406b70a98dda7bf8f757a533188d748f95c85af8adc6f368c8d0b604f0b7d4e17f4ba540822cf05f6ce67001b3981c989e66eef450013d46244b116f1f72a12217b729cbf99d216ddee7611a3ba0b2af4dfb8d81714535fb619858e31471d0375f07fbc659df0bda2f21c9c6f84d0d15077b1c9b46152c3bb826eba14399c0792a1484e0d6cb6857583f90da8b2969adb75c5052c792a0eabd7e322c2e953cf6e2711ad3322eaf71e180850f4a366d687bda2e9f37ed9953f76d01e2796385435255c14b4a728fb852c106fb0219399757a710b78e355f09cebfd1c22855ca9f48e532ff97b6ce13b20c5baa7717925aca7aab3c9da69aaeecfdf75241f59a59298a07097b583db0c9f67a90f16a89c3ad9233aba7bcf29ee51ccfc132e8463c2a137283cdb4400bbd4ad884a83c991c845a9c459c682846afbb8710433b02fc2e4ad75ea78e2035db7f8d558575b1c440a31a33ef0a6e6377c9a3335c463b8ed1aea542a7a1f12d94929f5f985d6fe9227142b0690a3671d6d040418b1aea952232fadec5468c0d8e699a8ba2db0be1ade971549fee84dfe8ca353d125295971a57baedf17bd5e4858cff393d190d1ca6e458610e77b95b2b849640d9646b088d5eadcf6e500cf178e83971be5c5040b7b078d53f92998052148a863e1f2c5ea1ac07316e3b7b841161387c0c8d3d7e7cc5a893932781f630ac45f30154bb494ca2eb13ecabcd74a5375dafa6542fc6be834a9c32b780ae88b9cfbac726fd333a7830b9aa15060d49071f4cf02d50caa8b1afc003f28ad1dd7ac49e78c1dd89ce6c2f537aca294f1d2f93850110bae565be0e5872680f49c91f2208d9a685bc75c2f7e635bdf652e9196c7c3f164e2cee6affadf18080080975c12866c8fab3a13955d2a74594b1bb612950d04dd5ddd5b398b83c68591675d15263367bb21400346146bf8b394fbdf58755aec3dce81aeb5d75e9004f8434a72566b6d59bbf1cdf160d6c2f2e47c76e50130080c0f15a56abe4411aa6673ef24e3ddfbac290ffebde67fce8baa78cbb1f91b946cdcbabe39d04216810f15745d0bdbd0e112d93dac4e1cdef13757cd24af566d594dbd97473f02c324482d0d063e70e11b0177cc31b55ef1cbe0df702a18d118895ce8587537334cfbc6d1e3a48feae324dc26a812114f65d380f103e184ee75ebf9ffc94b90504d20e43027c3dbb7e10f4ed6888fefd4e59f2e62d5106cdcd627fa5bce1516935ab879b525c1e65b14729b37606a0d9512e5892a906dd657d3153b6dbd852c5dcf673728771e52bf1b8d1d1e8b8927d8718f06964e5e7f164cb5ffe7552573ef95d9e04cb1f6c9f28385bac675904e4cae140295c238f697f7fb9b4df514943c9791efa53c4cf4200e061318504dbfc30e448433f70d0557f32ba4ae094e4a9eba503605a3043b0c8063bb07183fbbb20d61059d48ea5d6a5d04d647322ad73cabcfa55f88050455bda31e0482737b8d21395df410f577a5ccdcd40b515575a4dcf545c7f1690aca6068db289939c6b40774651114c6f84cda9065abe34dcd8e13e153a0b42ee0e445ded0c15cbb4e63d69f21173a1842b74db40599a6be314cb07878b0a2744cbdd56d6bfe3f5f330e852565918499efc059f7894257fdae6c16d9e44a19ecc9b3c059a9238f9fd219359aa816003e9709e1262d9fe083cd313b440c5c0fc76888a39f2b9f3ed80ae9209525172291a2d1a5cc394e9032387bdb64b90e577f4406189b0da737073d7c469792e0a9393263367b9e7b42d198b1e0c685d40c4abce987fbec725e431bbcf52beb2c1b93d2465a4ec8cf01a98416417d"),
            0x1f07ffff, 4, 0);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00055119765e0230f2a135ca8f897869c5e6b05dc371160042405da1f5c3906d"));
        assert(genesis.hashMerkleRoot == uint256S("0xc44bb8cb5ccae05712ee77382685ac0daa9d6201ab44f7b8932b234ceef23f3f"));

        vFixedSeeds.clear();
        vSeeds.clear();
        //vSeeds.push_back(CDNSSeedData("bitzec.org", "seed.bitzec.org")); //
        vSeeds.push_back(CDNSSeedData("35.237.52.66", "35.237.52.66")); // seed node
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
        bech32HRPs[SAPLING_EXTENDED_SPEND_KEY]   = "secret-extended-key-main";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = false;

         checkpointData = (CCheckpointData) {
             boost::assign::map_list_of
             //(0, consensus.hashGenesisBlock)
             ( 0, consensus.hashGenesisBlock),
             genesis.nTime,
             0,
             0
             //(1, uint256S("0x000754d3537ff6b10518c8000b178e26a13c89f7488c89f4c2ac3246e7a7e1d7"))
             //(2, uint256S("0x000725c2746473d804e5e8b3b066527f641b710889b22cb283f2c89cbada531d"))
             //(29, uint256S("0x0003ab5b034516371e3fb76abfe22e761536a087b9b4604ee2a8dcaa264ad16e"))
             //(34, uint256S("0x000000001c5c82cd6baccfc0879e3830fd50d5ede17fa2c37a9a253c610eb285")),
            //(133337, uint256S("0x0000000002776ccfaf06cc19857accf3e20c01965282f916b8a886e3e4a05be9"))
            //(180000, uint256S("0x000000001205b742eac4a1b3959635bdf8aeada078d6a996df89740f7b54351d"))
            //(222222, uint256S("0x000000000cafb9e56445a6cabc8057b57ee6fcc709e7adbfa195e5c7fac61343"))
            //(270000, uint256S("0x00000000025c1cfa0258e33ab050aaa9338a3d4aaa3eb41defefc887779a9729"))
            //(304600, uint256S("0x00000000028324e022a45014c4a4dc51e95d41e6bceb6ad554c5b65d5cea3ea5")),
            //1540367102,     // * UNIX timestamp of last checkpoint block
            //35,        // * total number of transactions between genesis and last checkpoint
                            //   (the tx=... number in the SetBestChain debug.log lines)
            //700            // * estimated number of transactions per day after checkpoint
                            //   total number of tx / (checkpoint block height / (24 * 24))

        };

        // Founders reward script expects a vector of 2-of-3 multisig addresses
        vFoundersRewardAddress = {
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 0*/
            "t3ZwokSicGHQhF7nuPVzKxTfm5qHVbXV5vS", /* main-index: 1*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 2*/
            "t3MpjbqV1f6dQcnXjBbdYCzDa87XQYuTbWz", /* main-index: 3*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 4*/
            "t3NdSKHyB7siGWGzXy6NLWNMdjF6wwWZjxy", /* main-index: 5*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 6*/
            "t3dYeSR5bNsCXtGwythocQGxfvChetbBbXj", /* main-index: 7*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 8*/
            "t3bTvatHrv7CgtNY8ZVtqeYrRsHcDGUBqSg", /* main-index: 9*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 10*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 11*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 12*/
            "t3fTavgWgerUopjuYyJLPi8mQDhcFhDRvDa", /* main-index: 13*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 14*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 15*/
            "t3MpjbqV1f6dQcnXjBbdYCzDa87XQYuTbWz", /* main-index: 16*/
            "t3SAe5q2qTaZyFvQwGDTRLYGVtNpzhi9EyG", /* main-index: 17*/
            "t3fHgXgwhP4UjxCLZwyiaBNPVWrzYL1GffL", /* main-index: 18*/
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
            "t3aaW4aTdP7a8d1VTE1Bod2yhbeggHgMajR", /* main-index: 32*/
            "t3PPMGfYJ7FXzvRxNefS21Hgh8Fqp8Es93e", /* main-index: 33*/
            "t3NTfpUNJ1au66E1hvqNwFzL4qdvZp2Rwfk", /* main-index: 34*/
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
        consensus.nSubsidySlowStartInterval = 7777;
        consensus.nSubsidyHalvingInterval = 1314001;
        consensus.nMajorityEnforceBlockUpgrade = 51;
        consensus.nMajorityRejectBlockOutdated = 75;
        consensus.nMajorityWindow = 400;
        consensus.powLimit = uint256S("07ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowAveragingWindow = 17;
        assert(maxUint/UintToArith256(consensus.powLimit) >= consensus.nPowAveragingWindow);
        consensus.nPowMaxAdjustDown = 32; // 32% adjustment down
        consensus.nPowMaxAdjustUp = 16; // 16% adjustment up
        consensus.nPowTargetSpacing =2.5 * 60;
        consensus.vUpgrades[Consensus::BASE_SPROUT].nProtocolVersion = 170002;
        consensus.vUpgrades[Consensus::BASE_SPROUT].nActivationHeight =
            Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nProtocolVersion = 170002;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
            Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_OVERWINTER].nProtocolVersion = 175001;
        consensus.vUpgrades[Consensus::UPGRADE_OVERWINTER].nActivationHeight = 3;
        consensus.vUpgrades[Consensus::UPGRADE_SAPLING].nProtocolVersion = 175001;
        consensus.vUpgrades[Consensus::UPGRADE_SAPLING].nActivationHeight = 5;




   // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");


        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0x1a;
        pchMessageStart[2] = 0xf9;
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
            uint256S("0x000000000000000000000000000000000000000000000000000000000000000b"),
            ParseHex("00be48248fc56f60f7b192a2336b935545eeb67a375bcafd1a216abdb3d3e326a0595e2f1a9d17fd445a01d2a7394315545b3dc5b44fc07be875c29f0e9f9a24769f4f214a95f064cfe2c7c03b828addde9e549b01b3b8b68501f108c358f292355f5d829c5257ab8218eb1daf0e8d2f6d7c7583ffac594089d64315c70f092de782546325cb7896a19a2c6af6970115fca3d2563047a1f116bb45c033f9352b6409f65ee553fbcf057b4be198c23fc7c9850227b418659de6aa50d9ef0ec0b48f74960057de60e30eef9e4c9cf2942ba238235eaa0faaab98255e85948147a9dd72ed7dda5232668d4410ace473735383c76015f9453200f63d5bc312dc25de4d14b040b966e1f819e0ce35303c6fb52e2a98f3c913193cc7af5bd39f6264439d53819c1e5a21e59db2eb5c902eff8df93ae2541d2a65a919edb45a5b6b9714e29a5dfa5106dbdebc5ac6db03fb6ac8026215df4347ff7664f4764bd1ffadb59408d753031c8064237fa1592b5fb7c26b1eb170dd0898b89f6308d8742364667dadb665c4e9d1dd71513ee4cad517176774c74861916f4bcb737bdd7775ee4aef7517bb038f0a4bab17e2c0d9f65d7b2afdc2a77f655f1cdf0c224c818fc3aad756bfa0f37a6cb348495a93a7d1265215edb9cc4cc1ba19427b797d4cb150f39919642a846b43200cbb9fac45962968e15651bf2b912f2d030c716875d8533b7b8f64b3c378e9116fc437da1510c7d56ea34956fd601f327309b4db130867fc0e9f1a66058541b3df45f90e01ae795bd17640cd7c24422f1d8d880dd3d812b9c15a993cd6358ee6d79ebafc04020b31c2417667b6d3d3020df4af1962ba59761b26434e171666ea57ae2e06ef805f09026ae5db81b808b36f337a4f5e78a22f7195775cf5e55a4a90a021447095ff9e962fa15e940bd4fc60036b7da91ca47c01ae52b342911d31f6b030b1111ceff83366feb6f63b8a1ddef49228d56f5506f525753a1626dbfdf29904d8b747a887644bc2c5509dc1873585ab1730f02d0efd718b29ea8747a135c22751df04e4afcbe6eeb1031aa4ec960f81899346211e8cddc330f66977fdf90db4da44e11ba3a952d1aa6af36593cbbc27fe1ea4045045c2a4619887647e23e990ebffe6f4899df9fc09e0b451a28b03e875e44323efd14e810b66f7f29402e500ac6100ee815f7a606a6c8869f6c8681abc8f34b7350919d79ca3933264ef3e5e3f7654e0b67390059707acfad06581e4cda956164e939aed875a75ee0feb5c88bb0ccd086a2818eaa3e3b0eed0c25a6f57068f93579644f6f2ca09b087c315c1664f533781d61496cb94c7d76497cc1a23057e7ec7fdbb51f401670d1384163e20cfbbd22da49036ca50adb6dcfc9d9726c66f4f408c22ecffee46f351d66bfe59a6f56fad01c476aae6cd16c95f0381d3db79e54d0897115e0a13b537a90c62a7938e13b385fefd76832f885d1548277ded06b79979f9ce9507ad317f8e832ffe3abd5a42e6bccadbeaa947f6197523d32dcfd24d071cbd101f4b567bec34b183d52354efe45990ed54dacf73f32c5c5de8118fa205138114b21e77ca2e196fd9c8ff21bca2c3d76de72df4da335d683e3d6ae3ab5c38d745e1cf07429de675294ee521d9ce59e617acfd0d64043928aa2421cc4f827b01a3a44fa5c8dfaed9b44a319be2eb727336f9b0c8c6dcc3e99bb353887e4adb11ba8bf4a323b51f9fa1f5c3cf75ba05b64cb779d716bf153d538d83db2612d56b9be5d5296060f0eefa0ccc075c73c7835ecea92aebec6704eb8a2bfc6f406c84cd41d25c7d9b2c4d688233d98f936c945e09232baa82b8b7149449e27d778895663b4b9ea73daeb932ac9a2ce3dfc0c9470bf6b821fcc76e89551573c9"),
            0x2007ffff, 4, 0);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x0034bdd8cedc446a5f1ff2dbcf7333b499a92a21d06b247ee57fb161d7360091"));
        assert(genesis.hashMerkleRoot == uint256S("0xc44bb8cb5ccae05712ee77382685ac0daa9d6201ab44f7b8932b234ceef23f3f"));

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
        bech32HRPs[SAPLING_EXTENDED_SPEND_KEY]   = "secret-extended-key-test";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;


        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            ( 0, consensus.hashGenesisBlock),
            genesis.nTime,
            0,
            0
            //(0, uint256S("0x0034bdd8cedc446a5f1ff2dbcf7333b499a92a21d06b247ee57fb161d7360091")),
            //(3,   uint256S("0x0614b59c26ded31075377ef3980c7db4b3a1663bab4ca96f8d525dae723cdb5a"))
            //(4,   uint256S("0x01547d1faa3fea42b0838fab3a6bc7c608a56728c9c0b95ca40a5047fbcccfb7"))
            //(5,   uint256S("0x024adc569580decf8551d3bf9275c3fa960be871cd929f63264c614ee2a6b336")),
              //1540411734,  // * UNIX timestamp of last checkpoint block
              //6,       // * total number of transactions between genesis and last checkpoint
                         //   (the tx=... number in the SetBestChain debug.log lines)
              //100           //   total number of tx / (checkpoint block height / (24 * 24))
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
        consensus.nPowTargetSpacing =2.5 * 60;


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
            uint256S("0x000000000000000000000000000000000000000000000000000000000000000d"),
            ParseHex("0aeb92f353cd4da379233823f24269a27d45163f8fecc1d2d08f155137587fb65ec7bde1"),
            0x200f0f0f, 4, 0);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x0d8885ee19400cb5af537d20875f4e1869fb438342464f92102cd510e25bfaea"));
        assert(genesis.hashMerkleRoot == uint256S("0xc44bb8cb5ccae05712ee77382685ac0daa9d6201ab44f7b8932b234ceef23f3f"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        checkpointData = (CCheckpointData){
            boost::assign::map_list_of
            ( 0, uint256S("0x0d8885ee19400cb5af537d20875f4e1869fb438342464f92102cd510e25bfaea")),
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
        bech32HRPs[SAPLING_EXTENDED_SPEND_KEY]   = "secret-extended-key-regtest";

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

void UpdateNetworkUpgradeParameters(Consensus::UpgradeIndex idx, int nActivationHeight)
{
    regTestParams.UpdateNetworkUpgradeParameters(idx, nActivationHeight);
}
