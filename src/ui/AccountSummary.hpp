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

#ifndef OPENTXS_UI_ACCOUNTSUMMARY_IMPLEMENTATION_HPP
#define OPENTXS_UI_ACCOUNTSUMMARY_IMPLEMENTATION_HPP

#include "Internal.hpp"

namespace opentxs::ui::implementation
{
using AccountSummaryList = List<
    AccountSummaryExternalInterface,
    AccountSummaryInternalInterface,
    AccountSummaryRowID,
    AccountSummaryRowInterface,
    AccountSummaryRowBlank,
    AccountSummarySortKey>;

class AccountSummary : virtual public AccountSummaryList
{
public:
    proto::ContactItemType Currency() const override { return currency_; }
    const Identifier& NymID() const override { return nym_id_.get(); }

    ~AccountSummary() = default;

private:
    friend Factory;

    static const ListenerDefinitions listeners_;

    const api::client::Wallet& wallet_;
    const api::network::ZMQ& connection_;
    const api::storage::Storage& storage_;
    const proto::ContactItemType currency_;
    std::set<OTIdentifier> threads_;
    std::map<OTIdentifier, OTIdentifier> server_thread_map_;

    void construct_row(
        const AccountSummaryRowID& id,
        const AccountSummarySortKey& index,
        const CustomData& custom) const override;

    AccountSummarySortKey extract_key(
        const Identifier& nymID,
        const Identifier& issuerID);
    void process_issuer(const Identifier& issuerID);
    void process_issuer(const network::zeromq::Message& message);
    void process_server(const network::zeromq::Message& message);
    void startup();

    AccountSummary(
        const network::zeromq::Context& zmq,
        const network::zeromq::PublishSocket& publisher,
        const api::client::Wallet& wallet,
        const api::network::ZMQ& connection,
        const api::storage::Storage& storage,
        const api::ContactManager& contact,
        const Identifier& nymID,
        const proto::ContactItemType currency);
    AccountSummary() = delete;
    AccountSummary(const AccountSummary&) = delete;
    AccountSummary(AccountSummary&&) = delete;
    AccountSummary& operator=(const AccountSummary&) = delete;
    AccountSummary& operator=(AccountSummary&&) = delete;
};
}  // namespace opentxs::ui::implementation
#endif  // OPENTXS_UI_ACCOUNTSUMMARY_IMPLEMENTATION_HPP