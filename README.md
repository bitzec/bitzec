BITZEC 1.0.0
<img align="right" width="120" height="80" src="doc/imgs/logo.png">
===========
What are 
[Zero knowledge proofs](https://en.wikipedia.org/wiki/Zero-knowledge_proof) ?
[Zcash](https://z.cash/) is an implementation of the "Zerocash" protocol.
Based on Bitcoin's code.
What is [Bitcoin](https://en.wikipedia.org/wiki/Bitcoin) ?
--------------

[Zcash](https://z.cash/) is an implementation of the "Zerocash" protocol.
Based on Bitcoin's code, it intends to offer a far higher standard of privacy
through a sophisticated zero-knowledge proving scheme that preserves
confidentiality of transaction metadata. Technical details are available
in our [Protocol Specification](https://github.com/zcash/zips/raw/master/protocol/protocol.pdf).

This software is the Bitzec client. It downloads and stores the entire history
of Bitzec transactions; depending on the speed of your computer and network
connection, the synchronization process could take a day or more once the
blockchain has reached a significant size.

<p align="center">
  <img src="doc/imgs/zcashd_screen.gif" height="500">
</p>

#### :lock: Security Warnings

See important security warnings on the
[Security Information page](https://z.cash/support/security/).

```{r, engine='bash'}
# Clone Bitzec Repository
git clone https://github.com/bitzec/bitzec.git
# Build
cd bitzec/
./zcutil/build.sh --disable-tests -j$(nproc)
# fetch key
./zcutil/fetch-params.sh
# Run
./src/bitzecd
# Test getting information about the network
cd src/
./bitzec-cli getmininginfo
# Test creating new transparent address
./bitzec-cli getnewaddress
# Test creating new private address
./bitzec-cli z_getnewaddress
# Test checking transparent balance
./bitzec-cli getbalance
# Test checking total balance 
./bitzec-cli z_gettotalbalance
# Check all available wallet commands
./bitzec-cli help
# Get more info about a single wallet command
./bitzec-cli help "The-command-you-want-to-learn-more-about"
./bitzec-cli help "getbalance"
```

####  :ledger: Deprecation Policy

This release is considered deprecated 16 weeks after the release day. There
is an automatic deprecation shutdown feature which will halt the node some
time after this 16 week time period. The automatic feature is based on block
height.

## Getting Started

Please see our [user guide](https://zcash.readthedocs.io/en/latest/rtd_pages/rtd_docs/user_guide.html) for joining the main Zcash network.

### Need Help?

* :blue_book: See the documentation at the [ReadtheDocs](https://zcash.readthedocs.io)
  for help and more information.

Participation in the Zcash project is subject to a
[Code of Conduct](code_of_conduct.md).

### Building

Build Bitzec along with most dependencies from source by running:

```
./zcutil/build.sh -j$(nproc)
```

Currently only Linux is officially supported.

License
-------

For license information see the file [COPYING](COPYING).
