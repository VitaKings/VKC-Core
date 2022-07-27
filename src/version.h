// Copyright (c) 2012-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2017-2018 The Bulwark developers
// Copyright (c) 2018-2021 The ESBC Core developers
// Copyright (c) 2021 The VKC Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_VERSION_H
#define BITCOIN_VERSION_H

/**
 * network protocol versioning
 */

static const int PROTOCOL_VERSION = 70228;

//! disconnect from peers older than this proto version
static const int MIN_PEER_PROTO_VERSION_BEFORE_ENFORCEMENT = 70225;
static const int MIN_PEER_PROTO_VERSION_AFTER_ENFORCEMENT = 70228;

//! Need to fork to remove AU Mattycoz AU  Discord ID: 360279208049508353 spork keys since he turned scam
static const int CONSENSUS_FORK_REWARD_UPDATE_PROTOCOL = 70225;
static const int CONSENSUS_FORK_REWARD_UPDATE_BLOCK = 260000;



static const int CONSENSUS_FORK_PROTO = 70223;           // On by default
static const int CONSENSUS_FORK_PROTO_TIME = 1554746400; // Monday, 08-Apr-19 18:00:00 UTC Not used in this chain

//! initial proto version, to be increased after version/verack negotiation
static const int INIT_PROTO_VERSION = 209;

//! nTime field added to CAddress, starting with this version;
//! if possible, avoid requesting addresses nodes older than this
static const int CADDR_TIME_VERSION = 31402;

//! BIP 0031, pong message, is enabled for all versions AFTER this one
static const int BIP0031_VERSION = 60000;

#endif // BITCOIN_VERSION_H
