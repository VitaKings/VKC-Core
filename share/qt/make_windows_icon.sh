#!/bin/bash
# create multiresolution windows icon
#mainnet
ICON_SRC=../../src/qt/res/icons/vkcoin.png
ICON_DST=../../src/qt/res/icons/vkcoin.ico
convert ${ICON_SRC} -resize 16x16 vkcoin-16.png
convert ${ICON_SRC} -resize 32x32 vkcoin-32.png
convert ${ICON_SRC} -resize 48x48 vkcoin-48.png
convert vkcoin-16.png vkcoin-32.png vkcoin-48.png ${ICON_DST}
#testnet
ICON_SRC=../../src/qt/res/icons/vkcoin_testnet.png
ICON_DST=../../src/qt/res/icons/vkcoin_testnet.ico
convert ${ICON_SRC} -resize 16x16 vkcoin-16.png
convert ${ICON_SRC} -resize 32x32 vkcoin-32.png
convert ${ICON_SRC} -resize 48x48 vkcoin-48.png
convert vkcoin-16.png vkcoin-32.png vkcoin-48.png ${ICON_DST}
rm vkcoin-16.png vkcoin-32.png vkcoin-48.png
