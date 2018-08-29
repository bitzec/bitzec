#!/bin/bash

sudo apt -y update
sudo apt-get install -y libc6-dev g++-multilib python p7zip-full pwgen jq curl
cd ~

if [ -f bitzec.zip ]
then
    rm bitzec.zip
fi
wget -O bitzec.zip `curl -s 'https://api.github.com/repos/bitzec/bitzec/releases/latest' | jq -r '.assets[].browser_download_url' | egrep "bitzec.+x64.zip"`
7z x -y bitzec.zip
chmod -R a+x ~/bitzec-pkg
rm bitzec.zip

cd ~/bitzec-pkg
./fetch-params.sh

if ! [[ -d ~/.bitzec ]]
then
    mkdir -p ~/.bitzec
fi

if ! [[ -f ~/.bitzec/bitzec.conf ]]
then
    echo "rpcuser=rpc`pwgen 15 1`" > ~/.bitzec/bitzec.conf
    echo "rpcpassword=rpc`pwgen 15 1`" >> ~/.bitzec/bitzec.conf
fi

./bitzecd
