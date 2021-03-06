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

#pragma once

namespace opentxs::storage::implementation
{
// In-memory implementation of opentxs::storage
class StorageMemDB final : public Plugin,
                           virtual public opentxs::api::storage::Driver,
                           Lockable
{
public:
    bool EmptyBucket(const bool bucket) const override;
    bool LoadFromBucket(
        const std::string& key,
        std::string& value,
        const bool bucket) const override;
    std::string LoadRoot() const override;
    bool StoreRoot(const bool commit, const std::string& hash) const override;

    void Cleanup() override {}

    ~StorageMemDB() = default;

private:
    using ot_super = Plugin;

    friend opentxs::Factory;

    mutable std::string root_{""};
    mutable std::map<std::string, std::string> a_{};
    mutable std::map<std::string, std::string> b_{};

    void store(
        const bool isTransaction,
        const std::string& key,
        const std::string& value,
        const bool bucket,
        std::promise<bool>* promise) const override;

    StorageMemDB(
        const api::storage::Storage& storage,
        const StorageConfig& config,
        const Digest& hash,
        const Random& random,
        const Flag& bucket);
    StorageMemDB() = delete;
    StorageMemDB(const StorageMemDB&) = delete;
    StorageMemDB(StorageMemDB&&) = delete;
    StorageMemDB& operator=(const StorageMemDB&) = delete;
    StorageMemDB& operator=(StorageMemDB&&) = delete;
};
}  // namespace opentxs::storage::implementation
