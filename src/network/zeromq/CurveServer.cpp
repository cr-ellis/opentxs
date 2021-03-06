// Copyright (c) 2018 The Open-Transactions developers
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "stdafx.hpp"

#include "CurveServer.hpp"

#include "opentxs/core/crypto/OTPassword.hpp"
#include "opentxs/core/Log.hpp"

#include "Socket.hpp"

#include <zmq.h>

#define OT_METHOD "opentxs::network::zeromq::implementation::CurveServer::"

namespace opentxs::network::zeromq::implementation
{
CurveServer::CurveServer(std::mutex& lock, void* socket)
    : server_curve_lock_(lock)
    , server_curve_socket_(socket)
{
}

bool CurveServer::SetPrivateKey(const OTPassword& key) const
{
    return set_private_key(key);
}

bool CurveServer::set_private_key(const OTPassword& key) const
{
    OT_ASSERT(nullptr != server_curve_socket_);

    Lock lock(server_curve_lock_);

    if (CURVE_KEY_BYTES != key.getMemorySize()) {
        otErr << OT_METHOD << __FUNCTION__ << ": Invalid private key."
              << std::endl;

        return false;
    }

    const int server{1};
    auto set = zmq_setsockopt(
        server_curve_socket_, ZMQ_CURVE_SERVER, &server, sizeof(server));

    if (0 != set) {
        otErr << OT_METHOD << __FUNCTION__ << ": Failed to set ZMQ_CURVE_SERVER"
              << std::endl;

        return false;
    }

    set = zmq_setsockopt(
        server_curve_socket_,
        ZMQ_CURVE_SECRETKEY,
        key.getMemory(),
        key.getMemorySize());

    if (0 != set) {
        otErr << OT_METHOD << __FUNCTION__ << ": Failed to set private key."
              << std::endl;

        return false;
    }

    return true;
}

CurveServer::~CurveServer() { server_curve_socket_ = nullptr; }
}  // namespace opentxs::network::zeromq::implementation
