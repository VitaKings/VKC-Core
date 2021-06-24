
Debian
====================
This directory contains files used to package vkccoind/vkccoin-qt
for Debian-based Linux systems. If you compile vkccoind/vkccoin-qt yourself, there are some useful files here.

## vkccoin: URI support ##


vkccoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install vkccoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your vkccoinqt binary to `/usr/bin`
and the `../../share/pixmaps/vkccoin128.png` to `/usr/share/pixmaps`

vkccoin-qt.protocol (KDE)
