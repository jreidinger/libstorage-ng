/*
 * Copyright (c) [2014-2015] Novell, Inc.
 * Copyright (c) 2016 SUSE LLC
 *
 * All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, contact Novell, Inc.
 *
 * To contact Novell about this file by physical or electronic mail, you may
 * find current contact information at www.novell.com.
 */


#ifndef STORAGE_PARTITION_TABLE_IMPL_H
#define STORAGE_PARTITION_TABLE_IMPL_H


#include "storage/Devices/PartitionTable.h"
#include "storage/Devices/DeviceImpl.h"
#include "storage/Utils/Enum.h"


namespace storage
{

    using namespace std;


    template <> struct EnumTraits<PtType> { static const vector<string> names; };

    std::ostream& operator<<(std::ostream& s, const PartitionSlot& partition_slot);


    template <> struct DeviceTraits<PartitionTable> { static const char* classname; };


    // abstract class

    class PartitionTable::Impl : public Device::Impl
    {
    public:

	virtual void probe_pass_1(Devicegraph* probed, SystemInfo& systeminfo) override;

	Partition* create_partition(const string& name, const Region& region, PartitionType type);

	void delete_partition(Partition* partition);

	void delete_partition(const string& name);

	virtual PtType get_type() const = 0;

	Partition* get_partition(const string& name);

	vector<Partition*> get_partitions();
	vector<const Partition*> get_partitions() const;

	Partitionable* get_partitionable();
	const Partitionable* get_partitionable() const;

	virtual bool equal(const Device::Impl& rhs) const override = 0;
	virtual void log_diff(std::ostream& log, const Device::Impl& rhs_base) const override = 0;

	virtual void print(std::ostream& out) const override = 0;

	virtual unsigned int max_primary() const = 0;
	virtual bool extended_possible() const { return false; }
	virtual unsigned int max_logical() const { return 0; }

	virtual unsigned int num_primary() const;
	virtual bool has_extended() const { return false; }
	virtual unsigned int num_logical() const { return 0; }

	const Partition* get_extended() const;

	virtual Region get_usable_region() const = 0;

	std::vector<PartitionSlot> get_unused_partition_slots(AlignPolicy align_policy = AlignPolicy::KEEP_END) const;

	Region align(const Region& region, AlignPolicy align_policy = AlignPolicy::ALIGN_END) const;

    protected:

	Impl()
	    : Device::Impl(), read_only(false) {}

	Impl(const xmlNode* node);

	virtual void save(xmlNode* node) const override;

    private:

	bool read_only;

    };

}

#endif
