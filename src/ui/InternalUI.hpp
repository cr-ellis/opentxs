// Copyright (c) 2018 The Open-Transactions developers
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "Internal.hpp"

#include "opentxs/ui/ActivitySummaryItem.hpp"
#include "opentxs/ui/AccountSummaryItem.hpp"
#include "opentxs/ui/ActivityThreadItem.hpp"
#include "opentxs/ui/BalanceItem.hpp"
#include "opentxs/ui/ContactItem.hpp"
#include "opentxs/ui/ContactListItem.hpp"
#include "opentxs/ui/ContactSection.hpp"
#include "opentxs/ui/ContactSubsection.hpp"
#include "opentxs/ui/IssuerItem.hpp"
#include "opentxs/ui/PayableListItem.hpp"
#include "opentxs/ui/Profile.hpp"
#include "opentxs/ui/ProfileItem.hpp"
#include "opentxs/ui/ProfileSection.hpp"
#include "opentxs/ui/ProfileSubsection.hpp"

namespace opentxs::ui::internal
{
struct AccountActivity {
    virtual bool last(const implementation::AccountActivityRowID& id) const = 0;
    virtual OTIdentifier WidgetID() const = 0;
};
struct AccountSummary {
    virtual bool last(const implementation::AccountSummaryRowID& id) const = 0;
    virtual OTIdentifier WidgetID() const = 0;
    // custom
    virtual proto::ContactItemType Currency() const = 0;
    virtual const Identifier& NymID() const = 0;
};
struct AccountSummaryItem : virtual public ui::AccountSummaryItem {
    virtual void reindex(
        const implementation::IssuerItemSortKey& key,
        const implementation::CustomData& custom) = 0;
};
struct ActivitySummary {
    virtual bool last(const implementation::ActivitySummaryRowID& id) const = 0;
    virtual OTIdentifier WidgetID() const = 0;
};
struct ActivitySummaryItem : virtual public ui::ActivitySummaryItem {
    virtual void reindex(
        const implementation::ActivitySummarySortKey& key,
        const implementation::CustomData& custom) = 0;
};
struct ActivityThread {
    virtual bool last(const implementation::ActivityThreadRowID& id) const = 0;
    virtual OTIdentifier WidgetID() const = 0;
    // custom
    virtual std::string ThreadID() const = 0;
};
struct ActivityThreadItem : virtual public ui::ActivityThreadItem {
    virtual void reindex(
        const implementation::ActivityThreadSortKey& key,
        const implementation::CustomData& custom) = 0;
};
struct BalanceItem : virtual public ui::BalanceItem {
    virtual void reindex(
        const implementation::AccountActivitySortKey& key,
        const implementation::CustomData& custom) = 0;
};
struct Contact {
    virtual bool last(const implementation::ContactRowID& id) const = 0;
    virtual OTIdentifier WidgetID() const = 0;
    // custom
    virtual std::string ContactID() const = 0;
};
struct ContactItem : virtual public ui::ContactItem {
    virtual void reindex(
        const implementation::ContactSubsectionSortKey& key,
        const implementation::CustomData& custom) = 0;
};
struct ContactList {
    virtual bool last(const implementation::ContactListRowID& id) const = 0;
    virtual OTIdentifier WidgetID() const = 0;
    // custom
    virtual const Identifier& ID() const = 0;
};
struct ContactListItem : virtual public ui::ContactListItem {
    virtual void reindex(
        const implementation::ContactListSortKey& key,
        const implementation::CustomData& custom) = 0;
};
struct ContactSection : virtual public ui::ContactSection {
    // Row
    virtual void reindex(
        const implementation::ContactSortKey& key,
        const implementation::CustomData& custom) = 0;
    // List
    virtual bool last(const implementation::ContactSectionRowID& id) const = 0;
    virtual OTIdentifier WidgetID() const = 0;
    // custom
    virtual std::string ContactID() const = 0;
};
struct ContactSubsection : virtual public ui::ContactSubsection {
    virtual void reindex(
        const implementation::ContactSectionSortKey& key,
        const implementation::CustomData& custom) = 0;
    // List
    virtual bool last(
        const implementation::ContactSubsectionRowID& id) const = 0;
    virtual OTIdentifier WidgetID() const = 0;
};
struct IssuerItem : virtual public ui::IssuerItem {
    // Row
    virtual void reindex(
        const implementation::AccountSummarySortKey& key,
        const implementation::CustomData& custom) = 0;
    // List
    virtual bool last(const implementation::IssuerItemRowID& id) const = 0;
    virtual OTIdentifier WidgetID() const = 0;
};
struct PayableListItem : virtual public ui::PayableListItem {
    virtual void reindex(
        const implementation::PayableListSortKey& key,
        const implementation::CustomData& custom) = 0;
};
struct Profile : virtual public ui::Profile {
    virtual bool last(const implementation::ProfileRowID& id) const = 0;
    virtual OTIdentifier WidgetID() const = 0;
    // custom
    virtual const Identifier& NymID() const = 0;
};
struct ProfileSection : virtual public ui::ProfileSection {
    // Row
    virtual void reindex(
        const implementation::ProfileSortKey& key,
        const implementation::CustomData& custom) = 0;
    // List
    virtual bool last(const implementation::ProfileSectionRowID& id) const = 0;
    virtual OTIdentifier WidgetID() const = 0;
    // custom
    virtual const Identifier& NymID() const = 0;
};
struct ProfileSubsection : virtual public ui::ProfileSubsection {
    // Row
    virtual void reindex(
        const implementation::ProfileSectionSortKey& key,
        const implementation::CustomData& custom) = 0;
    // List
    virtual bool last(
        const implementation::ProfileSubsectionRowID& id) const = 0;
    virtual OTIdentifier WidgetID() const = 0;
    // custom
    virtual const Identifier& NymID() const = 0;
    virtual proto::ContactSectionName Section() const = 0;
};
struct ProfileItem : virtual public ui::ProfileItem {
    virtual void reindex(
        const implementation::ProfileSubsectionSortKey& key,
        const implementation::CustomData& custom) = 0;
};
}  // namespace opentxs::ui::internal
