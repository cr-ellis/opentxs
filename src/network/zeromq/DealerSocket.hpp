/************************************************************
 *
 *                 OPEN TRANSACTIONS
 *
 *       Financial Cryptography and Digital Cash
 *       Library, Protocol, API, Server, CLI, GUI
 *
 *       -- Anonymous Numbered Accounts.
 *       -- Untraceable Digital Cash.
 *       -- Triple-Signed Receipts.
 *       -- Cheques, Vouchers, Transfers, Inboxes.
 *       -- Basket Currencies, Markets, Payment Plans.
 *       -- Signed, XML, Ricardian-style Contracts.
 *       -- Scripted smart contracts.
 *
 *  EMAIL:
 *  fellowtraveler@opentransactions.org
 *
 *  WEBSITE:
 *  http://www.opentransactions.org/
 *
 *  -----------------------------------------------------
 *
 *   LICENSE:
 *   This Source Code Form is subject to the terms of the
 *   Mozilla Public License, v. 2.0. If a copy of the MPL
 *   was not distributed with this file, You can obtain one
 *   at http://mozilla.org/MPL/2.0/.
 *
 *   DISCLAIMER:
 *   This program is distributed in the hope that it will
 *   be useful, but WITHOUT ANY WARRANTY; without even the
 *   implied warranty of MERCHANTABILITY or FITNESS FOR A
 *   PARTICULAR PURPOSE.  See the Mozilla Public License
 *   for more details.
 *
 ************************************************************/

#ifndef OPENTXS_NETWORK_ZEROMQ_IMPLEMENTATION_DEALERSOCKET_HPP
#define OPENTXS_NETWORK_ZEROMQ_IMPLEMENTATION_DEALERSOCKET_HPP

#include "opentxs/Forward.hpp"

#include "opentxs/network/zeromq/DealerSocket.hpp"

#include "CurveClient.hpp"
#include "Receiver.hpp"
#include "Socket.hpp"

namespace opentxs::network::zeromq::implementation
{
class DealerSocket : virtual public zeromq::DealerSocket,
                     public Socket,
                     CurveClient,
                     Receiver
{
public:
    bool Send(opentxs::Data& message) const override;
    bool Send(const std::string& message) const override;
    bool Send(zeromq::Message& message) const override;
    bool SetCurve(const ServerContract& contract) const override;
    bool SetSocksProxy(const std::string& proxy) const override;
    bool Start(const std::string& endpoint) const override;

    virtual ~DealerSocket();

protected:
    const ListenCallback& callback_;

    DealerSocket(
        const zeromq::Context& context,
        const bool client,
        const zeromq::ListenCallback& callback);

private:
    friend opentxs::network::zeromq::DealerSocket;
    typedef Socket ot_super;

    const bool client_{false};

    DealerSocket* clone() const override;
    bool have_callback() const override;

    void process_incoming(const Lock& lock, Message& message) override;

    DealerSocket() = delete;
    DealerSocket(const DealerSocket&) = delete;
    DealerSocket(DealerSocket&&) = delete;
    DealerSocket& operator=(const DealerSocket&) = delete;
    DealerSocket& operator=(DealerSocket&&) = delete;
};
}  // namespace opentxs::network::zeromq::implementation
#endif  // OPENTXS_NETWORK_ZEROMQ_IMPLEMENTATION_DEALERSOCKET_HPP
