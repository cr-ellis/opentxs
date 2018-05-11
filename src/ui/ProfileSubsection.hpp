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

#ifndef OPENTXS_UI_PROFILE_SUBSECTION_IMPLEMENTATION_HPP
#define OPENTXS_UI_PROFILE_SUBSECTION_IMPLEMENTATION_HPP

#include "opentxs/Internal.hpp"

namespace opentxs::ui::implementation
{
using ProfileSubsectionPimpl = std::unique_ptr<opentxs::ui::ProfileItem>;
using ProfileSubsectionIDType = OTIdentifier;
using ProfileSubsectionSortKey = int;
using ProfileSubsectionInner =
    std::map<ProfileSubsectionIDType, ProfileSubsectionPimpl>;
using ProfileSubsectionOuter =
    std::map<ProfileSubsectionSortKey, ProfileSubsectionInner>;
using ProfileSubsectionReverse =
    std::map<ProfileSubsectionIDType, ProfileSubsectionSortKey>;
using ProfileSubsectionType = List<
    opentxs::ui::ProfileSubsection,
    ProfileSubsectionParent,
    opentxs::ui::ProfileItem,
    ProfileSubsectionIDType,
    ProfileSubsectionPimpl,
    ProfileSubsectionInner,
    ProfileSubsectionSortKey,
    ProfileSubsectionOuter,
    ProfileSubsectionOuter::const_iterator,
    ProfileSubsectionReverse>;
using ProfileSubsectionRowType = RowType<
    opentxs::ui::ProfileSubsection,
    ProfileSectionParent,
    std::pair<proto::ContactSectionName, proto::ContactItemType>>;

class ProfileSubsection : public ProfileSubsectionType,
                          public ProfileSubsectionRowType
{
public:
    bool AddItem(
        const std::string& value,
        const bool primary,
        const bool active) const override;
    bool Delete(const std::string& claimID) const override;
    std::string Name(const std::string& lang) const override;
    const Identifier& NymID() const override { return nym_id_; }
    proto::ContactSectionName Section() const override { return id_.first; }
    bool SetActive(const std::string& claimID, const bool active)
        const override;
    bool SetPrimary(const std::string& claimID, const bool primary)
        const override;
    bool SetValue(const std::string& claimID, const std::string& value)
        const override;
    int SubsectionType() const override { return static_cast<int>(Type()); }
    proto::ContactItemType Type() const override { return id_.second; }

    void Update(const opentxs::ContactGroup& group) override;

    ~ProfileSubsection() = default;

private:
    friend Factory;

    static bool check_type(const ProfileSubsectionIDType type);
    static const opentxs::ContactItem& recover(const void* input);

    const api::client::Wallet& wallet_;

    ProfileSubsectionIDType blank_id() const override
    {
        return Identifier::Factory();
    }
    void construct_item(
        const ProfileSubsectionIDType& id,
        const ProfileSubsectionSortKey& index,
        void* custom = nullptr) const override;

    bool last(const ProfileSubsectionIDType& id) const override
    {
        return ProfileSubsectionType::last(id);
    }
    ProfileSubsectionOuter::const_iterator outer_first() const override
    {
        return items_.begin();
    }
    ProfileSubsectionOuter::const_iterator outer_end() const override
    {
        return items_.end();
    }
    void process_group(const opentxs::ContactGroup& group);
    int sort_key(const ProfileSubsectionIDType type) const;
    void startup(const opentxs::ContactGroup group);

    ProfileSubsection(
        const network::zeromq::Context& zmq,
        const api::ContactManager& contact,
        const api::client::Wallet& wallet,
        const ProfileSectionParent& parent,
        const opentxs::ContactGroup& group);
    ProfileSubsection() = delete;
    ProfileSubsection(const ProfileSubsection&) = delete;
    ProfileSubsection(ProfileSubsection&&) = delete;
    ProfileSubsection& operator=(const ProfileSubsection&) = delete;
    ProfileSubsection& operator=(ProfileSubsection&&) = delete;
};
}  // opentxs::ui::implementation
#endif  // OPENTXS_UI_PROFILE_SUBSECTION_IMPLEMENTATION_HPP