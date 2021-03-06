/*
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


#include <iostream>

#include "storage/Devices/LvmVgImpl.h"
#include "storage/Devices/LvmPv.h"
#include "storage/Devices/LvmLv.h"
#include "storage/Holders/Subdevice.h"
#include "storage/Devicegraph.h"
#include "storage/Action.h"


namespace storage
{

    using namespace std;


    InvalidExtentSize::InvalidExtentSize(unsigned long long extent_size)
	: Exception(sformat("invalid extent size '%lld'", extent_size))
    {
    }


    LvmVg*
    LvmVg::create(Devicegraph* devicegraph, const string& vg_name)
    {
	LvmVg* ret = new LvmVg(new LvmVg::Impl(vg_name));
	ret->Device::create(devicegraph);
	return ret;
    }


    LvmVg*
    LvmVg::load(Devicegraph* devicegraph, const xmlNode* node)
    {
	LvmVg* ret = new LvmVg(new LvmVg::Impl(node));
	ret->Device::load(devicegraph);
	return ret;
    }


    LvmVg::LvmVg(Impl* impl)
	: Device(impl)
    {
    }


    LvmVg*
    LvmVg::clone() const
    {
	return new LvmVg(get_impl().clone());
    }


    LvmVg::Impl&
    LvmVg::get_impl()
    {
	return dynamic_cast<Impl&>(Device::get_impl());
    }


    const LvmVg::Impl&
    LvmVg::get_impl() const
    {
	return dynamic_cast<const Impl&>(Device::get_impl());
    }


    const Region&
    LvmVg::get_region() const
    {
	return get_impl().get_region();
    }


    unsigned long long
    LvmVg::get_size() const
    {
	return get_impl().get_size();
    }


    unsigned long long
    LvmVg::get_extent_size() const
    {
	return get_impl().get_extent_size();
    }


    void
    LvmVg::set_extent_size(unsigned long long extent_size)
    {
	get_impl().set_extent_size(extent_size);
    }


    const string&
    LvmVg::get_vg_name() const
    {
	return get_impl().get_vg_name();
    }


    void
    LvmVg::set_vg_name(const string& vg_name)
    {
	get_impl().set_vg_name(vg_name);
    }


    LvmPv*
    LvmVg::add_lvm_pv(BlkDevice* blk_device)
    {
	return get_impl().add_lvm_pv(blk_device);
    }


    void
    LvmVg::remove_lvm_pv(BlkDevice* blk_device)
    {
	get_impl().remove_lvm_pv(blk_device);
    }


    vector<LvmVg*>
    LvmVg::get_all(Devicegraph* devicegraph)
    {
	return devicegraph->get_impl().get_devices_of_type<LvmVg>(compare_by_vg_name);
    }


    vector<const LvmVg*>
    LvmVg::get_all(const Devicegraph* devicegraph)
    {
	return devicegraph->get_impl().get_devices_of_type<const LvmVg>(compare_by_vg_name);
    }


    vector<LvmPv*>
    LvmVg::get_lvm_pvs()
    {
	return get_impl().get_lvm_pvs();
    }


    vector<const LvmPv*>
    LvmVg::get_lvm_pvs() const
    {
	return get_impl().get_lvm_pvs();
    }


    vector<LvmLv*>
    LvmVg::get_lvm_lvs()
    {
	return get_impl().get_lvm_lvs();
    }


    vector<const LvmLv*>
    LvmVg::get_lvm_lvs() const
    {
	return get_impl().get_lvm_lvs();
    }


    void
    LvmVg::check() const
    {
	Device::check();

	if (get_vg_name().empty())
	    cerr << "volume group has no vg-name" << endl;
    }


    LvmLv*
    LvmVg::create_lvm_lv(const string& lv_name, unsigned long long size)
    {
	return get_impl().create_lvm_lv(lv_name, size);
    }


    void
    LvmVg::delete_lvm_lv(LvmLv* lvm_lv)
    {
	return get_impl().delete_lvm_lv(lvm_lv);
    }


    LvmLv*
    LvmVg::get_lvm_lv(const string& lv_name)
    {
	return get_impl().get_lvm_lv(lv_name);
    }


    bool
    is_lvm_vg(const Device* device)
    {
	return is_device_of_type<const LvmVg>(device);
    }


    LvmVg*
    to_lvm_vg(Device* device)
    {
	return to_device_of_type<LvmVg>(device);
    }


    const LvmVg*
    to_lvm_vg(const Device* device)
    {
	return to_device_of_type<const LvmVg>(device);
    }

}
