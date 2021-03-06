// Copyright (c) 2018 The Open-Transactions developers
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#if OT_STORAGE_FS
namespace opentxs::storage::implementation
{
// Simple filesystem implementation of opentxs::storage
class StorageFSGC : public StorageFS,
                    public virtual opentxs::api::storage::Driver
{
private:
    typedef StorageFS ot_super;

public:
    bool EmptyBucket(const bool bucket) const override;

    void Cleanup() override;

    ~StorageFSGC();

private:
    friend Factory;

    std::string bucket_name(const bool bucket) const;
    std::string calculate_path(
        const std::string& key,
        const bool bucket,
        std::string& directory) const override;
    void purge(const std::string& path) const;
    std::string root_filename() const override;

    void Cleanup_StorageFSGC();
    void Init_StorageFSGC();

    StorageFSGC(
        const api::storage::Storage& storage,
        const StorageConfig& config,
        const Digest& hash,
        const Random& random,
        const Flag& bucket);
    StorageFSGC() = delete;
    StorageFSGC(const StorageFSGC&) = delete;
    StorageFSGC(StorageFSGC&&) = delete;
    StorageFSGC& operator=(const StorageFSGC&) = delete;
    StorageFSGC& operator=(StorageFSGC&&) = delete;
};
}  // namespace opentxs::storage::implementation
#endif  // OT_STORAGE_FS
