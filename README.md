BITZEC 1.0.0 is based on the genesis chain of zcash, but on the zhash (equihash 144.5) algorithm
<img align="right" width="120" height="80" src="doc/imgs/logo.png">
===========
https://bitzec.org

What is Zcash?
[Zcash](https://z.cash/) is an implementation of the "Zerocash" protocol.
Based on Bitcoin's code,
--------------

[Zcash](https://z.cash/) is an implementation of the "Zerocash" protocol.
Based on Bitcoin's code, it intends to offer a far higher standard of privacy
through a sophisticated zero-knowledge proving scheme that preserves
confidentiality of transaction metadata. Technical details are available
in our [Protocol Specification](https://github.com/zcash/zips/raw/master/protocol/protocol.pdf).

Install required dependencies:
```
apt-get update \
&& apt-get install -y \
    curl build-essential pkg-config libc6-dev m4 g++-multilib autoconf \
    libtool ncurses-dev unzip git python zlib1g-dev wget bsdmainutils \
    automake p7zip-full pwgen mingw-w64 cmake
```

Execute the build command:
```
./zcutil/build-win.sh --disable-rust -j$(nproc)
```

### Windows Wallet
Windows wallet build is maintained in bitzec

License
-------

For license information see the file [COPYING](COPYING).
