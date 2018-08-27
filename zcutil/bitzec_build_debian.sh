#!/usr/bin/env bash

cd "$(dirname "$(readlink -f "$0")")"    #'"%#@!

sudo apt-get install \
      build-essential pkg-config libc6-dev m4 g++-multilib \
      autoconf libtool ncurses-dev unzip git python python-zmq \
      zlib1g-dev wget bsdmainutils automake

./fetch-params.sh || exit 1

./build.sh --disable-tests --disable-rust -j$(nproc) || exit 1

if [ ! -r ~/.bitcoinz/bitcoinz.conf ]; then
   mkdir -p ~/.bitcoinz
   echo "addnode=mainnet.bitcoinz.site" >~/.bitcoinz/bitcoinz.conf
   echo "rpcuser=username" >>~/.bitcoinz/bitcoinz.conf
   echo "rpcpassword=`head -c 32 /dev/urandom | base64`" >>~/.bitcoinz/bitcoinz.conf
fi

cd ../src/
cp -f zcashd bitzecd
cp -f zcash-cli bitzec-cli
cp -f zcash-tx bitzec-tx

echo ""
echo "--------------------------------------------------------------------------"
echo "Compilation complete. Now you can run ./src/bitcoinzd to start the daemon."
echo "It will use configuration file from ~/.bitcoinz/bitcoinz.conf"
echo ""
