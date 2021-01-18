#!/bin/bash

# Elevate permissions
if [ $EUID != 0 ]; then
    sudo "$0" "$@"
    exit $?
fi

export DEBIAN_FRONTEND=noninteractive

apt-get --quiet --assume-yes update || exit $?

apt-get --quiet --assume-yes install \
    software-properties-common \
    curl ||
    exit $?

add-apt-repository --yes ppa:ubuntu-toolchain-r/test || exit $?
curl --silent --show-error \
    -L https://apt.llvm.org/llvm-snapshot.gpg.key |
    gpg --dearmor - | tee /etc/apt/trusted.gpg.d/llvm-snapshot.gpg >/dev/null || exit $?


# clang version should be compatible with libstdc++ version
CLANG_VERSION=11
LIBSTDCXX_VERSION=8

echo deb http://apt.llvm.org/$(lsb_release -sc)/ llvm-toolchain-$(lsb_release -sc)-$CLANG_VERSION main \
    >/etc/apt/sources.list.d/llvm.list || exit $?
apt-get --quiet --assume-yes update || exit $?

# Install common packages
apt-get --quiet --assume-yes install \
    clang-tidy-$CLANG_VERSION \
    || exit $?
