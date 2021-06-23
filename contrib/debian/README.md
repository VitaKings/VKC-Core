
Debian
====================
This directory contains files used to package vkccoind/vkcoin-qt
for Debian-based Linux systems. If you compile vkccoind/vkcoin-qt yourself, there are some useful files here.

## vkcoin: URI support ##


vkcoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install vkcoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your vkcoinqt binary to `/usr/bin`
and the `../../share/pixmaps/vkcoin128.png` to `/usr/share/pixmaps`

vkcoin-qt.protocol (KDE)
