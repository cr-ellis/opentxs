// Copyright (c) 2018 The Open-Transactions developers
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "stdafx.hpp"

#include "opentxs/api/Activity.hpp"
#include "opentxs/core/Flag.hpp"
#include "opentxs/core/Identifier.hpp"
#include "opentxs/core/Lockable.hpp"
#include "opentxs/core/Log.hpp"
#include "opentxs/core/Message.hpp"
#include "opentxs/ui/ActivityThreadItem.hpp"

#include "ActivityThreadParent.hpp"
#include "Row.hpp"

#include <memory>
#include <thread>

#include "MailItem.hpp"

namespace opentxs
{
ui::ActivityThreadItem* Factory::MailItem(
    const ui::implementation::ActivityThreadParent& parent,
    const network::zeromq::Context& zmq,
    const network::zeromq::PublishSocket& publisher,
    const api::ContactManager& contact,
    const ui::implementation::ActivityThreadRowID& id,
    const Identifier& nymID,
    const api::Activity& activity,
    const std::chrono::system_clock::time_point& time,
    const std::string& text,
    const bool loading,
    const bool pending)
{
    return new ui::implementation::MailItem(
        parent,
        zmq,
        publisher,
        contact,
        id,
        nymID,
        activity,
        time,
        text,
        loading,
        pending);
}

ui::ActivityThreadItem* Factory::MailItem(
    const ui::implementation::ActivityThreadParent& parent,
    const network::zeromq::Context& zmq,
    const network::zeromq::PublishSocket& publisher,
    const api::ContactManager& contact,
    const ui::implementation::ActivityThreadRowID& id,
    const Identifier& nymID,
    const api::Activity& activity,
    const std::chrono::system_clock::time_point& time)
{
    return new ui::implementation::MailItem(
        parent, zmq, publisher, contact, id, nymID, activity, time);
}
}  // namespace opentxs

namespace opentxs::ui::implementation
{
MailItem::MailItem(
    const ActivityThreadParent& parent,
    const network::zeromq::Context& zmq,
    const network::zeromq::PublishSocket& publisher,
    const api::ContactManager& contact,
    const ActivityThreadRowID& id,
    const Identifier& nymID,
    const api::Activity& activity,
    const std::chrono::system_clock::time_point& time,
    const std::string& text,
    const bool loading,
    const bool pending)
    : ActivityThreadItem(
          parent,
          zmq,
          publisher,
          contact,
          id,
          nymID,
          activity,
          time,
          text,
          loading,
          pending)
    , load_(nullptr)
{
    OT_ASSERT(false == nym_id_.empty());
    OT_ASSERT(false == item_id_.empty())
}

MailItem::MailItem(
    const ActivityThreadParent& parent,
    const network::zeromq::Context& zmq,
    const network::zeromq::PublishSocket& publisher,
    const api::ContactManager& contact,
    const ActivityThreadRowID& id,
    const Identifier& nymID,
    const api::Activity& activity,
    const std::chrono::system_clock::time_point& time)
    : MailItem(
          parent,
          zmq,
          publisher,
          contact,
          id,
          nymID,
          activity,
          time,
          "",
          true,
          false)
{
    switch (box_) {
        case StorageBox::MAILINBOX:
        case StorageBox::MAILOUTBOX: {
            load_.reset(new std::thread(&MailItem::load, this));
        } break;
        case StorageBox::SENTPEERREQUEST:
        case StorageBox::INCOMINGPEERREQUEST:
        case StorageBox::SENTPEERREPLY:
        case StorageBox::INCOMINGPEERREPLY:
        case StorageBox::FINISHEDPEERREQUEST:
        case StorageBox::FINISHEDPEERREPLY:
        case StorageBox::PROCESSEDPEERREQUEST:
        case StorageBox::PROCESSEDPEERREPLY:
        case StorageBox::INCOMINGBLOCKCHAIN:
        case StorageBox::OUTGOINGBLOCKCHAIN:
        case StorageBox::INCOMINGCHEQUE:
        case StorageBox::OUTGOINGCHEQUE:
        case StorageBox::DRAFT:
        case StorageBox::UNKNOWN:
        default: {
        }
    }

    OT_ASSERT(load_)
}

void MailItem::load()
{
    std::shared_ptr<const std::string> text{nullptr};

    switch (box_) {
        case StorageBox::MAILINBOX:
        case StorageBox::MAILOUTBOX: {
            text = activity_.MailText(nym_id_, item_id_, box_);
        } break;
        case StorageBox::SENTPEERREQUEST:
        case StorageBox::INCOMINGPEERREQUEST:
        case StorageBox::SENTPEERREPLY:
        case StorageBox::INCOMINGPEERREPLY:
        case StorageBox::FINISHEDPEERREQUEST:
        case StorageBox::FINISHEDPEERREPLY:
        case StorageBox::PROCESSEDPEERREQUEST:
        case StorageBox::PROCESSEDPEERREPLY:
        case StorageBox::INCOMINGBLOCKCHAIN:
        case StorageBox::OUTGOINGBLOCKCHAIN:
        case StorageBox::INCOMINGCHEQUE:
        case StorageBox::OUTGOINGCHEQUE:
        case StorageBox::DRAFT:
        case StorageBox::UNKNOWN:
        default: {
            OT_FAIL
        }
    }

    OT_ASSERT(text)

    eLock lock(shared_lock_);
    text_ = *text;
    loading_->Off();
    pending_->Off();
    UpdateNotify();
}

MailItem::~MailItem()
{
    if (load_ && load_->joinable()) { load_->join(); }
}
}  // namespace opentxs::ui::implementation
