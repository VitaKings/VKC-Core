#!/bin/bash
# create multiresolution windows icon
#mainnet
ICON_SRC=../../src/qt/res/icons/vkccoin.png
ICON_DST=../../src/qt/res/icons/vkccoin.ico
convert ${ICON_SRC} -resize 16x16 vkccoin-16.png
convert ${ICON_SRC} -resize 32x32 vkccoin-32.png
convert ${ICON_SRC} -resize 48x48 vkccoin-48.png
convert vkccoin-16.png vkccoin-32.png vkccoin-48.png ${ICON_DST}
#testnet
ICON_SRC=../../src/qt/res/icons/vkccoin_testnet.png
ICON_DST=../../src/qt/res/icons/vkccoin_testnet.ico
convert ${ICON_SRC} -resize 16x16 vkccoin-16.png
convert ${ICON_SRC} -resize 32x32 vkccoin-32.png
convert ${ICON_SRC} -resize 48x48 vkccoin-48.png
convert vkccoin-16.png vkccoin-32.png vkccoin-48.png ${ICON_DST}
rm vkccoin-16.png vkccoin-32.png vkccoin-48.png
