BITZEC 1.0.0
<img align="right" width="140" height="140" src="doc/imgs/logo.png">
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
Install dependencies:
sudo apt-get install \
build-essential pkg-config libc6-dev m4 g++-multilib \
autoconf libtool ncurses-dev unzip git python python-zmq \
zlib1g-dev wget curl bsdmainutils automake
Clone Bitzec Repository :
git clone https://github.com/bitzec/bitzec.git
###Build:
cd bitzec/
./zcutil/build.sh -j$(nproc)
fetch key:
./zcutil/fetch-params.sh
Run
./src/bitzecd
Test getting information about the network
./src/bitzec-cli blockchain info

./bitzec-cli help      <--- for full command list 
```
Installation video :https://youtu.be/5ahQZZYcntQ
<p align="center">
  <img src="doc/imgs/blockreward .png" height="500">

### START TESTING:Testing

Add unit tests for Bitzec under Bitzec  ./src/gtest.

To list all tests, run ./src/zcash-gtest --gtest_list_tests.

To run a subset of tests, use a regular expression with the flag --gtest_filter. Example:

` ./src/zcash-gtest --gtest_filter=DeprecationTest.* `

For debugging: --gtest_break_on_failure.

To run a subset of BOOST tests: ` src/test/test_bitcoin -t TESTGROUP/TESTNAME


https://zcash.readthedocs.io/en/latest/rtd_pages/development_guidelines.html#development-guidelines


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

<p align="center">
  <img src="doc/imgs/bzloveblack.png" height="350">
  
  
